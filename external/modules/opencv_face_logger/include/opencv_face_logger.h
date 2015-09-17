#ifndef OPENCV_FACE_LOGGER_H
#define OPENCV_FACE_LOGGER_H

#include <lms/datamanager.h>
#include <lms/module.h>
#include <lms/type/module_config.h>

#include "opencv_utils.h"

class OpencvFaceLogger : public lms::Module {
public:
    bool initialize();
    bool deinitialize();
    bool cycle();

private:
    const cv_utils::ImageWithFaces *iFaces;
    int facesSaved;
};

#endif // OPENCV_FACE_LOGGER_H
