#ifndef __MVDAPI_H__
#define __MVDAPI_H__

/// -----------------------------------------------------------------------------
///
/// @file    MVDAPI.h
/// @author  Mike
/// @version 0.1
/// @date    2020.08.06
/// @brief   MVDAPI应用开发接口函数声明头文件
/// @details 所有Get起始的函数，如果有多个可获取的参数时，可以只传入一个或多个有效地址，不需获取的参数只需传入NULL指针。
///          对于没有明确规定设置范围和步长的，需要参考值的数据类型，以数据类型的最小，最大值为依据。
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
	/// @brief     获取MVDAPI开发包版本。
	/// @param     [OUT]pSdkVersion  返回SDK版本号。
	///
	/// -----------------------------------------------------------------------------
	MVD_API MVD_ReturnCode __stdcall GetSdkVersion(OUT MVD_VERSION *pSdkVersion);

	/// -----------------------------------------------------------------------------
	///
	/// @ingroup   Global
	/// @brief     设置开发包使用的语言。
	/// @attention 语言的设置将影响MVDAPI_String.h中函数返回的字符串信息(立即生效)以及OpenSettingPage界面的信息（再次打开生效）。
	/// @param     [IN]Language    设置的语言
	///
	/// -----------------------------------------------------------------------------
	MVD_API MVD_ReturnCode __stdcall SetLanguage(IN MVD_LANGUAGE Language);

	/// -----------------------------------------------------------------------------
	///
	/// @ingroup   Global
	/// @brief     获取开发包使用的语言
	/// @param     [OUT]pLanguage   返回当前设置的语言。
	///
	/// -----------------------------------------------------------------------------
	MVD_API MVD_ReturnCode __stdcall GetLanguage(IN MVD_LANGUAGE *pLanguage);

	/** \defgroup Device

	* 设备初始化、打开、关闭、反初始化操作

	*/

    /// -----------------------------------------------------------------------------
	///
	/// @ingroup   Device
	/// @brief     初始化SDK库，枚举指定接口的设备，并返回设备信息列表。
    /// @attention 此函数可连续调用，但连续调用不会改变设备的数目，需要调用Uninitial之后再次调用此函数才可重新获取所连接设备数目和信息。
	/// @attention 用户获取到的MVD_DEVICE_INFORMATION指针数组可通过调用GetDeviceIndex来获取设备的索引（nIndex）
	/// @attention pstDeviceInfoList指向SDK内部的内存地址，这段地址用户不可修改。
    /// @param     [IN]nDeviceInterfaceType 设定要枚举的设备接口类型，请参考MVD_DEVICE_INTERFACE_TYPE枚举类型的定义，可进行组合。
    /// @param     [OUT]pstDeviceInfoList   成功返回后，设备信息的指针会被填写进此结构中。
    /// @return    MVD_SUCCESS              表示成功。 其他返回值请参考MVDAPI_ReturnCode.h头文件。
	/// @see       MVD_DEVICE_INTERFACE_TYPE
	///
    /// -----------------------------------------------------------------------------
	MVD_API MVD_ReturnCode __stdcall Initial(IN const unsigned int uiDeviceInterfaceType, OUT MVD_DEVICE_INFORMATION_LIST* pstDeviceInformationList);



    /// -----------------------------------------------------------------------------
	///
	/// @ingroup   Device
	/// @brief     反初始化SDK库，释放所有资源并自动关闭没有关闭的设备。
    /// @attention 此函数必须在进程退出之前被调用，以释放库里分配的资源。也可以在程序运行中调用，然后再次调用MVD_Initial以重新初始化库并获取设备信息列表。
    /// @param     无。
	/// @return    MVD_SUCCESS              表示成功。 其他返回值请参考MVDAPI_ReturnCode.h头文件。
	/// @see       Initial
	///
	/// -----------------------------------------------------------------------------
	MVD_API MVD_ReturnCode __stdcall Uninitial();

	/// -----------------------------------------------------------------------------
	/// @ingroup   Device
	/// @brief     设置设备序列号
	/// @attention 设备序列号是同型号设备用于身份的唯一标识，如果多台设备使用，需保证同一型号设备具有不同的设备序列号
	/// @return    MVD_SUCCESS              表示成功。 其他返回值请参考MVDAPI_ReturnCode.h头文件。
	/// @see       MVDAPI_ReturnCode.h
	///
	/// -----------------------------------------------------------------------------
	MVD_API MVD_ReturnCode __stdcall SetDeviceSerialNumber(IN int nIndex, unsigned int uiSerialNumber);

	/// -----------------------------------------------------------------------------
	///
	/// @ingroup   Device
	/// @brief     获取设备序列号
	/// @return    MVD_SUCCESS              表示成功。 其他返回值请参考MVDAPI_ReturnCode.h头文件。
	/// @see       MVDAPI_ReturnCode.h
	///
	/// -----------------------------------------------------------------------------
	MVD_API MVD_ReturnCode __stdcall GetDeviceSerialNumber(IN int nIndex, unsigned int *puiSerialNumber);

	/// -----------------------------------------------------------------------------
	///
	/// @ingroup   Device
	/// @brief     通过设备信息，获取设备所对应的索引（这个索引可以看作是这个设备的句柄)。
	/// @attention 对于多台设备操作时，一定要先调用这个函数以确定设备的索引值，这个索引值将作为对设备操作函数的第一个参数。注意不能有多台设备信息相同的设备同时存在。
	/// @attention pDeviceInformation需要使用通过调用Initial获取到的设备信息指针数组里的指针，注意这个函数是通过指针判断，所以不要把自己分配保存设备的信息进行传入。
	/// @param     [IN]pDeviceInformation 
	/// @return    MVD_SUCCESS              表示成功。 其他返回值请参考MVDAPI_ReturnCode.h头文件。
	///
	/// -----------------------------------------------------------------------------
	MVD_API int __stdcall GetDeviceIndex(IN MVD_DEVICE_INFORMATION *pDeviceInformation);

	/// -----------------------------------------------------------------------------
	///
	/// @ingroup   Device
	/// @brief     通过索引获取设备信息。
	/// @attention 注意，获取的是SDK内部对应的设备信息内存地址，用户不可改写其内容
	/// @return    MVD_SUCCESS              表示成功。 其他返回值请参考MVDAPI_ReturnCode.h头文件。
	///
	/// -----------------------------------------------------------------------------
	MVD_API MVD_ReturnCode __stdcall GetDeviceInformation(IN int nIndex, OUT MVD_DEVICE_INFORMATION **ppDeviceInformation);

	/// -----------------------------------------------------------------------------
	/// 
	/// @ingroup   Device
	/// @~chinese
	/// @brief     打开或关闭指定的设备
	/// @attention 多进程控制时，只有其他进程没有打开此设备，才可以对其打开操作。
	/// @return    MVD_SUCCESS              表示成功。 其他返回值请参考MVDAPI_ReturnCode.h头文件。
	///
	/// -----------------------------------------------------------------------------
	MVD_API MVD_ReturnCode __stdcall SetDeviceOpen(IN int nIndex, bool bOpen);


	/// -----------------------------------------------------------------------------
	///
	/// @ingroup   Device
	/// @~chinese
	/// @brief     获取设备开启状态
	/// @attention 本进程或其他进程是否此设备打开
	/// @return    MVD_SUCCESS              表示成功。 其他返回值请参考MVDAPI_ReturnCode.h头文件。
	///
	/// @~english
	/// @brief     Get Device Open Status
	/// @attention The Status Of Current Process or Other Process Open Status
	/// @return    MVD_SUCCESS              Success. Other return code refer to MVDAPI_ReturnCode.h.
	///
	/// -----------------------------------------------------------------------------
	MVD_API MVD_ReturnCode __stdcall GetDeviceOpen(IN int nIndex, bool *pbOpen);

	/** \defgroup Roi

	* 视场设置相关函数

	*/

	/// -----------------------------------------------------------------------------
	///
	/// @ingroup   Roi
	/// @brief     获取默认最大的ROI(感兴趣区域)信息。
	/// @attention 默认ROI也就是图像传感器最大视场时的设置。
	/// @param     [IN]nIndex         设备对应的索引，通过GetDeviceIndex获取。
	/// @param     [OUT]pRoiMaxSize   ROI(感兴趣区域)最大设置值。
	/// @return    MVD_SUCCESS        表示成功。 其他返回值请参考MVDAPI_ReturnCode.h头文件。
	///
	/// -----------------------------------------------------------------------------
	MVD_API MVD_ReturnCode __stdcall GetRoiMaxSize(IN int nIndex, OUT MVD_ROI_SIZE *pRoiMaxSize);

	/// -----------------------------------------------------------------------------
	///
	/// @ingroup   Roi
	/// @brief     获取当前的ROI(感兴趣区域)信息。
	/// @attention 无
	/// @param     [IN]nIndex         设备对应的索引，通过GetDeviceIndex获取。
	/// @param     [OUT]pRoiSize      当前ROI(感兴趣区域)大小。
	/// @return    MVD_SUCCESS        表示成功。 其他返回值请参考MVDAPI_ReturnCode.h头文件。
	///
	/// -----------------------------------------------------------------------------
	MVD_API MVD_ReturnCode __stdcall GetRoiSize(IN int nIndex, OUT MVD_ROI_SIZE *pRoiSize);

	/// -----------------------------------------------------------------------------
	///
	/// @ingroup   Roi
	/// @brief     设置ROI(感兴趣区域)。
	/// @attention 注意，这个函数不可以在启动采集后调用，必须要停止数据流后调用。
	///            另外，由于视场的设置根据图像传感器的不同，内部有可能会对设置的值进行调整，调整后的视场真实值可以通过GetRoiSize再次获取得到。
	/// @param     [IN]nIndex         设备对应的索引，通过GetDeviceIndex获取。
	/// @param     [IN]RoiSize        需要设置的ROI(感兴趣区域)大小。
	/// @return    MVD_SUCCESS        表示成功。 其他返回值请参考MVDAPI_ReturnCode.h头文件。
	///
	/// -----------------------------------------------------------------------------
	MVD_API MVD_ReturnCode __stdcall SetRoiSize(IN int nIndex, IN MVD_ROI_SIZE RoiSize);

	/// -----------------------------------------------------------------------------
	///
	/// @ingroup   Roi
	/// @brief     获取当前的ROI视场设置下，可设置的起始列(水平偏移)的最大值、最小值、默认值（默认值是指保持ROI视场在全视场的水平中心位置的值）。
	/// @attention 如果通过SetFieldOfView改变了ROI，需要再次调用重新获取。
	/// @param     [IN]nIndex         设备对应的索引，通过GetDeviceIndex获取。
	/// @param     [OUT]puiMin        当前ROI(感兴趣区域)最小可设置的水平偏移。
	/// @param     [OUT]puiMax        当前ROI(感兴趣区域)最大可设置的水平偏移。
	/// @param     [OUT]puiDef        当前ROI(感兴趣区域)居中时的水平偏移。
	/// @return    MVD_SUCCESS        表示成功。 其他返回值请参考MVDAPI_ReturnCode.h头文件。
	///
	/// -----------------------------------------------------------------------------
	MVD_API MVD_ReturnCode __stdcall GetRoiColStartRange(IN int nIndex, OUT unsigned int *puiMin, OUT unsigned int *puiMax, OUT unsigned int *puiDef);


	/// -----------------------------------------------------------------------------
	///
	/// @ingroup   Roi
	/// @brief     设置ROI(感兴趣区域)的在全阵列中的起始列（水平偏移）。
	/// @attention 如果通过SetFieldOfView改变了ROI，需要再次调用重新获取。
	/// @param     [IN]nIndex         设备对应的索引，通过GetDeviceIndex获取。
	/// @param     [IN]uiValue        需要设置的ROI(感兴趣区域)水平偏移值。
	/// @return    MVD_SUCCESS        表示成功。 其他返回值请参考MVDAPI_ReturnCode.h头文件。
	///
	/// -----------------------------------------------------------------------------
	MVD_API MVD_ReturnCode __stdcall SetRoiColStart(IN int nIndex, IN unsigned int uiValue);

	/// -----------------------------------------------------------------------------
	///
	/// @ingroup   Roi
	/// @brief     设置ROI(感兴趣区域)的在全阵列中的起始列（水平偏移）。
	/// @attention 如果通过SetFieldOfView改变了ROI，需要再次调用重新获取。
	/// @param     [IN]nIndex         设备对应的索引，通过GetDeviceIndex获取。
	/// @param     [OUT]puiValue      返回当前ROI(感兴趣区域)水平偏移值。
	/// @return    MVD_SUCCESS        表示成功。 其他返回值请参考MVDAPI_ReturnCode.h头文件。
	///
	/// -----------------------------------------------------------------------------
	MVD_API MVD_ReturnCode __stdcall GetRoiColStart(IN int nIndex, OUT unsigned int *puiValue);

	/// -----------------------------------------------------------------------------
	///
	/// @ingroup   Roi
	/// @brief     获取当前的ROI视场设置下，可设置的起始行(垂直偏移)的最大值、最小值、默认值（默认值是指保持ROI视场在全视场的垂直中心位置的值）。
	/// @attention 如果通过SetFieldOfView改变了ROI，需要再次调用重新获取。
	/// @param     [IN]nIndex         设备对应的索引，通过GetDeviceIndex获取。
	/// @param     [OUT]puiMin        当前ROI(感兴趣区域)最小可设置的垂直偏移。
	/// @param     [OUT]puiMax        当前ROI(感兴趣区域)最大可设置的垂直偏移。
	/// @param     [OUT]puiDef        当前ROI(感兴趣区域)居中时的垂直偏移。
	/// @return    MVD_SUCCESS        表示成功。 其他返回值请参考MVDAPI_ReturnCode.h头文件。
	///
	/// -----------------------------------------------------------------------------
	MVD_API MVD_ReturnCode __stdcall GetRoiRowStartRange(IN int nIndex, OUT unsigned int *puiMin, OUT unsigned int *puiMax, OUT unsigned int *puiDef);

	/// @ingroup   Roi
	/// @brief     设置ROI垂直起始行。
	MVD_API MVD_ReturnCode __stdcall SetRoiRowStart(IN int nIndex, IN unsigned int uiValue);

	/// @ingroup   Roi
	/// @brief     获取ROI垂直起始行。
	MVD_API MVD_ReturnCode __stdcall GetRoiRowStart(IN int nIndex, OUT unsigned int *puiValue);


	/// @ingroup   Image
	/// @brief     设置采集图像格式。
	/// @attention 注意，这个函数不可以在启动采集后调用，必须要停止数据流后调用。
	MVD_API MVD_ReturnCode __stdcall SetPixelFormat(IN int nIndex, IN MVD_PIXEL_FORMAT PixelFormat);


	/// @brief     获取采集图像格式。
	MVD_API MVD_ReturnCode __stdcall GetPixelFormat(IN int nIndex, OUT MVD_PIXEL_FORMAT *pPixelFormat);

	/// @brief     设置图像是否垂直翻转。
	MVD_API MVD_ReturnCode __stdcall GetFlip(IN int nIndex, bool *pbFlip);
	/// @brief     获取图像是否垂直翻转。
	MVD_API MVD_ReturnCode __stdcall SetFlip(IN int nIndex, bool bFlip);


	/// @brief     设置图像是否水平镜像。
	MVD_API MVD_ReturnCode __stdcall SetMirror(IN int nIndex, bool bMirror);
	/// @brief     获取图像是否水平镜像。
	MVD_API MVD_ReturnCode __stdcall GetMirror(IN int nIndex, bool *pbMirror);



	/// @brief     获取当前设置条件下，采集图像的基本信息。
	MVD_API MVD_ReturnCode __stdcall GetImageBaseInfo(IN int nIndex, MVD_IMAGE_BASE_INFO *pImageBaseInfo);


	/// @brief     打开设备设置属性对话框。
	/// @attention 这个对话框可以简化用户的编程流程，这里的设置都是可以在视频流开启或停止状态下进行操作。
	MVD_API MVD_ReturnCode __stdcall OpenSettingPage(IN int nIndex, IN void *hWndParent, int nLeft, int nTop);

	/// @ingroup   Grab
 	/// @brief     设置采集超时时间。
	MVD_API MVD_ReturnCode __stdcall SetGrabTimeout(IN int nIndex, unsigned long ulTimeoutMs);


	/// @brief     获取采集超时时间。
	MVD_API MVD_ReturnCode __stdcall GetGrabTimeout(IN int nIndex, unsigned long *pulTimeoutMs);

	/// @brief     开启采集数据流
	/// @attention 在调用SetGrabbingCallback或GrabImage之前必须先调用此函数开启采集数据流。
	MVD_API MVD_ReturnCode __stdcall SetGrabbingStart(IN int nIndex, IN bool bStart);

	/// @brief     获取采集流是否开启
	MVD_API MVD_ReturnCode __stdcall GetGrabbingStart(IN int nIndex, OUT bool *pbStart);

	/// @brief     获取采集帧率，必须开启采集数据流才可获取到有效帧率
	MVD_API MVD_ReturnCode __stdcall GetGrabbingFps(IN int nIndex, OUT float *pFps);


	/// @brief     开启或关闭采集回调。
	/// @attention 当pfGrabbingCallback设置为NULL会停止回调。回调采集与主动采集（调用GrabImage进行采集）用户只能选择其一，不可同时使用。
	MVD_API MVD_ReturnCode __stdcall SetGrabbingCallback(IN int nIndex, IN PMVD_GRABBING_CALLBACK pfGrabbingCallback, IN void* lpContext);

	/// @brief     获取采集回调是否开启或关闭。
	/// @attention 当*ppfGrabbingCallback的值为NULL表示采集回调已经关闭，否则为开启状态。
	MVD_API MVD_ReturnCode __stdcall GetGrabbingCallback(IN int nIndex, OUT PMVD_GRABBING_CALLBACK *ppfGrabbingCallback, OUT void** lpContext);


	/// -----------------------------------------------------------------------------
	///
	/// @brief     主动采集。
	/// @attention 调用GrabImage之前，必须调用SetGrabbingStart开启视频流，这个内存由SDK分配，用户不需要分配内存。使用之后需要调用GrabImageRelease通知SDK释放资源，否则会堵塞Grabbing线程。
	///            回调采集（SetGrabbingCallback）与主动采集（调用GrabImage进行采集）用户只能选择其一，不可同时使用。
	///
	/// -----------------------------------------------------------------------------
	MVD_API MVD_ReturnCode __stdcall GrabImage(IN const int nIndex, OUT MVD_GRAB_IMAGE_INFO **ppGrabImageInfo, OUT unsigned char **ppGrabImageData);

	/// @brief     通知SDK释放主动采集资源。
	/// @attention 每次调用一次MVD_GrabImage并对图像处理之后，必须调用一次此函数，以通知SDK释放资源，否则会堵塞Grabbing线程。
	MVD_API MVD_ReturnCode __stdcall GrabImageRelease(IN const int nIndex);


	/// @brief     保存图像。
	MVD_API MVD_ReturnCode __stdcall SaveImage(IN const MVD_GRAB_IMAGE_INFO *pGrabImageInfo, IN unsigned char *ppGrabImageData, IN const MVD_SAVE_IMAGE_INFORMATION SaveImageInformation);



	/// @brief     获取增益设置范围
	MVD_API MVD_ReturnCode __stdcall GetGainRange(IN int nIndex, MVD_GAIN_SELECTOR GainSelector, float *pfMin, float *pfMax);

	/// @brief     设置增益
	MVD_API MVD_ReturnCode __stdcall SetGain(IN int nIndex, MVD_GAIN_SELECTOR GainIndex, float fGain);

	/// @brief     获取增益
	MVD_API MVD_ReturnCode __stdcall GetGain(IN int nIndex, MVD_GAIN_SELECTOR GainIndex, float *pfGain);


	/// @brief     设置自动曝光调节上限（单位毫秒）
	/// @attention 当自动曝光调节的曝光时间超出设置的上限时，会在自动曝光回调状态里返回AES_ONCE_FAIL_OVER_RANGE或AES_CONTINUOUS_FAIL_OVER_RANGE
	MVD_API MVD_ReturnCode __stdcall SetAutoExposureTimeUpperLimit(IN int nIndex, float fAutoExposureTimeMs);

	/// @brief     获取自动曝光调节上限（单位毫秒）
	MVD_API MVD_ReturnCode __stdcall GetAutoExposureTimeUpperLimit(IN int nIndex, float *pfAutoExposureTimeMs);

	/// @brief     获取自动曝光调节目标灰度值范围
	MVD_API MVD_ReturnCode __stdcall GetAutoExposureTargetRange(IN int nIndex, int *pnMin, int *pnMax, int *pnDef);

	/// @brief     设置自动曝光调节目标灰度值
	MVD_API MVD_ReturnCode __stdcall SetAutoExposureTarget(IN int nIndex, int nAutoExposureTarget);

	/// @brief     获取自动曝光调节目标灰度值
	MVD_API MVD_ReturnCode __stdcall GetAutoExposureTarget(IN int nIndex, int *pnAutoExposureTarget);

	/// @brief     设置自动曝光回调函数
	MVD_API MVD_ReturnCode __stdcall SetAutoExposureCallback(IN int nIndex, PMVD_AUTO_EXPOSURE_CALLBACK pfCallback, void *lpContext);

	/// @brief     获取当前曝光模式
	MVD_API MVD_ReturnCode __stdcall GetExposureMode(IN int nIndex, MVD_EXPOSURE_MODE *pExposureModeSelector);

	/// @brief     设置曝光模式
	MVD_API MVD_ReturnCode __stdcall SetExposureMode(IN int nIndex, MVD_EXPOSURE_MODE ExposureMode);

	/// @brief     获取曝光设置范围（单位微秒）
	MVD_API MVD_ReturnCode __stdcall GetExposureTimeRange(IN int nIndex, float *pfMinUs, float *pfMaxUs);

	/// @brief     设置曝光时间（单位微秒）
	/// @attention 只有在曝光模式为手动模式EM_MANUAL时可以设置曝光时间
	MVD_API MVD_ReturnCode __stdcall SetExposureTime(IN int nIndex, float fExposureTimeUs);

	/// @brief     获取曝光时间（单位微秒）
	MVD_API MVD_ReturnCode __stdcall GetExposureTime(IN int nIndex, float *pfExposureTimeUs);

	/// @ingroup   WhiteBalance
	/// @brief     设置自动白平衡回调函数
	MVD_API MVD_ReturnCode __stdcall SetAutoWhiteBalanceCallback(IN int nIndex, PMVD_WHITE_BALANCE_CALLBACK pfCallBack, void *lpContext);

	/// @brief     设置白平衡预设值
	/// @attention 这个设置只有在白平衡模式设置为WBM_SOFTWARE_PRESETTING或WBM_HARDWARE_PRESETTING模式时才生效
	MVD_API MVD_ReturnCode __stdcall SetWhiteBalancePresetting(IN int nIndex, MVD_COLOR_TEMPERATURE ColorTemperature);

	/// @brief     获取当前选择的白平衡预设值
	MVD_API MVD_ReturnCode __stdcall GetWhiteBalancePresetting(IN int nIndex, MVD_COLOR_TEMPERATURE *pColorTemperature);

	/// @brief     获取白平衡模式
	MVD_API MVD_ReturnCode __stdcall GetWhiteBalanceMode(IN int nIndex, MVD_WHITE_BALANC_MODE *pWhiteBalanceMode);

	/// @brief     设置白平衡模式
	MVD_API MVD_ReturnCode __stdcall SetWhiteBalanceMode(IN int nIndex, MVD_WHITE_BALANC_MODE WhiteBalanceMode);

	/// @brief     手动设置白平衡系数矩阵（范围推荐-10-10）
	/// @attention 只有在在白平衡模式设置为WBM_SOFTWARE_MANUAL或WBM_HARDWARE_MANUAL模式时才可调用
	MVD_API MVD_ReturnCode __stdcall SetWhiteBalanceMatrix(IN int nIndex, float fMatrix[3]);

	/// @brief     获取白平衡系数矩阵
	MVD_API MVD_ReturnCode __stdcall GetWhiteBalanceMatrix(IN int nIndex, float fMatrix[3]);

	/// @ingroup   ColorCorrection
	/// @brief     获取色彩效正模式
	MVD_API MVD_ReturnCode __stdcall GetColorCorrectionMode(IN int nIndex, MVD_COLOR_CORRECTION_MODE *pColorCorrectionMode);

	/// @brief     设置色彩效正模式
	MVD_API MVD_ReturnCode __stdcall SetColorCorrectionMode(IN int nIndex, MVD_COLOR_CORRECTION_MODE ColorCorrectionMode);

	///
	/// @brief     手动设置色彩效正系数矩阵（范围推荐-10-10）
	/// @attention 只有在在色彩效正模式设置为CCM_SOFTWARE_MANUAL或CCM_HARDWARE_MANUAL模式时才可调用
	/// @see       SetColorCorrectionMode
	/// @see       GetColorCorrectionMode
	///

	MVD_API MVD_ReturnCode __stdcall SetColorCorrectionMatrix(IN int nIndex, float fMatrix[3][3]);

	/// @brief     获取当前色彩效正系数矩阵。
	/// @attention 也可以通过此函数实时获取自动色彩效正后的系数矩阵。
	/// @see       SetColorCorrectionMode
	/// @see       GetColorCorrectionMode
	///

	MVD_API MVD_ReturnCode __stdcall GetColorCorrectionMatrix(IN int nIndex, float fMatrix[3][3]);

	/// @brief     设置色彩效正预设值
	/// @attention 这个设置只有在色彩效正模式设置为CCM_SOFTWARE_PRESETTING或CCM_HARDWARE_PRESETTING模式时才生效
	/// @param     [IN]nIndex         设备对应的索引，通过GetDeviceIndex获取。
	/// @see       SetColorCorrectionMode
	/// @see       GetColorCorrectionMode
	///
	MVD_API MVD_ReturnCode __stdcall SetColorCorrectionPresetting(IN int nIndex, MVD_COLOR_TEMPERATURE ColorTemperature);

	/// @brief     获取色彩效正预设值
	/// @see       SetColorCorrectionMode
	/// @see       GetColorCorrectionMode
	///
	MVD_API MVD_ReturnCode __stdcall GetColorCorrectionPresetting(IN int nIndex, MVD_COLOR_TEMPERATURE *pColorTemperature);

	/// @ingroup   AdcCompanding
	/// @brief     获取图像传感器ADC转换精度（比特位数）
	/// @see       GetAdcCompandingMode
	MVD_API MVD_ReturnCode __stdcall GetAdcResolution(IN int nIndex, unsigned char *pucAdcResolution);


	/// @brief     设置相机ADC精度转换为8比特的模式
	/// @see       SetAdcCompandingMode
	MVD_API MVD_ReturnCode __stdcall SetAdcCompandingMode(IN int nIndex, MVD_ADC_COMPANDING_MODE CompandingMode);


	/// @brief     获取比特压缩（相机ADC精度转换为8比特）模式
	MVD_API MVD_ReturnCode __stdcall GetAdcCompandingMode(IN int nIndex, MVD_ADC_COMPANDING_MODE *pCompandingMode);

	/// @brief     设置位截取模式
	/// @attention 当CompandingMode为ACM_EXTRACT时才可以生效
	/// @see       SetAdcCompandingMode
	MVD_API MVD_ReturnCode __stdcall SetAdcCompandingExtractMode(IN int nIndex, MVD_EXTRACT_MODE ExtractMode);
	
	/// @brief     获取当前位截取模式
	/// @see       SetAdcCompandingMode
	MVD_API MVD_ReturnCode __stdcall GetAdcCompandingExtractMode(IN int nIndex, MVD_EXTRACT_MODE *pExtractMode);

	/// @brief     设置压缩查找表
	/// @attention 当CompandingMode为ACM_LUT时才可以生效，LUT查找表元素个数必须为2^AdcResolution（AdcResolution通过GetAdcResolution函数获取）
	/// @see       GetAdcResolution
	MVD_API MVD_ReturnCode __stdcall SetAdcCompandingLut(IN int nIndex, IN  unsigned char *pucLut, unsigned short usLutBytesSize);

	/// @brief     获取当前压缩查找表
	MVD_API MVD_ReturnCode __stdcall GetAdcCompandingLut(IN int nIndex, OUT unsigned char *pucLut, unsigned short *pusLutBytesSize);

	/// @ingroup   ImageProcess
	/// @brief     获取图像对比度参数调节的范围
	MVD_API MVD_ReturnCode __stdcall GetContrastRange(IN int nIndex, int *pnMin, int *pnMax, int *pnDef);

	/// @brief     设置图像对比度
	MVD_API MVD_ReturnCode __stdcall SetContrast(IN int nIndex, int nContrast);
	/// @brief     获取图像对比度
	MVD_API MVD_ReturnCode __stdcall GetContrast(IN int nIndex, int *pnContrast);

	/// @brief     获取图像亮度参数调节的范围
	MVD_API MVD_ReturnCode __stdcall GetBrightnessRange(IN int nIndex, int *pnMin, int *pnMax, int *pnDef);
	/// @brief     设置图像亮度
	MVD_API MVD_ReturnCode __stdcall SetBrightness(IN int nIndex, int nValue);
	/// @brief     获取图像亮度
	MVD_API MVD_ReturnCode __stdcall GetBrightness(IN int nIndex, int *pnValue);

	/// @brief     获取图像Gamm参数调节的范围
	MVD_API MVD_ReturnCode __stdcall GetGammaRange(IN int nIndex, int *pnMin, int *pnMax, int *pnDef);
	/// @brief     设置图像Gamma
	MVD_API MVD_ReturnCode __stdcall SetGamma(IN int nIndex, int nValue);
	/// @brief     获取图像Gamma
	MVD_API MVD_ReturnCode __stdcall GetGamma(IN int nIndex, int *pnValue);

	/// @brief     获取图像饱和度参数调节的范围
	MVD_API MVD_ReturnCode __stdcall GetSaturationRange(IN int nIndex, int *pnMin, int *pnMax, int *pnDef);
	/// @brief     设置图像饱和度
	MVD_API MVD_ReturnCode __stdcall SetSaturation(IN int nIndex, int nValue);
	/// @brief     获取图像饱和度
	MVD_API MVD_ReturnCode __stdcall GetSaturation(IN int nIndex, int *pnValue);


	/**@defgroup AcquisitionTriggerControl
	* @{
	* @brief 采集模式相关控制函数
	*/

	/// @ingroup   AcquisitionTrigger
	/// @brief     设置开始采集的触发模式
	/// @attention 这个函数主要作为控制FrameTrigger（帧触发）何时有效，默认为STM_CONTINUOUS,对于面阵相机一般不需要设置此模式
	/// @attention 对于需要一个外部信号来控制何时帧触发有效时，可以调用此函数进行设置，只有AcquisitionTrigger满足的条件下，才会判断FrameTrigger的条件
	///
	// MVD_API MVD_ReturnCode __stdcall SetAcquisitionTriggerMode(IN int nIndex, MVD_ACQUISITION_TRIGGER_MODE AcquisitionTriggerMode);

	// MVD_API MVD_ReturnCode __stdcall GetAcquisitionTriggerMode(IN int nIndex, MVD_ACQUISITION_TRIGGER_MODE *pAcquisitionTriggerMode);

	/// @brief     设置采集触发外部信号源
	/// @attention 只有在帧触发模式为FTM_EXTERNAL时才能生效    
	// MVD_API MVD_ReturnCode __stdcall SetAcquisitionTriggerExternalSource(IN int nIndex, MVD_ACQUISITION_TRIGGER_EXTERNAL_SOURCE AcquisitionTriggerExternalSource);

	/// @brief     获取当前采集触发信号所使用的外部信号源
	// MVD_API MVD_ReturnCode __stdcall GetAcquisitionTriggerExternalSource(IN int nIndex, MVD_ACQUISITION_TRIGGER_EXTERNAL_SOURCE *pAcquisitionTriggerExternalSource);

	/// @brief     设置采集触发外部触发源有效条件
	/// @attention 只有在帧触发模式为FTM_EXTERNAL时才能生效    
	//MVD_API MVD_ReturnCode __stdcall SetAcquisitionTriggerExternalActivation(IN int nIndex, MVD_ACQUISITION_TRIGGER_EXTERNAL_ACTIVATION FrameTriggerExternalActivation);

	/// @brief     获取当前设置的采集触发外部触发源有效条件
	//MVD_API MVD_ReturnCode __stdcall GetAcquisitionTriggerExternalActivation(IN int nIndex, MVD_ACQUISITION_TRIGGER_EXTERNAL_ACTIVATION *pFrameTriggerActivation);

	/// @brief     获取采集触发信号延时时间设置范围（微秒）
	//MVD_API MVD_ReturnCode __stdcall GetAcquisitionTriggerExternalDelayRange(IN int nIndex, float *pfMinUs, float *pfMaxUs, float *pfDefUs);

	/// @brief     设置采集触发信号延时时间（微秒）
	/// @attention 只有在帧触发模式为FTM_EXTERNAL时才能生效    
	//MVD_API MVD_ReturnCode __stdcall SetAcquisitionTriggerExternalDelay(IN int nIndex, float fDelayUs);

	/// @brief     获取采集触发信号延时时间（微秒）
	//MVD_API MVD_ReturnCode __stdcall GetAcquisitionTriggerExternalDelay(IN int nIndex, float *pfDelayUs);

	/// @brief     获取采集触发信号滤波时间设置范围（微秒）
	//MVD_API MVD_ReturnCode __stdcall GetAcquisitionTriggerExternalFilterRange(IN int nIndex, float *pfMinUs, float *pfMaxUs, float *pfDefUs);

	/// @brief     设置采集触发信号滤波时间（微秒）
	/// @attention 只有在帧触发模式为FTM_EXTERNAL时才能生效    
	//MVD_API MVD_ReturnCode __stdcall SetAcquisitionTriggerExternalFilter(IN int nIndex, float fFilterUs);

	/// @brief     获取采集触发信号滤波时间（微秒）
	//MVD_API MVD_ReturnCode __stdcall GetAcquisitionTriggerExternalFilter(IN int nIndex, float *pfFilterUs);

	/// @brief     执行软件采集触发
	/// @attention 在采集触发模式为STM_SOFTWARE模式下才可调用
	// MVD_API MVD_ReturnCode __stdcall ExecuteSoftwareAcquisitionTrigger(IN int nIndex);

	/// @brief     在AcquisitionTrigger条件满足情况下，FrameTrigger输出多少帧后再继续检测AcquisitionTrigger条件。同时这些帧会拼接并返回采集结果。
	/// @attention 采集时序图请参考AcquisitionTrigger，FrameTrigger模式组合控制时序图
	MVD_API MVD_ReturnCode __stdcall SetAcquisitionTriggerFramesCount(IN int nIndex, unsigned int uiFramesCount);
	MVD_API MVD_ReturnCode __stdcall GetAcquisitionTriggerFramesCount(IN int nIndex, unsigned int *puiFramesCount);

	/** @} AcquisitionTriggerControl*/

	/**@defgroup FrameTriggerTriggerControl
	* @{
	* @brief 帧触发输出控制的相关函数
	*/

	/// @ingroup   FrameTrigger
	/// @brief     设置帧触发模式
	/// @attention 这个函数用于控制何时触发一帧，前提条件时StratTrigger信号满足，如果AcquisitionTriggerMode=STM_CONTINUOUS，则不必考虑StratTrigger信号

	MVD_API MVD_ReturnCode __stdcall SetFrameTriggerMode(IN int nIndex, MVD_FRAME_TRIGGER_MODE FrameTriggerMode);

	/// @brief     获取当前帧触发模式
	MVD_API MVD_ReturnCode __stdcall GetFrameTriggerMode(IN int nIndex, MVD_FRAME_TRIGGER_MODE *pFrameTriggerMode);

	/// @brief     设置帧触发外部信号源
	/// @attention 只有在帧触发模式为FTM_EXTERNAL时才能生效，这个函数无特殊情况下，不需用户设置，由硬件设计固定，参考硬件IO说明。  
	MVD_API MVD_ReturnCode __stdcall SetFrameTriggerExternalSource(IN int nIndex, MVD_FRAME_TRIGGER_EXTERNAL_SOURCE FrameTriggerExternalSource);

	/// @brief     获取当前帧触发信号所使用的外部触发源
	MVD_API MVD_ReturnCode __stdcall GetFrameTriggerExternalSource(IN int nIndex, MVD_FRAME_TRIGGER_EXTERNAL_SOURCE *pFrameTriggerExternalSource);

	/// @brief     设置帧触发外部触发源有效条件
	/// @attention 只有在帧触发模式为FTM_EXTERNAL时才能生效，设备在不接外部信号的情况下，内部默认为低电平信号    
	MVD_API MVD_ReturnCode __stdcall SetFrameTriggerExternalActivation(IN int nIndex, MVD_FRAME_TRIGGER_EXTERNAL_ACTIVATION FrameTriggerExternalActivation);

	/// @brief     获取当前设置的帧触发外部触发源有效条件
	MVD_API MVD_ReturnCode __stdcall GetFrameTriggerExternalActivation(IN int nIndex, MVD_FRAME_TRIGGER_EXTERNAL_ACTIVATION *pFrameTriggerActivation);

	/// @brief     获取帧触发延时时间设置范围（微秒）
	MVD_API MVD_ReturnCode __stdcall GetFrameTriggerExternalDelayRange(IN int nIndex, float *pfMinUs, float *pfMaxUs, float *pfDefUs);
	
	/// @brief     设置帧触发延时时间（微秒）
	/// @attention 只有在帧触发模式为FTM_EXTERNAL时才能生效    
	MVD_API MVD_ReturnCode __stdcall SetFrameTriggerExternalDelay(IN int nIndex, float fDelayUs);

	/// @brief     获取帧触发延时时间（微秒）
	MVD_API MVD_ReturnCode __stdcall GetFrameTriggerExternalDelay(IN int nIndex, float *pfDelayUs);

	/// @brief     获取帧触发滤波时间设置范围（微秒）
	MVD_API MVD_ReturnCode __stdcall GetFrameTriggerExternalFilterRange(IN int nIndex, float *pfMinUs, float *pfMaxUs, float *pfDefUs);

	/// @brief     设置帧触发滤波时间（微秒）
	/// @attention 只有在帧触发模式为FTM_EXTERNAL时才能生效    
	MVD_API MVD_ReturnCode __stdcall SetFrameTriggerExternalFilter(IN int nIndex, float fFilterUs);

	/// @brief     获取帧触发滤波时间（微秒）
	MVD_API MVD_ReturnCode __stdcall GetFrameTriggerExternalFilter(IN int nIndex, float *pfFilterUs);

	/// @brief     获取固定帧率设置范围（帧每秒）
	MVD_API MVD_ReturnCode __stdcall GetFrameTriggerFixedRateRange(IN int nIndex, float *pfMin, float *pfMax, float *pfDef);

	/// @brief     设置固定帧率（帧每秒）
	/// @attention 只有在帧触发模式为FTM_FIXED_FRAME_RATE时才能生效    
	MVD_API MVD_ReturnCode __stdcall SetFrameTriggerFixedRate(IN int nIndex, float fFps);

	/// @brief     获取当前设置的固定帧率（帧每秒）
	MVD_API MVD_ReturnCode __stdcall GetFrameTriggerFixedRate(IN int nIndex, float *pfFps);



	/// @brief     执行软件帧触发
	/// @attention 之后在帧触发模式为FTM_SOFTWARE模式下才可调用（这个函数暂不需调用，只要设置软件触发模式，会在采集时自动触发）
	MVD_API MVD_ReturnCode __stdcall ExecuteSoftwareFrameTrigger(IN int nIndex);

	/** @} FrameTriggerTriggerControl*/

	/**@defgroup UserPresettingControl
	* @{
	* @brief 用户预设配置相关控制函数
	*/

	/// -----------------------------------------------------------------------------
	///
	/// @brief     保存当前设备状态到指定的用户预设组。
	/// @attention 将当前设备所有相关信息保存到指定的用户预设组，方便用户通过LoadUserPresetting进行重新加载。
	/// @param     [IN]nIndex         设备对应的索引，通过GetDeviceIndex获取。
	/// @param     [IN]UserPresetting 用户预设组号，参考MVD_USER_PRESETTING枚举类型
	/// @return    MVD_SUCCESS        表示成功。 其他返回值请参考MVDAPI_ReturnCode.h头文件。
	/// @see       LoadUserPresetting
	///
	/// -----------------------------------------------------------------------------
	MVD_API MVD_ReturnCode __stdcall SaveUserPresetting(IN int nIndex, IN MVD_USER_PRESETTING UserPresetting);


	/// -----------------------------------------------------------------------------
	///
	/// @brief     加载指定的用户预设组。
	/// @attention 将之前保存的、相应的用户预设组信息重新加载。
	/// @param     [IN]nIndex         设备对应的索引，通过GetDeviceIndex获取。
	/// @param     [IN]UserPresetting 用户预设组号，参考MVD_USER_PRESETTING枚举类型
	/// @return    MVD_SUCCESS        表示成功。 其他返回值请参考MVDAPI_ReturnCode.h头文件。
	/// @see       SaveUserPresetting
	///
	/// -----------------------------------------------------------------------------
	MVD_API MVD_ReturnCode __stdcall LoadUserPresetting(IN int nIndex, IN MVD_USER_PRESETTING UserPresetting);


	/// -----------------------------------------------------------------------------
	///
	/// @brief     设置默认加载的预设组。
	/// @attention 设置默认加载预设组后，每次调用Initial会按照此预设组的信息对设备进行加载设置。
	/// @param     [IN]nIndex         设备对应的索引，通过GetDeviceIndex获取。
	/// @param     [IN]UserPresetting 要设置为默认加载的用户预设组，参考MVD_USER_PRESETTING枚举类型
	/// @return    MVD_SUCCESS        表示成功。 其他返回值请参考MVDAPI_ReturnCode.h头文件。
	/// @see       GetDefaultUserPresetting
	///
	/// -----------------------------------------------------------------------------
	MVD_API MVD_ReturnCode __stdcall SetDefaultUserPresetting(IN int nIndex, IN MVD_USER_PRESETTING UserPresetting);


	/// -----------------------------------------------------------------------------
	///
	/// @brief     获取默认加载的预设组。
	/// @attention 如果没有预设组？？。
	/// @param     [IN]nIndex           设备对应的索引，通过GetDeviceIndex获取。
	/// @param     [OUT]pUserPresetting 返回当前默认的预设组
	/// @return    MVD_SUCCESS        表示成功。 其他返回值请参考MVDAPI_ReturnCode.h头文件。
	/// @see       SetDefaultUserPresetting
	///
	/// -----------------------------------------------------------------------------
	MVD_API MVD_ReturnCode __stdcall GetDefaultUserPresetting(IN int nIndex, OUT MVD_USER_PRESETTING *pUserPresetting);

	MVD_API bool __stdcall IsUserPresettingAvailable(IN int nIndex, IN MVD_USER_PRESETTING UserPresetting);

	/** @} UserPresettingControl*/

	/**@defgroup EncoderControl
	* @{
	* @brief 差分编码器控制相关函数
	*/

	/// 可能支持的编码器枚举类型
	typedef enum
	{
		E_Encoder0 = 0,
		E_Encoder1 = 1,
	}MVD_ENCODER;

	/// 可能作为编码器A,B相连接的物理引脚
	typedef enum
	{
		ES_Off = 0,      ///< 不使用物理引脚，释放Line做其他用途（定义Line的默认行为）
		ES_Line0 = 1,    ///< 使用Line0物理引脚
		ES_Line1 = 2,    ///< 使用Line1物理引脚
		ES_Line2 = 2,    ///< 使用Line2物理引脚
		ES_Line3 = 3,    ///< 使用Line3物理引脚
		ES_Line4 = 4,    ///< 使用Line4物理引脚
		ES_Line5 = 5,    ///< 使用Line5物理引脚
	}MVD_ENCODER_SOURCE;

	/// @brief 设置差分编码器A，B相所连接的物理引脚Line
	/// @attention 注意有些Line可能不支持差分编码器的输入，请参考硬件IO说明文档，需要根据实际的物理连接进行相应的设置或采用默认设置（默认设置就是软件符合硬件的出厂定义设置）。
	MVD_API MVD_ReturnCode __stdcall SetEncoderSource(IN int nIndex, IN MVD_ENCODER  Encoder, IN MVD_ENCODER_SOURCE EncoderSourceA, IN MVD_ENCODER_SOURCE EncoderSourceB);
	MVD_API MVD_ReturnCode __stdcall GetEncoderSource(IN int nIndex, IN MVD_ENCODER  Encoder, OUT MVD_ENCODER_SOURCE *pEncoderSourceA, OUT MVD_ENCODER_SOURCE *pEncoderSourceB);

	/// 对编码器计数的可能模式
	typedef enum
	{
		EM_FourPhase = 0,         ///< 每全周期增加，减小计数（抖动滤波）
		EM_HighResolution = 1,    ///< 每90度相位增加，减小计数（无抖动滤波）
	}MVD_ENCODER_MODE;

	/// @brief 设置编码器计数模式
	MVD_API MVD_ReturnCode __stdcall SetEncoderMode(IN int nIndex, IN MVD_ENCODER  Encoder, IN MVD_ENCODER_MODE EncoderMode);
	MVD_API MVD_ReturnCode __stdcall GetEncoderMode(IN int nIndex, IN MVD_ENCODER  Encoder, IN MVD_ENCODER_MODE *pEncoderMode);

	/// @brief 设置编码器的分频数
	MVD_API MVD_ReturnCode __stdcall SetEncoderDivider(IN int nIndex, IN MVD_ENCODER  Encoder, IN unsigned short usEncoderDivider);
	MVD_API MVD_ReturnCode __stdcall GetEncoderDivider(IN int nIndex, IN MVD_ENCODER  Encoder, IN unsigned short *pusEncoderDivider);

	/// 编码器计数有效输出模式
	typedef enum
	{
		EOM_Off = 0,
		EOM_PositionUp = 1,    ///< 所有正向运动的新位置产生输出脉冲，需要考虑反向移动了多少，恢复正向时需减去反向的个数
		EOM_PositionDown = 2,  ///< 所有反向运动的新位置产生输出脉冲，需要考虑正向移动了多少，恢复反向时需减去正向的个数
		EOM_DirectionUp = 3,   ///< 所有正向运动都产生输出脉冲，反向忽略
		EOM_DirectionDown = 4, ///< 所有反向运动都产生输出脉冲，正向忽略
		EOM_Motion = 5,        ///< 正反向都输出脉冲
	}MVD_ENCODER_OUTPUT_MODE;

	/// @brief 设置编码器计数有效输出模式
	MVD_API MVD_ReturnCode __stdcall SetEncoderOutputMode(IN int nIndex, IN MVD_ENCODER  Encoder, IN MVD_ENCODER_OUTPUT_MODE usEncoderOutputMode);
	MVD_API MVD_ReturnCode __stdcall GetEncoderOutputMode(IN int nIndex, IN MVD_ENCODER  Encoder, IN MVD_ENCODER_OUTPUT_MODE *pusEncoderOutputMode);
	
	/** @} EncoderControl*/

	/**@defgroup DigitalIoControl
	* @{
	* @brief 数字IO控制相关函数
	*/

	/// 物理引脚Line可能的输入输出模式
	typedef enum
	{
		LM_Input = 0,    ///< Io 默认为Input输入
		LM_Output = 1,
	}MVD_LINE_MODE;

	/// 硬件可能支持的物理引脚，定义物理IO枚举类型（这个值对应设备的IO接口，请参考硬件IO说明文档）
	typedef enum
	{
		IO_Line0 = 0,    ///< 物理Io Line0
		IO_Line1 = 1,    ///< 物理Io Line1
		IO_Line2 = 2,    ///< 物理Io Line2
		IO_Line3 = 3,    ///< 物理Io Line3
		IO_Line4 = 4,    ///< 物理Io Line4
		IO_Line5 = 5,    ///< 物理Io Line5
		///...
	}MVD_LINE;

	/// 注意，如果Line被其他函数作为Source，这个Line将不能作为Digital Io使用。
	/// @brief 设置Line物理引脚的输入输出模式
	/// @attention 注意，有些Line只能支持输入或输出其中一种
	MVD_API MVD_ReturnCode __stdcall SetLineMode(IN int nIndex, IN MVD_LINE  Line, IN MVD_LINE_MODE LineMode);
	/// @brief 获取Line物理引脚的输入输出模式
	MVD_API MVD_ReturnCode __stdcall GetLineMode(IN int nIndex, IN MVD_LINE  Line, IN MVD_LINE_MODE *pLineMode);

	/// @brief 对Line上的输入输出信号进行翻转处理
	MVD_API MVD_ReturnCode __stdcall SetLineInvert(IN int nIndex, IN MVD_LINE  Line, IN bool bInvert);
	MVD_API MVD_ReturnCode __stdcall GetLineInvert(IN int nIndex, IN MVD_LINE  Line, IN bool *pInvert);

	/// 可能选择的输出源，通过指定的Line输出
	typedef enum
	{
		LS_Off = 0,
		LS_UserOutput = 1,         ///< 用户可以通过SetLineUserOutputValue来进行对输出IO的设置
		LS_FrameTriggerWait = 2,   ///< 信号有效（高电平有效），表示可以进行下一次FrameTrigger
		LS_FrameActive,            ///< 信号有效（高电平有效），表示正在曝光和Readout
		LS_FrameTriggerMissed,     ///< 信号有效（ ？ms的高电平），表示一个帧触发信号丢失
		LS_ExposureActive,         ///< 信号有效（高电平有效），表示Sensor曝光期间
		LS_Stream0TransferActive,  ///< 信号有效（高电平有效），表示正在传输图像数据
	}MVD_LINE_SOURCE;

	/// @brief     绑定信号源到一个输出引脚，从而输出此信号
	/// @attention 必须首先设置Io为输出，才可以设置输出源
	MVD_API MVD_ReturnCode __stdcall SetLineSource(IN int nIndex, IN MVD_LINE  Line, IN MVD_LINE_SOURCE LineSource);
	MVD_API MVD_ReturnCode __stdcall GetLineSource(IN int nIndex, IN MVD_LINE  Line, IN MVD_LINE_SOURCE *pLineSource);

	/// @brief     读取指定引脚的状态（输入输出引脚都可以读）
	MVD_API MVD_ReturnCode __stdcall GetLineStatus(IN int nIndex, IN MVD_LINE  Line, IN bool *pbValue);

	typedef union
	{
		struct
		{
			unsigned int bmLine0Status : 2;    // 0-低电平，1-高电平，其他值为次引脚不存在
			unsigned int bmLine1Status : 2;    // 0-低电平，1-高电平，其他值为次引脚不存在
			unsigned int bmLine2Status : 2;    // 0-低电平，1-高电平，其他值为次引脚不存在
			unsigned int bmLine3Status : 2;    // 0-低电平，1-高电平，其他值为次引脚不存在
			unsigned int bmLine4Status : 2;    // 0-低电平，1-高电平，其他值为次引脚不存在
			unsigned int bmLine5Status : 2;    // 0-低电平，1-高电平，其他值为次引脚不存在
		}bmValue;
		unsigned int uiValue;
	}LINE_STATUS_ALL;

	MVD_API MVD_ReturnCode __stdcall GetLineStatusAll(IN int nIndex, IN LINE_STATUS_ALL *pLineStatusAll);



	/// @attention 必须首先设置Io为输出，并且设置输出源为LS_UserOutput才可以设置
	MVD_API MVD_ReturnCode __stdcall SetLineUserOutputValue(IN int nIndex, IN MVD_LINE  Line, IN bool bValue);
	MVD_API MVD_ReturnCode __stdcall GetLineUserOutputValue(IN int nIndex, IN MVD_LINE  Line, IN bool *pbValue);


	/** @} DigitalIoControl*/

	/**@defgroup CounterControl
	* @{
	* @brief 计数器相关控制操作
	*/
	/// 可能支持的编码器枚举类型
	typedef enum
	{
		E_Counter0 = 0,
		E_Counter1 = 1,
		E_Counter2 = 2,
		E_Counter3 = 3,
	}MVD_COUNTER;

	/// 可能作为计数器信号源的枚举类型
	typedef enum
	{
		CES_Off = 0,      ///< 关闭计数器
		CES_Line0 = 1,    ///< 对Line0的信号进行计数
		CES_Line1 = 2,    ///< 对Line1的信号进行计数
		CES_Line2 = 2,    ///< 对Line2的信号进行计数
		CES_Line3 = 3,    ///< 对Line3的信号进行计数
		CES_Line4 = 4,    ///< 对Line4的信号进行计数
		CES_Line5 = 5,    ///< 对Line5的信号进行计数

		CES_Encoder0 = 7,   ///< 对Encoder0的计数值进行计数，计数方式以EncodeOutputMode为准
		CES_Encoder1 = 8,   ///< 对Encoder1的计数值进行计数，计数方式以EncodeOutputMode为准

	}MVD_COUNTER_EVENT_SOURCE;

	/// @brief 设置计数器的计数信号源
	/// @attention 
	MVD_API MVD_ReturnCode __stdcall SetCounterEventSource(IN int nIndex, IN MVD_COUNTER  Counter, IN MVD_COUNTER_EVENT_SOURCE CounterEventSource);
	MVD_API MVD_ReturnCode __stdcall GetCounterEventSource(IN int nIndex, IN MVD_COUNTER  Counter, OUT MVD_COUNTER_EVENT_SOURCE *pCounterEventSource);

	typedef enum
	{
		CEA_RisingEdge = 0,
		CEA_FallingEdge = 1,
		CEA_AnyEdge = 2,
	}MVD_COUNTER_EVENT_ACTIVATION;

	/// @brief 设置计数器的计数信号源的有效条件
	/// @attention 
	MVD_API MVD_ReturnCode __stdcall SetCounterEventActivation(IN int nIndex, IN MVD_COUNTER  Counter, IN MVD_COUNTER_EVENT_ACTIVATION CounterEventActivation);
	MVD_API MVD_ReturnCode __stdcall GetCounterEventActivation(IN int nIndex, IN MVD_COUNTER  Counter, OUT MVD_COUNTER_EVENT_ACTIVATION *pCounterEventActivation);
	
	/// @brief 对计数器进行复位
	MVD_API MVD_ReturnCode __stdcall ResetCounter(IN int nIndex, IN MVD_COUNTER  Counter);

	/// @brief 设置计数器的值
	MVD_API MVD_ReturnCode __stdcall SetCounterValue(IN int nIndex, IN MVD_COUNTER  Counter, unsigned int uiValue);

	/// @brief 读取计数器的当前值
	MVD_API MVD_ReturnCode __stdcall GetCounterValue(IN int nIndex, IN MVD_COUNTER  Counter, unsigned int *puiValue);

	/** @} CounterControl*/


	/**@defgroup StrobeControl
	* @{
	* @brief 闪光灯相关控制操作
	*/


	/// @brief 设置闪光灯输出使能（统一定义默认高电平有效）
	MVD_API MVD_ReturnCode __stdcall SetStrobeEnable(IN int nIndex, bool bEnable);

	/// @brief 读取闪光灯输出是否使能
	MVD_API MVD_ReturnCode __stdcall GetStrobeEnable(IN int nIndex, bool *pbEnable);

	/// @brief 设置闪光灯输出翻转
	MVD_API MVD_ReturnCode __stdcall SetStrobeInvert(IN int nIndex, bool bInvert);

	/// @brief 读取闪光灯输出是否翻转
	MVD_API MVD_ReturnCode __stdcall GetStrobeInvert(IN int nIndex, bool *pbInvert);

	/// @brief 设置闪光灯输出延时时间
	MVD_API MVD_ReturnCode __stdcall SetStrobeDelay(IN int nIndex, float fDelayUs);

	/// @brief 获取闪光灯输出延时时间
	MVD_API MVD_ReturnCode __stdcall GetStrobeDelay(IN int nIndex, float *pfDelayUs);

	/// @brief 设置闪光灯输出保持时间
	MVD_API MVD_ReturnCode __stdcall SetStrobeDuration(IN int nIndex, float fDurationUs);

	/// @brief 获取闪光灯输出保持时间
	MVD_API MVD_ReturnCode __stdcall GetStrobeDuration(IN int nIndex, float *pfDurationUs);

	/** @} StrobeControl*/




	}

#ifdef __cplusplus
}
#endif

#endif

