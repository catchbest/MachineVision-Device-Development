
//-----------------------------------------------------------------------------
// ��Ȩ�����Ӽ�
// �ļ����ƣ�MVD_Base.h
// ��Ҫ�������Ӿ��豸�������ƽӿں���

// �������ڣ�2020-2-24
// ��ǰ�汾��
// ���ߣ�Mike
// ˵���������ܼ򻯽ӿ�������������������

// �޸����ڣ� 
// ��ǰ�汾��
// ���ߣ�
// ˵����
//-----------------------------------------------------------------------------

//copyright��

//file��
//summy��

//date��
//version��
//author��
//modify��



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
	// ������MVD_Initial
	// ���ܣ���ʼ��SDK�⣬��ö��ָ���ӿڵ��豸���������豸��Ϣ�б�
	// ������
	//      nDeviceInterfaceType�� ���룬�趨Ҫö�ٵ��豸�ӿ����ͣ���ο�MVD_DEVICE_INTERFACE_TYPEö�����͵Ķ��壬�ɽ�����ϡ�
	//      MVD_DEVICE_INFO_LIST pstDeviceInfoList��������ɹ����غ��豸��Ϣ�ᱻ��д���˽ṹ�С�
	// ���أ�����MVD_SUCCESS��ʾ�ɹ���
	// ˵�����˺��������������ã�����MVD_Uninitial֮������ٴε��á����н�����豸����������ﱻȷ����
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
	// ������MVD_Uninitial
	// ���ܣ�����ʼ��SDK�⣬�ͷ�������Դ���Զ��ر�û�йرյ��豸��
	// ������
	//      ��
	// ���أ�����MVD_SUCCESS��ʾ�ɹ���
	// ˵�����˺��������ڽ����˳�֮ǰ�����ã����ͷſ���������Դ��Ҳ���Գ����е��ã�Ȼ���ٴε���MVD_Initial�����³�ʼ���Ⲣ��ȡ�豸��Ϣ�б�
	//-----------------------------------------------------------------------------
	MVD_API int __stdcall MVD_Uninitial();

	//-----------------------------------------------------------------------------
	// ������MVD_QueryInfo
	// ���ܣ���ѯ�豸����Ϣ
	// ������
	//      MVD_QUERY_INFO_TYPE enQueryInfoType�� ���룻ָ����ѯ��Ϣ����������ο�MVD_QUERY_INFO_TYPEö������˵��
	//      MVD_QUERY_INFO      pstQueryInfo��    �����������Ϣ���ݣ���ο�MVD_QUERY_INFO�ṹ˵��
	// ���أ�����MVD_SUCCESS��ʾ�ɹ�
	// ˵����MVD_Initial���óɹ�֮�󼴿ɵ��á���Щ��Ϣ�Ĳ�ѯ��Ҫ�ڵ���MVD_OpenDevice�ɹ�֮����е��á�
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

	// ����Ҫ�ɼ�֮ǰ�������
	MVD_API int __stdcall MVD_StartGrabbing(IN int nIndex);
	MVD_API int __stdcall MVD_StopGrabbing(IN int nIndex);

	// ���������Ϣ��Ч������ڿ����ص������ʾ����Ӧ�Ĵ���
	MVD_API int __stdcall MVD_SetDisplayPosition(IN int nIndex, MVD_DISPLAY_POSITION_INFO stDisplayPositionInfo);
	MVD_API int __stdcall MVD_GetDisplayPosition(IN int nIndex, MVD_DISPLAY_POSITION_INFO *pstDisplayPositionInfo);
	

	MVD_API int __stdcall MVD_SetCallBack(IN int nIndex, MVD_IMAGE_CALLBACK pfImageCallback, void* pUser);
	MVD_API int __stdcall MVD_StartCallback(IN int nIndex);
	MVD_API int __stdcall MVD_StopCallback(IN int nIndex);

	// ����MVD_GrabImage֮ǰ���������MVD_StartGrabbing������Ƶ��������ڴ���SDK���䣬�û�����Ҫ�����ڴ档ʹ��֮����Ҫ����MVD_GrabImageRelease
	MVD_API int __stdcall MVD_GrabImage(IN const int nIndex, OUT MVD_FRAME_OUT **ppImageOut);

	// ÿ�ε���MVD_GrabImage֮����Ҫ֪ͨSDK�����ٴ�ʹ���ڴ�
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

	// ��һ�����������Ե������öԻ���
	// ������MVD_Initial֮�����
	MVD_API int __stdcall MVD_OpenSettings(void *hWndParent, int nLeft, int nTop);
	MVD_API int __stdcall MVD_CloseSettings();




#ifdef __cplusplus
}
#endif 

#endif //_MV_BASE_H_