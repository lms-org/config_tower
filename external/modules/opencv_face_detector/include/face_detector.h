
// What is that? #pragma once
#include <lms/datamanager.h>
#include <lms/module.h>
#include <lms/type/module_config.h>
#include <lms/imaging/image.h>
#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <cstring>


namespace lms_opencv {

class FaceDetector : public lms::Module {
public:

    const lms::imaging::Image input;

    bool initialize();
    bool deinitialize();

    bool cycle();

    void detectAndDisplay( cv::Mat frame );


    void convertImage(cv::Mat output,const lms::imaging::Image input);
};

}  // namespace lms_opencv