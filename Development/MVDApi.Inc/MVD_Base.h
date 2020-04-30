
//-----------------------------------------------------------------------------
// 版权：凯视佳
// 文件名称：MVD_Base.h
// 简要描述：视觉设备基础控制接口函数

// 创建日期：2020-2-24
// 当前版本：
// 作者：Mike
// 说明：尽可能简化接口数量，明晰调用流程

// 修改日期： 
// 当前版本：
// 作者：
// 说明：
//-----------------------------------------------------------------------------

//copyright：

//file：
//summy：

//date：
//version：
//author：
//modify：



#ifndef _MVD_BASE_H_
#define _MVD_BASE_H_

#ifndef MVD_API

#if (defined (_WIN32) || defined(WIN64))
#if defined(MVDAPI_EXPORTS)
#define MVD_API __declspec(dllexport)
#else
#define MVD_API __declspec(dllimport)
#endif

#else

#ifndef __stdcall
#define __stdcall
#endif

#ifndef MVD_API
#define  MVD_API
#endif

#endif

#endif

#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

#include "MVD_ParamType.h"

#ifdef __cplusplus
extern "C" {
#endif 

	//-----------------------------------------------------------------------------
	// 函数：MVD_Initial
	// 功能：初始化SDK库，并枚举指定接口的设备，并返回设备信息列表
	// 参数：
	//      nDeviceInterfaceType： 输入，设定要枚举的设备接口类型，请参考MVD_DEVICE_INTERFACE_TYPE枚举类型的定义，可进行组合。
	//      MVD_DEVICE_INFO_LIST pstDeviceInfoList：输出，成功返回后，设备信息会被填写进此结构中。
	// 返回：返回MVD_SUCCESS表示成功。
	// 说明：此函数不可连续调用，调用MVD_Uninitial之后可以再次调用。所有接入的设备在这个函数里被确定。
	//-----------------------------------------------------------------------------
	MVD_API int __stdcall MVD_InitialA(IN const unsigned int nDeviceInterfaceType, IN OUT MVD_DEVICE_INFO_LIST_A* pstDeviceInfoList);
	MVD_API int __stdcall MVD_InitialW(IN const unsigned int nDeviceInterfaceType, IN OUT MVD_DEVICE_INFO_LIST_W* pstDeviceInfoList);

#ifdef UNICODE
	typedef MVD_DEVICE_INFO_W      MVD_DEVICE_INFO;
	typedef MVD_DEVICE_INFO_LIST_W MVD_DEVICE_INFO_LIST;
    #define MVD_Initial  MVD_InitialW
#else
	typedef MVD_DEVICE_INFO_A      MVD_DEVICE_INFO;
	typedef MVD_DEVICE_INFO_LIST_A MVD_DEVICE_INFO_LIST;
    #define MVD_Initial  MVD_InitialA
#endif

	//-----------------------------------------------------------------------------
	// 函数：MVD_Uninitial
	// 功能：反初始化SDK库，释放所有资源并自动关闭没有关闭的设备。
	// 参数：
	//      无
	// 返回：返回MVD_SUCCESS表示成功。
	// 说明：此函数必须在进程退出之前被调用，以释放库里分配的资源。也可以程序中调用，然后再次调用MVD_Initial以重新初始化库并获取设备信息列表。
	//-----------------------------------------------------------------------------
	MVD_API int __stdcall MVD_Uninitial();

	//-----------------------------------------------------------------------------
	// 函数：MVD_QueryInfo
	// 功能：查询设备的信息
	// 参数：
	//      MVD_QUERY_INFO_TYPE enQueryInfoType： 输入；指定查询信息的类型详情参考MVD_QUERY_INFO_TYPE枚举类型说明
	//      MVD_QUERY_INFO      pstQueryInfo：    输出；返回信息内容，请参考MVD_QUERY_INFO结构说明
	// 返回：返回MVD_SUCCESS表示成功
	// 说明：MVD_Initial调用成功之后即可调用。有些信息的查询需要在调用MVD_OpenDevice成功之后进行调用。
	//-----------------------------------------------------------------------------
	MVD_API int __stdcall MVD_QueryInfoA(IN int nIndex, IN MVD_QUERY_INFO_TYPE enQueryInfoType, OUT MVD_QUERY_INFO_A *pstQueryInfo);
	MVD_API int __stdcall MVD_QueryInfoW(IN int nIndex, IN MVD_QUERY_INFO_TYPE enQueryInfoType, OUT MVD_QUERY_INFO_W *pstQueryInfo);


#ifdef UNICODE
	typedef MVD_QUERY_INFO_W MVD_QUERY_INFO;
#define MVD_QueryInfo  MVD_QueryInfoW
#else
	typedef MVD_QUERY_INFO_A MVD_QUERY_INFO;
#define MVD_QueryInfo  MVD_QueryInfoA
#endif


	MVD_API int __stdcall MVD_OpenDevice(IN const int nIndex);
	MVD_API int __stdcall MVD_CloseDevice(IN const int nIndex);

	// 在需要采集之前必须调用
	MVD_API int __stdcall MVD_StartGrabbing(IN int nIndex);
	MVD_API int __stdcall MVD_StopGrabbing(IN int nIndex);

	// 如果窗口信息有效，则会在开启回调后会显示在相应的窗口
	MVD_API int __stdcall MVD_SetDisplayPosition(IN int nIndex, MVD_DISPLAY_POSITION_INFO stDisplayPositionInfo);
	MVD_API int __stdcall MVD_GetDisplayPosition(IN int nIndex, MVD_DISPLAY_POSITION_INFO *pstDisplayPositionInfo);
	

	MVD_API int __stdcall MVD_SetCallBack(IN int nIndex, MVD_IMAGE_CALLBACK pfImageCallback, void* pUser);
	MVD_API int __stdcall MVD_StartCallback(IN int nIndex);
	MVD_API int __stdcall MVD_StopCallback(IN int nIndex);

	// 调用MVD_GrabImage之前，必须调用MVD_StartGrabbing开启视频流，这个内存由SDK分配，用户不需要分配内存。使用之后需要调用MVD_GrabImageRelease
	MVD_API int __stdcall MVD_GrabImage(IN const int nIndex, OUT MVD_FRAME_OUT **ppImageOut);

	// 每次调用MVD_GrabImage之后，需要通知SDK可以再次使用内存
	MVD_API int __stdcall MVD_GrabImageRelease(IN const int nIndex);

	MVD_API int __stdcall MVD_SaveImageA(IN const MVD_FRAME_OUT *pstImageOut, IN const MVD_SAVE_IMAGE_PARAM_A *pstSaveParam);
	MVD_API int __stdcall MVD_SaveImageW(IN const MVD_FRAME_OUT *pstImageOut, IN const MVD_SAVE_IMAGE_PARAM_W *pstSaveParam);

#ifdef UNICODE
	typedef MVD_SAVE_IMAGE_PARAM_W MVD_SAVE_IMAGE_PARAM;
#define MVD_SaveImage  MVD_SaveImageW
#else
	typedef MVD_SAVE_IMAGE_PARAM_A MVD_SAVE_IMAGE_PARAM;
#define MVD_SaveImage  MVD_SaveImageA
#endif


	MVD_API int __stdcall MVD_GetParamA(IN int nIndex, IN const char    *pszParamName, OUT MVD_GET_PARAME_VALUE_A *pstGetParamValue);
	MVD_API int __stdcall MVD_GetParamW(IN int nIndex, IN const wchar_t *pszParamName, OUT MVD_GET_PARAME_VALUE_W *pstGetParamValue);

#ifdef UNICODE
	typedef MVD_GET_PARAME_VALUE_W MVD_GET_PARAME_VALUE;
#define MVD_GetParam  MVD_GetParamW
#else
	typedef MVD_GET_PARAME_VALUE_A MVD_GET_PARAME_VALUE;
#define MVD_GetParam  MVD_GetParamA
#endif

	MVD_API int __stdcall MVD_SetParamA(IN int nIndex, IN const char    *pszParamName, IN MVD_SET_PARAME_VALUE_A stSetParamValue);
	MVD_API int __stdcall MVD_SetParamW(IN int nIndex, IN const wchar_t *pszParamName, IN MVD_SET_PARAME_VALUE_W stSetParamValue);

#ifdef UNICODE
	typedef MVD_SET_PARAME_VALUE_W MVD_SET_PARAME_VALUE;
#define MVD_SetParam  MVD_SetParamW
#else
	typedef MVD_SET_PARAME_VALUE_A MVD_SET_PARAME_VALUE;
#define MVD_SetParam  MVD_SetParamA
#endif

	MVD_API int __stdcall MVD_ExecuteCommandA(IN int nIndex, IN const char    *pszCommandName);
	MVD_API int __stdcall MVD_ExecuteCommandW(IN int nIndex, IN const wchar_t *pszCommandName);

#ifdef UNICODE
#define MVD_ExecuteCommand  MVD_ExecuteCommandW
#else
#define MVD_ExecuteCommand  MVD_ExecuteCommandA
#endif

	// 做一个函数，可以弹出设置对话框
	// 必须在MVD_Initial之后调用
	MVD_API int __stdcall MVD_OpenSettings(void *hWndParent, int nLeft, int nTop);
	MVD_API int __stdcall MVD_CloseSettings();




#ifdef __cplusplus
}
#endif 

#endif //_MV_BASE_H_