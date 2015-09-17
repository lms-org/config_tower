set(SOURCES
    "src/opencv_face_to_target.cpp"
    "src/interface.cpp"
)

set(HEADERS
    "include/opencv_face_to_target.h"
)

include_directories(include)
add_library(opencv_face_to_target MODULE ${SOURCES} ${HEADERS})
target_link_libraries(opencv_face_to_target PRIVATE lmscore)
