#ifndef SCURVE_FUNCTIONS_H
#define SCURVE_FUNCTIONS_H

#include <iostream>
#include <vector>
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

    void set(double acceleration,
             double delta_velocity){
        a=acceleration;
        dv=delta_velocity;
        as=2*a;
    }

    void construct_motion(double vo,
                          double vm,
                          double ve,
                          double acs,
                          double ace,
                          double s);
    double jm();

    double curve_time();
    double curve_displacement();

    void interpolate(double at_time,
                     double &vi,
                     double &si,
                     double &ai,
                     period_id &id);

    void print_interpolation(double interval);

    void plot(double interval,
              std::vector<double> &vvec,
              std::vector<double> &svec,
              std::vector<double> &avec);

private:

    //! Bruto curve, given ve > s.
    double bruto_curve_time();
    double bruto_curve_displacement();
    //! Netto curve, without stich time.
    double netto_curve_time();
    double netto_curve_displacement();

    void bruto_interpolate(double at_time,
                           double &vi,
                           double &si,
                           double &ai,
                           period_id &id);

    void plot_bruto(double interval,
                    std::vector<double> &vvec,
                    std::vector<double> &svec,
                    std::vector<double> &avec);

    void print_bruto_journal();
    void print_bruto_interpolation(double interval);

    //! Custom ve, add stitch to get absolute s.
    double stitch_time();
    double stitch_displacement();

    void stitch_interpolate(double at_time,
                            double &vi,
                            double &si,
                            double &ai,
                            period_id &id);

    std::vector<period> pvec;
    period ve_stitch;
    motion m;
    double dv=10;
    double a=2;
    double as=0;
    //! Bruto curve to netto curve.
    double cte_del=0; //! Curve time end to delete.
    double ste_del=0; //! Displacement end to delete.

    std::string print_period_id(period_id id);

    //! Build acc stitch.
    void build_t2_stitch(double vo,
                         double s,
                         double a);

    //! Build steady stitch.
    void build_t4_stitch(double vo,
                         double s);

    //! Build acc period.
    void build_t1_t2_t3(double vo,
                        double ve,
                        double acs,
                        double ace);
    //! Build dcc period.
    void build_t5_t6_t7(double vo,
                        double ve,
                        double acs,
                        double ace);

    //! Build t7 period.
    //! Used to start with negative acs.
    void build_t7(double vo,
                  double acs,
                  double &ve);

    //! Build dcc stitch.
    void build_t6_stitch(double vo,
                         double s,
                         double a);

    //! Build steady period.
    void build_t4_period(double vo,
                         double s);
    //! Build acc,dcc periods.
    double build_t1_t2_t3_t5_t6_t7(double vo,
                                   double vm,
                                   double ve,
                                   double acs,
                                   double ace);

    //! Build acc,steady,dcc periods.
    double build_t1_t2_t3_t4_t5_t6_t7(double vo,
                                      double vm,
                                      double ve,
                                      double acs,
                                      double ace,
                                      double s4);
};

#endif





















