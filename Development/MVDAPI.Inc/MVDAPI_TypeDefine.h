#ifndef __MVDAPI_TYPE_DEFINE_H__
#define __MVDAPI_TYPE_DEFINE_H__

/// -----------------------------------------------------------------------------
///
/// @file    MVDAPI_TypeDefine.h
/// @author  Mike.Guo
/// @version 0.1
/// @date    2020.08.06
/// @brief   MVDAPI应用开发接口数据类型定义头文件
///
/// -----------------------------------------------------------------------------


#include <tchar.h>

typedef int MVD_ReturnCode;         ///< MVDAPI函数返回码

#define MVD_MAX_DEVICE_NUM   32     ///< MVDAPI最多支持的设备数目

///-----------------------------------------------------------------------------
/// 语言枚举类型，GetLanguage，SetLanguage
///-----------------------------------------------------------------------------
enum MVD_LANGUAGE
{
	L_CHS = 0,    ///< 中文
	L_ENG = 1     ///< 英文
};

///-----------------------------------------------------------------------------
/// 设备接口枚举类型
///-----------------------------------------------------------------------------
enum MVD_DEVICE_INTERFACE_TYPE
{
	DIT_ALL  = 0x00000000,    ///< 所有支持的设备接口
	DIT_USB  = 0x00000001,    ///< 设备接口类型为USB2.0或USB3.0
	DIT_GIGE = 0x00000002     ///< 设备接口类型为千兆网
};

union MVD_VERSION
{
	struct
	{
		unsigned char ucMinor;
		unsigned char ucMajor;
	}sValue;

	unsigned short usVersion;
};

enum MVD_GIGE_DRIVER_TYPE
{
	GDT_SOCKET = 0,
	GDT_FILTER = 1
};
///-----------------------------------------------------------------------------
///  设备信息结构体，兼容不同的设备接口类型的设备
///-----------------------------------------------------------------------------
struct MVD_DEVICE_INFORMATION
{
	unsigned int    uiDeviceModel;            ///< 设备型号
	TCHAR           szModelName[64];          ///< 型号名称
	unsigned int    uiSerialNumber;           ///< 设备序列号
	MVD_VERSION     FirmwareVersion;          ///< 固件版本号
	MVD_VERSION     FpgaVersion;              ///< FPGA版本号
	MVD_VERSION     HardwareVersion;          ///< 硬件版本

	TCHAR           szUserDefinedName[32];    ///< 用户自定义名称++0.4
	int             nReserved0[32];           ///< Common Information

	MVD_DEVICE_INTERFACE_TYPE    DeviceInterfaceType;    ///< 设备的接口类型

	union
	{
		struct
		{
			MVD_GIGE_DRIVER_TYPE    DriverType;

			TCHAR         szAdapterFriendlyName[128];
			unsigned char ucAdapterMac[8];
			unsigned char ucAdapterIp[8];
			unsigned char ucAdapterSubnetMask[8];
			unsigned char ucAdapterDefaultGateWay[8];

			
			unsigned char ucDeviceMac[8];
			unsigned char ucDeviceIp[8];
			unsigned char ucDeviceSubnetMask[8];
			unsigned char ucDeviceDefaultGateWay[8];
		}GigE;

		struct
		{

		}Usb;

		int                          nReserved0[64];         ///< 保留信息，USB与GIGE区别信息
	}SpecialInfo;
};

//-----------------------------------------------------------------------------
//  设备信息列表结构体，由MVD_Initial返回时填写。
//-----------------------------------------------------------------------------
typedef struct _tag_MVD_DEVICE_INFORMATION_LIST
{
	unsigned int             uiDeviceNum;                                 ///< 查找到的设备数目
	MVD_DEVICE_INFORMATION   *pDeviceInformation[MVD_MAX_DEVICE_NUM];     ///< 相应的设备信息指针，这个指针指向SDK对应的地址，不可进行内容的修改
}MVD_DEVICE_INFORMATION_LIST, *PMVD_DEVICE_INFORMATION_LIST;

/// 读取模式(抽点模式)
enum MVD_ADDRESS_MODE
{
	AM_1 = 0,     ///< 正常读取
	AM_2 = 1,     ///< 2x2抽取1个像素
	AM_4 = 2,     ///< 4x4抽取1个像素
	AM_8 = 3,     ///< 8x8抽取1个像素
};

/// ROI(感兴趣区域)数据结构定义
typedef struct _tag_MVD_ROI_SIZE
{
	unsigned int     uiColSize;         ///< 视场列像元数目
	unsigned int     uiRowSize;         ///< 视场行像元数目
	MVD_ADDRESS_MODE ColAddressMode;    ///< 列像元提取模式（是在ColSize基础上进行提取)
	MVD_ADDRESS_MODE RowAddressMode;    ///< 行像元提取模式（是在RowSize基础上进行提取)

}MVD_ROI_SIZE, *PMVD_MVD_ROI_SIZE;

typedef struct _tag_MVD_ROI_OFFSET
{
	unsigned int     uiColStart;
	unsigned int     uiRowStart;
}MVD_ROI_START, *PMVD_ROI_START;

/// 用户预设组定义
enum MVD_USER_PRESETTING
{
	UP_0 = 0,     ///< 用户预设组0
	UP_1 = 1,     ///< 用户预设组1
	UP_2 = 2,     ///< 用户预设组2
	UP_3 = 3,     ///< 用户预设组3
	UP_INVALID = -1    ///< 无效预设组
};

/// 增益选择子
enum MVD_GAIN_SELECTOR
{
	GS_GLOBAL = 0,                  ///< 全局增益，对于彩色会同时调节红绿蓝增益
	GS_RED = 1,                     ///< 红增益
	GS_GREEN = 2,                   ///< 绿增益
	GS_BLUE = 3                     ///< 兰增益
};

/// 自动曝光模式
enum MVD_EXPOSURE_MODE
{
	EM_MANUAL = 0,          ///< 手动调节曝光
	EM_AUTO_ONCE = 1,       ///< 软件处理自动单次调节曝光，设置后即启动
	EM_AUTO_CONTINUOUS = 2, ///< 软件处理自动连续调节曝光，设置后即启动
};

/// 自动曝光回调中提示当前自动曝光处理状态
enum MVD_AUTO_EXPOSURE_STATUS
{
	AES_ONCE_SUCCESS = 0, 			///< 单次调节成功
	AES_ONCE_FAIL_MAX_COUNT, 		///< 单次调节失败，失败原因达到最大调节次数（这个调节次数是表示连续使用多少帧图像作为一次调节，默认20帧）
	AES_ONCE_FAIL_WAVE, 			///< 单次调节失败，失败原因调节上下振动
	AES_ONCE_FAIL_OVER_RANGE, 		///< 单次调节失败，失败原因曝光超出设置范围
	AES_DOING, 						///< 一次调节完成，曝光时间发生了变化，但还不确定成功或失败
	AES_CONTINUOUS_SUCCESS,			///< 连续调节成功，当前达到了目标值
	AES_CONTINUOUS_FAIL_WAVE, 		///< 连续调节失败，失败原因调节上下振动
	AES_CONTINUOUS_FAIL_OVER_RANGE 	///< 连续调节失败，失败原因曝光超出设置范围
};

/// 白平衡模式
/// 如果设备支持硬件白平衡，优先选择硬件白平衡(保证效率)
enum MVD_WHITE_BALANC_MODE
{
	WBM_DISABLE = 0,                  ///< 使白平衡无效
	WBM_SOFTWARE_PRESETTING = 1,      ///< 软件色温预设组
	WBM_SOFTWARE_AUTO_ONCE = 2,       ///< 软件处理单次自动调节
	WBM_SOFTWARE_AUTO_CONTINUOUS = 3, ///< 软件处理单次连续调节
	WBM_SOFTWARE_MANUAL = 4,          ///< 手动调节软件白平衡效正矩阵
	WBM_HARDWARE_PRESETTING = 5,      ///< 硬件色温预设组
	WBM_HARDWARE_AUTO_ONCE = 6,       ///< 硬件处理单次自动调节
	WBM_HARDWARE_AUTO_CONTINUOUS = 7, ///< 硬件处理连续自动调节
	WBM_HARDWARE_MANUAL = 8           ///< 手动设置硬件白平衡效正矩阵
};

/// 颜色效正模式枚举类型
/// 如果设备支持硬件颜色效正，优先选择硬件效正模式(保证效率)
enum MVD_COLOR_CORRECTION_MODE
{
	CCM_DISABLE = 0,                  ///< 颜色效正不使能
	CCM_SOFTWARE_PRESETTING = 1,      ///< 软件颜色效正预设值模式，参看SetColorCorrectionPresetting
	CCM_SOFTWARE_MANUAL = 2,          ///< 手动设置软件颜色效正系数矩阵模式，参看SetColorCorrectionMatrix
	CCM_HARDWARE_PRESETTING = 3,      ///< 硬件颜色效正预设值模式，参看SetColorCorrectionPresetting
	CCM_HARDWARE_MANUAL = 4           ///< 手动设置硬件颜色效正系数矩阵模式，参看SetColorCorrectionMatrix
};

/// 色温定义枚举类型
enum MVD_COLOR_TEMPERATURE
{
	CT_5000K = 0,                         ///< 色温5000K
	CT_6500K = 1,                         ///< 色温6500K
	CT_2800K = 2                          ///< 色温2800K
};

/// 像素格式枚举类型(小端字节序)
enum MVD_PIXEL_FORMAT
{
	PF_RAW8 = 0,    ///< 8bit原始
	PF_GRAY8,       ///< 8bit灰度（对于黑白相机，等同于PF_RAW8)
	PF_RGB24,       ///< 24bit，RGB排列，内存B在低地址
	PF_RGB32,       ///< 32bit，RGBA排列，内存B在低地址
	PF_BGR24,       ///< 24bit，BGR排列，内存R在低地址
	PF_BGR32,       ///< 32bit，BGRA排列，内存R在低地址
	PF_RAW16,       ///< 16bit原始(其中的有效位可通过GetAdcResolution函数获取)
	PF_GRAY16,      ///< 16bit灰度（对于黑白相机，等同于PF_RAW16)
	PF_RGB48,       ///< 48bit, RGB排列，内存B在低地址，R,G,B各占2字节，低8位在低地址
	PF_RGB64,       ///< 64bit, RGBA排列，内存B在低地址，R,G,B各占2字节，低8位在低地址
	PF_BGR48,       ///< 48bit, BGR排列，内存R在低地址，R,G,B各占2字节，低8位在低地址
	PF_BGR64,       ///< 64bit, BGRA排列，内存R在低地址，R,G,B各占2字节，低8位在低地址

};

/// 压缩8bit模式
enum MVD_ADC_COMPANDING_MODE
{
	ACM_EXTRACT = 0,     ///< 硬件截取位模式转换为8bit精度
	ACM_LUT = 1          ///< 硬件通过LUT查找表转换为8bit精度
};

/// 截取模式
enum MVD_EXTRACT_MODE
{
	EM_0_7 = 0,         ///< 截取0-7位
	EM_1_8 = 1,
	EM_2_9 = 2,
	EM_3_10 = 3,
	EM_4_11 = 4,        ///< 截取4-11位
};

enum MVD_FRAME_TRIGGER_MODE
{
	FTM_CONTINUOUS = 0,     ///< 自动连续触发
	FTM_EXTERNAL = 1,       ///< 通过外部输入信号触发
	FTM_SOFTWARE = 2,       ///< 通过软件命令触发
	FTM_FIXED = 3           ///< 固定帧率触发
};

enum MVD_FRAME_TRIGGER_EXTERNAL_SOURCE
{
	FTES_LINE0 = 0,
};

enum MVD_FRAME_TRIGGER_EXTERNAL_ACTIVATION
{
	FTEA_RISING_EDGE = 0,
	FTEA_FALING_EDGE = 1,
	FTEA_HIGH_LEVEL = 2,
	FTEA_LOW_LEVEL = 3,
};

#pragma pack(push, 1)

/// 采集图像的基本信息
struct MVD_IMAGE_BASE_INFO
{
	int nImageWidth;            ///< 图形宽度（像素）
	int nImageHeight;           ///< 图形高度（像素）
	int nImageBitCount;         ///< 位图深度 8/24/32
	int nImageBitsPerSample;    ///< 每个采样的比特数 8/16
	int nTotalBytes;            ///< 图像的总字节数=nImageWidth*nImageHeight*(nImageBitCount/8)*(nImageBitsPerSample/8)

	int nReserved[32];
};

/// 采集图像的扩展信息
struct MVD_IMAGE_EXTEND_INFO
{
	float                    fGain;                       ///< 增益，放大倍率
	float                    fExposureTimeUs;             ///< 曝光时间（uS）
	int                      nReserved0[16];

	unsigned __int64         ui64HostTimeStamp;           ///< 主机生成的时间戳，当前系统时钟的滴答计数，参考QueryPerformanceCounter
	unsigned __int64         ui64ElapseTimeMicrosecond;   ///< 主机计算获取这一帧的时间
	unsigned __int64         ui64DeviceTimeStamp;         ///< 设备时间戳，设备时钟滴答计数
	unsigned int             uiDeviceFrequency;           ///< 设备时间戳时钟频率(Hz), Fpga时钟频率，每秒钟有多少个时钟滴答计数

	unsigned int             uiTriggerCounter;            ///< 输入外触发信号计数，是否需要区分外触发、软件触发计数，是否区分上升沿，电平？
	unsigned int             uiFrameCounter;              ///< 传输帧计数
	unsigned int             uiFrameId;                   ///< 帧ID
	unsigned int             uiLostPacket;                ///< 丢包数量
	unsigned int             uiImageBytesRead;            ///< 实际读取的字节数

	int                      nReserved1[32];
};

/// 采集图像的信息及数据，是一段连续的内存地址空间，ucImageData数组的大小等于ImageBaseInfo的nTotalBytes值。
typedef struct
{
	MVD_IMAGE_BASE_INFO     ImageBaseInfo;     ///< 采集图像的基本信息。
	MVD_IMAGE_EXTEND_INFO   ImageExtendInfo;   ///< 采集图像的扩展信息。
	// unsigned char           ucImageData[1];    ///< 为图像的第一个数据，是一段由库内动态分配的，与ImageExtendInfo连续的一段内存地址，内存大小等于ImageBaseInfo的nTotalBytes值。
}MVD_GRAB_IMAGE_INFO;

#pragma pack(pop)

///-----------------------------------------------------------------------------
/// 保存图象格式的枚举类型
///-----------------------------------------------------------------------------
typedef enum
{
	SIF_UNKNOWN = 0,  ///< 根据文件扩展名保存
	SIF_BMP = 1,      ///< 保存为BMP格式
	SIF_JPG = 2,      ///< 保存为JPG格式
	SIF_PNG = 3,      ///< 保存为PNG格式
	SIF_TIF = 4,      ///< 保存为TIF格式
}MVD_SAVE_IMAGE_FORMAT;

/// 保存图像的相关信息
typedef struct _tag_MVD_SAVE_IMAGE_INFORMATION
{
	TCHAR                    *pszImageName;               ///< 保存文件的完整路径：如c:\MVD\2020-02-23.bmp
	MVD_SAVE_IMAGE_FORMAT    SaveImageFormat;            ///< 参考enum MVD_IAMGE_TYPE定义
	unsigned int             nJpgQuality;                ///< 只有enImageFormat=MVD_IMAGE_FORMAT_JPG，此数据有效
}MVD_SAVE_IMAGE_INFORMATION;



/// 白平衡回调函数指针定义
typedef void(__stdcall *PMVD_WHITE_BALANCE_CALLBACK)(OUT int nDeviceIndex, OUT float fMatrixR, OUT float fMatrixG, OUT float fMatrixB, OUT void *lpContext);
/// 自动曝光回调函数指针定义
typedef void(__stdcall *PMVD_AUTO_EXPOSURE_CALLBACK)(OUT int nDeviceIndex, OUT MVD_AUTO_EXPOSURE_STATUS Status, OUT float fExpsoureTimeUs, OUT void *lpContext);
/// 采集图像回调函数指针定义
typedef void(__stdcall *PMVD_GRABBING_CALLBACK)(OUT int nDeviceIndex, OUT MVD_GRAB_IMAGE_INFO* pGrabImageInfo, OUT unsigned char *pGrabImageData,  OUT void* lpContext);


#endif