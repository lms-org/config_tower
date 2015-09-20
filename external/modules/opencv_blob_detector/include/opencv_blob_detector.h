#ifndef OPENCV_BLOB_DETECTOR_H
#define OPENCV_BLOB_DETECTOR_H

#include <lms/datamanager.h>
#include <lms/module.h>
#include "lms/module_config.h"
#include "lms/imaging/image.h"
#include "opencv2/opencv.hpp"
#include "opencv_utils.h"
class OpencvBlobDetector : public lms::Module {
public:
    bool initialize();
    bool deinitialize();
    bool cycle();
private:
    const lms::ModuleConfig *config;
    //Datachannels
    const lms::imaging::Image* image;
    cv_utils::ImageWithBlobs* iBlobs;
    //detector
    cv::Ptr<cv::SimpleBlobDetector> detector;
};

#endif // OPENCV_BLOB_DETECTOR_H
