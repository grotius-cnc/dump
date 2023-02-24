#ifndef SC_STRUCT_H
#define SC_STRUCT_H

typedef double T;

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
    T vo=0;
    //! Velocity end.
    T ve=0;
    //! Acceleration start.
    T acs=0;
    //! Acceleration end.
    T ace=0;
    //! Netto curve displacement.
    T ncs=0;
    //! Netto curve time.
    T nct=0;
};

struct sc_motion_params {
    T maxacc=0;
    T maxdv=0;
};

struct sc_motion_in {
    T curvel=0;
    T maxvel=0;
    T endvel=0;
    T curpos=0;
    T endpos=0;
    T curacc=0;
    T endacc=0;
};

struct sc_motion_out {
    T newvel=0;
    T newpos=0;
    T newacc=0;
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
    Busy=2,
    Finished=3
};

#endif










