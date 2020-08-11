#ifndef __MVDAPI_INTERNAL_H__
#define __MVDAPI_INTERNAL_H__

/// -----------------------------------------------------------------------------
///
/// @file    MVDAPI_String.h
/// @author  Mike.Guo
/// @version 0.1
/// @date    2020.08.06
/// @brief   MVDAPIӦ�ÿ����ӿں�������ͷ�ļ�(�����ڲ������ĺ����ӿ�)
/// @details ��Щ�ӿ��û����Բ����ã�������ʵ���Զ����ַ���Ϣ��
///
/// -----------------------------------------------------------------------------


#if (defined (_WIN32) || defined(_WIN64))
#    if defined(MVDAPI_EXPORTS)
#        define MVD_API __declspec(dllexport)
#    else
#        define MVD_API __declspec(dllimport)
#    endif

#else
#    define MVD_API
#endif

#ifndef IN
#    define IN
#endif // IN

#ifndef OUT
#    define OUT
#endif // OUT

#ifdef __cplusplus
extern "C" {
#endif 
#include "MVDAPI_TypeDefine.h"

#define MAX_ROI_SIZE_TIEMS_NUM   16

	struct MVD_ROI_SIZE_LIST
	{
		unsigned int     uiRoiSizeItemsNum;
		MVD_ROI_SIZE    *pRoiSizeItem[MAX_ROI_SIZE_TIEMS_NUM];
		TCHAR           *pRoiSizeItemString[MAX_ROI_SIZE_TIEMS_NUM];
	};

	MVD_API int __stdcall GetRoiSizeItems(IN int nIndex, OUT MVD_ROI_SIZE_LIST *pRoiSizeList);


#ifdef __cplusplus
}
#endif

#endif