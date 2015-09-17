set(SOURCES
  "src/opencv_face_logger.cpp"
  "src/interface.cpp"
)

set(HEADERS
	"include/opencv_face_logger.h"
)

include_directories("include")

add_library(opencv_face_logger MODULE ${SOURCES} ${HEADERS})
target_link_libraries(opencv_face_logger PRIVATE lmscore opencv_binding imaging)
