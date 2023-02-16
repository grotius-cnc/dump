#ifndef SCURVE_FUNCTIONS_H
#define SCURVE_FUNCTIONS_H

#include <print.h>
#include <math.h>

enum period_id {
    t1,
    t2,
    t3,
    t4,
    t5,
    t6,
    t7,
    none
};

struct period {
    period_id id=period_id::none;
    double vo=0;
    double ve=0;
    double acs=0;
    double ace=0;
    double nct=0;
    double nsi=0;
};

struct motion {
    double vo=0;
    double vm=0;
    double ve=0;
    double acs=0;
    double ace=0;
    double s=0;
};

//! Todo : displacements.
class sc {

public:
    sc(){}

    void set(double acceleration, double delta_velocity){
        a=acceleration;
        dv=delta_velocity;
        as=2*a;
    }

    void create(double vo,
                double vm,
                double ve,
                double acs,
                double ace,
                double s);

    double curve_time();

    void interpolate(double at_time,
                     double &vi,
                     double &si,
                     double &ai);

    void plot(double interval,
              std::vector<double> &vvec,
              std::vector<double> &svec,
              std::vector<double> &avec);

    void print_journal();
    void print_interpolation(double interval);

private:
    std::vector<period> pvec;
    motion m;
    double dv=10;
    double a=2;
    double as=0;

    void sc_construct_t1_t2_t3_period(double vo,
                                      double ve,
                                      double acs);

    void sc_construct_t5_t6_t7_period(double vo,
                                      double ve,
                                      double ace);
};

#endif





















