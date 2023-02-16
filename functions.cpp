
#include <functions.h>

//! vo=velocity start.
//! a=acceleration.
//! as=acceleration at inflection point, 2*a.
//! acs=acceleration start.
//! ace=acceleration end.
//! dv=velocity delta value from 0 to 2*a to 0. (determines curve power)
//! ti=time interpolation request.
//! vi=velocity interpolation.
//! si=displacement interpolation.
//! ai=acceleration interpolation.
//! nct=netto curve time.
//! nsi=netto displacement.
void sc_t1(double vo, double a, double acs, double ace, double dv,
           double &vf_, double &vo_, double &ve_, double &acs_, double &ace_,
           double &nct_, double &nsi_, double ti_, double &vi_, double &si_, double &ai_){

    //! Internals:
    double ct=0;
    double jm=0;
    double as=0;
    double t=0;
    double th=0;
    double ts=0;
    double te=0;
    double sf=0, so=0, se=0;


    ai_=0;

    //! No changes.
    if(acs==ace){
        nct_=0;
        vo_=vo;
        ve_=vo;
        acs_=acs;
        ace_=ace;
        return;
    }

    ct=dv/a;
    th=0.5*ct;
    as=2*a;
    jm=2*as/ct;

    acs=abs(acs);
    if(acs>as){
        acs=as;
    }
    ace=abs(ace);

    ts=acs/jm;
    t=ts;
    vf_=vo-(jm*(t*t)/2);

    t=0;
    sf=vf_*t+jm*(t*t*t)/6;

    t=ts;
    so=vf_*t+jm*(t*t*t)/6;

    te=ace/jm;
    t=te;
    ve_=vf_+jm*(t*t)/2;
    se=vf_*t+jm*(t*t*t)/6;

    t=ti_+ts;
    vi_=vf_+jm*(t*t)/2;
    si_=vf_*t+jm*(t*t*t)/6;
    si_-=so-sf;
    ai_=jm*t;

    nct_=te-ts;
    nsi_=se-so;
    vo_=vo;
    acs_=acs;
    ace_=ace;
}

void sc_t1_ve(double vo, double ve, double a, double acs, double dv,
              double &vf_, double &vo_, double &ve_, double &acs_, double &ace_,
              double &nct_, double &nsi_, double ti_, double &vi_, double &si_, double &ai_){

    //! Internals:
    double ct=0;
    double jm=0;
    double as=0;
    double t=0;
    double th=0;
    double ts=0;
    double te=0;
    double sf=0, so=0, se=0;

    ct=dv/a;
    th=0.5*ct;
    as=2*a;
    jm=2*as/ct;

    acs=abs(acs);
    if(acs>as){
        acs=as;
    }

    ts=acs/jm;
    t=ts;
    vf_=vo-(jm*(t*t)/2);

    if(ve-vf_>dv){ //! Limit curve to respect dv.
        ve=vf_+dv;
    }

    te=sqrt(2)*sqrt(ve-vf_)/sqrt(jm);

    t=0;
    sf=vf_*t+jm*(t*t*t)/6;

    t=ts;
    so=vf_*t+jm*(t*t*t)/6;

    t=te;
    ace_=jm*t;
    se=vf_*t+jm*(t*t*t)/6;

    nct_=te-ts;
    nsi_=se-so;

    t=ti_+ts;
    vi_=vf_+jm*(t*t)/2;
    si_=vf_*t+jm*(t*t*t)/6;
    si_-=so-sf;
    ai_=jm*t;

    vo_=vo;
    ve_=ve;
    acs_=acs;
}

//! For a input current acceleration.
void sc_t2(double vo, double ve, double a,
           double &vo_, double &ve_, double &acs_, double &ace_,
           double &nct_, double &nsi_, double ti, double &vi_, double &si_, double &ai_){

    double t=0;

    nct_=(ve-vo)/a;
    nsi_=((ve*ve) - (vo*vo))/(2*a) ;
    vo_=vo;
    ve_=ve;
    acs_=a;
    ace_=a;

    t=ti;
    vi_=vo + a*t;
    si_=vo*t + 0.5*a*(t*t);
    ai_=a;
}

void sc_t3(double vo, double a, double acs, double ace, double dv,
           double &vf_, double &vo_, double &ve_, double &acs_, double &ace_,
           double &nct_, double &nsi_, double ti_, double &vi_, double &si_, double &ai_){

    //! Internals:
    double ct=0;
    double jm=0;
    double as=0;
    double t=0;
    double th=0;
    double ts=0;
    double te=0;
    double sf=0, so=0, se=0;

    ct=dv/a;
    th=0.5*ct;
    as=2*a;
    jm=2*as/ct;

    acs=abs(acs);
    if(acs>as){
        acs=as;
    }
    ace=abs(ace);

    ts=(as-acs)/jm;
    t=ts;
    vf_ = -as*t+((jm*(t*t))/2)+vo;
    so=vf_*t + as*(t*t)/2 - jm*(t*t*t)/6;

    t=0;
    sf=vf_*t + as*(t*t)/2 - jm*(t*t*t)/6;

    te=(as-ace)/jm;
    t=te;
    ve_=vf_ + as*t - jm*(t*t)/2;
    se=vf_*t + as*(t*t)/2 - jm*(t*t*t)/6;

    t=ti_+ts;
    vi_=vf_ + as*t - jm*(t*t)/2;
    si_=vf_*t + as*(t*t)/2 - jm*(t*t*t)/6;
    si_-=so-sf;
    ai_=as-jm*t;

    nsi_=se-so;
    nct_=te-ts;
    acs_=acs;
    ace_=ace;
    vo_=vo;
}

void sc_t4(double vo, double s,
           double &vo_, double &ve_, double &acs_, double &ace_, double &nct_, double ti_, double &vi_, double &ai_){
    nct_=s/vo;
    vo_=vo;
    ve_=vo;
    acs_=0;
    ace_=0;

    vi_=s/ti_;
    ai_=0;
}

void sc_t5(double vo, double a, double acs, double ace, double dv,
           double &vf_, double &vo_, double &ve, double &acs_, double &ace_, double &nct, double ti_, double &vi_, double &ai_){

    //! Internals:
    double ct=0;
    double jm=0;
    double as=0;
    double t=0;
    double th=0;
    double ts=0;
    double te=0;

    //! No changes.
    if(acs==ace){
        nct=0;
        vo_=vo;
        ve=vo;
        acs_=acs;
        ace_=ace;
        return;
    }

    ct=dv/a;
    th=0.5*ct;
    as=2*a;
    jm=2*as/ct;

    acs=abs(acs);
    if(acs>as){
        acs=as;
    }

    ace=abs(ace);

    ts=acs/jm;
    t=ts;
    vf_=((jm*(t*t))/2)+vo;

    te=ace/jm;
    t=te;
    ve=vf_-jm*(t*t)/2;

    t=ti_+ts;
    vi_=vf_-jm*(t*t)/2;
    ai_=-abs(jm*t);

    acs_=-abs(acs);
    ace_=-abs(ace);
    vo_=vo;
    nct=te-ts;
}

void sc_t5_ve(double vo, double ve, double a, double acs, double dv,
              double &vf_, double &vo_, double &ve_, double &acs_, double &ace, double &nct, double ti_, double &vi_, double &ai_){

    //! Internals:
    double ct=0;
    double jm=0;
    double as=0;
    double t=0;
    double th=0;
    double ts=0;
    double te=0;

    ct=dv/a;
    th=0.5*ct;
    as=2*a;
    jm=2*as/ct;

    acs=abs(acs);
    if(acs>as){
        acs=as;
    }

    ts=acs/jm;
    t=ts;
    vf_=((jm*(t*t))/2)+vo;

    if(vf_-ve>dv){ //! Limit curve to respect dv.
        ve=vf_-dv;
    }

    te=sqrt(2)*sqrt(vf_-ve)/sqrt(jm);
    t=te;
    ace=-abs(jm*t);

    t=ti_+ts;
    vi_=vf_-jm*(t*t)/2;
    ai_=-abs(jm*t);

    nct=te-ts;
    vo_=vo;
    ve_=ve;
    acs_=-abs(acs);
}

void sc_t6(double vo, double ve, double a,
           double &vo_, double &ve_, double &acs, double &ace, double &nct, double ti_, double &vi_, double &ai_){
    double apositive=abs(a);
    nct=(vo-ve)/apositive;
    vo_=vo;
    ve_=ve;
    acs=a;
    ace=a;

    double t=0;
    t=ti_;
    vi_=vo - apositive*t;
    ai_=-abs(a);
}

//! For a input current acceleration.
void sc_t7(double vo, double a, double acs, double ace, double dv,
           double &vf_, double &vo_, double &ve, double &acs_, double &ace_, double &nct, double ti_, double &vi_, double &ai_){

    //! Internals:
    double ct=0;
    double jm=0;
    double as=0;
    double t=0;
    double th=0;
    double ts=0;
    double te=0;

    ct=dv/a;
    th=0.5*ct;
    as=2*a;
    jm=2*as/ct;

    acs=abs(acs);
    if(acs>as){
        acs=as;
    }

    ace=abs(ace);

    ts=(as-acs)/jm;
    t=ts;
    vf_=as*t - ((jm*(t*t))/2) + vo;

    te=(as-ace)/jm;
    t=te;
    ve=vf_ - as*t + jm*(t*t)/2;

    t=ti_+ts;
    vi_=vf_ - as*t + jm*(t*t)/2;
    ai_=as-jm*t;

    vo_=vo;
    acs_=-abs(acs);
    ace_=-abs(ace);
    nct=te-ts;
}

double to_vh_acc(double vo, double ve){
    return ((ve-vo)/2)+vo;
}

double to_vh_dcc(double vo, double ve){
    return ((vo-ve)/2)+ve;
}

void sc::sc_construct_t1_t2_t3_period(double vo, double ve, double acs){

    double vf1=0,vo1=0,ve1=0,acs1=0,ace1=0,nct1=0,nsi1=0, ti1=0,vi1=0,si1=0,ai1=0;
    double vf2=0,vo2=0,ve2=0,acs2=0,ace2=0,nct2=0,nsi2=0, ti2=0,vi2=0,si2=0,ai2=0;
    double vf3=0,vo3=0,ve3=0,acs3=0,ace3=0,nct3=0,nsi3=0, ti3=0,vi3=0,si3=0, ai3=0;
    double vh=to_vh_acc(vo,ve);

    //! Calculate standard curve.
    sc_t1(vo,a,acs,as,dv,vf1,vo1,ve1,acs1,ace1,nct1,nsi1,ti1,vi1,si1,ai1);
    sc_t3(ve1,a,ace1,0,dv,vf3,vo3,ve3,acs3,ace3,nct3,nsi3,ti3,vi3,si3,ai3);

    double vt2= (ve-vo) - ((ve1-vo1)+(ve3-vo3));

    //! Curve can not reach as, t1 has ace, t3 has acs.
    if(vt2<0){
        //! std::cout<<"curve can not reach as"<<std::endl;
        sc_t1_ve(vo,vh,a,acs,dv,vf1,vo1,ve1,acs1,ace1,nct1,nsi1,ti1,vi1,si1,ai1);
        sc_t3(ve1,a,ace1,0,dv,vf3,vo3,ve3,acs3,ace3,nct3,nsi3,ti3,vi3,si3,ai3);

        pvec.push_back({period_id::t1,vo1,ve1,acs1,ace1,nct1,nsi1});
        pvec.push_back({period_id::t3,vo3,ve3,acs3,ace3,nct3,nsi3});
    }
    //! Curve = dv.
    if(vt2==0){
        //! std::cout<<"curve = dv"<<std::endl;
        pvec.push_back({period_id::t1,vo1,ve1,acs1,ace1,nct1,nsi1});
        pvec.push_back({period_id::t3,vo3,ve3,acs3,ace3,nct3,nsi3});
    }
    //! Curve needs t2.
    if(vt2>0){
        //! std::cout<<"curve incl. t2"<<std::endl;
        sc_t2(ve1,ve1+vt2,ace1,vo2,ve2,acs2,ace2,nct2,nsi2,ti2,vi2,si2,ai2);
        sc_t3(ve2,a,ace2,0,dv,vf3,vo3,ve3,acs3,ace3,nct3,nsi3,ti3,vi3,si3,ai3);

        pvec.push_back({period_id::t1,vo1,ve1,acs1,ace1,nct1,nsi1});
        pvec.push_back({period_id::t2,vo2,ve2,acs2,ace2,nct2,nsi2});
        pvec.push_back({period_id::t3,vo3,ve3,acs3,ace3,nct3,nsi3});
    }
}

void sc::sc_construct_t5_t6_t7_period(double vo, double ve, double ace){

    //    double vf5=0,vo5=0,ve5=0,acs5=0,ace5=0,nct5=0,ti5=0,vi5=0,ai5=0;
    //    double vf6=0,vo6=0,ve6=0,acs6=0,ace6=0,nct6=0,ti6=0,vi6=0,ai6=0;
    //    double vf7=0,vo7=0,ve7=0,acs7=0,ace7=0,nct7=0,ti7=0,vi7=0,ai7=0;
    //    double vh=to_vh_dcc(vo,ve);

    //    //! Calculate standard curve.
    //    sc_t5(vo,a,0,as,dv,vf5,vo5,ve5,acs5,ace5,nct5,ti5,vi5,ai5);
    //    sc_t7(ve5,a,ace5,0,dv,vf7,vo7,ve7,acs7,ace7,nct7,ti7,vi7,ai7);

    //    double vt2= (vo-ve) - ((vo5-ve5)+(vo7-ve7));

    //    //! Curve can not reach as, t1 has ace, t3 has acs.
    //    if(vt2<0){
    //        std::cout<<"curve can not reach as"<<std::endl;
    //        sc_t1_ve(vo,vh,a,acs,dv,vf1,vo1,ve1,acs1,ace1,nct1,ti1,vi1,ai1);
    //        sc_t3(ve1,a,ace1,0,dv,vf3,vo3,ve3,acs3,ace3,nct3,ti3,vi3,ai3);

    //        pvec.push_back({period_id::t1,vo1,ve1,acs1,ace1,nct1});
    //        pvec.push_back({period_id::t3,vo3,ve3,acs3,ace3,nct3});
    //    }
    //    //! Curve = dv.
    //    if(vt2==0){
    //        std::cout<<"curve = dv"<<std::endl;
    //        pvec.push_back({period_id::t1,vo1,ve1,acs1,ace1,nct1});
    //        pvec.push_back({period_id::t3,vo3,ve3,acs3,ace3,nct3});
    //    }
    //    //! Curve needs t2.
    //    if(vt2>0){
    //        std::cout<<"curve incl. t2"<<std::endl;
    //        sc_t2(ve1,ve1+vt2,ace1,vo2,ve2,acs2,ace2,nct2,ti2,vi2,ai2);
    //        sc_t3(ve2,a,ace2,0,dv,vf3,vo3,ve3,acs3,ace3,nct3,ti3,vi3,ai3);

    //        pvec.push_back({period_id::t1,vo1,ve1,acs1,ace1,nct1});
    //        pvec.push_back({period_id::t2,vo2,ve2,acs2,ace2,nct2});
    //        pvec.push_back({period_id::t3,vo3,ve3,acs3,ace3,nct3});
    //    }
}

void sc::create(double vo, double vm, double ve, double acs, double ace, double s){
    pvec.clear();
    if(vo<vm && ve<vm){
        sc_construct_t1_t2_t3_period(vo,vm,acs);
        //sc_construct_t5_t6_t7_period(vm,ve,ace);
    }
}

double sc::curve_time(){
    double t=0;
    for(uint i=0; i<pvec.size(); i++){
        t+=pvec.at(i).nct;
        //! std::cout<<"pvec i:"<<i<<" ct:"<<pvec.at(i).ct<<std::endl;
    }
    return t;
}

void sc::interpolate(double at_time, double &vi, double &si, double &ai){

    double vf=0,vo=0,ve=0,acs=0,ace=0,nct=0,nsi=0,ti=0;
    double ts=0;
    double te=0;
    double sf=0;
    for(uint i=0; i<pvec.size(); i++){

        if(i>0){
            sf+=pvec.at(i-1).nsi;
        }

        ts=te;
        te+=pvec.at(i).nct;

        if(at_time>=ts && at_time<=te){

            ti=at_time-ts;

            if(pvec.at(i).id==period_id::t1){
                sc_t1(pvec.at(i).vo,
                      a,
                      pvec.at(i).acs,
                      pvec.at(i).ace,
                      dv,
                      vf,vo,ve,acs,ace,nct,nsi,ti,vi,si,ai);
            }
            if(pvec.at(i).id==period_id::t2){
                sc_t2(pvec.at(i).vo,
                      pvec.at(i).ve,
                      pvec.at(i).acs,
                      vo,ve,acs,ace,nct,nsi,ti,vi,si,ai);
            }
            if(pvec.at(i).id==period_id::t3){
                sc_t3(pvec.at(i).vo,
                      a,
                      pvec.at(i).acs,
                      pvec.at(i).ace,
                      dv,
                      vf,vo,ve,acs,ace,nct,nsi,ti,vi,si,ai);
            }
            if(pvec.at(i).id==period_id::t4){
                sc_t4(pvec.at(i).vo,
                      pvec.at(i).nsi,
                      vo,ve,acs,ace,nct,ti,vi,ai);
            }
            if(pvec.at(i).id==period_id::t5){
                sc_t5(pvec.at(i).vo,
                      a,
                      pvec.at(i).acs,
                      pvec.at(i).ace,
                      dv,
                      vf,vo,ve,acs,ace,nct,ti,vi,ai);
            }
            if(pvec.at(i).id==period_id::t6){
                sc_t6(pvec.at(i).vo,
                      pvec.at(i).ve,
                      pvec.at(i).acs,
                      vo,ve,acs,ace,nct,ti,vi,ai);
            }
            if(pvec.at(i).id==period_id::t7){
                sc_t7(pvec.at(i).vo,
                      a,
                      pvec.at(i).acs,
                      pvec.at(i).ace,
                      dv,
                      vf,vo,ve,acs,ace,nct,ti,vi,ai);
            }

            si+=sf;
        }
    }
}

void sc::plot(double interval,
              std::vector<double> &vvec,
              std::vector<double> &svec,
              std::vector<double> &avec){

    double vi=0, si=0, ai=0;
    for(double t=0; t<=curve_time(); t+=interval){
        interpolate(t,vi,si,ai);
        vvec.push_back(vi);
        svec.push_back(si);
        avec.push_back(ai);
    }
}

void sc::print_journal(){

    for(uint i=0; i<pvec.size(); i++){
        std::cout<<"i:"<<i<<" vo:"<<pvec.at(i).vo<<" ve:"<<pvec.at(i).ve
                <<" acs:"<<pvec.at(i).acs<<" ace:"<<pvec.at(i).ace
               <<" nsi:"<<pvec.at(i).nsi<<" nct:"<<pvec.at(i).nct<<std::endl;
    }
}

void sc::print_interpolation(double interval){

    double vi=0, si=0, ai=0;
    for(double t=0; t<=curve_time(); t+=interval){
        interpolate(t,vi,si,ai);
        std::cout<<"t:"<<t<<" v:"<<vi<<" s:"<<si<<" a:"<<ai<<std::endl;
    }
}









































