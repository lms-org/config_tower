set(SOURCES
  "src/opencv_face_recognizer.cpp"
  "src/interface.cpp"
)

set(HEADERS
	"include/opencv_face_recognizer.h"
)

include_directories(include)
add_library(opencv_face_recognizer MODULE ${SOURCES} ${HEADERS})
target_link_libraries(opencv_face_recognizer PRIVATE lmscore opencv_binding)
