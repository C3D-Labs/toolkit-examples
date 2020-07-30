################################################################################
#                                                                              #
#  Copyright (c) 2018, C3D Labs LLC                                            #
#  All rights reserved.                                                        #
#                                                                              #
#  This file is part of C3DVision Library                                      #
#  http://c3dlabs.com                                                          #
#                                                                              #
#  Exclusive rights to C3D Vision, any copies or components (parts) thereof    #
#  and other intellectual property belong to C3D Labs, LLC (the Rightholder).  # 
#  The license rights and restrictions are regulated by the Agreement between  #
#  the User and the Rightholder.                                               #
#                                                                              #
################################################################################
CMAKE_MINIMUM_REQUIRED(VERSION 3.4)
PROJECT(MfcVision)


SET(MfcCore_SRC
    ./src/mfc_stdafx.cpp
    ./src/mfc_openglview.cpp
    ./src/mfc_openglwnd.cpp
    ./src/mfc_scenerenderer.cpp
    ./src/mfc_licensewnd.cpp
    ./src/mfc_exampleview.cpp
    ./src/mfc_exampletools.cpp
)
SOURCE_GROUP(\\Core FILES ${MfcCore_SRC})


SET(MfcVision_INC
    ./include/mfc_stdafx.h
    ./include/mfc_openglview.h
    ./include/mfc_openglwnd.h
    ./include/mfc_scenerenderer.h
    ./include/mfc_scenerendererprivate.h
    ./include/mfc_exampleview.h
    ./include/mfc_exampletools.h
    ./include/mfc_licensewnd.h
    ./include/mfc_visiondef.h
)
SOURCE_GROUP(Include FILES ${MfcVision_INC})

INCLUDE_DIRECTORIES(
    ${VLD_INCLUDE_DIRS}
    ${MfcVision_SOURCE_DIR}/include
    ${C3D_Math_INCLUDE_DIR}/
    ${C3D_Vision_INCLUDE_DIR}/
)

ADD_DEFINITIONS( 
  -D_WIN32_WINNT=0X0502
  )

ADD_DEFINITIONS(
    -D_BUILDMFCVISIONDLL
    -D__TEST_ONLY__
    -DOGLFT_NO_SOLID
    -DVSN_COMPILER_EXPLICIT_OVERRIDES
    -DNOMINMAX
    -D_AFXDLL
  )

ADD_DEFINITIONS(-DVSN_OS_WIN32 -DVSN_OS_WIN)

IF(C3DVision_USING_UNICODE)
    ADD_DEFINITIONS( 
    -DUNICODE
    -D_UNICODE
    )
ENDIF(C3DVision_USING_UNICODE)

SET(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG_INIT} -D_DEBUG -D_DRAWGI /Zi /W3 /MP /bigobj")
SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE_INIT} -D_SECURE_SCL=0 /W3")

ADD_LIBRARY(${MfcVision_OUTPUT} SHARED ${MfcCore_SRC} ${MfcVision_INC})

TARGET_LINK_LIBRARIES(
    ${MfcVision_OUTPUT}
    ${C3D_VIS_LIB}
    ${C3D_MATH_LIB}
    opengl32
    glu32
)
