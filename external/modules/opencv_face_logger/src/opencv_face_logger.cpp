#include "opencv_face_logger.h"

bool OpencvFaceLogger::initialize() {
    iFaces = datamanager()->readChannel<cv_utils::ImageWithFaces>(this,"FACES");
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
        cv::imwrite(std::to_string(i)+".bmp",img);
    }
    return true;
}
