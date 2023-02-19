
#include <sc.h>
#include <cmath>

//! Author  : SKynet Cyberdyne
//! Licence : GPL2
//! Data    : 2023

//! Legenda of used variables:
//!
//! vo  velocity start.
//! ve  velocity end.
//! vf  velocity front of curve. ts=0.
//! ts  time start.
//! te  time end.
//! th  time half.
//! t   time.
//! a   acceleration.
//! as  acceleration at inflection point, 2*a.
//! acs acceleration start.
//! ace acceleration end.
//! dv  velocity delta value from 0 to 2*a to 0. (determines curve power)
//! ti  time interpolation request.
//! vi  velocity interpolation.
//! si  displacement interpolation.
//! ai  acceleration interpolation.
//! ct  curve time.
//! nct netto curve time.
//! nsi netto displacement.
//! sf  displacement at t=0.
//! so  displacement at ts.
//! se  displacement at ct.

// search for bugfix in code to see bugfixes.

//! Returns curve displacement, fast algo.
double sc::sc_t1_fast_s(double vo, double a, double acs, double ace, double dv){

    //! Internals:
    double ct=0;
    double jm=0;
    double as=0;
    double t=0;
    double ts=0;
    double te=0;
    double so=0;
    double se=0;
    double vf_=0;

    ct=dv/a;
    as=2*a;
    jm=2*as/ct;

    acs=abs(acs);
    if(acs>as){
        acs=as;
    }
    ace=abs(ace);
    if(ace>as){
        ace=as;
    }

    ts=acs/jm;
    t=ts;
    vf_=vo-(jm*(t*t)/2);
    so=vf_*t+jm*(t*t*t)/6;

    te=ace/jm;
    t=te;
    se=vf_*t+jm*(t*t*t)/6;

    return se-so;
}

void sc::sc_t1(double vo, double a, double acs, double ace, double dv,
               double &vf_, double &vo_, double &ve_, double &acs_, double &ace_,
               double &nct_, double &nsi_, double ti_, double &vi_, double &si_, double &ai_){

    //! Internals:
    double ct=0;
    double jm=0;
    double as=0;
    double t=0;
    double ts=0;
    double te=0;
    double sf=0;
    double so=0;
    double se=0;


    ai_=0;

    ct=dv/a;
    as=2*a;
    jm=2*as/ct;

    acs=abs(acs);
    if(acs>as){
        acs=as;
    }
    ace=abs(ace);
    if(ace>as){
        ace=as;
    }

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
    double ts=0;
    double te=0;
    double sf=0, so=0, se=0;

    ai_=0;

    ct=dv/a;
    as=2*a;
    jm=2*as/ct;

    acs=abs(acs);
    if(acs>as){
        acs=as;
    }

    ts=acs/jm;
    t=ts;
    vf_=vo-(jm*(t*t)/2);

    t=0;
    sf=vf_*t+jm*(t*t*t)/6;

    t=ts;
    so=vf_*t+jm*(t*t*t)/6;

    te=sqrt(-2*vf_+2*ve)/sqrt(jm);
    // bugfix, te can exceed 0.5*ct some how.
    if(te>0.5*ct){
        te=0.5*ct;
    }
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
    ace_=jm*te;
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
    double ts=0;
    double te=0;
    double sf=0, so=0, se=0;

    ct=dv/a;
    as=2*a;
    jm=2*as/ct;

    acs=abs(acs);
    if(acs>as){
        acs=as;
    }
    ace=abs(ace);
    if(ace>as){
        ace=as;
    }

    if(ace>acs){ // bugfix.
        ace=acs;
        std::cerr<<"t3 ace>acs"<<std::endl;
    }

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
    ai_=as-(jm*t);

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
    as=2*a;
    jm=2*as/ct;

    acs=abs(acs);
    if(acs>as){
        acs=as;
    }
    ace=abs(ace);
    if(ace>as){
        ace=as;
    }

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
    double ts=0;
    double te=0;
    double sf=0, so=0, se=0;

    ct=dv/a;
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

    t=0;
    sf=vf_*t-jm*(t*t*t)/6;

    te= (sqrt(2)*sqrt(vf_-ve))/sqrt(jm);

    // bugfix, te can exceed 0.5*ct some how.
    if(te>0.5*ct){
        te=0.5*ct;
    }

    t=te;
    ace=-abs(jm*t);
    ve=vf_-jm*(t*t)/2; // bugfix, added ve forumula.
    se=vf_*t-jm*(t*t*t)/6;

    t=ti_+ts;
    vi_=vf_-jm*(t*t)/2;
    si_=vf_*t-jm*(t*t*t)/6;
    si_-=so-sf;
    ai_=-abs(jm*t);

    nct_=te-ts;
    nsi_=se-so;
    vo_=vo;
    t=te;
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
    double ts=0;
    double te=0;
    double sf=0, so=0, se=0;

    ct=dv/a;
    as=2*a;
    jm=2*as/ct;

    acs=abs(acs);
    if(acs>as){
        acs=as;
    }
    ace=abs(ace);
    if(ace>as){
        ace=as;
    }

    if(ace>acs){ // bugfix.
        ace=acs;
        std::cerr<<"t7 ace>acs"<<std::endl;
    }
    //    if(acs<ace){ // bugfix.
    //        acs=ace;
    //        std::cerr<<"t7 acs<ace"<<std::endl;
    //    }

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

sc::sc()
{

}

void sc::set(double theA,
             double theDv){

    if(theDv==0){
        std::cerr<<"dv=0"<<std::endl;
    }
    if(theA==0){
        std::cerr<<"a=0"<<std::endl;
    }
    a=theA;
    dv=theDv;
    as=2*theA;
}

double sc::jm(){
    double ct=dv/a;
    double as=2*a;
    double jm=2*as/ct;
    return jm;
}

double sc::build_t1_t2_t3(double vo, double ve, double acs, double ace, double &ve_, bool push_back){

    double l=0;
    double ace_=0;

    //! Calculation pre process to find out t2.
    build_t1_ve(vo,((ve-vo)/2)+vo,acs,ace_,ve_,false);
    build_t3(ve_,ace_,ace,ve_,false);

    double to_ve=ve-ve_;
    if(to_ve<0){
        to_ve=0;
    }

    l+=build_t1_ve(vo,((ve-vo)/2)+vo,acs,ace_,ve_,push_back);
    l+=build_t2(ve_,ve_+to_ve,ace_,ve_,push_back);
    l+=build_t3(ve_,ace_,ace,ve_,push_back);

    return l;
}

double sc::build_t7_t1_t2_t3(double vo, double ve, double acs, double ace, double &ve_, bool push_back){

    double l=0;

    if(acs<0){
        l+=build_t7(vo,acs,0,ve_,push_back);
        l+=build_t1_t2_t3(ve_,ve,0,ace,ve_,push_back);
    } else {
        l+=build_t1_t2_t3(vo,ve,acs,ace,ve_,push_back);
    }

    return l;
}

double sc::build_t1_t2_t3_t5(double vo, double ve, double acs, double ace, double &ve_, bool push_back){

    double l=0;

    if(ace<0){
        //! Preprocess.
        build_t1_t2_t3(vo,ve,acs,0,ve_,false);
        build_t5(ve_,0,ace,ve_,false);
        double to_ve=ve-ve_;
        l+=build_t1_t2_t3(vo,ve+to_ve,acs,0,ve_,push_back);
        l+=build_t5(ve_,0,ace,ve_,push_back);

    }
    if(ace>=0){
        l+=build_t1_t2_t3(vo,ve,acs,ace,ve_,push_back);
    }

    return l;
}

double sc::build_t1(double vo, double acs, double ace, double &ve_, bool push_back){

    double vf1=0,vo1=0,acs1=0,ace1=0,nct1=0,nsi1=0, ti1=0,vi1=0,si1=0,ai1=0;
    sc_t1(vo,a,acs,ace,dv,vf1,vo1,ve_,acs1,ace1,nct1,nsi1,ti1,vi1,si1,ai1);
    if(push_back){
        pvec.push_back({period_id::t1,vo1,ve_,acs1,ace1,nct1,nsi1});
    }
    return nsi1;
}

//! Curve ve is limeted to dv.
double sc::build_t1_ve(double vo, double ve, double acs, double &ace_, double &ve_, bool push_back){

    double vf1=0,vo1=0,acs1=0,nct1=0,nsi1=0, ti1=0,vi1=0,si1=0,ai1=0;
    sc_t1_ve(vo,ve,a,acs,dv,vf1,vo1,ve_,acs1,ace_,nct1,nsi1,ti1,vi1,si1,ai1);
    if(push_back){
        pvec.push_back({period_id::t1,vo1,ve_,acs1,ace_,nct1,nsi1});
    }
    return nsi1;
}

double sc::build_t2(double vo, double ve, double a,  double &ve_, bool push_back){

    double vo2=0,acs2=0,ace2=0,nct2=0,nsi2=0, ti2=0,vi2=0,si2=0,ai2=0;
    sc_t2(vo,ve,a,vo2,ve_,acs2,ace2,nct2,nsi2,ti2,vi2,si2,ai2);
    if(push_back){
        pvec.push_back({period_id::t2,vo2,ve_,acs2,ace2,nct2,nsi2});
    }
    return nsi2;
}

double sc::build_t3(double vo, double acs, double ace, double &ve_, bool push_back){

    double vf3=0,vo3=0,acs3=0,ace3=0,nct3=0,nsi3=0, ti3=0,vi3=0,si3=0,ai3=0;
    sc_t3(vo,a,acs,ace,dv,vf3,vo3,ve_,acs3,ace3,nct3,nsi3,ti3,vi3,si3,ai3);
    if(push_back){
        pvec.push_back({period_id::t3,vo3,ve_,acs3,ace3,nct3,nsi3});
    }
    return nsi3;
}

void sc::build_t2_stitch(double vo, double s, double a){

    double t=0,ve=0;
    t= abs( (-vo + sqrt(vo*vo - 2*a*s)) / a);
    ve=vo + a * t;
    ve_stitch={period_id::t2,vo,ve,a,a,t,s};
}

void sc::build_t4_stitch(double vo, double s){

    ve_stitch={period_id::t4,vo,vo,0,0,s/vo,s};
}

double sc::build_t5_t6_t7(double vo, double ve, double acs, double ace, double &ve_, bool push_back){

    double ace_=0;
    double l=0;

    build_t5_ve(vo,vo-((vo-ve)/2),acs,ace_,ve_,false);
    build_t7(ve_,ace_,ace,ve_,false);
    double to_ve=ve_-ve;
    if(to_ve<0){
        to_ve=0;
    }

    l+=build_t5_ve(vo,vo-((vo-ve)/2),acs,ace_,ve_,push_back);
    l+=build_t6(ve_,ve_-to_ve,ace_,ve_,push_back);
    l+=build_t7(ve_,ace_,ace,ve_,push_back);
    return l;
}

double sc::build_t5_t6_t7_t1(double vo, double ve, double acs, double ace, double &ve_, bool push_back){

    double l=0;
    if(ace<0){
        l+=build_t5_t6_t7(vo,ve,acs,ace,ve_,push_back);
    } else {
        //! Preprocess.
        build_t5_t6_t7(vo,ve,acs,0,ve_,false);
        build_t1(ve_,0,ace,ve_,false);
        double to_ve=ve_-ve;
        //! Write.
        l+=build_t5_t6_t7(vo,ve-to_ve,acs,0,ve_,push_back);
        l+=build_t1(ve_,0,ace,ve_,push_back);
    }
    return l;
}

double sc::build_t3_t5_t6_t7_t1(double vo, double ve, double acs, double ace, double &ve_, bool push_back){

    double l=0;
    if(acs>0){
        build_t3(vo,acs,0,ve_,push_back);
        if(ace<0){
            l+=build_t5_t6_t7(ve_,ve,0,ace,ve_,push_back);
        } else {
            //! Preprocess.
            double v=ve_;
            build_t5_t6_t7(v,ve,0,0,v,false);
            build_t1(v,0,ace,v,false);
            double to_ve=v-ve;
            //! Write.
            l+=build_t5_t6_t7(ve_,ve-to_ve,0,0,ve_,push_back);
            l+=build_t1(ve_,0,ace,ve_,push_back);
        }
    }

    if(acs<=0){
        if(ace<0){
            l+=build_t5_t6_t7(vo,ve,acs,ace,ve_,push_back);
        } else {
            //! Preprocess.
            build_t5_t6_t7(vo,ve,acs,0,ve_,false);
            build_t1(ve_,0,ace,ve_,false);
            double to_ve=ve_-ve;
            //! Write.
            l+=build_t5_t6_t7(vo,ve-to_ve,acs,0,ve_,push_back);
            l+=build_t1(ve_,0,ace,ve_,push_back);
        }
    }
    return l;
}

double sc::build_t3_t5_t6_t7(double vo, double ve, double acs, double ace, double &ve_, bool push_back){

    double l=0;
    if(acs<0){
        l+=build_t5_t6_t7(vo,ve,acs,ace,ve_,push_back);
    } else {
        l+=build_t3(vo,acs,0,ve_,push_back);
        l+=build_t5_t6_t7(ve_,ve,0,ace,ve_,push_back);
    }
    return l;
}

//! Curve ve is limeted to dv.
double sc::build_t5_ve(double vo, double ve, double acs, double &ace_, double &ve_, bool push_back){

    double vf5=0,vo5=0,ve5=0,acs5=0,nct5=0,nsi5=0,ti5=0,vi5=0,si5=0,ai5=0;
    sc_t5_ve(vo,ve,a,acs,dv,vf5,vo5,ve5,acs5,ace_,nct5,nsi5,ti5,vi5,si5,ai5);
    if(push_back){
        pvec.push_back({period_id::t5,vo5,ve5,acs5,ace_,nct5,nsi5});
    };
    ve_=ve5;
    return nsi5;
}

double sc::build_t5(double vo, double acs, double ace, double &ve_, bool push_back){

    double vf5=0,vo5=0,acs5=0,ace5=0,nct5=0,nsi5=0,ti5=0,vi5=0,si5=0,ai5=0;
    sc_t5(vo,a,acs,ace,dv,vf5,vo5,ve_,acs5,ace5,nct5,nsi5,ti5,vi5,si5,ai5);
    if(push_back){
        pvec.push_back({period_id::t5,vo5,ve_,acs5,ace5,nct5,nsi5});
    }
    return nsi5;
}

double sc::build_t6(double vo, double ve, double a,  double &ve_, bool push_back){

    double vo6=0,acs6=0,ace6=0,nct6=0,nsi6=0, ti6=0,vi6=0,si6=0,ai6=0;
    sc_t6(vo,ve,a,vo6,ve_,acs6,ace6,nct6,nsi6,ti6,vi6,si6,ai6);
    if(push_back){
        pvec.push_back({period_id::t6,vo6,ve_,acs6,ace6,nct6,nsi6});
    }
    return nsi6;
}

double sc::build_t7(double vo, double acs, double ace, double &ve_, bool push_back){

    double vf7=0,vo7=0,ve7=0,acs7=0,ace7=0,nct7=0,nsi7=0,ti7=0,vi7=0,si7=0,ai7=0;
    sc_t7(vo,a,acs,ace,dv,vf7,vo7,ve7,acs7,ace7,nct7,nsi7,ti7,vi7,si7,ai7);
    if(push_back){
        pvec.push_back({period_id::t7,vo7,ve7,acs7,ace7,nct7,nsi7});
    }
    ve_=ve7;
    return nsi7;
}

void sc::build_t6_stitch(double vo, double s, double a){

    double t=0,ve=0;
    t= abs( (-vo + sqrt(vo*vo - 2*a*s)) / a);
    ve=vo - a*t;
    ve_stitch={period_id::t6,vo,ve,a,a,t,s};
}

double sc::build_t4_period(double vo, double s, bool push_back){

    double vo4=0,ve4=0,acs4=0,ace4=0,nct4=0,nsi4=0,ti4=0,vi4=0,si4=0,ai4=0;

    sc_t4(vo,s,vo4,ve4,acs4,ace4,nct4,nsi4,ti4,vi4,si4,ai4);

    if(push_back){
        pvec.push_back({period_id::t4,vo4,ve4,acs4,ace4,nct4,nsi4});
    }
    return nsi4;
}

double sc::vo_ve_time(){
    double t=0;
    for(uint i=0; i<pvec.size(); i++){
        t+=pvec.at(i).nct;
    }
    return t;
}

double sc::s_time_excl_stitch(){
    return vo_ve_time()-cte_del;
}

double sc::stitch_time(){
    return ve_stitch.nct;
}

double sc::stitch_displacement(){
    return ve_stitch.nsi;
}

double sc::vo_ve_displacement(){
    double s=0;
    for(uint i=0; i<pvec.size(); i++){
        s+=pvec.at(i).nsi;
    }
    return s;
}

double sc::s_displacement_excl_stitch(){
    return vo_ve_displacement()-ste_del;
}

void sc::vo_ve_interpolate(double at_time, double &vi, double &si, double &ai, period_id &id){

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

void sc::vo_ve_plot(double interval,
                    std::vector<double> &vvec,
                    std::vector<double> &svec,
                    std::vector<double> &avec){

    double vi=0, si=0, ai=0;
    period_id id;
    for(double t=0; t<=vo_ve_time(); t+=interval){
        vo_ve_interpolate(t,vi,si,ai,id);
        vvec.push_back(vi);
        svec.push_back(si);
        avec.push_back(ai);
    }
}

void sc::vo_ve_print_journal(){

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
    std::cout<<std::fixed<<"ttot:"<<vo_ve_time()<<std::endl;
    std::cout<<std::fixed<<"stot:"<<vo_ve_displacement()<<std::endl;
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

void sc::vo_ve_print_interpolation(double interval){

    double vi=0, si=0, ai=0;
    period_id id=period_id::none;
    std::cout<<std::endl;
    std::cout<<"print interpolation:"<<std::endl;

    for(double t=0; t<=vo_ve_time(); t+=interval){
        vo_ve_interpolate(t,vi,si,ai,id);
        std::cout<<std::fixed
                <<" id:"<<print_period_id(id)
               <<" t:"<<t
              <<" v:"<<vi
             <<" s:"<<si
            <<" a:"<<ai
           <<std::endl;
    }

    //! Absolute end.
    vo_ve_interpolate(vo_ve_time(),vi,si,ai,id);
    std::cout<<std::fixed
            <<" id:"<<print_period_id(id)
           <<" t:"<<vo_ve_time()
          <<" v:"<<vi
         <<" s:"<<si
        <<" a:"<<ai
       <<std::endl;

    std::cout<<std::endl;
}

double sc::s_curve_time(){
    return (vo_ve_time()-cte_del)+stitch_time();
}

double sc::s_curve_displacement(){
    return (vo_ve_displacement()-ste_del)+stitch_displacement();
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
    if(id==period_id::t4){
        vi=vo;
        si=vo*t;
    }
}

void sc::s_interpolate(double at_time, double &vi, double &si, double &ai, period_id &id){

    if(at_time<=s_time_excl_stitch()){
        vo_ve_interpolate(at_time,vi,si,ai,id);
    }
    if(at_time>s_time_excl_stitch()){
        at_time-=s_time_excl_stitch();

        stitch_interpolate(at_time,vi,si,ai,id);
        si+=s_displacement_excl_stitch();
    }
}

void sc::s_plot(double interval,
                std::vector<double> &vvec,
                std::vector<double> &svec,
                std::vector<double> &avec){

    double vi=0, si=0, ai=0;
    period_id id;
    for(double t=0; t<=s_curve_time(); t+=interval){
        s_interpolate(t,vi,si,ai,id);
        vvec.push_back(vi);
        svec.push_back(si);
        avec.push_back(ai);
    }
}

void sc::s_print_interpolation(double interval){

    double vi=0, si=0, ai=0;
    period_id id=period_id::none;
    std::cout<<std::endl;
    std::cout<<"print interpolation:"<<std::endl;

    for(double t=0; t<=s_curve_time(); t+=interval){
        s_interpolate(t,vi,si,ai,id);
        std::cout<<std::fixed
                <<" id:"<<print_period_id(id)
               <<" t:"<<t
              <<" v:"<<vi
             <<" s:"<<si
            <<" a:"<<ai
           <<std::endl;
    }

    //! Absolute end.
    s_interpolate(s_curve_time(),vi,si,ai,id);
    std::cout<<std::fixed
            <<" id:"<<print_period_id(id)
           <<" t:"<<s_curve_time()
          <<" v:"<<vi
         <<" s:"<<si
        <<" a:"<<ai
       <<std::endl;

    std::cout<<std::endl;
}

void sc::preprocess(double vo,
                    double vm,
                    double ve,
                    double acs,
                    double ace,
                    double s){

    bool pb=false;
    double l=0;
    double lf=0;
    double ve_=0;
    pvec.clear();

    if(vo==vm && ve==vm){
        //! t4.
        build_t4_period(vo,s,pb);
    }
    if(vo<vm && ve==vm){
        l+=build_t7_t1_t2_t3(vo,vm,acs,0,ve_,pb);
        //! t4.
    }
    if(vo>vm && ve==vm){
        l+=build_t3_t5_t6_t7(vo,vm,acs,0,ve_,pb);
        //! t4.
    }
    if(vo==vm && ve<vm){
        //! t4.
        l+=build_t3_t5_t6_t7_t1(vo,ve,acs,ace,ve_,pb);
    }
    if(vo==vm && ve>vm){
        if(ace<0){
            l+=build_t7_t1_t2_t3(vo,ve,acs,0,ve_,pb);
            l+=build_t5(ve_,0,ace,ve_,pb);
        } else {
            l+=build_t7_t1_t2_t3(vo,ve,acs,ace,ve_,pb);
        }
    }
    //! working on.
    if(vo<vm && ve<vm){
        l=0;
        l+=build_t7_t1_t2_t3(vo,vm,acs,0,ve_,pb);
        l+=build_t5_t6_t7_t1(ve_,ve,0,ace,ve_,pb);

        //! Need t4.
        if(l<=s){
            //! std::cerr<<"need t4"<<std::endl;
            lf+=build_t7_t1_t2_t3(vo,vm,acs,0,ve_,true);
            lf+=build_t4_period(ve_,s-l,true);
            lf+=build_t5_t6_t7_t1(ve_,ve,0,ace,ve_,true);
        }
        if(l>s){
            //! std::cerr<<"need sampling down"<<std::endl;
            double l1=0, l2=0;
            for(double vms=vm; vms>(vo||ve); vms-=1.0){
                l1=build_t7_t1_t2_t3(vo,vms,acs,0,ve_,false);
                l2=build_t5_t6_t7_t1(ve_,ve,0,ace,ve_,false);
                if(l1+l2<s){
                    lf+=build_t7_t1_t2_t3(vo,vms,acs,0,ve_,true);
                    lf+=build_t4_period(ve_,s-(l1+l2),true);
                    lf+=build_t5_t6_t7_t1(ve_,ve,0,ace,ve_,true);
                    break;
                }
            }
        }
    }
    std::cout<<"lf:"<<lf<<std::endl;
    if(vo<vm && ve>vm){
        l+=build_t7_t1_t2_t3(vo,vm,acs,0,ve_,pb);
        //! t4.
        if(ve>ve_){
            l+=build_t1_t2_t3_t5(ve_,ve,0,ace,ve_,pb);
        }
    }
    if(vo>vm && ve<vm){
        l+=build_t3_t5_t6_t7(vo,vm,acs,0,ve_,pb);
        //! t4.
        if(ve<ve_){
            l+=build_t5_t6_t7_t1(ve_,ve,0,ace,ve_,pb);
        }
    }
    if(vo>vm && ve>vm){
        l+=build_t3_t5_t6_t7(vo,vm,acs,0,ve_,pb);
        //! t4.
        l+=build_t1_t2_t3_t5(ve_,ve,0,ace,ve_,pb);
    }
}

double max=0;
double tm=0;
void sc::build_motion(double vo,
                      double vm,
                      double ve,
                      double acs,
                      double ace,
                      double s){

    auto start = std::chrono::high_resolution_clock::now();

    preprocess(vo,vm,ve,acs,ace,s);
     preprocess(vo,vm,ve,acs,ace,s);
      preprocess(vo,vm,ve,acs,ace,s);
       preprocess(vo,vm,ve,acs,ace,s);
        preprocess(vo,vm,ve,acs,ace,s);
         preprocess(vo,vm,ve,acs,ace,s);
          preprocess(vo,vm,ve,acs,ace,s);
           preprocess(vo,vm,ve,acs,ace,s);
            preprocess(vo,vm,ve,acs,ace,s);

    auto end = std::chrono::high_resolution_clock::now();
    auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    tm=nanoseconds_to_milliseconds(nanoseconds.count());
    if(max<tm){
        max=tm;
    }

    std::cout<<std::fixed<<"function time:"<<max<<std::endl;


}




























