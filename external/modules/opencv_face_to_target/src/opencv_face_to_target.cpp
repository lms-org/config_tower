#include "opencv_face_to_target.h"

bool OpencvFaceToTarget::initialize() {
    iFaces = datamanager()->readChannel<cv_utils::ImageWithFaces>(this,"FACES");
    target = datamanager()->writeChannel<lms::target::Target>(this, "TARGET");

    return true;
}

bool OpencvFaceToTarget::deinitialize() {
    return true;
}

bool OpencvFaceToTarget::cycle() {
    for(size_t i = 0; i < iFaces->faces.size(); i++){
        target->name = "default";
        target->x = iFaces->faces[i].x + iFaces->faces[i].width / 2;
        target->y = iFaces->faces[i].y + iFaces->faces[i].height / 2;
    }

    return true;
}
