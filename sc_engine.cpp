#include "sc_engine.h"

inline int sc_engine::t1_v(double vo, double acs, double ace, double &ve){

    ts=acs/jm;
    vf=vo-(jm*(ts*ts)/2);

    te=ace/jm;
    ve=vf+jm*(te*te)/2;

    return 1;
}

inline int sc_engine::t1_s(double vo, double acs, double ace, double &ncs, double &nct){

    ts=acs/jm;
    vf=vo-(jm*(ts*ts)/2);
    so=vf*ts+jm*(ts*ts*ts)/6;

    te=ace/jm;
    se=vf*te+jm*(te*te*te)/6;

    ncs=se-so;
    nct=te-ts;
    return 1;
}

inline int sc_engine::t1_v_ve(double vo, double ve, double acs, double &ace, double &ve_){

    ts=acs/jm;
    vf=vo-(jm*(ts*ts)/2);

    te=sqrt(-2*vf+2*ve)/sqrt(jm);
    te=std::min(0.5*ct,te);

    ve_=vf+jm*(te*te)/2;
    ace=jm*te;

    return 1;
}

inline int sc_engine::t1_s_ve(double vo, double ve, double acs, double &ncs, double &nct){

    ts=acs/jm;
    vf=vo-(jm*(ts*ts)/2);

    so=vf*ts+jm*(ts*ts*ts)/6;

    te=sqrt(-2*vf+2*ve)/sqrt(jm);
    te=std::min(0.5*ct,te);

    se=vf*te+jm*(te*te*te)/6;

    ncs=se-so;
    nct=te-ts;

    return 1;
}

inline int sc_engine::t1_v_i(double vo, double acs, double ti, double &vi, double &ai){

    ts=acs/jm;
    vf=vo-(jm*(ts*ts)/2);

    ti+=ts;
    vi=vf+jm*(ti*ti)/2;
    ai=jm*ti;
    return 1;
}

inline int sc_engine::t2_v(double ve, double &ve_){

    ve_=ve;

    return 1;
}

inline int sc_engine::t2_v_i(double ti, sc_period p, double &vi){

    vi=p.vo + p.acs*ti;

    return 1;
}

inline int sc_engine::t2_s(double vo, double ve, double a, double &ncs, double &nct){

    ncs=((ve*ve) - (vo*vo))/(2*a) ;
    nct=(ve-vo)/a;
    return 1;
}

inline int sc_engine::t3_v(double vo, double acs, double ace, double &ve){

    ace=std::min(std::abs(ace),std::abs(acs));

    ts=(as-acs)/jm;
    vf = -as*ts+((jm*(ts*ts))/2)+vo;

    te=(as-ace)/jm;
    ve=vf + as*te - jm*(te*te)/2;

    return 1;
}

inline int sc_engine::t3_v_i(double ti, sc_period p, double &vi){

    p.ace=std::min(std::abs(p.ace),std::abs(p.acs));

    ts=(as-p.acs)/jm;
    vf = -as*ts+((jm*(ts*ts))/2)+p.vo;

    ti+=ts;
    vi=vf + as*ti - jm*(ti*ti)/2;

    return 1;
}

inline int sc_engine::t3_s(double vo, double acs, double ace, double &ncs, double &nct){

    ace=std::min(std::abs(ace),std::abs(acs));

    ts=(as-acs)/jm;
    vf = -as*ts+((jm*(ts*ts))/2)+vo;
    so=vf*ts + as*(ts*ts)/2 - jm*(ts*ts*ts)/6;

    te=(as-ace)/jm;
    se=vf*te + as*(te*te)/2 - jm*(te*te*te)/6;

    ncs=se-so;
    nct=te-ts;

    return 2;
}

inline int sc_engine::t4_s(double vo, double s, double &ncs, double &nct){
    nct=s/vo;
    ncs=s;
    return 1;
}

inline int sc_engine::t5_v(double vo, double acs, double ace, double &ve){

    if(acs==ace){
        return vo;
    }

    ts=acs/jm;
    vf=((jm*(ts*ts))/2)+vo;

    te=ace/jm;
    ve=vf-jm*(te*te)/2;

    return 1;
}

inline int sc_engine::t5_s(double vo, double acs, double ace, double &ncs, double &nct){

    if(acs==ace){
        return vo;
    }

    ts=acs/jm;
    vf=((jm*(ts*ts))/2)+vo;
    so=vf*ts-jm*(ts*ts*ts)/6;

    te=ace/jm;
    se=vf*te-jm*(te*te*te)/6;

    ncs=se-so;
    nct=te-ts;

    return 1;
}

inline int sc_engine::t5_v_ve(double vo, double ve, double acs, double &ace, double &ve_){

    ts=acs/jm;
    vf=((jm*(ts*ts))/2)+vo;

    te=(sqrt(2)*sqrt(vf-ve))/sqrt(jm);
    te=std::min(0.5*ct,te);

    ve_=vf-jm*(te*te)/2; // bugfix, added ve forumula.
    ace=-std::abs(jm*te);

    return 1;
}

inline int sc_engine::t5_s_ve(double vo, double ve, double acs, double &ncs, double &nct){

    ts=ve/jm;
    vf=((jm*(ts*ts))/2)+vo;
    so=vf*ts-jm*(ts*ts*ts)/6;

    te=(sqrt(2)*sqrt(vf-ve))/sqrt(jm);
    te=std::min(0.5*ct,te);

    se=vf*te-jm*(te*te*te)/6;

    ncs=se-so;
    nct=te-ts;

    return 1;
}

inline int sc_engine::t6_v(double ve, double &ve_){

    ve_=ve;

    return 1;
}

inline int sc_engine::t6_s(double vo, double ve, double a, double &ncs, double &nct){

    a=std::abs(a);
    ncs=((vo*vo) - (ve*ve))/(2*a);
    nct=(vo-ve)/a;

    return 1;
}

inline int sc_engine::t7_v(double vo, double acs, double ace, double &ve){

    ace=std::min(std::abs(ace),std::abs(acs));

    ts=(as-acs)/jm;
    vf=as*ts - ((jm*(ts*ts))/2) + vo;

    te=(as-ace)/jm;
    ve=vf - as*te + jm*(te*te)/2;

    return 1;
}

inline int sc_engine::t7_s(double vo, double acs, double ace, double &ncs, double &nct){

    ace=std::min(std::abs(ace),std::abs(acs));

    ts=(as-acs)/jm;
    vf=as*ts - ((jm*(ts*ts))/2) + vo;
    so=vf*ts - as*(ts*ts)/2 + jm*(ts*ts*ts)/6;

    te=(as-ace)/jm;
    se=vf*te - as*(te*te)/2 + jm*(te*te*te)/6;

    ncs=se-so;
    nct=te-ts;

    return 1;
}

inline int sc_engine::t1_t2_t3_s(double vo, double ve, double acs, double ace, bool pb, double &ncs, double &nct){

    t1_v_ve(vo,((ve-vo)/2)+vo,acs,ace_,v1);
    t3_v(v1,ace_,ace,v2);

    to_ve=ve-v2;
    to_ve=std::max(0.0,to_ve);

    t1_s_ve(vo,v1,acs,s1,t1);
    t2_s(v1,v1+to_ve,ace_,s2,t2);
    t3_s(v1+to_ve,ace_,ace,s3,t3);

    if(pb){
        pvec.push_back({sc_period_id::id_t1,vo,v1,acs,ace_,s1,t1});
        pvec.push_back({sc_period_id::id_t2,v1,v1+to_ve,ace_,ace_,s2,t2});
        pvec.push_back({sc_period_id::id_t3,v1+to_ve,ace_,ace,s3,t3});
    };

    ncs=s1+s2+s3;
    nct=t1+t2+t3;

    return 1;
}

inline int sc_engine::t5_t6_t7_s(double vo, double ve, double acs, double ace, bool pb, double &ncs, double nct){

    t5_v_ve(vo,vo-((vo-ve)/2),acs,ace_,v1);
    t7_v(v1,ace_,ace,v2);

    to_ve=v2-ve;
    to_ve=std::max(0.0,to_ve);

    t5_s_ve(vo,v1,acs,s1,t1);
    t6_s(v1,v1-to_ve,ace_,s2,t2);
    t7_s(v1-to_ve,ace_,ace,s3,t3);

    if(pb){
        pvec.push_back({sc_period_id::id_t5,vo,v1,acs,ace_,s1,t1});
        pvec.push_back({sc_period_id::id_t6,v1,v1-to_ve,ace_,ace_,s2,t2});
        pvec.push_back({sc_period_id::id_t7,v1-to_ve,ace_,ace,s3,t3});
    };

    ncs=s1+s2+s3;
    nct=t1+t2+t3;

    return 1;
}

void sc_engine::set_a_dv(double theA, double theDv){


    a=theA;
    dv=theDv;
    ct=dv/a;
    as=2*a;
    jm=2*as/ct;
}

void sc_engine::set_acs_ace(double theAcs, double theAce){

    acs=theAcs;
    ace=theAce;
    acs=std::min(std::abs(acs),as);
    ace=std::min(std::abs(ace),as);
}

sc_status sc_engine::update(double interval, sc_motion_in in, sc_motion_out &out){
    return process_scurve(in.curvel,in.maxvel,in.endvel,in.curacc,in.endacc,in.curpos,in.endpos,interval,
                       out.finished,
                       out.newvel,
                       out.newpos,
                       out.newacc);
};

sc_status sc_engine::process_scurve(double vo, double vm,  double ve, double acs, double ace, double sc, double se, double ti,
                                   bool &finished, double &vi, double &si, double &ai){

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
    //! working on.
    if(vo<vm && ve<vm){

        // build_t7_t1_t2_t3(vo,vm,acs,0,ve_,pb);
        // build_t5_t6_t7_t1(ve_,ve,0,ace,ve_,pb);
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

























