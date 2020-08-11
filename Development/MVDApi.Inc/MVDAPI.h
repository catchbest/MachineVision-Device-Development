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


	/// -----------------------------------------------------------------------------
	///
	/// @brief     获取MVDAPI开发包版本。
	/// @param     [OUT]pSdkVersion  返回SDK版本号。
	///
	/// -----------------------------------------------------------------------------
	MVD_API MVD_ReturnCode __stdcall GetSdkVersion(OUT MVD_VERSION *pSdkVersion);

	/// -----------------------------------------------------------------------------
	///
	/// @brief     设置开发包使用的语言。
	/// @attention 语言的设置将影响MVDAPI_String.h中函数返回的字符串信息(立即生效)以及OpenSettingPage界面的信息（再次打开生效）。
	/// @param     [IN]Language    设置的语言
	///
	/// -----------------------------------------------------------------------------
	MVD_API MVD_ReturnCode __stdcall SetLanguage(IN MVD_LANGUAGE Language);

	/// -----------------------------------------------------------------------------
	///
	/// @brief     获取开发包使用的语言
	/// @param     [OUT]pLanguage   返回当前设置的语言。
	///
	/// -----------------------------------------------------------------------------
	MVD_API MVD_ReturnCode __stdcall GetLanguage(IN MVD_LANGUAGE *pLanguage);

    /// -----------------------------------------------------------------------------
	///
    /// @brief     初始化SDK库，枚举指定接口的设备，并返回设备信息列表。
    /// @attention 此函数可连续调用，但连续调用不会改变设备的数目，需要调用Uninitial之后再次调用此函数才可重新获取所连接设备数目和信息。
	/// @attention 用户获取到的MVD_DEVICE_INFORMATION指针数组可通过调用GetDeviceIndex来获取设备的索引（nIndex）
    /// @param     [IN]nDeviceInterfaceType 设定要枚举的设备接口类型，请参考MVD_DEVICE_INTERFACE_TYPE枚举类型的定义，可进行组合。
    /// @param     [OUT]pstDeviceInfoList   成功返回后，设备信息的指针会被填写进此结构中。
    /// @return    MVD_SUCCESS              表示成功。 其他返回值请参考MVDAPI_ReturnCode.h头文件。
	/// @see       MVD_DEVICE_INTERFACE_TYPE
	/// @note      pstDeviceInfoList指向SDK内部的内存地址，这段地址用户不可修改。
	///
    /// -----------------------------------------------------------------------------
	MVD_API MVD_ReturnCode __stdcall Initial(IN const unsigned int uiDeviceInterfaceType, OUT MVD_DEVICE_INFORMATION_LIST* pstDeviceInformationList);

    /// -----------------------------------------------------------------------------
	///
    /// @brief     反初始化SDK库，释放所有资源并自动关闭没有关闭的设备。
    /// @attention 此函数必须在进程退出之前被调用，以释放库里分配的资源。也可以在程序运行中调用，然后再次调用MVD_Initial以重新初始化库并获取设备信息列表。
    /// @param     无。
	/// @return    MVD_SUCCESS              表示成功。 其他返回值请参考MVDAPI_ReturnCode.h头文件。
	/// @see       Initial
	///
	/// -----------------------------------------------------------------------------
	MVD_API MVD_ReturnCode __stdcall Uninitial();

	///
	/// @brief     设置设备序列号
	/// @attention 设备序列号是同型号设备用于身份的唯一标识，如果多台设备使用，需保证同一型号设备具有不同的设备序列号
	/// @return    MVD_SUCCESS              表示成功。 其他返回值请参考MVDAPI_ReturnCode.h头文件。
	/// @see       MVDAPI_ReturnCode.h
	///
	MVD_API MVD_ReturnCode __stdcall SetDeviceSerialNumber(IN int nIndex, unsigned int uiSerialNumber);

	///
	/// @brief     获取设备序列号
	/// @return    MVD_SUCCESS              表示成功。 其他返回值请参考MVDAPI_ReturnCode.h头文件。
	/// @see       MVDAPI_ReturnCode.h
	///
	MVD_API MVD_ReturnCode __stdcall GetDeviceSerialNumber(IN int nIndex, unsigned int *puiSerialNumber);

	/// -----------------------------------------------------------------------------
	///
	/// @brief     通过设备信息，获取设备所对应的索引（这个索引可以看作是这个设备的句柄)。
	/// @attention 对于多台设备操作时，一定要先调用这个函数以确定设备的索引值，这个索引值将作为对设备操作函数的第一个参数。注意不能有多台设备信息相同的设备同时存在。
	/// @attention pDeviceInformation需要使用通过调用Initial获取到的设备信息指针数组里的指针，注意这个函数是通过指针判断，所以不要把自己分配保存设备的信息进行传入。
	/// @param     [IN]pDeviceInformation 
	/// @return    MVD_SUCCESS              表示成功。 其他返回值请参考MVDAPI_ReturnCode.h头文件。
	///
	/// -----------------------------------------------------------------------------
	MVD_API int __stdcall GetDeviceIndex(IN MVD_DEVICE_INFORMATION *pDeviceInformation);

	/// @brief     通过索引获取设备信息。
	/// @attention 注意，获取的是SDK内部对应的设备信息内存地址，用户不可改写其内容
	/// @return    MVD_SUCCESS              表示成功。 其他返回值请参考MVDAPI_ReturnCode.h头文件。
	///
	MVD_API MVD_ReturnCode __stdcall GetDeviceInformation(IN int nIndex, OUT MVD_DEVICE_INFORMATION **ppDeviceInformation);

	/// @brief     打开或关闭指定的设备
	/// @attention 多进程控制时，只有其他进程没有打开此设备，才可以对其打开操作。
	/// @return    MVD_SUCCESS              表示成功。 其他返回值请参考MVDAPI_ReturnCode.h头文件。
	///
	MVD_API MVD_ReturnCode __stdcall SetDeviceOpen(IN int nIndex, bool bOpen);


	/// @brief     获取设备开启状态
	/// @attention 本进程或其他进程是否此设备打开
	/// @return    MVD_SUCCESS              表示成功。 其他返回值请参考MVDAPI_ReturnCode.h头文件。
	///
	MVD_API MVD_ReturnCode __stdcall GetDeviceOpen(IN int nIndex, bool *pbOpen);

	/// -----------------------------------------------------------------------------
	///
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
	/// @brief     设置ROI(感兴趣区域)。
	/// @attention 注意，这个函数不可以在启动采集后调用，必须要停止数据流后调用。
	///            另外，由于视场的设置根据图像传感器的不同，内部有可能会对设置的值进行调整，调整后的视场真实值可以通过GetRoiSize再次获取得到。
	/// @param     [IN]nIndex         设备对应的索引，通过GetDeviceIndex获取。
	/// @param     [IN]RoiSize        需要设置的ROI(感兴趣区域)大小。
	/// @return    MVD_SUCCESS        表示成功。 其他返回值请参考MVDAPI_ReturnCode.h头文件。
	///
	/// -----------------------------------------------------------------------------
	MVD_API MVD_ReturnCode __stdcall SetRoiSize(IN int nIndex, IN MVD_ROI_SIZE RoiSize);

	/// @brief     设置采集图像格式。
	/// @attention 注意，这个函数不可以在启动采集后调用，必须要停止数据流后调用。
	MVD_API MVD_ReturnCode __stdcall SetImageFormat(IN int nIndex, MVD_IMAGE_FORMAT ImageFormat);


	/// @brief     获取采集图像格式。
	MVD_API MVD_ReturnCode __stdcall GetImageFormat(IN int nIndex, MVD_IMAGE_FORMAT *pImageFormat);

	/// @brief     获取当前设置条件下，采集图像的基本信息。
	MVD_API MVD_ReturnCode __stdcall GetImageBaseInfo(IN int nIndex, MVD_IMAGE_BASE_INFO *pImageBaseInfo);


	/// @brief     打开设备设置属性对话框。
	/// @attention 这个对话框可以简化用户的编程流程，这里的设置都是可以在视频流开启或停止状态下进行操作。
	MVD_API MVD_ReturnCode __stdcall OpenSettingPage(IN int nIndex, IN void *hWndParent, int nLeft, int nTop);


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


	/// @brief     主动采集。
	/// @attention 调用GrabImage之前，必须调用SetGrabbingStart开启视频流，这个内存由SDK分配，用户不需要分配内存。使用之后需要调用GrabImageRelease通知SDK释放资源，否则会堵塞Grabbing线程。
	///            回调采集（SetGrabbingCallback）与主动采集（调用GrabImage进行采集）用户只能选择其一，不可同时使用。
	MVD_API MVD_ReturnCode __stdcall GrabImage(IN const int nIndex, OUT MVD_GRAB_IMAGE **ppGrabImage);

	/// @brief     通知SDK释放主动采集资源。
	/// @attention 每次调用一次MVD_GrabImage并对图像处理之后，必须调用一次此函数，以通知SDK释放资源，否则会堵塞Grabbing线程。
	MVD_API MVD_ReturnCode __stdcall GrabImageRelease(IN const int nIndex);


	/// @brief     保存图像。
	MVD_API MVD_ReturnCode __stdcall SaveImage(IN const MVD_GRAB_IMAGE *pGrabImage, IN const MVD_SAVE_IMAGE_INFORMATION SaveImageInformation);

	/// @brief     设置图像是否垂直翻转。
	MVD_API MVD_ReturnCode __stdcall GetFlip(IN int nIndex, bool *pbFlip);
	/// @brief     获取图像是否垂直翻转。
	MVD_API MVD_ReturnCode __stdcall SetFlip(IN int nIndex, bool bFlip);


	/// @brief     设置图像是否水平镜像。
	MVD_API MVD_ReturnCode __stdcall SetMirror(IN int nIndex, bool bMirror);
	/// @brief     获取图像是否水平镜像。
	MVD_API MVD_ReturnCode __stdcall GetMirror(IN int nIndex, bool *pbMirror);


	/// -----------------------------------------------------------------------------
	///
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

	/// @brief     设置ROI垂直起始行。
	MVD_API MVD_ReturnCode __stdcall SetRoiRowStart(IN int nIndex, IN unsigned int uiValue);

	/// @brief     获取ROI垂直起始行。
	MVD_API MVD_ReturnCode __stdcall GetRoiRowStart(IN int nIndex, OUT unsigned int *puiValue);

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

	/// @brief     设置帧触发模式
	MVD_API MVD_ReturnCode __stdcall SetFrameTriggerMode(IN int nIndex, MVD_FRAME_TRIGGER_MODE FrameTriggerMode);

	/// @brief     获取当前帧触发模式
	MVD_API MVD_ReturnCode __stdcall GetFrameTriggerMode(IN int nIndex, MVD_FRAME_TRIGGER_MODE *pFrameTriggerMode);

	/// @brief     设置外部触发源
	/// @attention 只有在帧触发模式为FTM_EXTERNAL时才能生效    
	MVD_API MVD_ReturnCode __stdcall SetFrameTriggerExternalSource(IN int nIndex, MVD_FRAME_TRIGGER_EXTERNAL_SOURCE FrameTriggerExternalSource);

	/// @brief     获取当前选择的外部触发源
	MVD_API MVD_ReturnCode __stdcall GetFrameTriggerExternalSource(IN int nIndex, MVD_FRAME_TRIGGER_EXTERNAL_SOURCE *pFrameTriggerSource);

	/// @brief     设置外部触发源有效条件
	/// @attention 只有在帧触发模式为FTM_EXTERNAL时才能生效    
	MVD_API MVD_ReturnCode __stdcall SetFrameTriggerExternalActivation(IN int nIndex, MVD_FRAME_TRIGGER_EXTERNAL_ACTIVATION FrameTriggerExternalActivation);

	/// @brief     获取当前设置的外部触发源有效条件
	MVD_API MVD_ReturnCode __stdcall GetFrameTriggerExternalActivation(IN int nIndex, MVD_FRAME_TRIGGER_EXTERNAL_ACTIVATION *pFrameTriggerActivation);

	/// @brief     获取外部触发延时时间设置范围（微秒）
	MVD_API MVD_ReturnCode __stdcall GetFrameTriggerExternalDelayRange(IN int nIndex, float *pfMinUs, float *pfMaxUs, float *pfDefUs);
	
	/// @brief     设置外部触发延时时间（微秒）
	/// @attention 只有在帧触发模式为FTM_EXTERNAL时才能生效    
	MVD_API MVD_ReturnCode __stdcall SetFrameTriggerExternalDelay(IN int nIndex, float fDelayUs);

	/// @brief     获取外部触发延时时间（微秒）
	MVD_API MVD_ReturnCode __stdcall GetFrameTriggerExternalDelay(IN int nIndex, float *pfDelayUs);

	/// @brief     获取外部触发滤波时间设置范围（微秒）
	MVD_API MVD_ReturnCode __stdcall GetFrameTriggerExternalFilterRange(IN int nIndex, float *pfMinUs, float *pfMaxUs, float *pfDefUs);

	/// @brief     设置外部触发滤波时间（微秒）
	/// @attention 只有在帧触发模式为FTM_EXTERNAL时才能生效    
	MVD_API MVD_ReturnCode __stdcall SetFrameTriggerExternalFilter(IN int nIndex, float fFilterUs);

	/// @brief     获取外部触发滤波时间（微秒）
	MVD_API MVD_ReturnCode __stdcall GetFrameTriggerExternalFilter(IN int nIndex, float *pfFilterUs);

	/// @brief     获取固定帧率设置范围（帧每秒）
	MVD_API MVD_ReturnCode __stdcall GetFrameTriggerFixedRateRange(IN int nIndex, float *pfMin, float *pfMax, float *pfDef);

	/// @brief     设置固定帧率（帧每秒）
	/// @attention 只有在帧触发模式为FTM_FIXED_FRAME_RATE时才能生效    
	MVD_API MVD_ReturnCode __stdcall SetFrameTriggerFixedRate(IN int nIndex, float fFps);

	/// @brief     获取当前设置的固定帧率（帧每秒）
	MVD_API MVD_ReturnCode __stdcall GetFrameTriggerFixedRate(IN int nIndex, float *pfFps);

	/// @brief     执行软件触发
	/// @attention 之后在帧触发模式为FTM_SOFTWARE模式下才可调用（这个函数暂不需调用，只要设置软件触发模式，会在采集时自动触发）
	MVD_API MVD_ReturnCode __stdcall ExecuteSoftwareTrigger(IN int nIndex);


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

#ifdef __cplusplus
}
#endif

#endif

