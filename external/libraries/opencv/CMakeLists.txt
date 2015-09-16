# Find independently installed OpenCV libraries

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

set ( SOURCES
 "foo.cpp"
)

set (HEADERS
)

add_library (opencv_binding SHARED ${SOURCES} ${HEADERS})
target_link_libraries (opencv_binding PUBLIC ${OpenCV_LIBS})
