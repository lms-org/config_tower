set(SOURCES
  "src/opencv_blob_detector.cpp"
  "src/interface.cpp"
)

set(HEADERS
	"include/opencv_blob_detector.h"
)

include_directories(include)
add_library(opencv_blob_detector MODULE ${SOURCES} ${HEADERS})
target_link_libraries(opencv_blob_detector PRIVATE lmscore imaging opencv_binding)
