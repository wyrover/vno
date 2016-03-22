INCLUDE_DIRECTORIES(
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    )

FILE(GLOB_RECURSE JSON_INCS "${CMAKE_CURRENT_SOURCE_DIR}/../include/*.h")

SET(JSON_SRCS
    json_value.cpp
    json_writer.cpp
    json_reader.cpp
)

ADD_LIBRARY(jsoncpp STATIC ${JSON_SRCS} ${JSON_INCS})
#TARGET_LINK_LIBRARIES(vno vnf emon ${NL_OPT_LIBRARY} ${PARADISEO_LIBRARIES})
#如果动态库是通过动态链接给外部使用的,那么需要链接dl库
#TARGET_LINK_LIBRARIES(jsoncpp dl)
SET(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")
