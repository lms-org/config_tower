#include "opencv_face_to_target.h"

extern "C" {
void* getInstance () {
    return new OpencvFaceToTarget();
}
}
