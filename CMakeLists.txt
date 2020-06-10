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

SET(C3D_MATH_LIB c3d)
SET(C3D_VIS_LIB  c3dvision)
SET(Qt_VIS_LIB   qtvision)

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
message("qt- ${QtVision_OUTPUT}")

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
	
	LIST(FILTER e_sources EXCLUDE REGEX "sample\.cpp$")
	LIST(FILTER e_sources EXCLUDE REGEX "mfc_")
	
	FOREACH(header ${e_sources})
	  message(${header})
	ENDFOREACH()
	
	IF(EXISTS "${CMAKE_SOURCE_DIR}/${dir}/resources.qrc")
		QT5_ADD_RESOURCES(RCC_example ${dir}/resources.qrc)
	ENDIF()
    QT5_WRAP_CPP(MOC_example ${qt_headers})
		
	add_executable( ${dir} ${e_headers} ${e_sources} ${MOC_example} ${RCC_example} )
	target_include_directories( ${dir} PRIVATE ${dir} ${C3D_Math_INCLUDE_DIR} ${C3D_Vision_INCLUDE_DIR} ${Qt_Vision_INCLUDE_DIR} )
	target_link_libraries( ${dir} ${C3D_MATH_LIB} ${C3D_VIS_LIB} ${Qt_VIS_LIB} )

	qt5_use_modules( ${dir} Core Gui OpenGL Widgets )
  ENDIF()
ENDMACRO()

# generate examples
SUBDIRLIST(SUBDIRS ${CMAKE_SOURCE_DIR})
FOREACH(subdir ${SUBDIRS})
  MAKE_QT_EXAMPLE(${subdir})
ENDFOREACH()

