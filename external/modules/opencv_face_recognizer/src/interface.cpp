#include "opencv_face_recognizer.h"

extern "C" {
void* getInstance () {
    return new OpencvFaceRecognizer();
}
}
