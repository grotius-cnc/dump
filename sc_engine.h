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

    inline int t1_v(T vo, T acs, T ace, T &ve);

    inline int t1_s(T vo, T acs, T ace, T &ncs, T &nct);

    inline int t1_v_s(T vo, T acs, T ace, bool pb, T &ve, T &ncs, T &nct);

    inline int t1_v_ve(T vo, T ve, T acs, T &ace, T &ve_);

    inline int t1_s_ve(T vo, T ve, T acs, T &ncs, T &nct);

    inline int t1_v_s_ve(T vo, T ve, T acs, bool pb, T &ace, T &ve_, T &ncs, T &nct);

    inline int t1_v_s_a_i(T vo, T acs, T ti, T &vi, T &si, T &ai);

    inline int t2_s(T vo, T ve, T a, bool pb, T &ncs, T &nct);

    inline int t2_v_s_a_i(T vo, T a, T ti, T &vi, T &si, T &ai);

    inline int t3_v(T vo, T acs, T ace, T &ve);

    inline int t3_s(T vo, T acs, T ace, T &ncs, T &nct);

    inline int t3_v_s(T vo, T acs, T ace, bool pb, T &ve, T &ncs, T &nct);

    inline int t3_v_s_a_i(T vo, T acs, T ti, T &vi, T &si, T &ai);

    inline int t4_s(T vo, T s, bool pb, T &ncs, T &nct);

    inline int t4_v_s_a_i(T vo, T ti, T &vi, T &si, T &ai);

    inline int t5_v(T vo, T acs, T ace, T &ve);

    inline int t5_s(T vo, T acs, T ace, T &ncs, T &nct);

    inline int t5_v_s(T vo, T acs, T ace, bool pb, T &ve_, T &ncs, T &nct);

    inline int t5_v_ve(T vo, T ve, T acs, T &ace, T &ve_);

    inline int t5_s_ve(T vo, T ve, T acs, T &ncs, T &nct);

    inline int t5_v_s_ve(T vo, T ve, T acs, bool pb, T &ace_, T &ve_, T &ncs, T &nct);

    inline int t5_v_s_a_i(T vo, T acs, T ti, T &vi, T &si, T &ai);

    inline int t6_s(T vo, T ve, T a, bool pb, T &ncs, T &nct);

    inline int t6_v_s_a_i(T vo, T a, T ti, T &vi, T &si, T &ai);

    inline int t7_v(T vo, T acs, T ace, T &ve);

    inline int t7_s(T vo, T acs, T ace, T &ncs, T &nct);

    inline int t7_v_s(T vo, T acs, T ace, bool pb, T &ve, T &ncs, T &nct);

    inline int t7_v_s_a_i(T vo, T acs, T ti, T &vi, T &si, T &ai);

    inline T to_vh_acc(T vo, T ve);

    inline T to_vh_dcc(T vo, T ve);

    inline int t7_t1_t2_t3_t5_s(T vo, T ve, T acs, T ace, bool pb, T &ve_, T &ncs, T &nct);

    inline int t3_t5_t6_t7_t1_s(T vo, T ve, T acs, T ace, bool pb, T &ve_, T &ncs, T &nct);

    void set_a_dv(T theA, T theDv);

    void interpolate(T at_time,
                     T &vi,
                     T &dtg,
                     T &ai);

    double curve_time();

    sc_status process_scurve(T vo,
                             T vm,
                             T ve,
                             T acs,
                             T ace,
                             T s);

    sc_status update(T interval,
                     sc_motion_in in,
                     sc_motion_out &out);

    inline std::string print_period_id(sc_period_id id);
    inline void print_diagnostics();

private:

    T as=0;
    T a=0;
    T jm=0;
    T dv=0;
    T ct=0;

    std::vector<sc_period> pvec;
    sc_motion_in old_in;

    bool is_equal_except_vm(sc_motion_in a, sc_motion_in b);
    bool is_equal_vm(sc_motion_in a, sc_motion_in b);
    T sc_timer=0;
    bool sc_finished=0;
    double old_pos=0;
    double new_pos=0;
    double pos=0;
    double vel=0;
    double acc=0;
};
#endif
