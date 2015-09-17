#include "opencv_blob_detector.h"

extern "C" {
void* getInstance () {
    return new OpencvBlobDetector();
}
}
