#include "to_arduiono.h"

extern "C" {
void* getInstance () {
    return new ToArduiono();
}
}
