#ifndef LMS_TARGET_H
#define LMS_TARGET_H

#include <string>

namespace lms {
namespace target {

struct Target {
    /**
     * @brief Horizontal position of the target
     *
     * Value in range [-1, 1], giving the horizontal translation of
     * the target in the visible plane (of the camera).
     *
     * Value -1 means the far left of the visible area.
     * Value 1 means the far right of the visible area.
     * Value 0 means the horizontal center.
     */
    float x;

    /**
     * @brief Vertical position of the target
     *
     * Value in range [-1, 1], giving the vertical translation of
     * the target in the visible plane (of the camera).
     *
     * Value -1 means the far top of the visible area.
     * Value 1 means the far bottom of the visible area.
     * Value 0 means the vertical center.
     */
    float y;

    /**
     * @brief Identifier name
     */
    std::string name;
};

}  // namespace target
}  // namespace lms

#endif // LMS_TARGET_H
