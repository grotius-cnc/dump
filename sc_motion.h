#ifndef SC_MOTION_H
#define SC_MOTION_H

#include <sc_engine.h>
#include <sc_struct.h>

//! Scurve front end interface.
class sc_motion {
public:
    sc_motion();

    struct sc_axis {
        sc_motion_joint_id id;
        sc_engine *engine=new sc_engine();
    };

    sc_status nr_of_joints(int nr_of_axis);

    sc_status set(sc_motion_joint_id id,
                  T a,
                  T dv);

    sc_status update(T interval,
                     sc_motion_joint_id id,
                     sc_motion_in in,
                     sc_motion_out &out);

    T curve_time(sc_motion_joint_id id);

private:
    sc_axis *axis;
    std::vector<sc_axis*> axisvec;
    uint reset_vec_nr=0;
};

#endif












