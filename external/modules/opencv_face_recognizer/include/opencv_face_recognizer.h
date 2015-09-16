#ifndef OPENCV_FACE_RECOGNIZER_H
#define OPENCV_FACE_RECOGNIZER_H

#include "lms/datamanager.h"
#include "lms/module.h"
#include "opencv_utils.h"

#include "opencv2/core/core.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/highgui/highgui.hpp"

class OpencvFaceRecognizer : public lms::Module {
public:
    bool initialize();
    bool deinitialize();
    bool cycle();

private:
    cv::Ptr<cv::FaceRecognizer> model;
    const cv_utils::ImageWithFaces iFaces;
    void train();
};

#endif // OPENCV_FACE_RECOGNIZER_H
