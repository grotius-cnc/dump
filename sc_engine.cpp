#include "sc_engine.h"

inline int sc_engine::t1_v(T vo, T acs, T ace, T&ve){

    T ts=acs/jm;
    T vf=vo-(jm*(ts*ts)/2);

    T te=ace/jm;
    ve=vf+jm*(te*te)/2;

    return 1;
}

inline int sc_engine::t1_s(T vo, T acs, T ace, T &ncs, T &nct){

    T ts=acs/jm;
    T vf=vo-(jm*(ts*ts)/2);
    T so=vf*ts+jm*(ts*ts*ts)/6;

    T te=ace/jm;
    T se=vf*te+jm*(te*te*te)/6;

    ncs=se-so;
    nct=te-ts;
    return 1;
}

inline int sc_engine::t1_v_s(T vo, T acs, T ace, bool pb, T &ve, T &ncs, T &nct){

    T ts=acs/jm;
    T vf=vo-(jm*(ts*ts)/2);
    T so=vf*ts+jm*(ts*ts*ts)/6;

    T te=ace/jm;
    ve=vf+jm*(te*te)/2;
    T se=vf*te+jm*(te*te*te)/6;

    ncs=se-so;
    nct=te-ts;

    if(pb){
        pvec.push_back({sc_period_id::id_t1,vo,ve,acs,ace,ncs,nct});
    }

    return 1;
}

inline int sc_engine::t1_v_ve(T vo, T ve, T acs, T &ace, T &ve_){

    T ts=acs/jm;
    T vf=vo-(jm*(ts*ts)/2);

    T te=sqrt(-2*vf+2*ve)/sqrt(jm);
    te=std::min(0.5*ct,te);

    ve_=vf+jm*(te*te)/2;
    ace=jm*te;

    return 1;
}

inline int sc_engine::t1_s_ve(T vo, T ve, T acs, T &ncs, T &nct){

    T ts=acs/jm;
    T vf=vo-(jm*(ts*ts)/2);

    T so=vf*ts+jm*(ts*ts*ts)/6;

    T te=sqrt(-2*vf+2*ve)/sqrt(jm);
    te=std::min(0.5*ct,te);

    T se=vf*te+jm*(te*te*te)/6;

    ncs=se-so;
    nct=te-ts;

    return 1;
}

inline int sc_engine::t1_v_s_ve(T vo, T ve, T acs, bool pb, T &ace, T &ve_, T &ncs, T &nct){

    T ts=acs/jm;
    T vf=vo-(jm*(ts*ts)/2);

    T so=vf*ts+jm*(ts*ts*ts)/6;

    T te=sqrt(-2*vf+2*ve)/sqrt(jm);
    te=std::min(0.5*ct,te);
    ve_=vf+jm*(te*te)/2;
    ace=jm*te;

    T se=vf*te+jm*(te*te*te)/6;

    ncs=se-so;
    nct=te-ts;

    if(pb){
        pvec.push_back({sc_period_id::id_t1,vo,ve,acs,ace,ncs,nct});
    }

    return 1;
}

inline int sc_engine::t1_v_s_a_i(T vo, T acs, T ti, T &vi, T &si, T &ai){

    T ts=acs/jm;
    T vf=vo-(jm*(ts*ts)/2);

    ti+=ts;
    vi=vf+jm*(ti*ti)/2;

    T so=vf*ts+jm*(ts*ts*ts)/6;
    T se=vf*ti+jm*(ti*ti*ti)/6;
    si=se-so;

    ai=jm*ti;
    return 1;
}

inline int sc_engine::t2_s(T vo, T ve, T a, bool pb, T &ncs, T &nct){

    ncs=((ve*ve) - (vo*vo))/(2*a) ;
    nct=(ve-vo)/a;

    if(pb){
        pvec.push_back({sc_period_id::id_t2,vo,ve,a,a,ncs,nct});
    }
    return 1;
}

inline int sc_engine::t2_v_s_a_i(T vo, T a, T ti, T &vi, T &si, T &ai){

    vi=vo + a*ti;
    si=vo*ti + 0.5*a*(ti*ti);
    ai=a;

    return 1;
}

inline int sc_engine::t3_v(T vo, T acs, T ace, T &ve){

    ace=std::min(std::abs(ace),std::abs(acs));

    T ts=(as-acs)/jm;
    T vf = -as*ts+((jm*(ts*ts))/2)+vo;

    T te=(as-ace)/jm;
    ve=vf + as*te - jm*(te*te)/2;

    return 1;
}

inline int sc_engine::t3_s(T vo, T acs, T ace, T &ncs, T &nct){

    ace=std::min(std::abs(ace),std::abs(acs));

    T ts=(as-acs)/jm;
    T vf = -as*ts+((jm*(ts*ts))/2)+vo;
    T so=vf*ts + as*(ts*ts)/2 - jm*(ts*ts*ts)/6;

    T te=(as-ace)/jm;
    T se=vf*te + as*(te*te)/2 - jm*(te*te*te)/6;

    ncs=se-so;
    nct=te-ts;

    return 2;
}

inline int sc_engine::t3_v_s(T vo, T acs, T ace, bool pb, T &ve,T &ncs, T &nct){

    ace=std::min(std::abs(ace),std::abs(acs));

    T ts=(as-acs)/jm;
    T vf = -as*ts+((jm*(ts*ts))/2)+vo;
    T so=vf*ts + as*(ts*ts)/2 - jm*(ts*ts*ts)/6;

    T te=(as-ace)/jm;
    ve=vf + as*te - jm*(te*te)/2;
    T se=vf*te + as*(te*te)/2 - jm*(te*te*te)/6;

    ncs=se-so;
    nct=te-ts;

    if(pb){
        pvec.push_back({sc_period_id::id_t3,vo,ve,acs,ace,ncs,nct});
    }

    return 2;
}

inline int sc_engine::t3_v_s_a_i(T vo, T acs, T ti, T &vi, T &si, T &ai){

    T ts=(as-acs)/jm;
    T t=ts;
    T vf = -as*t+((jm*(t*t))/2)+vo;
    T so=vf*t + as*(t*t)/2 - jm*(t*t*t)/6;

    t=0;
    T sf=vf*t + as*(t*t)/2 - jm*(t*t*t)/6;

    t=ti+ts;
    vi=vf + as*t - jm*(t*t)/2;
    si=vf*t + as*(t*t)/2 - jm*(t*t*t)/6;
    si-=so-sf;
    ai=as-(jm*t);

    return 1;
}

inline int sc_engine::t4_s(T vo, T s, bool pb, T &ncs, T &nct){
    nct=s/vo;
    ncs=s;

    if(pb){
        pvec.push_back({sc_period_id::id_t4,vo,vo,0,0,ncs,nct});
    }
    return 1;
}

inline int sc_engine::t4_v_s_a_i(T vo, T ti, T &vi, T &si, T &ai){

    vi=vo;
    si=vo*ti;
    ai=0;

    return 1;
}

inline int sc_engine::t5_v(T vo, T acs, T ace, T &ve){

    acs=std::abs(acs);
    ace=std::abs(ace);

    if(acs==ace){
        return vo;
    }

    T ts=acs/jm;
    T vf=((jm*(ts*ts))/2)+vo;

    T te=ace/jm;
    ve=vf-jm*(te*te)/2;

    return 1;
}

inline int sc_engine::t5_s(T vo, T acs, T ace, T &ncs, T &nct){

    acs=std::abs(acs);
    ace=std::abs(ace);

    if(acs==ace){
        return vo;
    }

    T ts=acs/jm;
    T vf=((jm*(ts*ts))/2)+vo;
    T so=vf*ts-jm*(ts*ts*ts)/6;

    T te=ace/jm;
    T se=vf*te-jm*(te*te*te)/6;

    ncs=se-so;
    nct=te-ts;

    return 1;
}

inline int sc_engine::t5_v_s(T vo, T acs, T ace, bool pb, T &ve_, T &ncs, T &nct){

    acs=std::abs(acs);
    ace=std::abs(ace);

    if(acs==ace){
        return vo;
    }

    T ts=acs/jm;
    T vf=((jm*(ts*ts))/2)+vo;
    T so=vf*ts-jm*(ts*ts*ts)/6;

    T te=ace/jm;
    ve_=vf-jm*(te*te)/2;
    T se=vf*te-jm*(te*te*te)/6;

    ncs=se-so;
    nct=te-ts;

    if(pb){
        pvec.push_back({sc_period_id::id_t5,vo,ve_,acs,ace,ncs,nct});
    }

    return 1;
}

inline int sc_engine::t5_v_ve(T vo, T ve, T acs, T &ace, T &ve_){

    acs=std::abs(acs);

    T ts=acs/jm;
    T vf=((jm*(ts*ts))/2)+vo;

    T te=(sqrt(2)*sqrt(vf-ve))/sqrt(jm);
    te=std::min(0.5*ct,te);

    ve_=vf-jm*(te*te)/2;
    ace=-std::abs(jm*te);

    return 1;
}

inline int sc_engine::t5_s_ve(T vo, T ve, T acs, T &ncs, T &nct){

    acs=std::abs(acs);

    T ts=acs/jm;
    T vf=((jm*(ts*ts))/2)+vo;
    T so=vf*ts-jm*(ts*ts*ts)/6;

    T te=(sqrt(2)*sqrt(vf-ve))/sqrt(jm);
    te=std::min(0.5*ct,te);

    T se=vf*te-jm*(te*te*te)/6;

    ncs=se-so;
    nct=te-ts;

    return 1;
}

inline int sc_engine::t5_v_s_ve(T vo, T ve, T acs, bool pb, T &ace_, T &ve_, T &ncs, T &nct){

    acs=std::abs(acs);

    T ts=acs/jm;
    T vf=((jm*(ts*ts))/2)+vo;
    T so=vf*ts-jm*(ts*ts*ts)/6;

    T te=(sqrt(2)*sqrt(vf-ve))/sqrt(jm);
    te=std::min(0.5*ct,te);
    ace_=-std::abs(jm*te);
    ve_=vf-jm*(te*te)/2;
    T se=vf*te-jm*(te*te*te)/6;

    ncs=se-so;
    nct=te-ts;

    if(pb){
        pvec.push_back({sc_period_id::id_t5,vo,ve,acs,ace_,ncs,nct});
    }

    return 1;
}

inline int sc_engine::t5_v_s_a_i(T vo, T acs, T ti, T &vi, T &si, T &ai){

    acs=std::abs(acs);

    T ts=acs/jm;
    T t=ts;
    T vf=((jm*(t*t))/2)+vo;
    T so=vf*t-jm*(t*t*t)/6;

    t=0;
    T sf=vf*t-jm*(t*t*t)/6;

    t=ti+ts;
    vi=vf-jm*(t*t)/2;
    ai=-std::abs(jm*t);
    si=vf*t-jm*(t*t*t)/6;
    si-=so-sf;

    return 1;
}

inline int sc_engine::t6_s(T vo, T ve, T a, bool pb, T &ncs, T &nct){

    a=std::abs(a);
    ncs=((vo*vo) - (ve*ve))/(2*a);
    nct=(vo-ve)/a;

    if(pb){
        pvec.push_back({sc_period_id::id_t6,vo,ve,a,a,ncs,nct});
    }

    return 1;
}

inline int sc_engine::t6_v_s_a_i(T vo, T a, T ti, T &vi, T &si, T &ai){

    T t=0;
    a=std::abs(a);

    t=ti;
    vi=vo - a*t;
    si=vo*t - 0.5*a*(t*t);
    ai=-std::abs(a);

    return 1;
}

inline int sc_engine::t7_v(T vo, T acs, T ace, T &ve){

    acs=std::abs(acs);
    ace=std::abs(ace);
    ace=std::min(std::abs(ace),std::abs(acs));

    T ts=(as-acs)/jm;
    T vf=as*ts - ((jm*(ts*ts))/2) + vo;

    T te=(as-ace)/jm;
    ve=vf - as*te + jm*(te*te)/2;

    return 1;
}

inline int sc_engine::t7_s(T vo, T acs, T ace, T &ncs, T &nct){

    acs=std::abs(acs);
    ace=std::abs(ace);
    ace=std::min(std::abs(ace),std::abs(acs));

    T ts=(as-acs)/jm;
    T vf=as*ts - ((jm*(ts*ts))/2) + vo;
    T so=vf*ts - as*(ts*ts)/2 + jm*(ts*ts*ts)/6;

    T te=(as-ace)/jm;
    T se=vf*te - as*(te*te)/2 + jm*(te*te*te)/6;

    ncs=se-so;
    nct=te-ts;

    return 1;
}

inline int sc_engine::t7_v_s(T vo, T acs, T ace, bool pb, T &ve, T &ncs, T &nct){

    acs=std::abs(acs);
    ace=std::abs(ace);
    ace=std::min(std::abs(ace),std::abs(acs));

    T ts=(as-acs)/jm;
    T vf=as*ts - ((jm*(ts*ts))/2) + vo;
    T so=vf*ts - as*(ts*ts)/2 + jm*(ts*ts*ts)/6;

    T te=(as-ace)/jm;
    T se=vf*te - as*(te*te)/2 + jm*(te*te*te)/6;
    ve=vf - as*te + jm*(te*te)/2;

    ncs=se-so;
    nct=te-ts;

    if(pb){
        pvec.push_back({sc_period_id::id_t7,vo,ve,acs,ace,ncs,nct});
    }

    return 1;
}

inline int sc_engine::t7_v_s_a_i(T vo, T acs, T ti, T &vi, T &si, T &ai){

    acs=std::abs(acs);
    //! ace=std::min(std::abs(ace),std::abs(acs));

    T ts=(as-acs)/jm;
    T t=ts;
    T vf=as*t - ((jm*(t*t))/2) + vo;
    T so=vf*t - as*(t*t)/2 + jm*(t*t*t)/6;

    t=0;
    T sf=vf*t - as*(t*t)/2 + jm*(t*t*t)/6;

    t=ti+ts;
    vi=vf - as*t + jm*(t*t)/2;
    si=vf*t - as*(t*t)/2 + jm*(t*t*t)/6;
    si-=so-sf;
    ai=-std::abs(as-jm*t);

    return 1;
}

inline T sc_engine::to_vh_acc(T vo, T ve){
    return ((ve-vo)/2)+vo;
}

inline T sc_engine::to_vh_dcc(T vo, T ve){
    return vo-((vo-ve)/2);
}

inline int sc_engine::t7_t1_t2_t3_t5_s(T vo, T ve, T acs, T ace, bool pb, T &ve_, T &ncs, T &nct){

    T v1=0;
    T t7=0, t1=0, t2=0, t3=0, t5=0;
    T ace_=0;
    T s7=0, s1=0, s2=0, s3=0, s5=0;

    if(acs<0){
        t7_v_s(vo,acs,0,pb,v1,s7,t7);
        vo=v1; //! Reset for next item.
        acs=0;
    }

    T vh=to_vh_acc(vo,ve);
    t1_v_s_ve(vo,vh,acs,false,ace_,ve_,s1,t1);
    if(ace>=0){
        t3_v_s(ve_,ace_,ace,false,ve_,s3,t3);
    }
    if(ace<0){
        t3_v_s(ve_,ace_,0,false,ve_,s3,t3);
        t5_v_s(ve_,0,ace,false,ve_,s5,t5);
    }

    T to_ve=ve-ve_;
    to_ve=std::max(0.0,to_ve);

    t1=0, t2=0, t3=0, t5=0;
    s1=0, s2=0, s3=0, s5=0;

    t1_v_s_ve(vo,vh,acs,pb,ace_,ve_,s1,t1);
    t2_s(ve_,ve_+to_ve,ace_,pb,s2,t2);
    if(ace>=0){
        t3_v_s(ve_+to_ve,ace_,ace,pb,ve_,s3,t3);
    }
    if(ace<0){
        t3_v_s(ve_+to_ve,ace_,0,pb,ve_,s3,t3);
        t5_v_s(ve_,0,ace,pb,ve_,s5,t5);
    }


    ncs=s7+s1+s2+s3+s5;
    nct=t7+t1+t2+t3+t5;

    return 1;
}

inline int sc_engine::t3_t5_t6_t7_t1_s(T vo, T ve, T acs, T ace, bool pb, T &ve_, T &ncs, T &nct){

    T v1=0;
    T t3=0, t5=0, t6=0, t7=0, t1=0;
    T ace_=0;
    T s3=0, s5=0, s6=0, s7=0, s1=0;

    T acs_=acs;
    T vo_=vo;

    if(acs>0){
        t3_v_s(vo,acs,0,false,ve_,s3,t3);
        vo=ve_;
        acs_=0;
    }
    T vh=to_vh_dcc(vo,ve);
    t5_v_s_ve(vo,vh,acs_,false,ace_,ve_,s5,t5);
    if(ace<=0){
        t7_v_s(ve_,ace_,ace,false,ve_,s7,t7);
    }
    if(ace>0){
        t7_v_s(ve_,ace_,0,false,ve_,s7,t7);
        t1_v_s(ve_,0,ace,false,ve_,s1,t1);
    }

    T to_ve=ve_-ve;
    to_ve=std::max(0.0,to_ve);

    t3=0, t5=0, t6=0, t7=0, t1=0;
    s3=0, s5=0, s6=0, s7=0, s1=0;

    if(acs>0){
        t3_v_s(vo_,acs,0,pb,ve_,s3,t3);
        vo_=ve_;
        acs_=0;
    }
    t5_v_s_ve(vo_,vh,acs_,pb,ace_,ve_,s5,t5);
    t6_s(ve_,ve_-to_ve,ace_,pb,s6,t6);
    if(ace<=0){
        t7_v_s(ve_-to_ve,ace_,ace,pb,ve_,s7,t7);
    }
    if(ace>0){
        t7_v_s(ve_-to_ve,ace_,0,pb,ve_,s7,t7);
        t1_v_s(ve_,0,ace,pb,ve_,s1,t1);
    }


    ncs=s3+s5+s6+s7+s1;
    nct=t3+t5+t6+t7+t1;

    return 1;
}

void sc_engine::set_a_dv(T theA, T theDv){


    a=theA;
    dv=theDv;
    ct=dv/a;
    as=2*a;
    jm=2*as/ct;
}

sc_status sc_engine::update(T interval, sc_motion_in in, sc_motion_out &out){
    /*
    std::cout<<" in.curvel:"<<in.curvel
            <<" in.maxvel:"<<in.maxvel
           <<" in.endvel:"<<in.endvel
          <<" in.curacc:"<<in.curacc
         <<" in.endacc:"<<in.endacc
        <<" in.endpos:"<<in.endpos
       <<std::endl;

    std::cout<<" a:"<<a<<" dv:"<<dv<<" jm:"<<jm<<std::endl;*/

    in.curacc=std::min(in.curacc,as);
    in.curacc=std::max(in.curacc,-std::abs(as));

    in.endacc=std::min(in.endacc,as);
    in.endacc=std::max(in.endacc,-std::abs(as));

    process_scurve(in.curvel,
                   in.maxvel,
                   in.endvel,
                   in.curacc,
                   in.endacc,
                   in.endpos);

    // in.curpos

    interpolate(interval,
                out.newvel,
                out.newpos,
                out.newacc);

    return sc_status::Ok;
};

sc_status sc_engine::process_scurve(T vo, T vm, T ve, T acs, T ace, T s){

    pvec.clear();

    T v=0, l=0;
    T l1=0, l2=0, l3=0;
    T t=0;
    T ace_=0, ve_=0;

    bool pb=1;

    //! Curve flow.
    if(vo==vm && ve==vm){

    }
    if(vo<vm && ve==vm){

    }
    if(vo>vm && ve==vm){

    }
    if(vo==vm && ve<vm){

    }
    if(vo==vm && ve>vm){

    }
    if(vo<vm && ve<vm){

        t7_t1_t2_t3_t5_s(vo,vm,acs,0,false,ve_,l1,t);
        t3_t5_t6_t7_t1_s(ve_,ve,0,ace,false,v,l3,t);
        l2=s-(l1+l3);

        if(l2<0){
            T i=0;
            T step=0.01*vm; //! 1% step.
            for(i=ve_; i>0; i-=step){
                t7_t1_t2_t3_t5_s(vo,i,acs,0,false,ve_,l1,t);
                t3_t5_t6_t7_t1_s(ve_,ve,0,ace,false,v,l3,t);
                l2=s-(l1+l3);
                if(l2>0){
                    break;
                }
            }
            vm=i;
        }

        t7_t1_t2_t3_t5_s(vo,vm,acs,0,pb,ve_,l1,t);
        t4_s(ve_,l2,pb,l,t);
        t3_t5_t6_t7_t1_s(ve_,ve,0,ace,pb,ve_,l3,t);
    }
    if(vo<vm && ve>vm){

    }
    if(vo>vm && ve<vm){

    }
    if(vo>vm && ve>vm){

    }

    //! Interpolate at time.

    return sc_status::Ok;
}

double sc_engine::curve_time(){
    T nct=0;
    for(uint i=0; i<pvec.size(); i++){
        nct+=pvec.at(i).nct;
    }
    return nct;
}

void sc_engine::interpolate(T at_time, T &vi, T &si, T &ai){

    T ti=0;
    T ts=0;
    T te=0;
    T sf=0;

    for(uint i=0; i<pvec.size(); i++){

        if(i>0){
            sf+=pvec.at(i-1).ncs;
        }

        ts=te;
        te+=pvec.at(i).nct;

        if(at_time>=ts && at_time<=te){

            ti=at_time-ts;

            if(pvec.at(i).id==sc_period_id::id_t1){
                t1_v_s_a_i(pvec.at(i).vo,pvec.at(i).acs,ti,vi,si,ai);
            }
            if(pvec.at(i).id==sc_period_id::id_t2){
                t2_v_s_a_i(pvec.at(i).vo,pvec.at(i).acs,ti,vi,si,ai);
            }
            if(pvec.at(i).id==sc_period_id::id_t3){
                t3_v_s_a_i(pvec.at(i).vo,pvec.at(i).acs,ti,vi,si,ai);
            }
            if(pvec.at(i).id==sc_period_id::id_t4){
                t4_v_s_a_i(pvec.at(i).vo,ti,vi,si,ai);
            }
            if(pvec.at(i).id==sc_period_id::id_t5){
                t5_v_s_a_i(pvec.at(i).vo,pvec.at(i).acs,ti,vi,si,ai);
            }
            if(pvec.at(i).id==sc_period_id::id_t6){
                t6_v_s_a_i(pvec.at(i).vo,pvec.at(i).acs,ti,vi,si,ai);
            }
            if(pvec.at(i).id==sc_period_id::id_t7){
                t7_v_s_a_i(pvec.at(i).vo,pvec.at(i).acs,ti,vi,si,ai);
            }
            si+=sf;
        }
    }
}




















