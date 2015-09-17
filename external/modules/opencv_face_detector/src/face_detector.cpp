#include <lms/type/module_config.h>
#include "lms/messaging.h"

#include "face_detector.h"
#include <iostream>
#include <stdio.h>
#include "lms/framework.h"
/** Global variables */
std::string face_cascade_name = "haarcascade_frontalface_alt.xml";
std::string eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
cv::CascadeClassifier face_cascade;
cv::CascadeClassifier eyes_cascade;
std::string window_name = "Capture - Face detection";

namespace lms_opencv {

bool FaceDetector::initialize(){
    config = getConfig();
    input = datamanager()->readChannel<lms::imaging::Image>(this,"IMAGE");
    iFaces = datamanager()->writeChannel<cv_utils::ImageWithFaces>(this,"FACES");
    iFaces->image = input;
    std::string configDir = lms::Framework::configsDirectory;
    if( !face_cascade.load(configDir+"/"+ face_cascade_name ) ){ printf("--(!)Error loading face cascade\n"); return false; };
    if( !eyes_cascade.load(configDir+"/"+ eyes_cascade_name ) ){ printf("--(!)Error loading eyes cascade\n"); return false; };
    return true;
}

bool FaceDetector::deinitialize() {
    return true;
}

bool FaceDetector::cycle () {
    cv::Mat frame = input->convertToOpenCVMat();
    //TODO convert image to opencv image
    if( frame.empty() ){
        logger.warn() << "No captured frame!";
        return true;
    }else{
        //-- 3. Apply the classifier to the frame
        detect(frame);

        //TODO render function
        if(config->get<bool>("detectEyes",false)){
            displayImage(frame);
        }
    }
    return true;
}

void FaceDetector::displayImage(cv::Mat frame){
    cv::imshow(window_name, frame );
    cv::waitKey(1);
}

/**
 * @function detectAndDisplay
 * frame should be a grey image!
*/
void FaceDetector::detect( cv::Mat frame ){
    //TODO use config to toggle drawing etc.
    using namespace cv;
    //reuse array
    std::vector<cv::Rect> &faces = iFaces->faces;
    faces.clear();

    //TODO not that good as it modifies the image!
    equalizeHist( frame, frame );

    //-- Detect faces
    face_cascade.detectMultiScale( frame, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30) );

    //TODO also toggles rendering
    if(config->get<bool>("detectEyes",false)){
        for ( size_t i = 0; i < faces.size(); i++ ){
            Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
            ellipse( frame, center, Size( faces[i].width/2, faces[i].height/2 ), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );

            Mat faceROI = frame( faces[i] );
            std::vector<Rect> eyes;

            //-- In each face, detect eyes
            eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CASCADE_SCALE_IMAGE, Size(30, 30) );

            for ( size_t j = 0; j < eyes.size(); j++ ){
                Point eye_center( faces[i].x + eyes[j].x + eyes[j].width/2, faces[i].y + eyes[j].y + eyes[j].height/2 );
                int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
                circle( frame, eye_center, radius, Scalar( 255, 0, 0 ), 4, 8, 0 );
            }
        }
    }
    iFaces->faces = faces;
}
}
