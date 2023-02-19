#include "sc_motion.h"

sc_motion::sc_motion()
{

}

void sc_motion::run(){

    while(dtg>0){

    scurve->set(a,dv);
    scurve->build_motion(curvel,vm,ve,curacc,ace,dtg);
    ct=scurve->s_curve_time();
    std::cout<<std::fixed<<" ct:"<<ct;

    scurve->s_interpolate(0.01,newvel,si,newacc,id);

    dtg-=si;
    newpos+=si;

    std::cout<<std::fixed<<" vel:"<<newvel;
    std::cout<<std::fixed<<" pos:"<<newpos;
    std::cout<<std::fixed<<" acc:"<<newacc;
    std::cout<<std::fixed<<" ;dtg:"<<dtg<<std::endl;


    curvel=newvel;
    curacc=newacc;
    }

}
