#include "opencv_blob_detector.h"
#include <vector>
bool OpencvBlobDetector::initialize() {
    //get the default config
    config = getConfig();

    image = datamanager()->readChannel<lms::imaging::Image>(this,"IMAGE");
    iBlobs = datamanager()->writeChannel<cv_utils::ImageWithBlobs>(this,"BLOBS");
    // Setup SimpleBlobDetector parameters.
    cv::SimpleBlobDetector::Params params;

    //TODO write config for it
    // Change thresholds
    params.minThreshold = 10;
    params.maxThreshold = 200;

    // Filter by Area.
    params.filterByArea = true;
    params.minArea = 1500;

    // Filter by Circularity
    params.filterByCircularity = true;
    params.minCircularity = 0.1;

    // Filter by Convexity
    params.filterByConvexity = true;
    params.minConvexity = 0.87;

    // Filter by Inertia
    params.filterByInertia = true;
    params.minInertiaRatio = 0.01;

    //Filter by darkness (0 -> looking for dark blobs)
    params.filterByColor = false;
    params.blobColor = 100;

    // Set up detector with params
    detector = cv::SimpleBlobDetector::create(params);
    return true;
}

bool OpencvBlobDetector::deinitialize() {
    return true;
}

bool OpencvBlobDetector::cycle() {
    cv::Mat toSearch;
    //filter image by color
    //currently the image is BRGA!
    if(config->get<bool>("filterColor")){
        //TODO add filter like http://opencv-srf.blogspot.de/2010/09/object-detection-using-color-seperation.html
        if(image->format() == lms::imaging::Format::BGRA || image->format() == lms::imaging::Format::RGB){
            int redMax = config->get<int>("redMax",255);
            int greenMax = config->get<int>("greenMax",255);
            int blueMax = config->get<int>("blueMax",255);

            int redMin = config->get<int>("redMin",0);
            int greenMin = config->get<int>("greenMin",0);
            int blueMin = config->get<int>("blueMin",0);
            if(image->format() == lms::imaging::Format::BGRA){
                int alphaMax = config->get<int>("alphaMax",255);
                int alphaMin = config->get<int>("alphaMin",0);
                cv::inRange(image->convertToOpenCVMat(),cv::Scalar(blueMin,redMin,greenMin,alphaMin),cv::Scalar(blueMax,redMax,greenMax,alphaMax),toSearch);
            }else{
                cv::inRange(image->convertToOpenCVMat(),cv::Scalar(blueMin,redMin,greenMin),cv::Scalar(blueMax,redMax,greenMax),toSearch);
            }
        }else if(image->format() == lms::imaging::Format::GREY){
            cv::inRange(image->convertToOpenCVMat(),cv::Scalar(config->get<int>("greyMin",0)),cv::Scalar(config->get<int>("greyMax",0)),toSearch);
        }
    }else{
        toSearch = image->convertToOpenCVMat();
    }

    //TODO add some kind of hints and reduce the searched area by that
    // Storage for blobs
    std::vector<cv::KeyPoint> &keypoints = iBlobs->points;
    keypoints.clear();

    detector->detect(toSearch, keypoints);
    logger.error("...")<<image->format() << " "<< image->width();

    cv::imshow("BLOB", image->convertToOpenCVMat() );
    cv::imshow("BLOB2", toSearch);
    cv::waitKey(1);

    return true;
}
