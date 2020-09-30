#ifndef __MVDAPI_H__
#define __MVDAPI_H__

/// -----------------------------------------------------------------------------
///
/// @file    MVDAPI.h
/// @author  Mike
/// @version 0.1
/// @date    2020.08.06
/// @brief   MVDAPIӦ�ÿ����ӿں�������ͷ�ļ�
/// @details ����Get��ʼ�ĺ���������ж���ɻ�ȡ�Ĳ���ʱ������ֻ����һ��������Ч��ַ�������ȡ�Ĳ���ֻ�贫��NULLָ�롣
///          ����û����ȷ�涨���÷�Χ�Ͳ����ģ���Ҫ�ο�ֵ���������ͣ����������͵���С�����ֵΪ���ݡ�
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

#include "MVDAPI_ReturnCode.h"
#include "MVDAPI_TypeDefine.h"
#include "MVDAPI_String.h"

	namespace MVD
	{

		/** \defgroup Global

		* This is the Global group

		*/

	/// -----------------------------------------------------------------------------
	///
	/// @ingroup   Global
	/// @brief     ��ȡMVDAPI�������汾��
	/// @param     [OUT]pSdkVersion  ����SDK�汾�š�
	///
	/// -----------------------------------------------------------------------------
	MVD_API MVD_ReturnCode __stdcall GetSdkVersion(OUT MVD_VERSION *pSdkVersion);

	/// -----------------------------------------------------------------------------
	///
	/// @ingroup   Global
	/// @brief     ���ÿ�����ʹ�õ����ԡ�
	/// @attention ���Ե����ý�Ӱ��MVDAPI_String.h�к������ص��ַ�����Ϣ(������Ч)�Լ�OpenSettingPage�������Ϣ���ٴδ���Ч����
	/// @param     [IN]Language    ���õ�����
	///
	/// -----------------------------------------------------------------------------
	MVD_API MVD_ReturnCode __stdcall SetLanguage(IN MVD_LANGUAGE Language);

	/// -----------------------------------------------------------------------------
	///
	/// @ingroup   Global
	/// @brief     ��ȡ������ʹ�õ�����
	/// @param     [OUT]pLanguage   ���ص�ǰ���õ����ԡ�
	///
	/// -----------------------------------------------------------------------------
	MVD_API MVD_ReturnCode __stdcall GetLanguage(IN MVD_LANGUAGE *pLanguage);

	/** \defgroup Device

	* �豸��ʼ�����򿪡��رա�����ʼ������

	*/

    /// -----------------------------------------------------------------------------
	///
	/// @ingroup   Device
	/// @brief     ��ʼ��SDK�⣬ö��ָ���ӿڵ��豸���������豸��Ϣ�б�
    /// @attention �˺������������ã����������ò���ı��豸����Ŀ����Ҫ����Uninitial֮���ٴε��ô˺����ſ����»�ȡ�������豸��Ŀ����Ϣ��
	/// @attention �û���ȡ����MVD_DEVICE_INFORMATIONָ�������ͨ������GetDeviceIndex����ȡ�豸��������nIndex��
	/// @attention pstDeviceInfoListָ��SDK�ڲ����ڴ��ַ����ε�ַ�û������޸ġ�
    /// @param     [IN]nDeviceInterfaceType �趨Ҫö�ٵ��豸�ӿ����ͣ���ο�MVD_DEVICE_INTERFACE_TYPEö�����͵Ķ��壬�ɽ�����ϡ�
    /// @param     [OUT]pstDeviceInfoList   �ɹ����غ��豸��Ϣ��ָ��ᱻ��д���˽ṹ�С�
    /// @return    MVD_SUCCESS              ��ʾ�ɹ��� ��������ֵ��ο�MVDAPI_ReturnCode.hͷ�ļ���
	/// @see       MVD_DEVICE_INTERFACE_TYPE
	///
    /// -----------------------------------------------------------------------------
	MVD_API MVD_ReturnCode __stdcall Initial(IN const unsigned int uiDeviceInterfaceType, OUT MVD_DEVICE_INFORMATION_LIST* pstDeviceInformationList);



    /// -----------------------------------------------------------------------------
	///
	/// @ingroup   Device
	/// @brief     ����ʼ��SDK�⣬�ͷ�������Դ���Զ��ر�û�йرյ��豸��
    /// @attention �˺��������ڽ����˳�֮ǰ�����ã����ͷſ���������Դ��Ҳ�����ڳ��������е��ã�Ȼ���ٴε���MVD_Initial�����³�ʼ���Ⲣ��ȡ�豸��Ϣ�б�
    /// @param     �ޡ�
	/// @return    MVD_SUCCESS              ��ʾ�ɹ��� ��������ֵ��ο�MVDAPI_ReturnCode.hͷ�ļ���
	/// @see       Initial
	///
	/// -----------------------------------------------------------------------------
	MVD_API MVD_ReturnCode __stdcall Uninitial();

	/// -----------------------------------------------------------------------------
	/// @ingroup   Device
	/// @brief     �����豸���к�
	/// @attention �豸���к���ͬ�ͺ��豸������ݵ�Ψһ��ʶ�������̨�豸ʹ�ã��豣֤ͬһ�ͺ��豸���в�ͬ���豸���к�
	/// @return    MVD_SUCCESS              ��ʾ�ɹ��� ��������ֵ��ο�MVDAPI_ReturnCode.hͷ�ļ���
	/// @see       MVDAPI_ReturnCode.h
	///
	/// -----------------------------------------------------------------------------
	MVD_API MVD_ReturnCode __stdcall SetDeviceSerialNumber(IN int nIndex, unsigned int uiSerialNumber);

	/// -----------------------------------------------------------------------------
	///
	/// @ingroup   Device
	/// @brief     ��ȡ�豸���к�
	/// @return    MVD_SUCCESS              ��ʾ�ɹ��� ��������ֵ��ο�MVDAPI_ReturnCode.hͷ�ļ���
	/// @see       MVDAPI_ReturnCode.h
	///
	/// -----------------------------------------------------------------------------
	MVD_API MVD_ReturnCode __stdcall GetDeviceSerialNumber(IN int nIndex, unsigned int *puiSerialNumber);

	/// -----------------------------------------------------------------------------
	///
	/// @ingroup   Device
	/// @brief     ͨ���豸��Ϣ����ȡ�豸����Ӧ������������������Կ���������豸�ľ��)��
	/// @attention ���ڶ�̨�豸����ʱ��һ��Ҫ�ȵ������������ȷ���豸������ֵ���������ֵ����Ϊ���豸���������ĵ�һ��������ע�ⲻ���ж�̨�豸��Ϣ��ͬ���豸ͬʱ���ڡ�
	/// @attention pDeviceInformation��Ҫʹ��ͨ������Initial��ȡ�����豸��Ϣָ���������ָ�룬ע�����������ͨ��ָ���жϣ����Բ�Ҫ���Լ����䱣���豸����Ϣ���д��롣
	/// @param     [IN]pDeviceInformation 
	/// @return    MVD_SUCCESS              ��ʾ�ɹ��� ��������ֵ��ο�MVDAPI_ReturnCode.hͷ�ļ���
	///
	/// -----------------------------------------------------------------------------
	MVD_API int __stdcall GetDeviceIndex(IN MVD_DEVICE_INFORMATION *pDeviceInformation);

	/// -----------------------------------------------------------------------------
	///
	/// @ingroup   Device
	/// @brief     ͨ��������ȡ�豸��Ϣ��
	/// @attention ע�⣬��ȡ����SDK�ڲ���Ӧ���豸��Ϣ�ڴ��ַ���û����ɸ�д������
	/// @return    MVD_SUCCESS              ��ʾ�ɹ��� ��������ֵ��ο�MVDAPI_ReturnCode.hͷ�ļ���
	///
	/// -----------------------------------------------------------------------------
	MVD_API MVD_ReturnCode __stdcall GetDeviceInformation(IN int nIndex, OUT MVD_DEVICE_INFORMATION **ppDeviceInformation);

	/// -----------------------------------------------------------------------------
	/// 
	/// @ingroup   Device
	/// @~chinese
	/// @brief     �򿪻�ر�ָ�����豸
	/// @attention ����̿���ʱ��ֻ����������û�д򿪴��豸���ſ��Զ���򿪲�����
	/// @return    MVD_SUCCESS              ��ʾ�ɹ��� ��������ֵ��ο�MVDAPI_ReturnCode.hͷ�ļ���
	///
	/// -----------------------------------------------------------------------------
	MVD_API MVD_ReturnCode __stdcall SetDeviceOpen(IN int nIndex, bool bOpen);


	/// -----------------------------------------------------------------------------
	///
	/// @ingroup   Device
	/// @~chinese
	/// @brief     ��ȡ�豸����״̬
	/// @attention �����̻����������Ƿ���豸��
	/// @return    MVD_SUCCESS              ��ʾ�ɹ��� ��������ֵ��ο�MVDAPI_ReturnCode.hͷ�ļ���
	///
	/// @~english
	/// @brief     Get Device Open Status
	/// @attention The Status Of Current Process or Other Process Open Status
	/// @return    MVD_SUCCESS              Success. Other return code refer to MVDAPI_ReturnCode.h.
	///
	/// -----------------------------------------------------------------------------
	MVD_API MVD_ReturnCode __stdcall GetDeviceOpen(IN int nIndex, bool *pbOpen);

	/** \defgroup Roi

	* �ӳ�������غ���

	*/

	/// -----------------------------------------------------------------------------
	///
	/// @ingroup   Roi
	/// @brief     ��ȡĬ������ROI(����Ȥ����)��Ϣ��
	/// @attention Ĭ��ROIҲ����ͼ�񴫸�������ӳ�ʱ�����á�
	/// @param     [IN]nIndex         �豸��Ӧ��������ͨ��GetDeviceIndex��ȡ��
	/// @param     [OUT]pRoiMaxSize   ROI(����Ȥ����)�������ֵ��
	/// @return    MVD_SUCCESS        ��ʾ�ɹ��� ��������ֵ��ο�MVDAPI_ReturnCode.hͷ�ļ���
	///
	/// -----------------------------------------------------------------------------
	MVD_API MVD_ReturnCode __stdcall GetRoiMaxSize(IN int nIndex, OUT MVD_ROI_SIZE *pRoiMaxSize);

	/// -----------------------------------------------------------------------------
	///
	/// @ingroup   Roi
	/// @brief     ��ȡ��ǰ��ROI(����Ȥ����)��Ϣ��
	/// @attention ��
	/// @param     [IN]nIndex         �豸��Ӧ��������ͨ��GetDeviceIndex��ȡ��
	/// @param     [OUT]pRoiSize      ��ǰROI(����Ȥ����)��С��
	/// @return    MVD_SUCCESS        ��ʾ�ɹ��� ��������ֵ��ο�MVDAPI_ReturnCode.hͷ�ļ���
	///
	/// -----------------------------------------------------------------------------
	MVD_API MVD_ReturnCode __stdcall GetRoiSize(IN int nIndex, OUT MVD_ROI_SIZE *pRoiSize);

	/// -----------------------------------------------------------------------------
	///
	/// @ingroup   Roi
	/// @brief     ����ROI(����Ȥ����)��
	/// @attention ע�⣬��������������������ɼ�����ã�����Ҫֹͣ����������á�
	///            ���⣬�����ӳ������ø���ͼ�񴫸����Ĳ�ͬ���ڲ��п��ܻ�����õ�ֵ���е�������������ӳ���ʵֵ����ͨ��GetRoiSize�ٴλ�ȡ�õ���
	/// @param     [IN]nIndex         �豸��Ӧ��������ͨ��GetDeviceIndex��ȡ��
	/// @param     [IN]RoiSize        ��Ҫ���õ�ROI(����Ȥ����)��С��
	/// @return    MVD_SUCCESS        ��ʾ�ɹ��� ��������ֵ��ο�MVDAPI_ReturnCode.hͷ�ļ���
	///
	/// -----------------------------------------------------------------------------
	MVD_API MVD_ReturnCode __stdcall SetRoiSize(IN int nIndex, IN MVD_ROI_SIZE RoiSize);

	/// -----------------------------------------------------------------------------
	///
	/// @ingroup   Roi
	/// @brief     ��ȡ��ǰ��ROI�ӳ������£������õ���ʼ��(ˮƽƫ��)�����ֵ����Сֵ��Ĭ��ֵ��Ĭ��ֵ��ָ����ROI�ӳ���ȫ�ӳ���ˮƽ����λ�õ�ֵ����
	/// @attention ���ͨ��SetFieldOfView�ı���ROI����Ҫ�ٴε������»�ȡ��
	/// @param     [IN]nIndex         �豸��Ӧ��������ͨ��GetDeviceIndex��ȡ��
	/// @param     [OUT]puiMin        ��ǰROI(����Ȥ����)��С�����õ�ˮƽƫ�ơ�
	/// @param     [OUT]puiMax        ��ǰROI(����Ȥ����)�������õ�ˮƽƫ�ơ�
	/// @param     [OUT]puiDef        ��ǰROI(����Ȥ����)����ʱ��ˮƽƫ�ơ�
	/// @return    MVD_SUCCESS        ��ʾ�ɹ��� ��������ֵ��ο�MVDAPI_ReturnCode.hͷ�ļ���
	///
	/// -----------------------------------------------------------------------------
	MVD_API MVD_ReturnCode __stdcall GetRoiColStartRange(IN int nIndex, OUT unsigned int *puiMin, OUT unsigned int *puiMax, OUT unsigned int *puiDef);


	/// -----------------------------------------------------------------------------
	///
	/// @ingroup   Roi
	/// @brief     ����ROI(����Ȥ����)����ȫ�����е���ʼ�У�ˮƽƫ�ƣ���
	/// @attention ���ͨ��SetFieldOfView�ı���ROI����Ҫ�ٴε������»�ȡ��
	/// @param     [IN]nIndex         �豸��Ӧ��������ͨ��GetDeviceIndex��ȡ��
	/// @param     [IN]uiValue        ��Ҫ���õ�ROI(����Ȥ����)ˮƽƫ��ֵ��
	/// @return    MVD_SUCCESS        ��ʾ�ɹ��� ��������ֵ��ο�MVDAPI_ReturnCode.hͷ�ļ���
	///
	/// -----------------------------------------------------------------------------
	MVD_API MVD_ReturnCode __stdcall SetRoiColStart(IN int nIndex, IN unsigned int uiValue);

	/// -----------------------------------------------------------------------------
	///
	/// @ingroup   Roi
	/// @brief     ����ROI(����Ȥ����)����ȫ�����е���ʼ�У�ˮƽƫ�ƣ���
	/// @attention ���ͨ��SetFieldOfView�ı���ROI����Ҫ�ٴε������»�ȡ��
	/// @param     [IN]nIndex         �豸��Ӧ��������ͨ��GetDeviceIndex��ȡ��
	/// @param     [OUT]puiValue      ���ص�ǰROI(����Ȥ����)ˮƽƫ��ֵ��
	/// @return    MVD_SUCCESS        ��ʾ�ɹ��� ��������ֵ��ο�MVDAPI_ReturnCode.hͷ�ļ���
	///
	/// -----------------------------------------------------------------------------
	MVD_API MVD_ReturnCode __stdcall GetRoiColStart(IN int nIndex, OUT unsigned int *puiValue);

	/// -----------------------------------------------------------------------------
	///
	/// @ingroup   Roi
	/// @brief     ��ȡ��ǰ��ROI�ӳ������£������õ���ʼ��(��ֱƫ��)�����ֵ����Сֵ��Ĭ��ֵ��Ĭ��ֵ��ָ����ROI�ӳ���ȫ�ӳ��Ĵ�ֱ����λ�õ�ֵ����
	/// @attention ���ͨ��SetFieldOfView�ı���ROI����Ҫ�ٴε������»�ȡ��
	/// @param     [IN]nIndex         �豸��Ӧ��������ͨ��GetDeviceIndex��ȡ��
	/// @param     [OUT]puiMin        ��ǰROI(����Ȥ����)��С�����õĴ�ֱƫ�ơ�
	/// @param     [OUT]puiMax        ��ǰROI(����Ȥ����)�������õĴ�ֱƫ�ơ�
	/// @param     [OUT]puiDef        ��ǰROI(����Ȥ����)����ʱ�Ĵ�ֱƫ�ơ�
	/// @return    MVD_SUCCESS        ��ʾ�ɹ��� ��������ֵ��ο�MVDAPI_ReturnCode.hͷ�ļ���
	///
	/// -----------------------------------------------------------------------------
	MVD_API MVD_ReturnCode __stdcall GetRoiRowStartRange(IN int nIndex, OUT unsigned int *puiMin, OUT unsigned int *puiMax, OUT unsigned int *puiDef);

	/// @ingroup   Roi
	/// @brief     ����ROI��ֱ��ʼ�С�
	MVD_API MVD_ReturnCode __stdcall SetRoiRowStart(IN int nIndex, IN unsigned int uiValue);

	/// @ingroup   Roi
	/// @brief     ��ȡROI��ֱ��ʼ�С�
	MVD_API MVD_ReturnCode __stdcall GetRoiRowStart(IN int nIndex, OUT unsigned int *puiValue);


	/// @ingroup   Image
	/// @brief     ���òɼ�ͼ���ʽ��
	/// @attention ע�⣬��������������������ɼ�����ã�����Ҫֹͣ����������á�
	MVD_API MVD_ReturnCode __stdcall SetPixelFormat(IN int nIndex, IN MVD_PIXEL_FORMAT PixelFormat);


	/// @brief     ��ȡ�ɼ�ͼ���ʽ��
	MVD_API MVD_ReturnCode __stdcall GetPixelFormat(IN int nIndex, OUT MVD_PIXEL_FORMAT *pPixelFormat);

	/// @brief     ����ͼ���Ƿ�ֱ��ת��
	MVD_API MVD_ReturnCode __stdcall GetFlip(IN int nIndex, bool *pbFlip);
	/// @brief     ��ȡͼ���Ƿ�ֱ��ת��
	MVD_API MVD_ReturnCode __stdcall SetFlip(IN int nIndex, bool bFlip);


	/// @brief     ����ͼ���Ƿ�ˮƽ����
	MVD_API MVD_ReturnCode __stdcall SetMirror(IN int nIndex, bool bMirror);
	/// @brief     ��ȡͼ���Ƿ�ˮƽ����
	MVD_API MVD_ReturnCode __stdcall GetMirror(IN int nIndex, bool *pbMirror);



	/// @brief     ��ȡ��ǰ���������£��ɼ�ͼ��Ļ�����Ϣ��
	MVD_API MVD_ReturnCode __stdcall GetImageBaseInfo(IN int nIndex, MVD_IMAGE_BASE_INFO *pImageBaseInfo);


	/// @brief     ���豸�������ԶԻ���
	/// @attention ����Ի�����Լ��û��ı�����̣���������ö��ǿ�������Ƶ��������ֹͣ״̬�½��в�����
	MVD_API MVD_ReturnCode __stdcall OpenSettingPage(IN int nIndex, IN void *hWndParent, int nLeft, int nTop);

	/// @ingroup   Grab
 	/// @brief     ���òɼ���ʱʱ�䡣
	MVD_API MVD_ReturnCode __stdcall SetGrabTimeout(IN int nIndex, unsigned long ulTimeoutMs);


	/// @brief     ��ȡ�ɼ���ʱʱ�䡣
	MVD_API MVD_ReturnCode __stdcall GetGrabTimeout(IN int nIndex, unsigned long *pulTimeoutMs);

	/// @brief     �����ɼ�������
	/// @attention �ڵ���SetGrabbingCallback��GrabImage֮ǰ�����ȵ��ô˺��������ɼ���������
	MVD_API MVD_ReturnCode __stdcall SetGrabbingStart(IN int nIndex, IN bool bStart);

	/// @brief     ��ȡ�ɼ����Ƿ���
	MVD_API MVD_ReturnCode __stdcall GetGrabbingStart(IN int nIndex, OUT bool *pbStart);

	/// @brief     ��ȡ�ɼ�֡�ʣ����뿪���ɼ��������ſɻ�ȡ����Ч֡��
	MVD_API MVD_ReturnCode __stdcall GetGrabbingFps(IN int nIndex, OUT float *pFps);


	/// @brief     ������رղɼ��ص���
	/// @attention ��pfGrabbingCallback����ΪNULL��ֹͣ�ص����ص��ɼ��������ɼ�������GrabImage���вɼ����û�ֻ��ѡ����һ������ͬʱʹ�á�
	MVD_API MVD_ReturnCode __stdcall SetGrabbingCallback(IN int nIndex, IN PMVD_GRABBING_CALLBACK pfGrabbingCallback, IN void* lpContext);

	/// @brief     ��ȡ�ɼ��ص��Ƿ�����رա�
	/// @attention ��*ppfGrabbingCallback��ֵΪNULL��ʾ�ɼ��ص��Ѿ��رգ�����Ϊ����״̬��
	MVD_API MVD_ReturnCode __stdcall GetGrabbingCallback(IN int nIndex, OUT PMVD_GRABBING_CALLBACK *ppfGrabbingCallback, OUT void** lpContext);


	/// -----------------------------------------------------------------------------
	///
	/// @brief     �����ɼ���
	/// @attention ����GrabImage֮ǰ���������SetGrabbingStart������Ƶ��������ڴ���SDK���䣬�û�����Ҫ�����ڴ档ʹ��֮����Ҫ����GrabImageRelease֪ͨSDK�ͷ���Դ����������Grabbing�̡߳�
	///            �ص��ɼ���SetGrabbingCallback���������ɼ�������GrabImage���вɼ����û�ֻ��ѡ����һ������ͬʱʹ�á�
	///
	/// -----------------------------------------------------------------------------
	MVD_API MVD_ReturnCode __stdcall GrabImage(IN const int nIndex, OUT MVD_GRAB_IMAGE_INFO **ppGrabImageInfo, OUT unsigned char **ppGrabImageData);

	/// @brief     ֪ͨSDK�ͷ������ɼ���Դ��
	/// @attention ÿ�ε���һ��MVD_GrabImage����ͼ����֮�󣬱������һ�δ˺�������֪ͨSDK�ͷ���Դ����������Grabbing�̡߳�
	MVD_API MVD_ReturnCode __stdcall GrabImageRelease(IN const int nIndex);


	/// @brief     ����ͼ��
	MVD_API MVD_ReturnCode __stdcall SaveImage(IN const MVD_GRAB_IMAGE_INFO *pGrabImageInfo, IN unsigned char *ppGrabImageData, IN const MVD_SAVE_IMAGE_INFORMATION SaveImageInformation);



	/// @brief     ��ȡ�������÷�Χ
	MVD_API MVD_ReturnCode __stdcall GetGainRange(IN int nIndex, MVD_GAIN_SELECTOR GainSelector, float *pfMin, float *pfMax);

	/// @brief     ��������
	MVD_API MVD_ReturnCode __stdcall SetGain(IN int nIndex, MVD_GAIN_SELECTOR GainIndex, float fGain);

	/// @brief     ��ȡ����
	MVD_API MVD_ReturnCode __stdcall GetGain(IN int nIndex, MVD_GAIN_SELECTOR GainIndex, float *pfGain);


	/// @brief     �����Զ��ع�������ޣ���λ���룩
	/// @attention ���Զ��ع���ڵ��ع�ʱ�䳬�����õ�����ʱ�������Զ��ع�ص�״̬�ﷵ��AES_ONCE_FAIL_OVER_RANGE��AES_CONTINUOUS_FAIL_OVER_RANGE
	MVD_API MVD_ReturnCode __stdcall SetAutoExposureTimeUpperLimit(IN int nIndex, float fAutoExposureTimeMs);

	/// @brief     ��ȡ�Զ��ع�������ޣ���λ���룩
	MVD_API MVD_ReturnCode __stdcall GetAutoExposureTimeUpperLimit(IN int nIndex, float *pfAutoExposureTimeMs);

	/// @brief     ��ȡ�Զ��ع����Ŀ��Ҷ�ֵ��Χ
	MVD_API MVD_ReturnCode __stdcall GetAutoExposureTargetRange(IN int nIndex, int *pnMin, int *pnMax, int *pnDef);

	/// @brief     �����Զ��ع����Ŀ��Ҷ�ֵ
	MVD_API MVD_ReturnCode __stdcall SetAutoExposureTarget(IN int nIndex, int nAutoExposureTarget);

	/// @brief     ��ȡ�Զ��ع����Ŀ��Ҷ�ֵ
	MVD_API MVD_ReturnCode __stdcall GetAutoExposureTarget(IN int nIndex, int *pnAutoExposureTarget);

	/// @brief     �����Զ��ع�ص�����
	MVD_API MVD_ReturnCode __stdcall SetAutoExposureCallback(IN int nIndex, PMVD_AUTO_EXPOSURE_CALLBACK pfCallback, void *lpContext);

	/// @brief     ��ȡ��ǰ�ع�ģʽ
	MVD_API MVD_ReturnCode __stdcall GetExposureMode(IN int nIndex, MVD_EXPOSURE_MODE *pExposureModeSelector);

	/// @brief     �����ع�ģʽ
	MVD_API MVD_ReturnCode __stdcall SetExposureMode(IN int nIndex, MVD_EXPOSURE_MODE ExposureMode);

	/// @brief     ��ȡ�ع����÷�Χ����λ΢�룩
	MVD_API MVD_ReturnCode __stdcall GetExposureTimeRange(IN int nIndex, float *pfMinUs, float *pfMaxUs);

	/// @brief     �����ع�ʱ�䣨��λ΢�룩
	/// @attention ֻ�����ع�ģʽΪ�ֶ�ģʽEM_MANUALʱ���������ع�ʱ��
	MVD_API MVD_ReturnCode __stdcall SetExposureTime(IN int nIndex, float fExposureTimeUs);

	/// @brief     ��ȡ�ع�ʱ�䣨��λ΢�룩
	MVD_API MVD_ReturnCode __stdcall GetExposureTime(IN int nIndex, float *pfExposureTimeUs);

	/// @ingroup   WhiteBalance
	/// @brief     �����Զ���ƽ��ص�����
	MVD_API MVD_ReturnCode __stdcall SetAutoWhiteBalanceCallback(IN int nIndex, PMVD_WHITE_BALANCE_CALLBACK pfCallBack, void *lpContext);

	/// @brief     ���ð�ƽ��Ԥ��ֵ
	/// @attention �������ֻ���ڰ�ƽ��ģʽ����ΪWBM_SOFTWARE_PRESETTING��WBM_HARDWARE_PRESETTINGģʽʱ����Ч
	MVD_API MVD_ReturnCode __stdcall SetWhiteBalancePresetting(IN int nIndex, MVD_COLOR_TEMPERATURE ColorTemperature);

	/// @brief     ��ȡ��ǰѡ��İ�ƽ��Ԥ��ֵ
	MVD_API MVD_ReturnCode __stdcall GetWhiteBalancePresetting(IN int nIndex, MVD_COLOR_TEMPERATURE *pColorTemperature);

	/// @brief     ��ȡ��ƽ��ģʽ
	MVD_API MVD_ReturnCode __stdcall GetWhiteBalanceMode(IN int nIndex, MVD_WHITE_BALANC_MODE *pWhiteBalanceMode);

	/// @brief     ���ð�ƽ��ģʽ
	MVD_API MVD_ReturnCode __stdcall SetWhiteBalanceMode(IN int nIndex, MVD_WHITE_BALANC_MODE WhiteBalanceMode);

	/// @brief     �ֶ����ð�ƽ��ϵ�����󣨷�Χ�Ƽ�-10-10��
	/// @attention ֻ�����ڰ�ƽ��ģʽ����ΪWBM_SOFTWARE_MANUAL��WBM_HARDWARE_MANUALģʽʱ�ſɵ���
	MVD_API MVD_ReturnCode __stdcall SetWhiteBalanceMatrix(IN int nIndex, float fMatrix[3]);

	/// @brief     ��ȡ��ƽ��ϵ������
	MVD_API MVD_ReturnCode __stdcall GetWhiteBalanceMatrix(IN int nIndex, float fMatrix[3]);

	/// @ingroup   ColorCorrection
	/// @brief     ��ȡɫ��Ч��ģʽ
	MVD_API MVD_ReturnCode __stdcall GetColorCorrectionMode(IN int nIndex, MVD_COLOR_CORRECTION_MODE *pColorCorrectionMode);

	/// @brief     ����ɫ��Ч��ģʽ
	MVD_API MVD_ReturnCode __stdcall SetColorCorrectionMode(IN int nIndex, MVD_COLOR_CORRECTION_MODE ColorCorrectionMode);

	///
	/// @brief     �ֶ�����ɫ��Ч��ϵ�����󣨷�Χ�Ƽ�-10-10��
	/// @attention ֻ������ɫ��Ч��ģʽ����ΪCCM_SOFTWARE_MANUAL��CCM_HARDWARE_MANUALģʽʱ�ſɵ���
	/// @see       SetColorCorrectionMode
	/// @see       GetColorCorrectionMode
	///

	MVD_API MVD_ReturnCode __stdcall SetColorCorrectionMatrix(IN int nIndex, float fMatrix[3][3]);

	/// @brief     ��ȡ��ǰɫ��Ч��ϵ������
	/// @attention Ҳ����ͨ���˺���ʵʱ��ȡ�Զ�ɫ��Ч�����ϵ������
	/// @see       SetColorCorrectionMode
	/// @see       GetColorCorrectionMode
	///

	MVD_API MVD_ReturnCode __stdcall GetColorCorrectionMatrix(IN int nIndex, float fMatrix[3][3]);

	/// @brief     ����ɫ��Ч��Ԥ��ֵ
	/// @attention �������ֻ����ɫ��Ч��ģʽ����ΪCCM_SOFTWARE_PRESETTING��CCM_HARDWARE_PRESETTINGģʽʱ����Ч
	/// @param     [IN]nIndex         �豸��Ӧ��������ͨ��GetDeviceIndex��ȡ��
	/// @see       SetColorCorrectionMode
	/// @see       GetColorCorrectionMode
	///
	MVD_API MVD_ReturnCode __stdcall SetColorCorrectionPresetting(IN int nIndex, MVD_COLOR_TEMPERATURE ColorTemperature);

	/// @brief     ��ȡɫ��Ч��Ԥ��ֵ
	/// @see       SetColorCorrectionMode
	/// @see       GetColorCorrectionMode
	///
	MVD_API MVD_ReturnCode __stdcall GetColorCorrectionPresetting(IN int nIndex, MVD_COLOR_TEMPERATURE *pColorTemperature);

	/// @ingroup   AdcCompanding
	/// @brief     ��ȡͼ�񴫸���ADCת�����ȣ�����λ����
	/// @see       GetAdcCompandingMode
	MVD_API MVD_ReturnCode __stdcall GetAdcResolution(IN int nIndex, unsigned char *pucAdcResolution);


	/// @brief     �������ADC����ת��Ϊ8���ص�ģʽ
	/// @see       SetAdcCompandingMode
	MVD_API MVD_ReturnCode __stdcall SetAdcCompandingMode(IN int nIndex, MVD_ADC_COMPANDING_MODE CompandingMode);


	/// @brief     ��ȡ����ѹ�������ADC����ת��Ϊ8���أ�ģʽ
	MVD_API MVD_ReturnCode __stdcall GetAdcCompandingMode(IN int nIndex, MVD_ADC_COMPANDING_MODE *pCompandingMode);

	/// @brief     ����λ��ȡģʽ
	/// @attention ��CompandingModeΪACM_EXTRACTʱ�ſ�����Ч
	/// @see       SetAdcCompandingMode
	MVD_API MVD_ReturnCode __stdcall SetAdcCompandingExtractMode(IN int nIndex, MVD_EXTRACT_MODE ExtractMode);
	
	/// @brief     ��ȡ��ǰλ��ȡģʽ
	/// @see       SetAdcCompandingMode
	MVD_API MVD_ReturnCode __stdcall GetAdcCompandingExtractMode(IN int nIndex, MVD_EXTRACT_MODE *pExtractMode);

	/// @brief     ����ѹ�����ұ�
	/// @attention ��CompandingModeΪACM_LUTʱ�ſ�����Ч��LUT���ұ�Ԫ�ظ�������Ϊ2^AdcResolution��AdcResolutionͨ��GetAdcResolution������ȡ��
	/// @see       GetAdcResolution
	MVD_API MVD_ReturnCode __stdcall SetAdcCompandingLut(IN int nIndex, IN  unsigned char *pucLut, unsigned short usLutBytesSize);

	/// @brief     ��ȡ��ǰѹ�����ұ�
	MVD_API MVD_ReturnCode __stdcall GetAdcCompandingLut(IN int nIndex, OUT unsigned char *pucLut, unsigned short *pusLutBytesSize);

	/// @ingroup   ImageProcess
	/// @brief     ��ȡͼ��ԱȶȲ������ڵķ�Χ
	MVD_API MVD_ReturnCode __stdcall GetContrastRange(IN int nIndex, int *pnMin, int *pnMax, int *pnDef);

	/// @brief     ����ͼ��Աȶ�
	MVD_API MVD_ReturnCode __stdcall SetContrast(IN int nIndex, int nContrast);
	/// @brief     ��ȡͼ��Աȶ�
	MVD_API MVD_ReturnCode __stdcall GetContrast(IN int nIndex, int *pnContrast);

	/// @brief     ��ȡͼ�����Ȳ������ڵķ�Χ
	MVD_API MVD_ReturnCode __stdcall GetBrightnessRange(IN int nIndex, int *pnMin, int *pnMax, int *pnDef);
	/// @brief     ����ͼ������
	MVD_API MVD_ReturnCode __stdcall SetBrightness(IN int nIndex, int nValue);
	/// @brief     ��ȡͼ������
	MVD_API MVD_ReturnCode __stdcall GetBrightness(IN int nIndex, int *pnValue);

	/// @brief     ��ȡͼ��Gamm�������ڵķ�Χ
	MVD_API MVD_ReturnCode __stdcall GetGammaRange(IN int nIndex, int *pnMin, int *pnMax, int *pnDef);
	/// @brief     ����ͼ��Gamma
	MVD_API MVD_ReturnCode __stdcall SetGamma(IN int nIndex, int nValue);
	/// @brief     ��ȡͼ��Gamma
	MVD_API MVD_ReturnCode __stdcall GetGamma(IN int nIndex, int *pnValue);

	/// @brief     ��ȡͼ�񱥺ͶȲ������ڵķ�Χ
	MVD_API MVD_ReturnCode __stdcall GetSaturationRange(IN int nIndex, int *pnMin, int *pnMax, int *pnDef);
	/// @brief     ����ͼ�񱥺Ͷ�
	MVD_API MVD_ReturnCode __stdcall SetSaturation(IN int nIndex, int nValue);
	/// @brief     ��ȡͼ�񱥺Ͷ�
	MVD_API MVD_ReturnCode __stdcall GetSaturation(IN int nIndex, int *pnValue);


	/**@defgroup AcquisitionTriggerControl
	* @{
	* @brief �ɼ�ģʽ��ؿ��ƺ���
	*/

	/// @ingroup   AcquisitionTrigger
	/// @brief     ���ÿ�ʼ�ɼ��Ĵ���ģʽ
	/// @attention ���������Ҫ��Ϊ����FrameTrigger��֡��������ʱ��Ч��Ĭ��ΪSTM_CONTINUOUS,�����������һ�㲻��Ҫ���ô�ģʽ
	/// @attention ������Ҫһ���ⲿ�ź������ƺ�ʱ֡������Чʱ�����Ե��ô˺����������ã�ֻ��AcquisitionTrigger����������£��Ż��ж�FrameTrigger������
	///
	// MVD_API MVD_ReturnCode __stdcall SetAcquisitionTriggerMode(IN int nIndex, MVD_ACQUISITION_TRIGGER_MODE AcquisitionTriggerMode);

	// MVD_API MVD_ReturnCode __stdcall GetAcquisitionTriggerMode(IN int nIndex, MVD_ACQUISITION_TRIGGER_MODE *pAcquisitionTriggerMode);

	/// @brief     ���òɼ������ⲿ�ź�Դ
	/// @attention ֻ����֡����ģʽΪFTM_EXTERNALʱ������Ч    
	// MVD_API MVD_ReturnCode __stdcall SetAcquisitionTriggerExternalSource(IN int nIndex, MVD_ACQUISITION_TRIGGER_EXTERNAL_SOURCE AcquisitionTriggerExternalSource);

	/// @brief     ��ȡ��ǰ�ɼ������ź���ʹ�õ��ⲿ�ź�Դ
	// MVD_API MVD_ReturnCode __stdcall GetAcquisitionTriggerExternalSource(IN int nIndex, MVD_ACQUISITION_TRIGGER_EXTERNAL_SOURCE *pAcquisitionTriggerExternalSource);

	/// @brief     ���òɼ������ⲿ����Դ��Ч����
	/// @attention ֻ����֡����ģʽΪFTM_EXTERNALʱ������Ч    
	//MVD_API MVD_ReturnCode __stdcall SetAcquisitionTriggerExternalActivation(IN int nIndex, MVD_ACQUISITION_TRIGGER_EXTERNAL_ACTIVATION FrameTriggerExternalActivation);

	/// @brief     ��ȡ��ǰ���õĲɼ������ⲿ����Դ��Ч����
	//MVD_API MVD_ReturnCode __stdcall GetAcquisitionTriggerExternalActivation(IN int nIndex, MVD_ACQUISITION_TRIGGER_EXTERNAL_ACTIVATION *pFrameTriggerActivation);

	/// @brief     ��ȡ�ɼ������ź���ʱʱ�����÷�Χ��΢�룩
	//MVD_API MVD_ReturnCode __stdcall GetAcquisitionTriggerExternalDelayRange(IN int nIndex, float *pfMinUs, float *pfMaxUs, float *pfDefUs);

	/// @brief     ���òɼ������ź���ʱʱ�䣨΢�룩
	/// @attention ֻ����֡����ģʽΪFTM_EXTERNALʱ������Ч    
	//MVD_API MVD_ReturnCode __stdcall SetAcquisitionTriggerExternalDelay(IN int nIndex, float fDelayUs);

	/// @brief     ��ȡ�ɼ������ź���ʱʱ�䣨΢�룩
	//MVD_API MVD_ReturnCode __stdcall GetAcquisitionTriggerExternalDelay(IN int nIndex, float *pfDelayUs);

	/// @brief     ��ȡ�ɼ������ź��˲�ʱ�����÷�Χ��΢�룩
	//MVD_API MVD_ReturnCode __stdcall GetAcquisitionTriggerExternalFilterRange(IN int nIndex, float *pfMinUs, float *pfMaxUs, float *pfDefUs);

	/// @brief     ���òɼ������ź��˲�ʱ�䣨΢�룩
	/// @attention ֻ����֡����ģʽΪFTM_EXTERNALʱ������Ч    
	//MVD_API MVD_ReturnCode __stdcall SetAcquisitionTriggerExternalFilter(IN int nIndex, float fFilterUs);

	/// @brief     ��ȡ�ɼ������ź��˲�ʱ�䣨΢�룩
	//MVD_API MVD_ReturnCode __stdcall GetAcquisitionTriggerExternalFilter(IN int nIndex, float *pfFilterUs);

	/// @brief     ִ������ɼ�����
	/// @attention �ڲɼ�����ģʽΪSTM_SOFTWAREģʽ�²ſɵ���
	// MVD_API MVD_ReturnCode __stdcall ExecuteSoftwareAcquisitionTrigger(IN int nIndex);

	/// @brief     ��AcquisitionTrigger������������£�FrameTrigger�������֡���ټ������AcquisitionTrigger������ͬʱ��Щ֡��ƴ�Ӳ����زɼ������
	/// @attention �ɼ�ʱ��ͼ��ο�AcquisitionTrigger��FrameTriggerģʽ��Ͽ���ʱ��ͼ
	MVD_API MVD_ReturnCode __stdcall SetAcquisitionTriggerFramesCount(IN int nIndex, unsigned int uiFramesCount);
	MVD_API MVD_ReturnCode __stdcall GetAcquisitionTriggerFramesCount(IN int nIndex, unsigned int *puiFramesCount);

	/** @} AcquisitionTriggerControl*/

	/**@defgroup FrameTriggerTriggerControl
	* @{
	* @brief ֡����������Ƶ���غ���
	*/

	/// @ingroup   FrameTrigger
	/// @brief     ����֡����ģʽ
	/// @attention ����������ڿ��ƺ�ʱ����һ֡��ǰ������ʱStratTrigger�ź����㣬���AcquisitionTriggerMode=STM_CONTINUOUS���򲻱ؿ���StratTrigger�ź�

	MVD_API MVD_ReturnCode __stdcall SetFrameTriggerMode(IN int nIndex, MVD_FRAME_TRIGGER_MODE FrameTriggerMode);

	/// @brief     ��ȡ��ǰ֡����ģʽ
	MVD_API MVD_ReturnCode __stdcall GetFrameTriggerMode(IN int nIndex, MVD_FRAME_TRIGGER_MODE *pFrameTriggerMode);

	/// @brief     ����֡�����ⲿ�ź�Դ
	/// @attention ֻ����֡����ģʽΪFTM_EXTERNALʱ������Ч�������������������£������û����ã���Ӳ����ƹ̶����ο�Ӳ��IO˵����  
	MVD_API MVD_ReturnCode __stdcall SetFrameTriggerExternalSource(IN int nIndex, MVD_FRAME_TRIGGER_EXTERNAL_SOURCE FrameTriggerExternalSource);

	/// @brief     ��ȡ��ǰ֡�����ź���ʹ�õ��ⲿ����Դ
	MVD_API MVD_ReturnCode __stdcall GetFrameTriggerExternalSource(IN int nIndex, MVD_FRAME_TRIGGER_EXTERNAL_SOURCE *pFrameTriggerExternalSource);

	/// @brief     ����֡�����ⲿ����Դ��Ч����
	/// @attention ֻ����֡����ģʽΪFTM_EXTERNALʱ������Ч���豸�ڲ����ⲿ�źŵ�����£��ڲ�Ĭ��Ϊ�͵�ƽ�ź�    
	MVD_API MVD_ReturnCode __stdcall SetFrameTriggerExternalActivation(IN int nIndex, MVD_FRAME_TRIGGER_EXTERNAL_ACTIVATION FrameTriggerExternalActivation);

	/// @brief     ��ȡ��ǰ���õ�֡�����ⲿ����Դ��Ч����
	MVD_API MVD_ReturnCode __stdcall GetFrameTriggerExternalActivation(IN int nIndex, MVD_FRAME_TRIGGER_EXTERNAL_ACTIVATION *pFrameTriggerActivation);

	/// @brief     ��ȡ֡������ʱʱ�����÷�Χ��΢�룩
	MVD_API MVD_ReturnCode __stdcall GetFrameTriggerExternalDelayRange(IN int nIndex, float *pfMinUs, float *pfMaxUs, float *pfDefUs);
	
	/// @brief     ����֡������ʱʱ�䣨΢�룩
	/// @attention ֻ����֡����ģʽΪFTM_EXTERNALʱ������Ч    
	MVD_API MVD_ReturnCode __stdcall SetFrameTriggerExternalDelay(IN int nIndex, float fDelayUs);

	/// @brief     ��ȡ֡������ʱʱ�䣨΢�룩
	MVD_API MVD_ReturnCode __stdcall GetFrameTriggerExternalDelay(IN int nIndex, float *pfDelayUs);

	/// @brief     ��ȡ֡�����˲�ʱ�����÷�Χ��΢�룩
	MVD_API MVD_ReturnCode __stdcall GetFrameTriggerExternalFilterRange(IN int nIndex, float *pfMinUs, float *pfMaxUs, float *pfDefUs);

	/// @brief     ����֡�����˲�ʱ�䣨΢�룩
	/// @attention ֻ����֡����ģʽΪFTM_EXTERNALʱ������Ч    
	MVD_API MVD_ReturnCode __stdcall SetFrameTriggerExternalFilter(IN int nIndex, float fFilterUs);

	/// @brief     ��ȡ֡�����˲�ʱ�䣨΢�룩
	MVD_API MVD_ReturnCode __stdcall GetFrameTriggerExternalFilter(IN int nIndex, float *pfFilterUs);

	/// @brief     ��ȡ�̶�֡�����÷�Χ��֡ÿ�룩
	MVD_API MVD_ReturnCode __stdcall GetFrameTriggerFixedRateRange(IN int nIndex, float *pfMin, float *pfMax, float *pfDef);

	/// @brief     ���ù̶�֡�ʣ�֡ÿ�룩
	/// @attention ֻ����֡����ģʽΪFTM_FIXED_FRAME_RATEʱ������Ч    
	MVD_API MVD_ReturnCode __stdcall SetFrameTriggerFixedRate(IN int nIndex, float fFps);

	/// @brief     ��ȡ��ǰ���õĹ̶�֡�ʣ�֡ÿ�룩
	MVD_API MVD_ReturnCode __stdcall GetFrameTriggerFixedRate(IN int nIndex, float *pfFps);



	/// @brief     ִ�����֡����
	/// @attention ֮����֡����ģʽΪFTM_SOFTWAREģʽ�²ſɵ��ã���������ݲ�����ã�ֻҪ�����������ģʽ�����ڲɼ�ʱ�Զ�������
	MVD_API MVD_ReturnCode __stdcall ExecuteSoftwareFrameTrigger(IN int nIndex);

	/** @} FrameTriggerTriggerControl*/

	/**@defgroup UserPresettingControl
	* @{
	* @brief �û�Ԥ��������ؿ��ƺ���
	*/

	/// -----------------------------------------------------------------------------
	///
	/// @brief     ���浱ǰ�豸״̬��ָ�����û�Ԥ���顣
	/// @attention ����ǰ�豸���������Ϣ���浽ָ�����û�Ԥ���飬�����û�ͨ��LoadUserPresetting�������¼��ء�
	/// @param     [IN]nIndex         �豸��Ӧ��������ͨ��GetDeviceIndex��ȡ��
	/// @param     [IN]UserPresetting �û�Ԥ����ţ��ο�MVD_USER_PRESETTINGö������
	/// @return    MVD_SUCCESS        ��ʾ�ɹ��� ��������ֵ��ο�MVDAPI_ReturnCode.hͷ�ļ���
	/// @see       LoadUserPresetting
	///
	/// -----------------------------------------------------------------------------
	MVD_API MVD_ReturnCode __stdcall SaveUserPresetting(IN int nIndex, IN MVD_USER_PRESETTING UserPresetting);


	/// -----------------------------------------------------------------------------
	///
	/// @brief     ����ָ�����û�Ԥ���顣
	/// @attention ��֮ǰ����ġ���Ӧ���û�Ԥ������Ϣ���¼��ء�
	/// @param     [IN]nIndex         �豸��Ӧ��������ͨ��GetDeviceIndex��ȡ��
	/// @param     [IN]UserPresetting �û�Ԥ����ţ��ο�MVD_USER_PRESETTINGö������
	/// @return    MVD_SUCCESS        ��ʾ�ɹ��� ��������ֵ��ο�MVDAPI_ReturnCode.hͷ�ļ���
	/// @see       SaveUserPresetting
	///
	/// -----------------------------------------------------------------------------
	MVD_API MVD_ReturnCode __stdcall LoadUserPresetting(IN int nIndex, IN MVD_USER_PRESETTING UserPresetting);


	/// -----------------------------------------------------------------------------
	///
	/// @brief     ����Ĭ�ϼ��ص�Ԥ���顣
	/// @attention ����Ĭ�ϼ���Ԥ�����ÿ�ε���Initial�ᰴ�մ�Ԥ�������Ϣ���豸���м������á�
	/// @param     [IN]nIndex         �豸��Ӧ��������ͨ��GetDeviceIndex��ȡ��
	/// @param     [IN]UserPresetting Ҫ����ΪĬ�ϼ��ص��û�Ԥ���飬�ο�MVD_USER_PRESETTINGö������
	/// @return    MVD_SUCCESS        ��ʾ�ɹ��� ��������ֵ��ο�MVDAPI_ReturnCode.hͷ�ļ���
	/// @see       GetDefaultUserPresetting
	///
	/// -----------------------------------------------------------------------------
	MVD_API MVD_ReturnCode __stdcall SetDefaultUserPresetting(IN int nIndex, IN MVD_USER_PRESETTING UserPresetting);


	/// -----------------------------------------------------------------------------
	///
	/// @brief     ��ȡĬ�ϼ��ص�Ԥ���顣
	/// @attention ���û��Ԥ���飿����
	/// @param     [IN]nIndex           �豸��Ӧ��������ͨ��GetDeviceIndex��ȡ��
	/// @param     [OUT]pUserPresetting ���ص�ǰĬ�ϵ�Ԥ����
	/// @return    MVD_SUCCESS        ��ʾ�ɹ��� ��������ֵ��ο�MVDAPI_ReturnCode.hͷ�ļ���
	/// @see       SetDefaultUserPresetting
	///
	/// -----------------------------------------------------------------------------
	MVD_API MVD_ReturnCode __stdcall GetDefaultUserPresetting(IN int nIndex, OUT MVD_USER_PRESETTING *pUserPresetting);

	MVD_API bool __stdcall IsUserPresettingAvailable(IN int nIndex, IN MVD_USER_PRESETTING UserPresetting);

	/** @} UserPresettingControl*/

	/**@defgroup EncoderControl
	* @{
	* @brief ��ֱ�����������غ���
	*/

	/// ����֧�ֵı�����ö������
	typedef enum
	{
		E_Encoder0 = 0,
		E_Encoder1 = 1,
	}MVD_ENCODER;

	/// ������Ϊ������A,B�����ӵ���������
	typedef enum
	{
		ES_Off = 0,      ///< ��ʹ���������ţ��ͷ�Line��������;������Line��Ĭ����Ϊ��
		ES_Line0 = 1,    ///< ʹ��Line0��������
		ES_Line1 = 2,    ///< ʹ��Line1��������
		ES_Line2 = 2,    ///< ʹ��Line2��������
		ES_Line3 = 3,    ///< ʹ��Line3��������
		ES_Line4 = 4,    ///< ʹ��Line4��������
		ES_Line5 = 5,    ///< ʹ��Line5��������
	}MVD_ENCODER_SOURCE;

	/// @brief ���ò�ֱ�����A��B�������ӵ���������Line
	/// @attention ע����ЩLine���ܲ�֧�ֲ�ֱ����������룬��ο�Ӳ��IO˵���ĵ�����Ҫ����ʵ�ʵ��������ӽ�����Ӧ�����û����Ĭ�����ã�Ĭ�����þ����������Ӳ���ĳ����������ã���
	MVD_API MVD_ReturnCode __stdcall SetEncoderSource(IN int nIndex, IN MVD_ENCODER  Encoder, IN MVD_ENCODER_SOURCE EncoderSourceA, IN MVD_ENCODER_SOURCE EncoderSourceB);
	MVD_API MVD_ReturnCode __stdcall GetEncoderSource(IN int nIndex, IN MVD_ENCODER  Encoder, OUT MVD_ENCODER_SOURCE *pEncoderSourceA, OUT MVD_ENCODER_SOURCE *pEncoderSourceB);

	/// �Ա����������Ŀ���ģʽ
	typedef enum
	{
		EM_FourPhase = 0,         ///< ÿȫ�������ӣ���С�����������˲���
		EM_HighResolution = 1,    ///< ÿ90����λ���ӣ���С�������޶����˲���
	}MVD_ENCODER_MODE;

	/// @brief ���ñ���������ģʽ
	MVD_API MVD_ReturnCode __stdcall SetEncoderMode(IN int nIndex, IN MVD_ENCODER  Encoder, IN MVD_ENCODER_MODE EncoderMode);
	MVD_API MVD_ReturnCode __stdcall GetEncoderMode(IN int nIndex, IN MVD_ENCODER  Encoder, IN MVD_ENCODER_MODE *pEncoderMode);

	/// @brief ���ñ������ķ�Ƶ��
	MVD_API MVD_ReturnCode __stdcall SetEncoderDivider(IN int nIndex, IN MVD_ENCODER  Encoder, IN unsigned short usEncoderDivider);
	MVD_API MVD_ReturnCode __stdcall GetEncoderDivider(IN int nIndex, IN MVD_ENCODER  Encoder, IN unsigned short *pusEncoderDivider);

	/// ������������Ч���ģʽ
	typedef enum
	{
		EOM_Off = 0,
		EOM_PositionUp = 1,    ///< ���������˶�����λ�ò���������壬��Ҫ���Ƿ����ƶ��˶��٣��ָ�����ʱ���ȥ����ĸ���
		EOM_PositionDown = 2,  ///< ���з����˶�����λ�ò���������壬��Ҫ���������ƶ��˶��٣��ָ�����ʱ���ȥ����ĸ���
		EOM_DirectionUp = 3,   ///< ���������˶�������������壬�������
		EOM_DirectionDown = 4, ///< ���з����˶�������������壬�������
		EOM_Motion = 5,        ///< �������������
	}MVD_ENCODER_OUTPUT_MODE;

	/// @brief ���ñ�����������Ч���ģʽ
	MVD_API MVD_ReturnCode __stdcall SetEncoderOutputMode(IN int nIndex, IN MVD_ENCODER  Encoder, IN MVD_ENCODER_OUTPUT_MODE usEncoderOutputMode);
	MVD_API MVD_ReturnCode __stdcall GetEncoderOutputMode(IN int nIndex, IN MVD_ENCODER  Encoder, IN MVD_ENCODER_OUTPUT_MODE *pusEncoderOutputMode);
	
	/** @} EncoderControl*/

	/**@defgroup DigitalIoControl
	* @{
	* @brief ����IO������غ���
	*/

	/// ��������Line���ܵ��������ģʽ
	typedef enum
	{
		LM_Input = 0,    ///< Io Ĭ��ΪInput����
		LM_Output = 1,
	}MVD_LINE_MODE;

	/// Ӳ������֧�ֵ��������ţ���������IOö�����ͣ����ֵ��Ӧ�豸��IO�ӿڣ���ο�Ӳ��IO˵���ĵ���
	typedef enum
	{
		IO_Line0 = 0,    ///< ����Io Line0
		IO_Line1 = 1,    ///< ����Io Line1
		IO_Line2 = 2,    ///< ����Io Line2
		IO_Line3 = 3,    ///< ����Io Line3
		IO_Line4 = 4,    ///< ����Io Line4
		IO_Line5 = 5,    ///< ����Io Line5
		///...
	}MVD_LINE;

	/// ע�⣬���Line������������ΪSource�����Line��������ΪDigital Ioʹ�á�
	/// @brief ����Line�������ŵ��������ģʽ
	/// @attention ע�⣬��ЩLineֻ��֧��������������һ��
	MVD_API MVD_ReturnCode __stdcall SetLineMode(IN int nIndex, IN MVD_LINE  Line, IN MVD_LINE_MODE LineMode);
	/// @brief ��ȡLine�������ŵ��������ģʽ
	MVD_API MVD_ReturnCode __stdcall GetLineMode(IN int nIndex, IN MVD_LINE  Line, IN MVD_LINE_MODE *pLineMode);

	/// @brief ��Line�ϵ���������źŽ��з�ת����
	MVD_API MVD_ReturnCode __stdcall SetLineInvert(IN int nIndex, IN MVD_LINE  Line, IN bool bInvert);
	MVD_API MVD_ReturnCode __stdcall GetLineInvert(IN int nIndex, IN MVD_LINE  Line, IN bool *pInvert);

	/// ����ѡ������Դ��ͨ��ָ����Line���
	typedef enum
	{
		LS_Off = 0,
		LS_UserOutput = 1,         ///< �û�����ͨ��SetLineUserOutputValue�����ж����IO������
		LS_FrameTriggerWait = 2,   ///< �ź���Ч���ߵ�ƽ��Ч������ʾ���Խ�����һ��FrameTrigger
		LS_FrameActive,            ///< �ź���Ч���ߵ�ƽ��Ч������ʾ�����ع��Readout
		LS_FrameTriggerMissed,     ///< �ź���Ч�� ��ms�ĸߵ�ƽ������ʾһ��֡�����źŶ�ʧ
		LS_ExposureActive,         ///< �ź���Ч���ߵ�ƽ��Ч������ʾSensor�ع��ڼ�
		LS_Stream0TransferActive,  ///< �ź���Ч���ߵ�ƽ��Ч������ʾ���ڴ���ͼ������
	}MVD_LINE_SOURCE;

	/// @brief     ���ź�Դ��һ��������ţ��Ӷ�������ź�
	/// @attention ������������IoΪ������ſ����������Դ
	MVD_API MVD_ReturnCode __stdcall SetLineSource(IN int nIndex, IN MVD_LINE  Line, IN MVD_LINE_SOURCE LineSource);
	MVD_API MVD_ReturnCode __stdcall GetLineSource(IN int nIndex, IN MVD_LINE  Line, IN MVD_LINE_SOURCE *pLineSource);

	/// @brief     ��ȡָ�����ŵ�״̬������������Ŷ����Զ���
	MVD_API MVD_ReturnCode __stdcall GetLineStatus(IN int nIndex, IN MVD_LINE  Line, IN bool *pbValue);

	typedef union
	{
		struct
		{
			unsigned int bmLine0Status : 2;    // 0-�͵�ƽ��1-�ߵ�ƽ������ֵΪ�����Ų�����
			unsigned int bmLine1Status : 2;    // 0-�͵�ƽ��1-�ߵ�ƽ������ֵΪ�����Ų�����
			unsigned int bmLine2Status : 2;    // 0-�͵�ƽ��1-�ߵ�ƽ������ֵΪ�����Ų�����
			unsigned int bmLine3Status : 2;    // 0-�͵�ƽ��1-�ߵ�ƽ������ֵΪ�����Ų�����
			unsigned int bmLine4Status : 2;    // 0-�͵�ƽ��1-�ߵ�ƽ������ֵΪ�����Ų�����
			unsigned int bmLine5Status : 2;    // 0-�͵�ƽ��1-�ߵ�ƽ������ֵΪ�����Ų�����
		}bmValue;
		unsigned int uiValue;
	}LINE_STATUS_ALL;

	MVD_API MVD_ReturnCode __stdcall GetLineStatusAll(IN int nIndex, IN LINE_STATUS_ALL *pLineStatusAll);



	/// @attention ������������IoΪ����������������ԴΪLS_UserOutput�ſ�������
	MVD_API MVD_ReturnCode __stdcall SetLineUserOutputValue(IN int nIndex, IN MVD_LINE  Line, IN bool bValue);
	MVD_API MVD_ReturnCode __stdcall GetLineUserOutputValue(IN int nIndex, IN MVD_LINE  Line, IN bool *pbValue);


	/** @} DigitalIoControl*/

	/**@defgroup CounterControl
	* @{
	* @brief ��������ؿ��Ʋ���
	*/
	/// ����֧�ֵı�����ö������
	typedef enum
	{
		E_Counter0 = 0,
		E_Counter1 = 1,
		E_Counter2 = 2,
		E_Counter3 = 3,
	}MVD_COUNTER;

	/// ������Ϊ�������ź�Դ��ö������
	typedef enum
	{
		CES_Off = 0,      ///< �رռ�����
		CES_Line0 = 1,    ///< ��Line0���źŽ��м���
		CES_Line1 = 2,    ///< ��Line1���źŽ��м���
		CES_Line2 = 2,    ///< ��Line2���źŽ��м���
		CES_Line3 = 3,    ///< ��Line3���źŽ��м���
		CES_Line4 = 4,    ///< ��Line4���źŽ��м���
		CES_Line5 = 5,    ///< ��Line5���źŽ��м���

		CES_Encoder0 = 7,   ///< ��Encoder0�ļ���ֵ���м�����������ʽ��EncodeOutputModeΪ׼
		CES_Encoder1 = 8,   ///< ��Encoder1�ļ���ֵ���м�����������ʽ��EncodeOutputModeΪ׼

	}MVD_COUNTER_EVENT_SOURCE;

	/// @brief ���ü������ļ����ź�Դ
	/// @attention 
	MVD_API MVD_ReturnCode __stdcall SetCounterEventSource(IN int nIndex, IN MVD_COUNTER  Counter, IN MVD_COUNTER_EVENT_SOURCE CounterEventSource);
	MVD_API MVD_ReturnCode __stdcall GetCounterEventSource(IN int nIndex, IN MVD_COUNTER  Counter, OUT MVD_COUNTER_EVENT_SOURCE *pCounterEventSource);

	typedef enum
	{
		CEA_RisingEdge = 0,
		CEA_FallingEdge = 1,
		CEA_AnyEdge = 2,
	}MVD_COUNTER_EVENT_ACTIVATION;

	/// @brief ���ü������ļ����ź�Դ����Ч����
	/// @attention 
	MVD_API MVD_ReturnCode __stdcall SetCounterEventActivation(IN int nIndex, IN MVD_COUNTER  Counter, IN MVD_COUNTER_EVENT_ACTIVATION CounterEventActivation);
	MVD_API MVD_ReturnCode __stdcall GetCounterEventActivation(IN int nIndex, IN MVD_COUNTER  Counter, OUT MVD_COUNTER_EVENT_ACTIVATION *pCounterEventActivation);
	
	/// @brief �Լ��������и�λ
	MVD_API MVD_ReturnCode __stdcall ResetCounter(IN int nIndex, IN MVD_COUNTER  Counter);

	/// @brief ���ü�������ֵ
	MVD_API MVD_ReturnCode __stdcall SetCounterValue(IN int nIndex, IN MVD_COUNTER  Counter, unsigned int uiValue);

	/// @brief ��ȡ�������ĵ�ǰֵ
	MVD_API MVD_ReturnCode __stdcall GetCounterValue(IN int nIndex, IN MVD_COUNTER  Counter, unsigned int *puiValue);

	/** @} CounterControl*/


	/**@defgroup StrobeControl
	* @{
	* @brief �������ؿ��Ʋ���
	*/


	/// @brief ������������ʹ�ܣ�ͳһ����Ĭ�ϸߵ�ƽ��Ч��
	MVD_API MVD_ReturnCode __stdcall SetStrobeEnable(IN int nIndex, bool bEnable);

	/// @brief ��ȡ���������Ƿ�ʹ��
	MVD_API MVD_ReturnCode __stdcall GetStrobeEnable(IN int nIndex, bool *pbEnable);

	/// @brief ��������������ת
	MVD_API MVD_ReturnCode __stdcall SetStrobeInvert(IN int nIndex, bool bInvert);

	/// @brief ��ȡ���������Ƿ�ת
	MVD_API MVD_ReturnCode __stdcall GetStrobeInvert(IN int nIndex, bool *pbInvert);

	/// @brief ��������������ʱʱ��
	MVD_API MVD_ReturnCode __stdcall SetStrobeDelay(IN int nIndex, float fDelayUs);

	/// @brief ��ȡ����������ʱʱ��
	MVD_API MVD_ReturnCode __stdcall GetStrobeDelay(IN int nIndex, float *pfDelayUs);

	/// @brief ����������������ʱ��
	MVD_API MVD_ReturnCode __stdcall SetStrobeDuration(IN int nIndex, float fDurationUs);

	/// @brief ��ȡ������������ʱ��
	MVD_API MVD_ReturnCode __stdcall GetStrobeDuration(IN int nIndex, float *pfDurationUs);

	/** @} StrobeControl*/




	}

#ifdef __cplusplus
}
#endif

#endif

