#ifndef SC_MOTION_H
#define SC_MOTION_H

#include <sc.h>

class sc_motion
{
public:

    sc_motion();

    double a=2;
    double dv=10;
    double vm=25;
    double ace=0;
    double ve=0;
    double dtg=100;

    double curvel=0;
    double curacc=0;

    void run();

private:

    sc *scurve=new sc();
    period_id id;
    double newpos=0,newvel=0,newacc=0;
    double si=0;
    double ct=0;
};

#endif
