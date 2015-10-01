set(SOURCES
    "src/to_sense_link.cpp"
    "src/interface.cpp"
)

set(HEADERS
    "include/to_sense_link.h"
)

include_directories(include)
add_library(to_sense_link MODULE ${SOURCES} ${HEADERS})
target_link_libraries(to_sense_link PRIVATE lmscore sense_link)
