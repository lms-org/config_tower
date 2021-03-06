#include "opencv_face_recognizer.h"
#include <fstream>
#include "lms/framework.h"
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
    config = getConfig();
    std::string recognizer = config->get<std::string>("recognizer","eigen");
    if(recognizer == "eigen"){
        model = cv::face::createEigenFaceRecognizer();
        logger.info("init")<<"using eigenfaces";
    }else if(recognizer == "fisher"){
        model = cv::face::createFisherFaceRecognizer();
        logger.info("init")<<"using fisherfaces";
    }else if(recognizer == "lbph"){
        model = cv::face::createLBPHFaceRecognizer();
        logger.info("init")<<"using LBPH";
    }else{
        logger.error("init")<<"Invalid recognizer given: "<<recognizer;
    }
    iFaces = datamanager()->readChannel<cv_utils::ImageWithFaces>(this,"FACES");
    train();
    return true;
}

void OpencvFaceRecognizer::train(){
    std::vector<cv::Mat> images;
    std::vector<int> labels;
    if(!config->hasKey("images")){
        logger.error("train")<<"no images given!";
        return;
    }
    read_csv(lms::Framework::configsDirectory+"/"+config->get<std::string>("images"),images,labels);

    //TODO I don't think that we need to normalize it
    //cv::normalize(_src, dst, 0, 255, NORM_MINMAX, CV_8UC1);
    if(images.size() > 0){
        model->train(images, labels);
    }else{
        logger.error("train")<<"No images for training given!";
    }
}

void OpencvFaceRecognizer::read_csv(const std::string& filename, std::vector<cv::Mat>& images, std::vector<int>& labels, char separator) {
    std::ifstream file(filename.c_str(), std::ifstream::in);
    if (!file) {
        logger.error("read_csv")<<"No valid input file was given, please check the given filename.";
        return;
    }
    std::string line, path, classlabel;
    while (std::getline(file, line)) {
        std::stringstream liness(line);
        std::getline(liness,path, separator);
        std::getline(liness, classlabel);
        if(!path.empty() && !classlabel.empty()) {
            std::string img = lms::Framework::configsDirectory+"/faces/"+ path;
            cv::imread(img, 0);
            images.push_back(prepareImage(cv::imread(img, 0)));
            labels.push_back(std::atoi(classlabel.c_str()));
        }
    }
}

cv::Mat OpencvFaceRecognizer::prepareImage(const cv::Mat& input){
    return cv_utils::croppResizeCentered(input,config->get<int>("imageWidth",256),config->get<int>("imageHeight",256));
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
        testSample = prepareImage(testSample);
        model->predict(testSample, predictedLabel, confidence);
        logger.debug("I found: ")<<predictedLabel<<" - confidence: "<<confidence;

        cv::imshow("face", testSample );
        cv::waitKey(1);
    }

    return true;
}
