#pragma once

#include <lms/datamanager.h>
#include <lms/module.h>
#include <lms/type/module_config.h>
#include <lms/imaging/image.h>

namespace lms_opencv {

class FaceDetector : public lms::Module {
public:

    bool initialize();
    bool deinitialize();

    bool cycle();
};

}  // namespace lms_opencv
