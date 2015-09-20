#ifndef OPENCV_FACE_DETECTOR_H
#define OPENCV_FACE_DETECTOR_H
#include <lms/datamanager.h>
#include <lms/module.h>
#include <lms/type/module_config.h>
#include <lms/imaging/image.h>
#include "lms/module_config.h"

#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <cstring>
#include "opencv_utils.h"


namespace lms_opencv {

class FaceDetector : public lms::Module {
public:
    bool initialize();
    bool deinitialize();

    bool cycle();

private:
    const lms::ModuleConfig* config;

    const lms::imaging::Image *input;
    cv_utils::ImageWithFaces *iFaces;


    void detect( cv::Mat frame );

    void displayImage(cv::Mat frame);
};

}  // namespace lms_opencv
#endif
