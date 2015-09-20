#ifndef OPENCV_FACE_RECOGNIZER_H
#define OPENCV_FACE_RECOGNIZER_H

#include "lms/datamanager.h"
#include "lms/module.h"
#include "opencv_utils.h"
#include "lms/module_config.h"

#include "opencv2/face.hpp"

class OpencvFaceRecognizer : public lms::Module {
public:
    bool initialize();
    bool deinitialize();
    bool cycle();

private:
    const lms::ModuleConfig* config;
    cv::Ptr<cv::face::FaceRecognizer> model;
    const cv_utils::ImageWithFaces *iFaces;
    void train();
    void read_csv(const std::string& filename, std::vector<cv::Mat>& images, std::vector<int>& labels, char separator = ';');
    cv::Mat prepareImage(const cv::Mat& input);
};

#endif // OPENCV_FACE_RECOGNIZER_H
