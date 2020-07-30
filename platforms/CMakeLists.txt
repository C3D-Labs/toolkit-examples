################################################################################
#                                                                              #
#  Copyright (c) 2020, C3D Labs LLC                                            #
#  All rights reserved.                                                        #
#                                                                              #
#  This file is part of the C3D Libraries                                      #
#  http://c3dlabs.com                                                          #
#                                                                              #
#                                                                              #
################################################################################

PROJECT(app_platforms)
cmake_minimum_required(VERSION 3.14)

IF(MSVC)
	SET(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG_INIT} -D_DEBUG -D_DRAWGI /Zi /W3 /MP /bigobj") 
	SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE_INIT} -D_SECURE_SCL=0 /W3") 
ELSE()
	SET(CMAKE_CXX_FLAGS_DEBUG  "${CMAKE_CXX_FLAGS_DEBUG_INIT} -D_DRAWGI -Wno-deprecated-declarations -fno-operator-names -fopenmp")
	SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE_INIT} -D_SECURE_SCL=0 -Wno-deprecated-declarations -fno-operator-names -fopenmp")
ENDIF()


#------------------------------------
#
#  QT Examples
#
#------------------------------------
IF (GUI_QT5_EXAMPLES)
  SET(DESIRED_QT_VERSION "5" CACHE STRING "")
  find_package( Qt5Core REQUIRED )
  find_package( Qt5Gui REQUIRED )
  find_package( Qt5OpenGL REQUIRED )
  
  ADD_DEFINITIONS(-D__USE_QT__)
  ADD_DEFINITIONS(-DQT_NO_DEPRECATED_WARNINGS)

  SET(QtVision_OUTPUT ${Qt_VIS_LIB})
  SET(QtVision_DIR QtVision)
  ADD_SUBDIRECTORY(QtVision)
  
  ADD_DEFINITIONS( -DNOMINMAX )
ENDIF()


#------------------------------------
#
#  MFC Examples
#
#------------------------------------
IF (GUI_MFC_EXAMPLES)
  SET(MfcVision_OUTPUT "mfcvision")
  SET(Examples_MFC_OUTPUT ${Qt_VIS_LIB}/MFC/)
  SET(QtVision_DIR QtVision)
  ADD_SUBDIRECTORY(MfcVision)
ENDIF()
