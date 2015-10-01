#include "to_sense_link.h"
#include "lms/math/vertex.h"
#include <cmath>
#include <cstdint>
bool ToSenseLink::initialize() {
    actuators = datamanager()->writeChannel<sense_link::Actuators>(this,"ACTUATORS");
    target = datamanager()->writeChannel<lms::target::Target>(this, "TARGET");
    return true;
}

bool ToSenseLink::deinitialize() {
    return true;
}

bool ToSenseLink::cycle() {
    actuators->clear();
    if(!target->valid){
        return true;
    }
    float transHor = 30;
    float transVert = 30;

    servoHor = servoHor + transHor*target->y;
    servoVert = servoVert + transVert*target->x;
    logger.debug("angle")<< servoHor<< " ; " << servoVert;

    //limit the angle
    if(servoHor < 0){
        servoHor = 0;
    }else if(servoHor > 180){
        servoHor = 180;
    }
    if(servoVert < 0){
        servoVert = 0;
    }else if(servoVert > 180){
        servoVert = 180;
    }
    sense_link::Servo s0;
    s0.angle = servoHor;
    sense_link::Servo s1;
    s1.angle = servoVert;
    actuators->set(sense_link::ActuatorType::SERVO,1,s0);
    actuators->set(sense_link::ActuatorType::SERVO,2,s1);
    sense_link::ActuatorData led;
    actuators->set(sense_link::ActuatorType::LED,0,led);
    return true;
}
