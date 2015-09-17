#ifndef LMS_OPENCV_UTILS
#define LMS_OPENCV_UTILS
#include "lms/imaging/image.h"
#include <vector>

//default opencv includes
#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

namespace cv_utils{
    struct ImageWithFaces{
        const lms::imaging::Image* image;
        std::vector<cv::Rect> faces;
    };

    struct ImageWithBlobs{
        const lms::imaging::Image* image;
        std::vector<cv::KeyPoint> points;
    };
}

#endif
