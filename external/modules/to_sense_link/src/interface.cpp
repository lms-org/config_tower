#include "to_sense_link.h"

extern "C" {
void* getInstance () {
    return new ToSenseLink();
}
}
