#ifndef SC_STRUCT_H
#define SC_STRUCT_H

//! Enum to define curve periods.
enum sc_period_id {
    id_t1,
    id_t2,
    id_t3,
    id_t4,
    id_t5,
    id_t6,
    id_t7,
    id_none
};

//! A period with it's values.
struct sc_period {
    //! Period type, t1,t2,t3, etc,
    sc_period_id id=sc_period_id::id_none;
    //! Velocity start.
    double vo=0;
    //! Velocity end.
    double ve=0;
    //! Acceleration start.
    double acs=0;
    //! Acceleration end.
    double ace=0;
    //! Netto curve displacement.
    double ncs=0;
    //! Netto curve time.
    double nct=0;
};

struct sc_motion_params {
    double maxacc=0;
    double maxdv=0;
};

struct sc_motion_in {
    double curvel=0;
    double maxvel=0;
    double endvel=0;
    double curpos=0;
    double endpos=0;
    double curacc=0;
    double endacc=0;
};

struct sc_motion_out {
    double newvel=0;
    double newpos=0;
    double newacc=0;
    bool finished=0;
};

enum sc_motion_joint_id {
    id_J0=0,
    id_J1=1,
    id_J2=2,
    id_J3=3,
    id_J4=4,
    id_J5=5,
    id_J6=6,
    id_J7=7,
    id_J8=8,
    id_J9=9,
    id_J10=10,
    id_J11=11,
    id_J12=12,
    id_J13=13,
    id_J14=14,
    id_J15=15
};

enum sc_status {
    Error=0,
    Ok=1,
};

#endif










