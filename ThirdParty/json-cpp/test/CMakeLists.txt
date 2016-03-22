INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src)
SET(VNO_SRCS
    NetworkData.cpp
    IndependentCycle.cpp
    VentNetworkCalc.cpp
    vno.cpp
)
#SET(NL_OPT_LIBRARY nlopt)
ADD_LIBRARY(vno SHARED ${VNO_SRCS})
#TARGET_LINK_LIBRARIES(vno vnf emon ${NL_OPT_LIBRARY} ${PARADISEO_LIBRARIES})
#如果动态库是通过动态链接给外部使用的，那么需要链接dl库
#TARGET_LINK_LIBRARIES(vnf dl)
TARGET_LINK_LIBRARIES(vno vnf emon)
SET(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")
