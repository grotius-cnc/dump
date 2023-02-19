#ifndef SC_H
#define SC_H

//! Author  : SKynet Cyberdyne
//! Licence : GPL2
//! Data    : 2023

#include <iostream>
#include <vector>
#include <math.h>
#include <chrono>

enum interpolation {
    position,
    velocity
};

//! Enum to define curve periods.
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

//! A period with it's values.
struct period {
    //! Period type, t1,t2,t3, etc,
    period_id id=period_id::none;
    //! Velocity start.
    double vo=0;
    //! Velocity end.
    double ve=0;
    //! Acceleration start.
    double acs=0;
    //! Acceleration end.
    double ace=0;
    //! Netto curve time.
    double nct=0;
    //! Netto curve displacement.
    double nsi=0;
};

//! Scurve class.
class sc {

public:
    //! Empty constructor.
    sc();

    //! Set acceleration, delta velocity.
    //! Delta velocity is a velocity value
    //! to get from acc 0 to acc "as" to dcc 0.
    //! Where "as" is acceleration at
    //! inflection point.
    void set(double theA, double theDv);

    //! Build motion.
    void build_motion(double vo,
                      double vm,
                      double ve,
                      double acs,
                      double ace,
                      double s);



    //! Curve time.
    double s_curve_time();
    //! Curve displacement.
    double s_curve_displacement();
    //! Interpolate at time, return
    //! "vi"=velocity at time.
    //! "si"=displacement at time.
    //! "ai"=acceleration at time.
    //! "id"=period id. (t1,t2,t3,etc)
    void s_interpolate(double at_time,
                       double &vi,
                       double &si,
                       double &ai,
                       period_id &id);
    //! Print interpolation, given a
    //! time interval, for example 0.01.
    void s_print_interpolation(double interval);
    //! Plot curve to a point vector.
    //! "vvec"=vector velocity.
    //! "svec"=vector displacement.
    //! "avec"=vector acceleration.
    void s_plot(double interval,
                std::vector<double> &vvec,
                std::vector<double> &svec,
                std::vector<double> &avec);



    //! Velocity mode :

    //! Motion time from vo to ve.
    double vo_ve_time();
    //! Motion displacement from vo to ve.
    double vo_ve_displacement();
    //! Motion interpolate from vo to ve.
    void vo_ve_interpolate(double at_time,
                           double &vi,
                           double &si,
                           double &ai,
                           period_id &id);
    //! Motion plot from vo to ve.
    void vo_ve_plot(double interval,
                    std::vector<double> &vvec,
                    std::vector<double> &svec,
                    std::vector<double> &avec);
    //! Motion print journal from vo to ve.
    void vo_ve_print_journal();
    //! Motion print interpolation from vo to ve.
    void vo_ve_print_interpolation(double interval);

    //! General :

    //! Jerk max value, calculated from
    //! "dv" delta velocity input.
    double jm();

private:

    //! Displacement time excl stitch.
    double s_time_excl_stitch();
    //! Displacment excl stitch.
    double s_displacement_excl_stitch();

    //! Stitch is used when velocity end can not
    //! be reached in position mode. A stitch is
    //! a tiny bridge to accomplish absolute s output.

    //! Stitch time.
    double stitch_time();
    //! Stitch displacement.
    double stitch_displacement();
    //! Stitch interpolate.
    void stitch_interpolate(double at_time,
                            double &vi,
                            double &si,
                            double &ai,
                            period_id &id);

    //! Period bucket. This can hold any combination
    //! or multiple of:
    //! of t1,t2,t3,t4,t5,t6,t7.
    std::vector<period> pvec;
    //! Period used to define the stitch.
    period ve_stitch;
    //! Delta velocity value used to calculate
    //! "jm" jerk max.
    double dv=10;
    //! Acceleration.
    double a=2;
    //! Acceleration at inflection point, 2*a.
    double as=0;
    //! Velocity curve to position curve.
    double cte_del=0; //! Curve time end to delete.
    double ste_del=0; //! Displacement end to delete.

    //! Print period id nr. in text from.
    std::string print_period_id(period_id id);

    //! Build periods & period assembly's
    void build_t2_stitch(double vo,
                         double s,
                         double a);

    void build_t4_stitch(double vo,
                         double s);

    double build_t1_t2_t3(double vo,
                          double ve,
                          double acs,
                          double ace,
                          double &ve_,
                          bool push_back);

    double build_t1_t2_t3_t5(double vo,
                             double ve,
                             double acs,
                             double ace,
                             double &ve_,
                             bool push_back);

    double build_t7_t1_t2_t3(double vo,
                             double ve,
                             double acs,
                             double ace,
                             double &ve_,
                             bool push_back);

    double build_t1(double vo,
                    double acs,
                    double ace,
                    double &ve_,
                    bool push_back);

    double build_t1_ve(double vo,
                       double ve,
                       double acs,
                       double &ace_,
                       double &ve_,
                       bool push_back);

    double build_t2(double vo,
                    double ve,
                    double a,
                    double &ve_,
                    bool push_back);

    double build_t3(double vo,
                    double acs,
                    double ace,
                    double &ve_,
                    bool push_back);

    double build_t5_t6_t7(double vo,
                          double ve,
                          double acs,
                          double ace,
                          double &ve_,
                          bool push_back);

    double build_t5_t6_t7_t1(double vo,
                             double ve,
                             double acs,
                             double ace,
                             double &ve_,
                             bool push_back);

    double build_t3_t5_t6_t7_t1(double vo,
                                double ve,
                                double acs,
                                double ace,
                                double &ve_,
                                bool push_back);

    double build_t3_t5_t6_t7(double vo,
                             double ve,
                             double acs,
                             double ace,
                             double &ve_,
                             bool push_back);



    double build_t5(double vo,
                    double acs,
                    double ace,
                    double &ve_,
                    bool push_back);

    double build_t5_ve(double vo,
                       double ve,
                       double acs,
                       double &ace_,
                       double &ve_,
                       bool push_back);

    double build_t6(double vo,
                    double ve,
                    double a,
                    double &ve_,
                    bool push_back);

    double build_t7(double vo,
                    double acs,
                    double ace,
                    double &ve_,
                    bool push_back);

    void build_t6_stitch(double vo,
                         double s,
                         double a);

    double build_t4_period(double vo,
                           double s, bool
                           push_back);

    void preprocess(double vo,
                      double vm,
                      double ve,
                      double acs,
                      double ace,
                      double s);


    double sc_t1_fast_s(double vo,
                        double a,
                        double acs,
                        double ace,
                        double dv);

    void sc_t1(double vo,
               double a,
               double acs,
               double ace,
               double dv,
               double &vf_,
               double &vo_,
               double &ve_,
               double &acs_,
               double &ace_,
               double &nct_,
               double &nsi_,
               double ti_,
               double &vi_,
               double &si_,
               double &ai_);

    //! Function elapsed time in milliseconds.
    double nanoseconds_to_milliseconds(double nanoseconds){
        //! Convert from nano- to milliseconds.
        return nanoseconds*0.000001;
    }
};

#endif





















