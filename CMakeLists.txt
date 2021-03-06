﻿################################################################################
#                                                                              #
#  Copyright (c) 2020, C3D Labs LLC                                            #
#  All rights reserved.                                                        #
#                                                                              #
#  This file is part of the C3D Libraries                                      #
#  http://c3dlabs.com                                                          #
#                                                                              #
#                                                                              #
################################################################################

PROJECT(Kernel_Examples)
cmake_minimum_required(VERSION 3.14)

IF(MSVC)
	SET(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG_INIT} -D_DEBUG -D_DRAWGI /Zi /W3 /MP /bigobj") 
	SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE_INIT} -D_SECURE_SCL=0 /W3") 
ELSE()
	SET(CMAKE_CXX_FLAGS_DEBUG  "${CMAKE_CXX_FLAGS_DEBUG_INIT} -D_DRAWGI -Wno-deprecated-declarations -fno-operator-names -fopenmp")
	SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE_INIT} -D_SECURE_SCL=0 -Wno-deprecated-declarations -fno-operator-names -fopenmp")
ENDIF()

# Unicode build
OPTION(EXAMPLES_UNICODE_MODE "Enable Unicode support" ON)
OPTION(GUI_QT5_EXAMPLES "Build Qt5 support" ON)
OPTION(GUI_MFC_EXAMPLES "Build MFC support" OFF)

SET(Examples_OUTPUT "Examples")


# Libraries    
if( NOT C3D_MATH_DIR )
  SET(C3D_MATH_DIR   ${CMAKE_SOURCE_DIR}/c3d-libs/kernel)
endif()

if( NOT C3D_Vision_DIR )
  SET(C3D_Vision_DIR ${CMAKE_SOURCE_DIR}/c3d-libs/vision)
endif()

# Libraries    
if( NOT C3D_Math_INCLUDE_DIR )
  SET(C3D_Math_INCLUDE_DIR   ${C3D_MATH_DIR}/Include)
endif()

if( NOT C3D_Vision_INCLUDE_DIR )
  SET(C3D_Vision_INCLUDE_DIR ${C3D_Vision_DIR}/Include)
endif()

if( NOT Qt_Vision_INCLUDE_DIR )
  SET(Qt_Vision_INCLUDE_DIR platforms/QtVision/Include)
endif()

if( NOT MFC_Vision_INCLUDE_DIR )
  SET(MFC_Vision_INCLUDE_DIR platforms/MfcVision/Include)
endif()

SET(C3D_MATH_LIB c3d)
SET(C3D_VIS_LIB  c3dvision)
SET(Qt_VIS_LIB   qtvision)
SET(MFC_VIS_LIB  mfcvision)

# MSVS
SET(CONFIG_ "$(Configuration)")

# MAKE
if(UNIX)
SET(CONFIG_ "${CMAKE_BUILD_TYPE}")
endif()

link_directories( "${C3D_MATH_DIR}/${CONFIG_}/" )
link_directories( "${C3D_Vision_DIR}/${CONFIG_}/" )

#binary
set(EXAMPLES_BIN ${CMAKE_BINARY_DIR}/bin/)
if( CMAKE_RUNTIME_OUTPUT_DIRECTORY )
    set(EXAMPLES_BIN ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif()

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${EXAMPLES_BIN})
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${EXAMPLES_BIN})
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${EXAMPLES_BIN})


IF(EXAMPLES_UNICODE_MODE)
  ADD_DEFINITIONS( 
    -DUNICODE
    -D_UNICODE
    )
ENDIF(EXAMPLES_UNICODE_MODE)

INCLUDE_DIRECTORIES(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${QT_USE_FILE}
    )

IF(UNIX)
  ADD_DEFINITIONS(
      -std=c++14
  )
  SET(STDLIB stdc++)
ELSE()
  SET(STDLIB "")
ENDIF()

# copy bins 
If( GUI_QT5_EXAMPLES OR GUI_MFC_EXAMPLES )
  #copy external dll, lib, pdb Math and Vision
  file(COPY "${C3D_MATH_DIR}/Debug/"     DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug")
  file(COPY "${C3D_MATH_DIR}/Release/"   DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release")
  file(COPY "${C3D_Vision_DIR}/Debug/"   DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug")
  file(COPY "${C3D_Vision_DIR}/Release/" DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release")
endif()

# add platforms
ADD_SUBDIRECTORY("platforms")

MACRO(SUBDIRLIST result curdir)
  FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
  SET(dirlist "")
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${curdir}/${child})
      LIST(APPEND dirlist ${child})
    ENDIF()
  ENDFOREACH()
  SET(${result} ${dirlist})
ENDMACRO()


#
# - looking for directories contain the "qt_main.cpp" file
# - for all header files begun by "qt_" the macro generates moc file
#
MACRO(MAKE_QT_EXAMPLE dir)
  IF(EXISTS "${CMAKE_SOURCE_DIR}/${dir}/qt_main.cpp")
	FILE(GLOB_RECURSE e_headers "${dir}/*.h")
	FILE(GLOB_RECURSE qt_headers "${dir}/qt_*.h")
	FILE(GLOB_RECURSE e_sources "${dir}/*.cpp")
	
	LIST(FILTER e_sources EXCLUDE REGEX "mfc_")
	
	IF(EXISTS "${CMAKE_SOURCE_DIR}/${dir}/resources.qrc")
		QT5_ADD_RESOURCES(RCC_example ${dir}/resources.qrc)
	ENDIF()
    QT5_WRAP_CPP(MOC_example ${qt_headers})
	
	SET(proj_name qt_${dir})	
	add_executable( ${proj_name} ${e_headers} ${e_sources} ${MOC_example} ${RCC_example} )
	target_include_directories( ${proj_name} PRIVATE ${dir} ${C3D_Math_INCLUDE_DIR} ${C3D_Vision_INCLUDE_DIR} ${Qt_Vision_INCLUDE_DIR} )
	target_link_libraries( ${proj_name} ${C3D_MATH_LIB} ${C3D_VIS_LIB} ${Qt_VIS_LIB} )
	
	qt5_use_modules( ${proj_name} Core Gui OpenGL Widgets )
  ENDIF()
ENDMACRO()


MACRO(MAKE_MFC_EXAMPLE dir)
  IF(EXISTS "${CMAKE_SOURCE_DIR}/${dir}/mfc_main.cpp")
  	FILE(GLOB_RECURSE e_headers "${dir}/*.h")
	FILE(GLOB_RECURSE e_sources "${dir}/*.cpp")
	
	SET(MFC_COMMON_DIR ${MFC_Vision_INCLUDE_DIR}/../Common)
	
	SET(MFC_COMMON
	    ${MFC_COMMON_DIR}/stdafx.cpp
	    ${MFC_COMMON_DIR}/stdafx.h	
	)
	
	LIST(FILTER e_sources EXCLUDE REGEX "qt_")
	
	SET(proj_name mfc_${dir})	
	add_executable( ${proj_name} ${e_headers} ${e_sources} ${MFC_COMMON})
	target_include_directories( ${proj_name} PRIVATE ${dir} ${C3D_Math_INCLUDE_DIR} ${C3D_Vision_INCLUDE_DIR} ${MFC_Vision_INCLUDE_DIR} ${MFC_COMMON_DIR} )
	target_link_libraries( ${proj_name} ${C3D_MATH_LIB} ${C3D_VIS_LIB} ${MFC_VIS_LIB} )

    SET_TARGET_PROPERTIES(${proj_name} PROPERTIES COMPILE_FLAGS -D_AFXDLL)
    IF(EXAMPLES_UNICODE_MODE)
	    SET_TARGET_PROPERTIES(${proj_name} PROPERTIES LINK_FLAGS /ENTRY:wWinMainCRTStartup)
    ENDIF()	
  ENDIF()
ENDMACRO()

# generate examples
SUBDIRLIST(SUBDIRS ${CMAKE_SOURCE_DIR})

IF (GUI_QT5_EXAMPLES)
  FOREACH(subdir ${SUBDIRS})
    MAKE_QT_EXAMPLE(${subdir})
  ENDFOREACH()
ENDIF()

IF (GUI_MFC_EXAMPLES)
  FOREACH(subdir ${SUBDIRS})
    MAKE_MFC_EXAMPLE(${subdir})
  ENDFOREACH()
ENDIF()

