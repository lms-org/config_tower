set(SOURCES
    src/target.cpp
)

set(HEADERS
    include/target/target.h
)

include_directories(include)
add_library(target SHARED ${SOURCES} ${HEADERS})
target_link_libraries(target PRIVATE lmscore)
