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
PROJECT(QtVision)
cmake_minimum_required(VERSION 3.14)

SET(DESIRED_QT_VERSION "5" CACHE STRING "")
find_package( Qt5 COMPONENTS Core Gui OpenGL )

SET(QtCore_SRC
	./src/qt_openglwidget.cpp
	./src/qt_openglcontext.cpp
)
SOURCE_GROUP(\\Core FILES ${QtCore_SRC})

SET(MOC_Files 
	./Include/qt_openglwidget.h
	./Include/qt_exampleview.h
  )
QT5_WRAP_CPP(MOC_Gui ${MOC_Files})

SET(QtVision_INC
	./Include/qt_openglcontext.h
	./Include/qt_openglwidget.h
	./Include/qt_visiondef.h
	./Include/qt_resstream.h
	./Include/lisencekey.h
)
SOURCE_GROUP(Include FILES ${QtVision_INC})


IF(MathTest_NAMES)
  STRING(REPLACE "Source" "Revisions" MATH_INSTALL_DIR ${CMAKE_SOURCE_DIR})
ELSE()
  STRING(REPLACE "Source" "Install" MATH_INSTALL_DIR ${CMAKE_SOURCE_DIR})
ENDIF()

INCLUDE_DIRECTORIES(
    Include/
    ${C3D_Math_INCLUDE_DIR}
    ${C3D_Vision_INCLUDE_DIR}
)

IF(MSVC)
ADD_DEFINITIONS( 
  -D_WIN32_WINNT=0X0502
  )
ENDIF()

ADD_DEFINITIONS(
	-D_BUILDQTVISIONDLL
	-D__TEST_ONLY__
	-DOGLFT_NO_QT
	-DOGLFT_NO_SOLID
	-DVSN_COMPILER_EXPLICIT_OVERRIDES
	-DNOMINMAX
  )

IF (UNIX)
  ADD_DEFINITIONS(
    -DVSN_OS_UNIX
    )
#  ADD_DEFINITIONS(-D_GLIBCXX_USE_CXX11_ABI=0)
ELSE()
  ADD_DEFINITIONS(
    -DVSN_OS_WIN32
    -DVSN_OS_WIN
    )
ENDIF()

IF(MSVC)
  IF(C3DVision_USING_UNICODE)
    ADD_DEFINITIONS( 
      -DUNICODE
      -D_UNICODE
      -DVSN_DEBUG
      )
  ENDIF(C3DVision_USING_UNICODE)
ENDIF()

ADD_DEFINITIONS( 
  -D__USE_QT__
)

# метод сборки библиотеки
SET(QtVisionBuildMethod SHARED)
IF (C3DVision_FOR_VIEWER)
  SET(QtVisionBuildMethod STATIC)
ENDIF()
  
ADD_LIBRARY(${QtVision_OUTPUT} ${QtVisionBuildMethod} 
  ${QtCore_SRC} 
  ${QtVision_INC} 
  ${MOC_Gui}
)

message(STATUS "qtvision cxx: ${CMAKE_CXX_FLAGS}")

QT5_USE_MODULES(${QtVision_OUTPUT} Core Gui OpenGL Widgets)

IF (UNIX)
  SET(CMAKE_SHARED_LINKER_FLAGS "-static-libgcc -static-libstdc++")
ENDIF()

IF(MSVC) 
 TARGET_LINK_LIBRARIES(
	${QtVision_OUTPUT}
	${C3D_VIS_LIB}
	${C3D_MATH_LIB}
    opengl32
    glu32
    )
ELSE()
    find_package(OpenGL REQUIRED)
    TARGET_LINK_LIBRARIES(
      ${QtVision_OUTPUT}
      ${C3D_VIS_LIB}
      ${C3D_MATH_LIB}
      ${OPENGL_LIBRARIES}
      ${GLU_LIBRARY}
    )
ENDIF()