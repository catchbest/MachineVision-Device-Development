#ifndef __MVDAPI_STRING_H__
#define __MVDAPI_STRING_H__

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

	/// @brief     获取API函数返回值对应的字符串描述信息。
	MVD_API PTCHAR __stdcall GetReturnCodeString(IN int nReturnCode);

	MVD_API PTCHAR __stdcall GetLanguageString(IN MVD_LANGUAGE Language);

	/// -----------------------------------------------------------------------------
	///
	/// @brief     这是一个辅助函数，方便用户获取MVD_ADDRESS_MODE枚举值对应的字符串，这个用户也可以不调用，自行设置对应的字符串信息。
	/// @attention 无。
	/// @param     [IN]AddressMode 参考MVD_ADDRESS_MODE枚举类型
	/// @return    返回对应的字符串指针。
	///
	/// -----------------------------------------------------------------------------
	MVD_API PTCHAR __stdcall GetAddressModeString(MVD_ADDRESS_MODE AddressMode);


	MVD_API PTCHAR __stdcall GetGainSelectorString(MVD_GAIN_SELECTOR GainSelector);

	MVD_API PTCHAR __stdcall GetExposureModeString(MVD_EXPOSURE_MODE ExposureMode);

	MVD_API PTCHAR __stdcall GetAutoExposureStatusString(MVD_AUTO_EXPOSURE_STATUS AutoExposureStatus);

	MVD_API PTCHAR __stdcall GetWhiteBalanceModeString(MVD_WHITE_BALANC_MODE WhiteBalanceMode);

	MVD_API PTCHAR __stdcall GetColorTemperatureString(MVD_COLOR_TEMPERATURE ColorTemperature);

	MVD_API PTCHAR __stdcall GetColorCorrectionModeString(MVD_COLOR_CORRECTION_MODE ColorCorrectionMode);

	MVD_API PTCHAR __stdcall GetAdcCompandingModeString(MVD_ADC_COMPANDING_MODE AdcCompandingMode);

	MVD_API PTCHAR __stdcall GetAdcCompandingExtractModeString(MVD_EXTRACT_MODE ExtractMode);

	MVD_API PTCHAR __stdcall GetFrameTriggerModeString(MVD_FRAME_TRIGGER_MODE FrameTriggerMode);

	MVD_API PTCHAR __stdcall GetFrameTriggerExternalSourceString(MVD_FRAME_TRIGGER_EXTERNAL_SOURCE FrameTriggerExternalSource);

	MVD_API PTCHAR __stdcall GetFrameTriggerExternalActivationString(MVD_FRAME_TRIGGER_EXTERNAL_ACTIVATION FrameTriggerExternalActivation);

	/// -----------------------------------------------------------------------------
	///
	/// @brief     这是一个辅助函数，方便用户获取MVD_USER_PRESETTING枚举值对应的字符串，这个用户也可以不调用，自行设置对应的字符串信息。
	/// @attention 无。
	/// @param     [IN]UserPresetting 参考MVD_USER_PRESETTING枚举类型
	/// @return    返回对应的字符串指针。
	///
	/// -----------------------------------------------------------------------------
	MVD_API PTCHAR __stdcall GetUserPresettingString(IN MVD_USER_PRESETTING UserPresetting);


#ifdef __cplusplus
}
#endif

#endif

