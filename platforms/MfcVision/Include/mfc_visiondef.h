////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Глобальные объявления типов и определения.
         \en Global type declarations and defines. \~
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __MFC_VISIONDEF_H
#define __MFC_VISIONDEF_H

#include <vsn_global.h>

VSN_USE_NAMESPACE
VSN_BEGIN_NAMESPACE

#if defined ( _BUILDMFCVISIONDLL )
#define MFC_CLASS          __declspec( dllexport )
#define MFC_FUNC(retType)  __declspec( dllexport ) retType CALL_DECLARATION
#define MFC_FUNC_EX        __declspec( dllexport ) // \ru для KNOWN_OBJECTS_RW_REF_OPERATORS_EX и KNOWN_OBJECTS_RW_PTR_OPERATORS_EX \en for KNOWN_OBJECTS_RW_REF_OPERATORS_EX and KNOWN_OBJECTS_RW_PTR_OPERATORS_EX 
#else
#define MFC_CLASS         __declspec( dllimport )
#define MFC_FUNC(retType) __declspec( dllimport ) retType CALL_DECLARATION
#define MFC_FUNC_EX       __declspec( dllimport ) 
#endif

VSN_END_NAMESPACE

#endif // __MFC_VISIONDEF_H

