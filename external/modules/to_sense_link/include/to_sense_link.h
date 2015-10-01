#ifndef TO_ARDUIONO_H
#define TO_ARDUIONO_H

#include <lms/datamanager.h>
#include <lms/module.h>
#include <ostream>
#include "lms/math/vertex.h"
#include "sense_link/datatypes.h"
#include "sense_link/actuators.h"

class ToSenseLink : public lms::Module {
public:
    bool initialize();
    bool deinitialize();
    bool cycle();
private:
    const lms::math::vertex2i* angles;
    sense_link::Actuators* actuators;
};

#endif // TO_ARDUIONO_H
