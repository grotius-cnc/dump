#include "sc_motion.h"
#include <vector>

sc_motion::sc_motion()
{

}

sc_status sc_motion::nr_of_joints(int nr_of_axis){
    std::max(abs(nr_of_axis),16);
    std::min(abs(nr_of_axis),1);

    for(uint i=0; i<uint(nr_of_axis); i++){
        axis=new sc_axis;
        axis->id=sc_motion_joint_id(i);
        axisvec.push_back(axis);
    }
    return sc_status::Ok;
}

sc_status sc_motion::set(sc_motion_joint_id id,
                    sc_motion_params params){

    if(id>axisvec.size()){
        return sc_status::Error;
    }
    axisvec.at(id)->params=params;
    return sc_status::Ok;
}

sc_status sc_motion::update(double interval,
                       sc_motion_joint_id id,
                       sc_motion_in in,
                       sc_motion_out &out){

    return axisvec.at(id)->engine->update(interval, in, out);
}
