set ( SOURCES
    "src/face_detector.cpp"
    "src/interface.cpp"
)

set (HEADERS
    "include/face_detector.h"
)

include_directories("include")

add_library ( opencv_face_detector MODULE ${SOURCES} ${HEADERS})
target_link_libraries(opencv_face_detector PRIVATE lmscore imaging opencv_binding)
