#ifndef SC_ENGINE_H
#define SC_ENGINE_H

#include <iostream>
#include <cmath>
#include <vector>
#include <sc_struct.h>

//! Scurve back end.
class sc_engine {
public:
    sc_engine(){};

    inline int t1_v(double vo, double acs, double ace, double &ve);

    inline int t1_s(double vo, double acs, double ace, double &ncs, double &nct);

    inline int t1_v_ve(double vo, double ve, double acs, double &ace, double &ve_);

    inline int t1_s_ve(double vo, double ve, double acs, double &ncs, double &nct);

    inline int t1_v_i(double vo, double acs, double ti, double &vi, double &ai);

    inline int t2_v(double ve, double &ve_);

    inline int t2_v_i(double ti, sc_period p, double &vi);

    inline int t2_s(double vo, double ve, double a, double &ncs, double &nct);

    inline int t3_v(double vo, double acs, double ace, double &ve);

    inline int t3_v_i(double ti, sc_period p, double &vi);

    inline int t3_s(double vo, double acs, double ace, double &ncs, double &nct);

    inline int t4_s(double vo, double s, double &ncs, double &nct);

    inline int t5_v(double vo, double acs, double ace, double &ve);

    inline int t5_s(double vo, double acs, double ace, double &ncs, double &nct);

    inline int t5_v_ve(double vo, double ve, double acs, double &ace, double &ve_);

    inline int t5_s_ve(double vo, double ve, double acs, double &ncs, double &nct);

    inline int t6_v(double ve, double &ve_);

    inline int t6_s(double vo, double ve, double a, double &ncs, double &nct);

    inline int t7_v(double vo, double acs, double ace, double &ve);

    inline int t7_s(double vo, double acs, double ace, double &ncs, double &nct);

    inline int t1_t2_t3_s(double vo, double ve, double acs, double ace, bool pb, double &ncs, double &nct);

    inline int t5_t6_t7_s(double vo, double ve, double acs, double ace, bool pb, double &ncs, double nct);

    void set_a_dv(double theA, double theDv);

    void set_acs_ace(double theAcs, double theAce);

    sc_status process_scurve(double vo,
                            double vm,
                            double ve,
                            double acs,
                            double ace,
                            double sc,
                            double se,
                            double ti,
                            bool &finished,
                            double &vi,
                            double &si,
                            double &ai);

    sc_status update(double interval,
                     sc_motion_in in,
                     sc_motion_out &out);

private:

    double as=0;
    double a=0;
    double jm=0;
    double dv=0;
    double ct=0;

    double ts=0;
    double te=0;

    double vf=0;

    double so=0;
    double se=0;
    double s1=0;
    double s2=0;
    double s3=0;
    double t1=0;
    double t2=0;
    double t3=0;
    double v1=0;
    double v2=0;

    double acs=0;
    double ace=0;

    double to_ve=0;
    double ace_=0;

    std::vector<sc_period> pvec;

};
#endif
