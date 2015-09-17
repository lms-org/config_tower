#include "opencv_face_logger.h"

bool OpencvFaceLogger::initialize() {
    iFaces = datamanager()->readChannel<cv_utils::ImageWithFaces>(this,"FACES");
    facesSaved = 0;
    return true;
}

bool OpencvFaceLogger::deinitialize() {
    return true;
}

bool OpencvFaceLogger::cycle() {
    if(iFaces->faces.size() == 0){
        logger.debug("no face found!");
        return true;
    }
    for(uint i = 0; i < iFaces->faces.size(); i++){
        cv::Mat img(iFaces->image->convertToOpenCVMat(),iFaces->faces[i]);
        if(cv::imwrite("faces/face_"+std::to_string(facesSaved)+".bmp",img)){
            logger.debug("cycle")<<"face successfully logged";
            facesSaved++;
        }else{
            logger.error("cycle")<<"face logging failed!";
        }
    }
    return true;
}
