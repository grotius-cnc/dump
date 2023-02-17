
#include <functions.h>
#include <cmath>

//! vo=velocity start.
//! ve=velocity end.
//! vf=velocity front of curve. ts=0.
//! ts=time start.
//! te=time end.
//! t=time.
//! a=acceleration.
//! as=acceleration at inflection point, 2*a.
//! acs=acceleration start.
//! ace=acceleration end.
//! dv=velocity delta value from 0 to 2*a to 0. (determines curve power)
//! ti=time interpolation request.
//! vi=velocity interpolation.
//! si=displacement interpolation.
//! ai=acceleration interpolation.
//! ct=curve time
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
           double &vo_, double &ve_, double &acs_, double &ace_,
           double &nct_, double &nsi_, double ti_, double &vi_, double &si_, double &ai_){
    nct_=s/vo;
    nsi_=s;
    vo_=vo;
    ve_=vo;
    acs_=0;
    ace_=0;

    vi_=vo;
    si_=vo*ti_;
    ai_=0;
}

void sc_t5(double vo, double a, double acs, double ace, double dv,
           double &vf_, double &vo_, double &ve, double &acs_, double &ace_,
           double &nct_, double &nsi_, double ti_, double &vi_, double &si_, double &ai_){

    //! Internals:
    double ct=0;
    double jm=0;
    double as=0;
    double t=0;
    double th=0;
    double ts=0;
    double te=0;
    double so=0, sf=0, se=0;

    //! No changes.
    if(acs==ace){
        nct_=0;
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
    so=vf_*t-jm*(t*t*t)/6;

    t=0;
    sf=vf_*t-jm*(t*t*t)/6;

    te=ace/jm;
    t=te;
    ve=vf_-jm*(t*t)/2;
    se=vf_*t-jm*(t*t*t)/6;

    t=ti_+ts;
    vi_=vf_-jm*(t*t)/2;
    ai_=-abs(jm*t);
    si_=vf_*t-jm*(t*t*t)/6;
    si_-=so-sf;

    acs_=-abs(acs);
    ace_=-abs(ace);
    vo_=vo;
    nct_=te-ts;
    nsi_=se-so;
}

void sc_t5_ve(double vo, double ve, double a, double acs, double dv,
              double &vf_, double &vo_, double &ve_, double &acs_, double &ace,
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
    vf_=((jm*(t*t))/2)+vo;
    so=vf_*t-jm*(t*t*t)/6;

    if(vf_-ve>dv){ //! Limit curve to respect dv.
        ve=vf_-dv;
    }

    t=0;
    sf=vf_*t-jm*(t*t*t)/6;

    te=sqrt(2)*sqrt(vf_-ve)/sqrt(jm);
    t=te;
    ace=-abs(jm*t);
    se=vf_*t-jm*(t*t*t)/6;

    t=ti_+ts;
    vi_=vf_-jm*(t*t)/2;
    si_=vf_*t-jm*(t*t*t)/6;
    si_-=so-sf;
    ai_=-abs(jm*t);

    nct_=te-ts;
    nsi_=se-so;
    vo_=vo;
    ve_=ve;
    acs_=-abs(acs);
}

void sc_t6(double vo, double ve, double a,
           double &vo_, double &ve_, double &acs, double &ace,
           double &nct_, double &nsi_, double ti_, double &vi_, double &si_, double &ai_){

    double t=0;
    a=abs(a);

    nct_=(vo-ve)/a;
    nsi_=((vo*vo) - (ve*ve))/(2*a) ;
    vo_=vo;
    ve_=ve;
    acs=-abs(a);
    ace=-abs(a);

    t=ti_;
    vi_=vo - a*t;
    si_=vo*t - 0.5*a*(t*t);
    ai_=-abs(a);
}

//! For a input current acceleration.
void sc_t7(double vo, double a, double acs, double ace, double dv,
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
    vf_=as*t - ((jm*(t*t))/2) + vo;
    so=vf_*t - as*(t*t)/2 + jm*(t*t*t)/6;

    t=0;
    sf=vf_*t - as*(t*t)/2 + jm*(t*t*t)/6;

    te=(as-ace)/jm;
    t=te;
    ve_=vf_ - as*t + jm*(t*t)/2;
    se=vf_*t - as*(t*t)/2 + jm*(t*t*t)/6;

    t=ti_+ts;
    vi_=vf_ - as*t + jm*(t*t)/2;
    si_=vf_*t - as*(t*t)/2 + jm*(t*t*t)/6;
    si_-=so-sf;
    ai_=-abs(as-jm*t);

    vo_=vo;
    acs_=-abs(acs);
    ace_=-abs(ace);
    nct_=te-ts;
    nsi_=se-so;
}

double to_vh_acc(double vo, double ve){
    return ((ve-vo)/2)+vo;
}

double to_vh_dcc(double vo, double ve){
    return ((vo-ve)/2)+ve;
}

double sc::jm(){
    double ct=dv/a;
    double as=2*a;
    double jm=2*as/ct;
    return jm;
}

void sc::build_t1_t2_t3(double vo, double ve, double acs, double ace){

    double vf1=0,vo1=0,ve1=0,acs1=0,ace1=0,nct1=0,nsi1=0, ti1=0,vi1=0,si1=0,ai1=0;
    double vf2=0,vo2=0,ve2=0,acs2=0,ace2=0,nct2=0,nsi2=0, ti2=0,vi2=0,si2=0,ai2=0;
    double vf3=0,vo3=0,ve3=0,acs3=0,ace3=0,nct3=0,nsi3=0, ti3=0,vi3=0,si3=0, ai3=0;
    double vh=to_vh_acc(vo,ve);

    //! Calculate standard curve.
    sc_t1(vo,a,acs,as,dv,vf1,vo1,ve1,acs1,ace1,nct1,nsi1,ti1,vi1,si1,ai1);
    sc_t3(ve1,a,ace1,ace,dv,vf3,vo3,ve3,acs3,ace3,nct3,nsi3,ti3,vi3,si3,ai3);

    double vt2= (ve-vo) - ((ve1-vo1)+(ve3-vo3));

    //! Curve can not reach as, t1 has ace, t3 has acs.
    if(vt2<0){
        //! std::cout<<"curve can not reach as"<<std::endl;
        sc_t1_ve(vo,vh,a,acs,dv,vf1,vo1,ve1,acs1,ace1,nct1,nsi1,ti1,vi1,si1,ai1);
        sc_t3(ve1,a,ace1,ace,dv,vf3,vo3,ve3,acs3,ace3,nct3,nsi3,ti3,vi3,si3,ai3);

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
        sc_t3(ve2,a,ace2,ace,dv,vf3,vo3,ve3,acs3,ace3,nct3,nsi3,ti3,vi3,si3,ai3);

        pvec.push_back({period_id::t1,vo1,ve1,acs1,ace1,nct1,nsi1});
        pvec.push_back({period_id::t2,vo2,ve2,acs2,ace2,nct2,nsi2});
        pvec.push_back({period_id::t3,vo3,ve3,acs3,ace3,nct3,nsi3});
    }
}

void sc::build_t2_stitch(double vo, double s, double a){

    //! std::cout<<"vo:"<<vo<<std::endl;
    //! std::cout<<"s:"<<s<<std::endl;
    //! std::cout<<"a:"<<a<<std::endl;

    double t=0,ve=0;
    t= abs( (-vo + sqrt(vo*vo - 2*a*s)) / a);
    ve=vo + a * t;
    //! std::cout<<"t:"<<t<<std::endl;
    //! std::cout<<"ve:"<<ve<<std::endl;
    ve_stitch={period_id::t2,vo,ve,a,a,t,s};
}

void sc::build_t4_stitch(double vo, double s){

    ve_stitch={period_id::t4,vo,vo,0,0,s/vo,s};
}

void sc::build_t5_t6_t7(double vo, double ve, double acs, double ace){

    double vf5=0,vo5=0,ve5=0,acs5=0,ace5=0,nct5=0,nsi5=0,ti5=0,vi5=0,si5=0,ai5=0;
    double vf6=0,vo6=0,ve6=0,acs6=0,ace6=0,nct6=0,nsi6=0,ti6=0,vi6=0,si6=0,ai6=0;
    double vf7=0,vo7=0,ve7=0,acs7=0,ace7=0,nct7=0,nsi7=0,ti7=0,vi7=0,si7=0,ai7=0;
    double vh=to_vh_dcc(vo,ve);

    //! Calculate standard curve.
    sc_t5(vo,a,acs,as,dv,vf5,vo5,ve5,acs5,ace5,nct5,nsi5,ti5,vi5,si5,ai5);
    sc_t7(ve5,a,ace5,ace,dv,vf7,vo7,ve7,acs7,ace7,nct7,nsi7,ti7,vi7,si7,ai7);

    double vt2= (vo-ve) - ((vo5-ve5)+(vo7-ve7));

    //! Curve can not reach as, t1 has ace, t3 has acs.
    if(vt2<0){
        //! std::cout<<"curve can not reach as"<<std::endl;
        sc_t5_ve(vo,vh,a,acs,dv,vf5,vo5,ve5,acs5,ace5,nct5,nsi5,ti5,vi5,si5,ai5);
        sc_t7(ve5,a,ace5,ace,dv,vf7,vo7,ve7,acs7,ace7,nct7,nsi7,ti7,vi7,si7,ai7);

        pvec.push_back({period_id::t5,vo5,ve5,acs5,ace5,nct5,nsi5});
        pvec.push_back({period_id::t7,vo7,ve7,acs7,ace7,nct7,nsi7});
    }
    //! Curve = dv.
    if(vt2==0){
        //! std::cout<<"curve = dv"<<std::endl;
        pvec.push_back({period_id::t5,vo5,ve5,acs5,ace5,nct5,nsi5});
        pvec.push_back({period_id::t7,vo7,ve7,acs7,ace7,nct7,nsi7});
    }
    //! Curve needs t2.
    if(vt2>0){
        //! std::cout<<"curve incl. t2"<<std::endl;
        sc_t6(ve5,ve5-vt2,ace5,vo6,ve6,acs6,ace6,nct6,nsi6,ti6,vi6,si6,ai6);
        sc_t7(ve6,a,ace6,ace,dv,vf7,vo7,ve7,acs7,ace7,nct7,nsi7,ti7,vi7,si7,ai7);

        pvec.push_back({period_id::t5,vo5,ve5,acs5,ace5,nct5,nsi5});
        pvec.push_back({period_id::t6,vo6,ve6,acs6,ace6,nct6,nsi6});
        pvec.push_back({period_id::t7,vo7,ve7,acs7,ace7,nct7,nsi7});
    }
}

void sc::build_t7(double vo, double acs, double &ve){

    double vf7=0,vo7=0,ve7=0,acs7=0,ace7=0,nct7=0,nsi7=0,ti7=0,vi7=0,si7=0,ai7=0;
    double ace=0;
    sc_t7(vo,a,acs,ace,dv,vf7,vo7,ve,acs7,ace7,nct7,nsi7,ti7,vi7,si7,ai7);
    pvec.push_back({period_id::t7,vo7,ve7,acs7,ace7,nct7,nsi7});
}

void sc::build_t6_stitch(double vo, double s, double a){

    double t=0,ve=0;
    t= abs( (-vo + sqrt(vo*vo - 2*a*s)) / a);
    ve=vo - a*t;
    ve_stitch={period_id::t6,vo,ve,a,a,t,s};
}

void sc::build_t4_period(double vo, double s){

    double vo4=0,ve4=0,acs4=0,ace4=0,nct4=0,nsi4=0,ti4=0,vi4=0,si4=0,ai4=0;

    sc_t4(vo,s,vo4,ve4,acs4,ace4,nct4,nsi4,ti4,vi4,si4,ai4);

    pvec.push_back({period_id::t4,vo4,ve4,acs4,ace4,nct4,nsi4});
}

double sc::bruto_curve_time(){
    double t=0;
    for(uint i=0; i<pvec.size(); i++){
        t+=pvec.at(i).nct;
    }
    return t;
}

double sc::netto_curve_time(){
    return bruto_curve_time()-cte_del;
}

double sc::stitch_time(){
    return ve_stitch.nct;
}

double sc::stitch_displacement(){
    return ve_stitch.nsi;
}

double sc::bruto_curve_displacement(){
    double s=0;
    for(uint i=0; i<pvec.size(); i++){
        s+=pvec.at(i).nsi;
    }
    return s;
}

double sc::netto_curve_displacement(){
    return bruto_curve_displacement()-ste_del;
}

void sc::bruto_interpolate(double at_time, double &vi, double &si, double &ai, period_id &id){

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
                id=period_id::t1;
            }
            if(pvec.at(i).id==period_id::t2){
                sc_t2(pvec.at(i).vo,
                      pvec.at(i).ve,
                      pvec.at(i).acs,
                      vo,ve,acs,ace,nct,nsi,ti,vi,si,ai);
                id=period_id::t2;
            }
            if(pvec.at(i).id==period_id::t3){
                sc_t3(pvec.at(i).vo,
                      a,
                      pvec.at(i).acs,
                      pvec.at(i).ace,
                      dv,
                      vf,vo,ve,acs,ace,nct,nsi,ti,vi,si,ai);
                id=period_id::t3;
            }
            if(pvec.at(i).id==period_id::t4){
                sc_t4(pvec.at(i).vo,
                      pvec.at(i).nsi,
                      vo,ve,acs,ace,nct,nsi,ti,vi,si,ai);
                id=period_id::t4;
            }
            if(pvec.at(i).id==period_id::t5){
                sc_t5(pvec.at(i).vo,
                      a,
                      pvec.at(i).acs,
                      pvec.at(i).ace,
                      dv,
                      vf,vo,ve,acs,ace,nct,nsi,ti,vi,si,ai);
                id=period_id::t5;
            }
            if(pvec.at(i).id==period_id::t6){
                sc_t6(pvec.at(i).vo,
                      pvec.at(i).ve,
                      pvec.at(i).acs,
                      vo,ve,acs,ace,nct,nsi,ti,vi,si,ai);
                id=period_id::t6;
            }
            if(pvec.at(i).id==period_id::t7){
                sc_t7(pvec.at(i).vo,
                      a,
                      pvec.at(i).acs,
                      pvec.at(i).ace,
                      dv,
                      vf,vo,ve,acs,ace,nct,nsi,ti,vi,si,ai);
                id=period_id::t7;
            }

            si+=sf;
        }
    }
}

void sc::plot_bruto(double interval,
                    std::vector<double> &vvec,
                    std::vector<double> &svec,
                    std::vector<double> &avec){

    double vi=0, si=0, ai=0;
    period_id id;
    for(double t=0; t<=bruto_curve_time(); t+=interval){
        bruto_interpolate(t,vi,si,ai,id);
        vvec.push_back(vi);
        svec.push_back(si);
        avec.push_back(ai);
    }
}

void sc::print_bruto_journal(){

    std::cout<<std::endl;
    std::cout<<"print journal:"<<std::endl;

    for(uint i=0; i<pvec.size(); i++){
        std::cout<<std::fixed
                <<" id:"<<print_period_id(pvec.at(i).id)
               <<" vo:"<<pvec.at(i).vo
              <<" ve:"<<pvec.at(i).ve
             <<" acs:"<<pvec.at(i).acs
            <<" ace:"<<pvec.at(i).ace
           <<" nsi:"<<pvec.at(i).nsi
          <<" nct:"<<pvec.at(i).nct<<std::endl;
    }
    std::cout<<std::fixed<<"ttot:"<<bruto_curve_time()<<std::endl;
    std::cout<<std::fixed<<"stot:"<<bruto_curve_displacement()<<std::endl;
    std::cout<<std::fixed<<"jm:"<<jm()<<std::endl;
    std::cout<<std::endl;
}

std::string sc::print_period_id(period_id id){
    if(id==period_id::none){
        return "period none";
    }
    if(id==period_id::t1){
        return "period t1";
    }
    if(id==period_id::t2){
        return "period t2";
    }
    if(id==period_id::t3){
        return "period t3";
    }
    if(id==period_id::t4){
        return "period t4";
    }
    if(id==period_id::t5){
        return "period t5";
    }
    if(id==period_id::t6){
        return "period t6";
    }
    if(id==period_id::t7){
        return "period t7";
    }
    return "period error";
}

void sc::print_bruto_interpolation(double interval){

    double vi=0, si=0, ai=0;
    period_id id=period_id::none;
    std::cout<<std::endl;
    std::cout<<"print interpolation:"<<std::endl;

    for(double t=0; t<=bruto_curve_time(); t+=interval){
        bruto_interpolate(t,vi,si,ai,id);
        std::cout<<std::fixed
                <<" id:"<<print_period_id(id)
               <<" t:"<<t
              <<" v:"<<vi
             <<" s:"<<si
            <<" a:"<<ai
           <<std::endl;
    }

    //! Absolute end.
    bruto_interpolate(bruto_curve_time(),vi,si,ai,id);
    std::cout<<std::fixed
            <<" id:"<<print_period_id(id)
           <<" t:"<<bruto_curve_time()
          <<" v:"<<vi
         <<" s:"<<si
        <<" a:"<<ai
       <<std::endl;

    std::cout<<std::endl;
}

double sc::build_t1_t2_t3_t5_t6_t7(double vo,
                                   double vm,
                                   double ve,
                                   double acs,
                                   double ace){
    pvec.clear();

    if(acs<0){ //! Neutralize negative acc to zero.
        //! Build a t7.
        build_t7(vo,acs,vo);
        acs=0; //! Reset for next build items.
    }

    if(vo==vm && ve==vm){
        //construct_t4_period(vm,l);
    }
    if(vo<vm && ve==vm){
        build_t1_t2_t3(vo,vm,acs,0);
        //construct_t4_period(vm,l);
    }
    if(vo>vm && ve==vm){
        build_t5_t6_t7(vo,vm,acs,0);
        //construct_t4_period(vm,l);
    }
    if(vo==vm && ve<vm){
        //construct_t4_period(vm,l);
        build_t5_t6_t7(vm,ve,0,ace);
    }
    if(vo==vm && ve>vm){
        //construct_t4_period(vm,l);
        build_t1_t2_t3(vm,ve,0,ace);
    }
    if(vo<vm && ve<vm){
        build_t1_t2_t3(vo,vm,acs,0);
        //construct_t4_period(vm,l);
        build_t5_t6_t7(vm,ve,0,ace);
    }
    if(vo<vm && ve>vm){
        build_t1_t2_t3(vo,vm,acs,0);
        //construct_t4_period(vm,l);
        build_t1_t2_t3(vm,ve,0,ace);
    }
    if(vo>vm && ve<vm){
        build_t5_t6_t7(vo,vm,acs,0);
        //construct_t4_period(vm,l);
        build_t5_t6_t7(vm,ve,0,ace);
    }
    if(vo>vm && ve>vm){
        build_t5_t6_t7(vo,vm,acs,0);
        //construct_t4_period(vm,l);
        build_t1_t2_t3(vm,ve,0,ace);
    }
    return bruto_curve_displacement();
}

double sc::build_t1_t2_t3_t4_t5_t6_t7(double vo,
                                      double vm,
                                      double ve,
                                      double acs,
                                      double ace,
                                      double s4){
    pvec.clear();

    if(acs<0){ //! Neutralize negative acc to zero.
        //! Build a t7.
        build_t7(vo,acs,vo);
        acs=0; //! Reset for next build items.
    }

    if(vo==vm && ve==vm){
        build_t4_period(vm,s4);
    }
    if(vo<vm && ve==vm){
        build_t1_t2_t3(vo,vm,acs,0);
        build_t4_period(vm,s4);
    }
    if(vo>vm && ve==vm){
        build_t5_t6_t7(vo,vm,acs,0);
        build_t4_period(vm,s4);
    }
    if(vo==vm && ve<vm){
        build_t4_period(vm,s4);
        build_t5_t6_t7(vm,ve,0,ace);
    }
    if(vo==vm && ve>vm){
        build_t4_period(vm,s4);
        build_t1_t2_t3(vm,ve,0,ace);
    }
    if(vo<vm && ve<vm){
        build_t1_t2_t3(vo,vm,acs,0);
        build_t4_period(vm,s4);
        build_t5_t6_t7(vm,ve,0,ace);
    }
    if(vo<vm && ve>vm){
        build_t1_t2_t3(vo,vm,acs,0);
        build_t4_period(vm,s4);
        build_t1_t2_t3(vm,ve,0,ace);
    }
    if(vo>vm && ve<vm){
        build_t5_t6_t7(vo,vm,acs,0);
        build_t4_period(vm,s4);
        build_t5_t6_t7(vm,ve,0,ace);
    }
    if(vo>vm && ve>vm){
        build_t5_t6_t7(vo,vm,acs,0);
        build_t4_period(vm,s4);
        build_t1_t2_t3(vm,ve,0,ace);
    }
    return bruto_curve_displacement();
}

void sc::construct_motion(double vo,
                          double vm,
                          double ve,
                          double acs,
                          double ace,
                          double s){

    double sc=build_t1_t2_t3_t5_t6_t7(vo,vm,ve,acs,ace);
    double new_vm=vm;

    cte_del=0;

    //! Ok, finish.
    if(sc==s){
        return;
    }

    //! Need t4, steady period.
    if(sc<s){
        sc=build_t1_t2_t3_t4_t5_t6_t7(vo,vm,ve,acs,ace,s-sc);
        if(sc==s){ //! Succes.
            return;
        }
    }

    if(sc>s){
        if(vo<vm && ve<vm){ //! Sample down.
            double v=vo;
            if(ve>vo){
                v=ve;
            }
            for(new_vm=vm; new_vm>v; new_vm-=0.1){
                sc=build_t1_t2_t3_t5_t6_t7(vo,new_vm,ve,acs,ace);
                if(sc<s){
                    sc=build_t1_t2_t3_t4_t5_t6_t7(vo,new_vm,ve,acs,ace,s-sc);
                    break;
                }
            }
        }
        if(vo>vm && ve>vm){ //! Sample up
            double v=vo;
            if(ve<vo){
                v=ve;
            }
            for(new_vm=vm; new_vm<v; new_vm+=0.1){
                sc=build_t1_t2_t3_t5_t6_t7(vo,new_vm,ve,acs,ace);
                if(sc<s){
                    sc=build_t1_t2_t3_t4_t5_t6_t7(vo,new_vm,ve,acs,ace,s-sc);
                    break;
                }
            }
        }
        if(sc==s){ //! Succes.
            return;
        }
    }

    if(sc>s){
        // std::cout<<"At this stage sc>s, output custom ve at s."<<std::endl;

        double vi=0, si=0, ai=0, t=0;
        period_id id=period_id::none;

        //! Interpolate back.
        for(t=bruto_curve_time(); t>0; t-=0.001){
            bruto_interpolate(t,vi,si,ai,id);
            if(si<s){
                std::cout<<"stopping curve at time :"<<t<<" s:"<<si<<std::endl;
                break;
            }
        }
        cte_del = bruto_curve_time()-t;
        ste_del = bruto_curve_displacement()-si;

        //! Create ve_stitch to absolute s.
        if(vi<ve){
            build_t2_stitch(vi,s-si,ai);
        }
        if(vi>ve){
            build_t6_stitch(vi,s-si,ai);
        }
        if(vi==ve){
            build_t4_stitch(vi,s-si);
        }
        //! std::cout<<"stitch displacement:"<<stitch_displacement()<<std::endl;
        //! std::cout<<"stitch id:"<<print_period_id(ve_stitch.id)<<std::endl;
        //! std::cout<<"stitch vo:"<<ve_stitch.vo<<std::endl;
        //! std::cout<<"stitch ve:"<<ve_stitch.ve<<std::endl;
        //! std::cout<<"stitch nct:"<<ve_stitch.nct<<std::endl;
        //! std::cout<<"stitch nsi:"<<ve_stitch.nsi<<std::endl;
        return;
    }
}

double sc::curve_time(){
    return (bruto_curve_time()-cte_del)+stitch_time();
}

double sc::curve_displacement(){
    return (bruto_curve_displacement()-ste_del)+stitch_displacement();
}

void sc::stitch_interpolate(double at_time,
                            double &vi,
                            double &si,
                            double &ai,
                            period_id &id){

    double vo=ve_stitch.vo;
    double t=at_time;
    ai=ve_stitch.acs;
    id=ve_stitch.id;

    if(id==period_id::t2){
        vi=vo + a*t;
        si=vo*t + 0.5*a*(t*t);
    }
    if(id==period_id::t6){
        vi=vo - a*t;
        si=vo*t - 0.5*a*(t*t);
    }
}

void sc::interpolate(double at_time, double &vi, double &si, double &ai, period_id &id){

    if(at_time<=netto_curve_time()){
        bruto_interpolate(at_time,vi,si,ai,id);
    }
    if(at_time>netto_curve_time()){
        at_time-=netto_curve_time();

        stitch_interpolate(at_time,vi,si,ai,id);
        si+=netto_curve_displacement();
    }
}

void sc::plot(double interval,
              std::vector<double> &vvec,
              std::vector<double> &svec,
              std::vector<double> &avec){

    double vi=0, si=0, ai=0;
    period_id id;
    for(double t=0; t<=curve_time(); t+=interval){
        interpolate(t,vi,si,ai,id);
        vvec.push_back(vi);
        svec.push_back(si);
        avec.push_back(ai);
    }
}

void sc::print_interpolation(double interval){

    double vi=0, si=0, ai=0;
    period_id id=period_id::none;
    std::cout<<std::endl;
    std::cout<<"print interpolation:"<<std::endl;

    for(double t=0; t<=curve_time(); t+=interval){
        interpolate(t,vi,si,ai,id);
        std::cout<<std::fixed
                <<" id:"<<print_period_id(id)
               <<" t:"<<t
              <<" v:"<<vi
             <<" s:"<<si
            <<" a:"<<ai
           <<std::endl;
    }

    //! Absolute end.
    interpolate(curve_time(),vi,si,ai,id);
    std::cout<<std::fixed
            <<" id:"<<print_period_id(id)
           <<" t:"<<curve_time()
          <<" v:"<<vi
         <<" s:"<<si
        <<" a:"<<ai
       <<std::endl;

    std::cout<<std::endl;
}






























