set(HEADER_FILES
        inc/RSAE.h
        )

set(SOURCE_FILES
         src/RSAE.cpp)
include_directories(inc)
add_library(lab10_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})
#target_link_libraries(lab10_lib)