//#ifndef SCURVE_H
//#define SCURVE_H

//#include <math.h>
//#include <iostream>
//#include <vector>
//#include <print.h>
//#include <functions.h>
//#include <interpolate.h>



////! From interupt v to ve, without try to reach vm first.
//struct interupt_curve {
//public:

//    void input(double theVo, double theVe, double theA, double theAcs, double theDv, bool theDebug){
//        vo=theVo;
//        ve=theVe;
//        a=theA;
//        acs=theAcs;
//        dv=theDv;
//        debug=theDebug;
//        as=2*a;
//    }

//    void solve(){
//        //! Acc curve using t1,t2,t3.

//        if(vo<ve && acs>=0){
//            pvec.clear();
//            period t1,t2,t3;
//            t1.id=period_id::t1;
//            t2.id=period_id::t2;
//            t3.id=period_id::t3;

//            if(ve-vo<dv){ //! Need t1,t3 chunks, and a t2 stitch.
//                print("need chunks for t1,t3, need a stitch for t2.",true,debug);
//                double ace=0, stitch=0;
//                for(ace=2*a+0.1; ace>acs; ace-=0.1){
//                    sc_t1(vo, a, acs, ace, dv, t1.vo, t1.ve, t1.acs, t1.ace, t1.ct, false);
//                    sc_t3(t1.ve, a, ace, 0, dv, t3.vo, t3.ve, t3.acs, t3.ace, t3.ct, false);
//                    if(t3.ve<=ve){
//                        stitch=ve-t3.ve;
//                        sc_t1(vo, a, acs, ace, dv, t1.vo, t1.ve, t1.acs, t1.ace, t1.ct, false);
//                        sc_t2(t1.ve, t1.ve+stitch, ace, t2.vo, t2.ve, t2.acs, t2.ace, t2.ct,false);
//                        sc_t3(t2.ve, a, ace, 0, dv, t3.vo, t3.ve, t3.acs, t3.ace, t3.ct, false);
//                        break;
//                    }
//                }

//                //! Exception.
//                if(t3.ve>ve){
//                    sc_t3(vo, a, acs, 0, dv, t3.vo, t3.ve, t3.acs, t3.ace, t3.ct, false);
//                    stitch=ve-t3.ve;
//                    if(stitch>0){
//                        sc_t2(vo, vo+stitch, acs, t2.vo, t2.ve, t2.acs, t2.ace, t2.ct,false);
//                        sc_t3(t2.ve, a, acs, 0, dv, t3.vo, t3.ve, t3.acs, t3.ace, t3.ct, false);
//                        pvec.push_back(t2);
//                        pvec.push_back(t3);
//                        printpvec(debug);
//                        return;
//                    }
//                    std::cerr<<"Can't finish at given acs,ve. Using custom ve output."<<std::endl;
//                    pvec.push_back(t3);
//                    printpvec(debug);
//                    return;
//                }

//                pvec.push_back(t1);
//                pvec.push_back(t2);
//                pvec.push_back(t3);
//                printpvec(debug);
//                return;
//            }
//            //! Scurve>=dv.
//            sc_t1(vo, a, acs, as, dv, t1.vo, t1.ve, t1.acs, t1.ace, t1.ct, false); //! Silent.
//            sc_t3(t1.ve, a, t1.ace, 0,dv, t3.vo, t3.ve, t3.acs, t3.ace, t3.ct,false);

//            if(t3.ve==ve){
//                pvec.push_back(t1);
//                pvec.push_back(t3);
//                printpvec(debug);
//                return;
//            }
//            if(ve-t3.ve>0){ //! Need t2.

//                sc_t2(t1.ve, t1.ve+(ve-t3.ve), 2*a, t2.vo, t2.ve, t2.acs, t2.ace, t2.ct,false);
//                sc_t3(t2.ve, a, 2*a, 0, dv, t3.vo, t3.ve, t3.acs, t3.ace, t3.ct,false);

//                pvec.push_back(t1);
//                pvec.push_back(t2);
//                pvec.push_back(t3);
//                printpvec(debug);
//                return;
//            }
//        }
//        //! Steady curve using t4.
//        if(vo==ve && acs==0){
//            pvec.clear();
//            period t4;
//            t4.id=period_id::t4;
//            print("no steady period's are used for interupt curve",true,debug);
//        }
//        //! Dcc curve using t5,t6,t7.
//        if(vo>ve && acs<=0){
//            pvec.clear();
//            period t5,t6,t7;
//            t5.id=period_id::t5;
//            t6.id=period_id::t6;
//            t7.id=period_id::t7;

//            if(vo-ve<=dv){ //! Need t1,t3 chunks.
//                print("need chunks for t5,t7, need a stitch for t6.",true,debug);
//                double ace=0, stitch=0;
//                for(ace=-2*a-0.01; ace<=0; ace+=0.1){
//                    sc_t5(vo, a, acs, ace, dv, t5.vo, t5.ve, t5.acs, t5.ace, t5.ct, false);
//                    sc_t7(t5.ve, a, ace, 0, dv, t7.vo, t7.ve, t7.acs, t7.ace, t7.ct, false);
//                    if(t7.ve>=ve){
//                        stitch=t7.ve-ve;
//                        sc_t5(vo, a, acs, ace, dv, t5.vo, t5.ve, t5.acs, t5.ace, t5.ct, false);
//                        sc_t6(t5.ve, t5.ve-stitch, ace, t6.vo, t6.ve, t6.acs, t6.ace, t6.ct,false);
//                        sc_t7(t6.ve, a, ace, 0, dv, t7.vo, t7.ve, t7.acs, t7.ace, t7.ct, false);
//                        break;
//                    }
//                }

//                //! Exception.
//                if(t5.ct<0){
//                    sc_t7(vo, a, acs, 0, dv, t7.vo, t7.ve, t7.acs, t7.ace, t7.ct, false);
//                    if(t7.ve>ve){
//                        stitch=t7.ve-ve;
//                        sc_t6(vo, vo-stitch, acs, t6.vo, t6.ve, t6.acs, t6.ace, t6.ct,false);
//                        sc_t7(t6.ve, a, acs, 0, dv, t7.vo, t7.ve, t7.acs, t7.ace, t7.ct, false);
//                        pvec.push_back(t6);
//                        pvec.push_back(t7);
//                        printpvec(debug);
//                        return;
//                    }

//                    std::cerr<<"Can't finish at given acs,ve. Using custom ve output."<<std::endl;
//                    pvec.push_back(t7);
//                    printpvec(debug);
//                    return;
//                }

//                pvec.push_back(t5);
//                pvec.push_back(t6);
//                pvec.push_back(t7);
//                printpvec(debug);
//                return;

//            }
//            //! Scurve>=dv.
//            sc_t5(vo, a, acs, as, dv, t5.vo, t5.ve, t5.acs, t5.ace, t5.ct, false);
//            sc_t7(t5.ve, a, t5.ace, 0, dv, t7.vo, t7.ve, t7.acs, t7.ace, t7.ct, false);

//            if(t7.ve==ve){
//                print("curve is size dv.",true,debug);
//                pvec.push_back(t5);
//                pvec.push_back(t7);
//                printpvec(debug);
//                return;
//            }
//            if(vo-ve>=dv){ //! Need t2.
//                print("curve needs t2.",true,debug);
//                sc_t6(t5.ve, t5.ve-(t7.ve-ve), t5.ace, t6.vo, t6.ve, t6.acs, t6.ace, t6.ct,false);
//                sc_t7(t6.ve, a, t6.ace, 0, dv, t7.vo, t7.ve, t7.acs, t7.ace, t7.ct,false);

//                pvec.push_back(t5);
//                pvec.push_back(t6);
//                pvec.push_back(t7);
//                printpvec(debug);
//                return;
//            }

//        }
//        //! Acc curve using t7,t1,t2,t3.
//        if(vo<ve && acs<=0){
//            print("curve needs front period t7 to neutralize negative acs.",true,debug);
//            pvec.clear();
//            period t7,t1,t2,t3;
//            t7.id=period_id::t7;
//            t1.id=period_id::t1;
//            t2.id=period_id::t2;
//            t3.id=period_id::t3;

//            sc_t7(vo, a, acs, as,  dv, t7.vo, t7.ve, t7.acs, t7.ace, t7.ct,false);
//            sc_t1_ve(t7.ve,((ve-t7.ve)/2)+t7.ve,a,t7.ace,dv,t1.vo,t1.ve,t1.acs,t1.ace,t1.ct,false);
//            sc_t3(t1.ve,a,t1.ace,0,dv,t3.vo,t3.ve,t3.acs,t3.ace,t3.ct,false);
//            std::cout<<"ve without linear stage:"<<t3.ve<<std::endl;

//            if(ve-t7.ve>=dv){
//                std::cout<<"use normal curves for t1,t3, use stitch if exceeds dv."<<std::endl;
//                double stitch=(ve-t7.ve)-dv;
//                sc_t1(t7.ve,a,t7.ace, as, dv,t1.vo,t1.ve,t1.acs,t1.ace,t1.ct,false);
//                sc_t2(t1.ve,t1.ve+stitch,t1.ace,t2.vo,t2.ve,t2.acs,t2.ace,t2.ct,false);
//                sc_t3(t2.ve,a,t2.ace,0,dv,t3.vo,t3.ve,t3.acs,t3.ace,t3.ct,false);

//                pvec.push_back(t7);
//                pvec.push_back(t1);
//                pvec.push_back(t2);
//                pvec.push_back(t3);
//                printpvec(debug);
//                return;
//            }

//            //! No need for stitch.
//            pvec.push_back(t7);
//            pvec.push_back(t1);
//            pvec.push_back(t3);
//            printpvec(debug);
//            return;

//        }

//        std::cerr<<"eof"<<std::endl;
//    }

//    void plot(std::vector<double> &tvec, std::vector<double> &vvec, std::vector<double> &avec){
//        //! For every period do a interpolation. Output periods timeline.
//        tvec.clear();
//        vvec.clear();
//        avec.clear();
//        double ti=0;

//        for(uint i=0; i<pvec.size(); i++){

//            double vo=pvec.at(i).vo;
//            double acs=pvec.at(i).acs;
//            double ct=pvec.at(i).ct;
//            double vi=0, ai=0;

//            //! For each period type, do a interpolation.
//            for(double at_time=0; at_time<ct; at_time+=interval){
//                if(pvec.at(i).id==period_id::t1){
//                    interpolate_t1(vo,a,acs,dv,at_time,vi,ai);
//                }
//                if(pvec.at(i).id==period_id::t2){
//                    interpolate_t2(vo,acs,dv,at_time,vi,ai);
//                }
//                if(pvec.at(i).id==period_id::t3){
//                    interpolate_t3(vo,a,acs,dv,at_time,vi,ai);
//                }
//                if(pvec.at(i).id==period_id::t4){
//                    interpolate_t4(vo,a,acs,dv,at_time,vi,ai);
//                }
//                if(pvec.at(i).id==period_id::t5){
//                    interpolate_t5(vo,a,acs,dv,at_time,vi,ai);
//                }
//                if(pvec.at(i).id==period_id::t6){
//                    interpolate_t6(vo,acs,dv,at_time,vi,ai);
//                }
//                if(pvec.at(i).id==period_id::t7){
//                    interpolate_t7(vo,a,acs,dv,at_time,vi,ai);
//                }


//                tvec.push_back(ti);
//                vvec.push_back(vi);
//                avec.push_back(ai);
//                ti+=interval;
//            }
//        }
//    }

//    std::vector<period> get_pvec(){
//        return pvec;
//    }

//    void printpvec(bool debug){
//        for(uint i=0; i<pvec.size(); i++){

//            std::cout<<"pvec i:"<<i<<" ";
//            pvec.at(i).print_id(debug);
//            print({"ct","vo","ve","acs","ace"},{pvec.at(i).ct,
//                                                pvec.at(i).vo,
//                                                pvec.at(i).ve,
//                                                pvec.at(i).acs,
//                                                pvec.at(i).ace}, debug);
//        }
//        std::cout<<std::endl;
//    }


//private:
//    std::vector<period> pvec;
//    double vo=0;
//    double ve=0;
//    double a=0;
//    double as=0;
//    double acs=0;
//    double dv=0;
//    bool debug=0;
//    //! Used for plot only:

//    double interval=0.001;
//};

//#endif // SCURVE_H











