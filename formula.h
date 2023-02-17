#ifndef FORMULAS_H
#define FORMULAS_H

#include <math.h>
#include <iostream>

/*
curve t1:
vi=vo+jm*(t*t)/2;                           //! Velocity current.
    vo=vi-(jm*(t*t)/2);
    t=sqrt(2)*sqrt((vi)-vo)/sqrt(jm);
si=vo*t+jm*(t*t*t)/6;                       //! Displacment.
ai=jm*t;                                    //! Acceleration.
ts=ai/jm;                                    //! Time at acceleration.

To get t from formula : s=vo*t+jm*(t*t*t)/6;
used https://www.wolframalpha.com/widgets/view.jsp?id=c778a2d8bf30ef1d3c2d6bc5696defad
to get a rearranged formula for solving t:
t= ( cbrt(3*(jm*jm)*s+ sqrt(9*(jm*jm*jm*jm)*(s*s)+8*(jm*jm*jm)*(vo*vo*vo))) / jm ) - ( 2*vo / cbrt(3*(jm*jm)*s+ sqrt(9*(jm*jm*jm*jm)*(s*s)+8*(jm*jm*jm)*(vo*vo*vo))));

curve t3:
vi=vh + as*t - jm*(t*t)/2;                  //! Velocity.
    t= (as -  sqrt( (as*as) + 2*(vh-vi) *jm))/jm;
    vh = -as*t+((jm*(t*t))/2)+vi

si=vh*t + as*(t*t)/2 - jm*(t*t*t)/6;        //! Displacment convex curve.
    t= see function solve_for_t
si+=sh;                                     //! Add concave displacement.
ai=as-jm*t;                                 //! Acceleration.
ts=(as-ai)/jm                                //! Time at acceleration.



curve t5:
vi=vo-jm*(t*t)/2;
    vo=((jm*(t*t))/2)+vi;
    t= (sqrt(2)*sqrt(vo-vi))/sqrt(jm)
si=vo*t-jm*(t*t*t)/6;
ts=ai/jm
ai=jm*t;

curve t7:
ve=vh - as*t + jm*(t*t)/2;
    vh=as*t - ((jm*(t*t))/2) + ve;
ai=as-jm*t;
ts=(as-acs)/jm;
si=vh*t - as*(t*t)/2 + jm*(t*t*t)/6


concave_convex:
as=2*a;                                     //! Max acceleration at inflection point. [2*A]
jm=2*as/ct;                                 //! Max jerk. Document page 2, ct=curve time. curve time is concave + convex periods together.
s=abs(ve*ve - vo*vo)/(2*a);                 //! Total curve displacement.
ct=abs(ve-vo)/a;                            //! Total curve time.
ht=0.5*ct.                                  //! Half curve time.

for interupt limit the curve steepness, given a "jm" jerk max value:
ct=jm/2*as;
for acc:
ve=vo + a*ct;
for dcc:
ve=vo - a*ct;

linear_acceleration:
v=vo + a*t;                                 //! Velocity.
s=vo*t + 0.5*a*(t*t);                       //! Displacement.
    t= abs( (-vo + sqrt(vo*vo - 2*a*s)) / a);
s=(ve*ve) - (vo*vo)/(2*a)                   //! Displacement.
v=sqrt((vo*vo) + 2*a*s);                    //! Velocity.

linear_deceleration:
v=vo - a*t;                                 //! Velocity.
s=vo*t - 0.5*a*(t*t);                       //! Displacement.
    t= abs( (-vo + sqrt(vo*vo - 2*a*s)) / a);
s=((vo*vo) - (ve*ve))/(2*a)                 //! Displacement.
v=sqrt((vo*vo) - 2*a*s);                    //! Velocity.

linear_general:
ct=abs(ve-vo)/a                             //! Total curve time.

steady:
s=v*t;                                      //! Displacement.
t=s/v;                                      //! Time.
v=s/t;                                      //! Velocity.
*/

#endif


























