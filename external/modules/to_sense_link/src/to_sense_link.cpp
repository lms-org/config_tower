#include "to_arduiono.h"
#include "lms/math/vertex.h"
#include <cmath>
#include <cstdint>
bool ToArduiono::initialize() {
    logger.debug("initialize")<<"start";
    angles = datamanager()->readChannel<lms::math::vertex2i>(this,"ANGLES");
    logger.debug("initialize")<<"completed";
    actuators = datamanager()->writeChannel<sense_link::Actuators>(this,"ACTUATORS");
    return true;
}

bool ToArduiono::deinitialize() {
    return true;
}

bool ToArduiono::cycle() {
    static float k = 0;
    k += .1;
    if(k >= 180)
        k = 0;
    actuators->clear();
    sense_link::Servo s0;
    s0.angle = k;
    sense_link::Servo s1;
    s1.angle = k;
    actuators->set(sense_link::ActuatorType::SERVO,1,s0);
    actuators->set(sense_link::ActuatorType::SERVO,2,s1);
    sense_link::ActuatorData led;
    if(k > 90){
        led.Led.value = 255;
    }else{
        led.Led.value = 0;
    }
    actuators->set(sense_link::ActuatorType::LED,0,led);
    return true;
}
