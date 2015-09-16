#include "opencv_face_logger.h"

extern "C" {
void* getInstance () {
    return new OpencvFaceLogger();
}
}
