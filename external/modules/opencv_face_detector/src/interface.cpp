#include "face_detector.h"

extern "C" {
void* getInstance () {
    return new lms_opencv::FaceDetector();
}
}
