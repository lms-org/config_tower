#include "opencv_face_recognizer.h"

bool OpencvFaceRecognizer::initialize() {
    // The following lines create an Eigenfaces model for
    // face recognition and train it with the images and
    // labels read from the given CSV file.
    // This here is a full PCA, if you just want to keep
    // 10 principal components (read Eigenfaces), then call
    // the factory method like this:
    //
    //      cv::createEigenFaceRecognizer(10);
    //
    // If you want to create a FaceRecognizer with a
    // confidence threshold (e.g. 123.0), call it with:
    //
    //      cv::createEigenFaceRecognizer(10, 123.0);
    //
    // If you want to use _all_ Eigenfaces and have a threshold,
    // then call the method like this:
    //
    //      cv::createEigenFaceRecognizer(0, 123.0);
    //
    model = cv::face::createEigenFaceRecognizer();
    iFaces = datamanager()->readChannel<cv_utils::ImageWithFaces>(this,"FACES");
    return true;
}

void OpencvFaceRecognizer::train(){
    std::vector<cv::Mat> images;
    std::vector<int> labels;
    //TODO load images/labels

    //TODO I don't think that we need to normalize it
    //cv::normalize(_src, dst, 0, 255, NORM_MINMAX, CV_8UC1);
    if(images.size() > 0){
        model->train(images, labels);
    }else{
        logger.error("train")<<"No images for training given!";
    }
}

bool OpencvFaceRecognizer::deinitialize() {
    return true;
}

bool OpencvFaceRecognizer::cycle() {
    if(iFaces->faces.size() == 0){
        logger.debug("cycle")<<"no faces given to look for";
        return true;
    }

    int predictedLabel = -1;
    double confidence = 0.0;
    for(const cv::Rect &rect:iFaces->faces){
        cv::Mat testSample(iFaces->image->convertToOpenCVMat(),rect);
        model->predict(testSample, predictedLabel, confidence);
    }
    return true;
}
