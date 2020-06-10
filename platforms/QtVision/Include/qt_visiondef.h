////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Глобальные объявления типов и определения.
         \en Global type declarations and defines. \~
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __QT_VISIONDEF_H
#define __QT_VISIONDEF_H

#include <vsn_global.h>

VSN_USE_NAMESPACE
VSN_BEGIN_NAMESPACE

#if /*_MSC_VER*/defined(_WIN32) && !defined(QT_VISION_STATIC) /* only windows dll */
#if defined ( _BUILDQTVISIONDLL )
#define QT_CLASS          __declspec( dllexport )
#define QT_FUNC(retType)  __declspec( dllexport ) retType CALL_DECLARATION
#define QT_FUNC_EX        __declspec( dllexport ) // \ru для KNOWN_OBJECTS_RW_REF_OPERATORS_EX и KNOWN_OBJECTS_RW_PTR_OPERATORS_EX \en for KNOWN_OBJECTS_RW_REF_OPERATORS_EX and KNOWN_OBJECTS_RW_PTR_OPERATORS_EX 
#else
#define QT_CLASS         __declspec( dllimport )
#define QT_FUNC(retType) __declspec( dllimport ) retType CALL_DECLARATION
#define QT_FUNC_EX       __declspec( dllimport ) 
#endif
#else // _MSC_VER
#define QT_CLASS
#define QT_FUNC(retType) retType
#define QT_FUNC_EX
#endif

VSN_END_NAMESPACE

#endif //__QT_VISIONDEF_H

