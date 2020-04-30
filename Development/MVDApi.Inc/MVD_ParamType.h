//-----------------------------------------------------------------------------
// 版权：凯视佳

// 文件名称：MVD_ParamType.h
// 简要描述：SDK函数接口参数的数据类型定义

// 创建日期：2020-2-24
// 当前版本：V1.0
// 作者：Mike
// 说明：后缀_A是非UNICODE的结构体定义，_W是宽字节字符串用于UNICODE编程


// 修改日期： 
// 当前版本：
// 作者：
// 说明：
//-----------------------------------------------------------------------------

#ifndef __MVD_PARAM_TYPE_H__
#define __MVD_PARAM_TYPE_H__




//跨平台定义
//Cross Platform Definition
#ifdef WIN32
typedef __int64          int64_t;
typedef unsigned __int64 uint64_t;
#else
#include <stdint.h>
#endif

// 最多支持的设备数目
#define MVD_MAX_DEVICE_NUM          256    
// 信息字符串的Buffer字节大小
#define MVD_BUFFER_SIZE             64
// 离散型数据最多有多少个离散值
#define MVD_MAX_VALUE_NUM           64
// 支持使用字符串的最大字符数目，库里返回的字符串的字符个数不会超过此数值。
#define MVD_MAX_STRING_CHARACTERS   512

//-----------------------------------------------------------------------------
// 设备接口枚举类型
//-----------------------------------------------------------------------------
typedef enum
{
	MVD_DEVICE_INTERFACE_TYPE_UNKNOWN = 0x00000000,    // 设备接口类型不能识别
	MVD_DEVICE_INTERFACE_TYPE_USB     = 0x00000001,    // 设备接口类型为USB2.0或USB3.0
	MVD_DEVICE_INTERFACE_TYPE_GIGE    = 0x00000002     // 设备接口类型为千兆网
}MVD_DEVICE_INTERFACE_TYPE;

//-----------------------------------------------------------------------------
// 保存图象格式的枚举类型
//-----------------------------------------------------------------------------
typedef enum
{
	MVD_IMAGE_FORMAT_UNKNOWN = 0,  // 根据文件扩展名保存
	MVD_IMAGE_FORMAT_BMP = 1,      // 保存为BMP格式
	MVD_IMAGE_FORMAT_JPG = 2,      // 保存为JPG格式
	MVD_IMAGE_FORMAT_PNG = 3,      // 保存为PNG格式
	MVD_IMAGE_FORMAT_TIF = 4,      // 保存为TIF格式
}MVD_IMAGE_FORMAT;

//-----------------------------------------------------------------------------
// 查询信息枚举类型，在调用MVD_QueryInfo函数时，作为第二个参数输入
//-----------------------------------------------------------------------------
typedef enum
{
	MVD_QUERY_INFO_TYPE_SDK_VERSION = 0,            // 查询SDK版本号信息，可在任何时刻查询，MVD_QueryInfo函数第一个参数被忽略
	MVD_QUERY_INFO_TYPE_PARAM_NAMES = 1,            // MVD_Initial调用成功之后即查询，返回所支持的参数名称列表，这些参数可以作为MVD_GetParam和MVD_SetParam的参数pchParamName进行传递。
	MVD_QUERY_INFO_TYPE_COMMAND_NAMES = 2,          // MVD_Initial调用成功之后即查询，返回所支持的命令名称列表，这些命令名称可以通过MVD_ExecuteCommand函数发送
	MVD_QUERY_INFO_TYPE_GRAB_FPS = 3,               // MVD_Initial调用成功之后即查询，返回当前的采集帧率
	MVD_QUERY_INFO_TYPE_DISPLAY_FPS = 4,            // MVD_Initial调用成功之后即查询，返回当前显示帧率
	MVD_QUERY_INFO_TYPE_IS_OPEN,                    // MVD_Initial调用成功之后即查询，返回设备是否打开
	MVD_QUERY_INFO_TYPE_IS_GRABBING_START,          // MVD_Initial调用成功之后即查询，返回是否采集已经开始
	MVD_QUERY_INFO_TYPE_IS_CALLBACK_GRAB,           // MVD_Initial调用成功之后即查询，返回是否回调采集已经开始
}MVD_QUERY_INFO_TYPE;

// 这个是在查询MVD_QUERY_INFO_TYPE_DRIVER_TYPE时可能返回的值
typedef enum
{
	MVD_DRIVER_TYPE_UNKNOWN = 0,
	MVD_DRIVER_TYPE_FILTER = 1,                     // 从Filter驱动读取
	MVD_DRIVER_TYPE_SOCKET = 0                      // 从Socket读取
};

//-----------------------------------------------------------------------------
// 数值的数据类型，为了使一个接口可以支持多种数据类型的获取和设置而定义的枚举类型
// 当数值类型为MVD_VALUE_TYPE_INT时，需要引用MVD_VALUE中的nValue成员
// 当数值类型为MVD_VALUE_TYPE_INT64时，需要引用MVD_VALUE中的nValue64成员
// 当数值类型为MVD_VALUE_TYPE_FLOAT时，需要引用MVD_VALUE中的fValue成员
// 当数值类型为MVD_VALUE_TYPE_STRING时，需要引用MVD_VALUE中的pszValue成员
//-----------------------------------------------------------------------------
typedef enum
{
	MVD_VALUE_TYPE_UNKNOWN = 0,
	MVD_VALUE_TYPE_INT = 1,              // 32位整型数据类型
	MVD_VALUE_TYPE_INT64 = 2,            // 32位整型数据类型
	MVD_VALUE_TYPE_FLOAT = 3,             // 浮点数据类型
	MVD_VALUE_TYPE_STRING = 4,            // 字符串数据类型
}MVD_VALUE_TYPE;

typedef enum
{
	MVD_ACCESS_MODE_RW = 0,                // 参数可读写
	MVD_ACCESS_MODE_RO = 1                 // 参数只读
}MVD_ACCESS_MODE;

#pragma pack(1)

//-----------------------------------------------------------------------------
// 设备接口类型为MVD_DEVICE_INTERFACE_TYPE_USB的设备信息结构体
//-----------------------------------------------------------------------------
typedef struct _tag_MVD_DEVICE_INFO_USB
{
	unsigned short          usVendorId;                                // ch:供应商ID号 | en:Vendor ID Number
	unsigned short          usProductId;                               // ch:产品ID号 | en:Device ID Number
	unsigned int            nDeviceNumber;                             // ch:设备序列号  | en:Device Serial Number
	char                    chDeviceGUID[MVD_BUFFER_SIZE];             // ch:设备GUID号 | en:Device GUID Number
	char                    chVendorName[MVD_BUFFER_SIZE];             // ch:供应商名字 | en:Vendor Name
	char                    chModelName[MVD_BUFFER_SIZE];              // ch:型号名字 | en:Model Name
	char                    chFamilyName[MVD_BUFFER_SIZE];             // ch:家族名字 | en:Family Name
	char                    szDeviceVersion[MVD_BUFFER_SIZE];          // ch:设备版本号 | en:Device Version
	char                    chManufacturerName[MVD_BUFFER_SIZE];       // ch:制造商名字 | en:Manufacturer Name
	char                    chSerialNumber[MVD_BUFFER_SIZE];           // ch:序列号 | en:Serial Number
	char                    chUserDefinedName[MVD_BUFFER_SIZE];        // ch:用户自定义名字 | en:User Defined Name
	unsigned int            nbcdUSB;                                   // ch:支持的USB协议 | en:Support USB Protocol
	unsigned int            nReserved[3];                              // ch:保留字节 | en:Reserved bytes

	unsigned short          usFirmwareVersion;
	unsigned short          usFpgaVersion;
	unsigned int            uiDeviceMode;

	unsigned int            usSerials;

	// USB主控制器/Hub
}MVD_DEVICE_INFO_USB, *PMVD_DEVICE_INFO_USB;

//-----------------------------------------------------------------------------
// 设备接口类型为MVD_DEVICE_INTERFACE_TYPE_GIGE的设备信息结构体，无特殊说明，为主机字节序
//-----------------------------------------------------------------------------
typedef struct _tag_MVD_DEVICE_INFO_GIGE_A
{
	unsigned int        uiDeviceMode;
	unsigned char       ucDeviceMac[8];
	unsigned short      usDeviceMacAddressH;
	unsigned int        uiDeviceMacAddressL;
	unsigned int        uiDeviceIpConfigOptions;
	unsigned int        uiDeviceIpConfigCurrent;       // IP configuration:bit31-static bit30-dhcp bit29-lla      
	unsigned int        uiDeviceIpCurrent;             // 比如IP地址为192.168.111.1，则uiDeviceIpCurrent=0x016FA8C0        
	unsigned int        uiDeviceSubnetMaskCurrent;     // 比如IP地址为255.255.255.0，则uiDeviceSubnetMaskCurrent=0x00ffffff      
	unsigned int        uiDeviceGatewayDefault;        // 比如IP地址为192.168.111.254，则uiDeviceGatewayDefault=0xfe6fa8c0
	char                szDeviceManufacturerName[MVD_BUFFER_SIZE];
	char                szDeviceModelName[MVD_BUFFER_SIZE];
	char                szDeviceVersion[MVD_BUFFER_SIZE];
	char                szDeviceManufacturerSpecificInfo[MVD_BUFFER_SIZE];
	char                szDeviceSerialNumber[MVD_BUFFER_SIZE];
	char                szDeviceUserDefinedName[MVD_BUFFER_SIZE];

	// 所关联网卡信息
	unsigned char       ucAdapterMac[8];
	unsigned long       ulAdapterIp;
	unsigned long       ulAdapterSubnetMask;
	char                szAdapterFriendlyName[MVD_MAX_STRING_CHARACTERS];
	char                szAdapterDescription[MVD_MAX_STRING_CHARACTERS];

	// 下面的后期删除
	unsigned char       ucAdapterIp[6];
	unsigned char       ucAdapterDns[6];

}MVD_DEVICE_INFO_GIGE_A, *PMVD_DEVICE_INFO_GIGE_A;

typedef struct _tag_MVD_DEVICE_INFO_GIGE_W
{
	unsigned int        uiDeviceMode;
	unsigned char       ucDeviceMac[8];                // ucDeviceMac[0]-ucDeviceMac[1]-ucDeviceMac[2]-ucDeviceMac[3]-ucDeviceMac[4]-ucDeviceMac[5]
	unsigned short      usDeviceMacAddressH;
	unsigned int        uiDeviceMacAddressL;
	unsigned int        uiDeviceIpConfigOptions;
	unsigned int        uiDeviceIpConfigCurrent;       //IP configuration:bit31-static bit30-dhcp bit29-lla      
	unsigned int        uiDeviceIpCurrent;             //比如IP地址为192.168.111.1，则uiDeviceIpCurrent=0x016FA8C0        
	unsigned int        uiDeviceSubnetMaskCurrent;     //比如IP地址为255.255.255.0，则uiDeviceSubnetMaskCurrent=0x00ffffff      
	unsigned int        uiDeviceGatewayDefault;        //比如IP地址为192.168.111.254，则uiDeviceGatewayDefault=0xfe6fa8c0
	wchar_t             szDeviceManufacturerName[MVD_BUFFER_SIZE];
	wchar_t             szDeviceModelName[MVD_BUFFER_SIZE];
	wchar_t             szDeviceVersion[MVD_BUFFER_SIZE];
	wchar_t             szDeviceManufacturerSpecificInfo[MVD_BUFFER_SIZE];
	wchar_t             szDeviceSerialNumber[MVD_BUFFER_SIZE];
	wchar_t             szDeviceUserDefinedName[MVD_BUFFER_SIZE];

	// 所关联网卡信息
	unsigned char       ucAdapterMac[8];
	unsigned long       ulAdapterIp;
	unsigned long       ulAdapterSubnetMask;
	wchar_t             szAdapterFriendlyName[MVD_MAX_STRING_CHARACTERS];
	wchar_t             szAdapterDescription[MVD_MAX_STRING_CHARACTERS];

	// 下面的后期删除
	unsigned char       ucAdapterIp[6];
	unsigned char       ucAdapterDns[6];

}MVD_DEVICE_INFO_GIGE_W, *PMVD_DEVICE_INFO_GIGE_W;

//-----------------------------------------------------------------------------
// 设备信息结构体，兼容不同的设备接口类型的设备
//-----------------------------------------------------------------------------
typedef struct _tag_MVD_DEVICE_INFO_A
{
	MVD_DEVICE_INTERFACE_TYPE    DeviceInterfaceType;    // 设备的接口类型

	union
	{
		MVD_DEVICE_INFO_USB    stDeviceInfoUsb;            // DeviceInterfaceType为MVD_DEVICE_INTERFACE_TYPE_USB时的设备信息
		MVD_DEVICE_INFO_GIGE_A stDeviceInfoGige;           // DeviceInterfaceType为MVD_DEVICE_INTERFACE_TYPE_GIGE时的设备信息
	}Info;
}MVD_DEVICE_INFO_A, *PMVD_DEVICE_INFO_A;

typedef struct _tag_MVD_DEVICE_INFO_W
{
	MVD_DEVICE_INTERFACE_TYPE    DeviceInterfaceType;    // 设备的接口类型

	union
	{
		MVD_DEVICE_INFO_USB    stDeviceInfoUsb;            // DeviceInterfaceType为MVD_DEVICE_INTERFACE_TYPE_USB时的设备信息
		MVD_DEVICE_INFO_GIGE_W stDeviceInfoGige;           // DeviceInterfaceType为MVD_DEVICE_INTERFACE_TYPE_GIGE时的设备信息
	}Info;
}MVD_DEVICE_INFO_W, *PMVD_DEVICE_INFO_W;


//-----------------------------------------------------------------------------
// 设备信息列表结构体，由MVD_Initial返回时填写。
//-----------------------------------------------------------------------------
typedef struct _tag_MVD_DEVICE_INFO_LIST_A
{
	unsigned int        uiDeviceNum;                         // 查找到的设备数目
	PMVD_DEVICE_INFO_A  pDeviceInfo[MVD_MAX_DEVICE_NUM];     // 相应的设备信息列表
}MVD_DEVICE_INFO_LIST_A;

typedef struct _tag_MVD_DEVICE_INFO_LIST_W
{
	unsigned int        uiDeviceNum;                         // 查找到的设备数目
	PMVD_DEVICE_INFO_W  pDeviceInfo[MVD_MAX_DEVICE_NUM];     // 相应的设备信息列表
}MVD_DEVICE_INFO_LIST_W;

//-----------------------------------------------------------------------------
// 实际的数值，为了使一个接口可以支持多种数据类型的获取和设置而定义的联合体类型
// 需要根据MVD_VALUE_TYPE的类型进行应用的引用。
// 当数值类型为MVD_VALUE_TYPE_INT时，需要引用MVD_VALUE中的nValue成员
// 当数值类型为MVD_VALUE_TYPE_INT64时，需要引用MVD_VALUE中的nValue64成员
// 当数值类型为MVD_VALUE_TYPE_FLOAT时，需要引用MVD_VALUE中的fValue成员
// 当数值类型为MVD_VALUE_TYPE_STRING时，需要引用MVD_VALUE中的pszValue成员
//-----------------------------------------------------------------------------
typedef union _tag_MVD_VALUE_A
{
	int     nValue;
	__int64 n64Value;
	float   fValue;
	char   *pszValue;
}MVD_VALUE_A;

typedef union _tag_MVD_VALUE_W
{
	int     nValue;
	__int64 n64Value;
	float   fValue;
	wchar_t *pszValue;
}MVD_VALUE_W;

//-----------------------------------------------------------------------------
// 接收返回的查询信息结果，这个结构体由MVD_QueryInfo函数所使用
// MVD_VALUE_TYPE      enInfoType                     信息值的类型，需要根据此类型，引用相应的unValues中的成员
// int                 nValueNum                      信息值的有效值个数，也就是unValues数组中有效的元素
// MVD_VALUE_A         unValues[MVD_MAX_VALUE_NUM]    信息实际值，根据enInfoType的实际类型，使用相应的成员
//-----------------------------------------------------------------------------
typedef struct
{
	MVD_VALUE_TYPE      enInfoType;                     // 信息值的类型
	int                 nValueNum;                      // 信息值得有效值个数
	MVD_VALUE_A         unValues[MVD_MAX_VALUE_NUM];    // 信息实际值，根据enInfoType的实际类型，使用相应的成员
}MVD_QUERY_INFO_A;

typedef struct
{
	MVD_VALUE_TYPE      enInfoType;                     // 信息值的类型
	int                 nValueNum;                      // 信息值得有效值个数
	MVD_VALUE_W         unValues[MVD_MAX_VALUE_NUM];    // 信息实际值，根据enInfoType的实际类型，使用相应的成员
}MVD_QUERY_INFO_W;

//-----------------------------------------------------------------------------
// 接收返回的参数信息，这个结构体由MVD_GetParam函数所使用
// 获取参数信息，包括最大值、最小值、默认值、步长、可设置的连续范围或离散值信息
// MVD_VALUE_TYPE      enParamType     参数值的数据类型，这个类型决定MVD_VALUE中需要引用的成员
// int                 nValueNum;                  参数可以设置的数值数目，当=0时，表示数组为连续型，需要查看[unValueMin, unValueMax]确定参数设置范围，不得引用unValues数组；当=1时，表示只能有一个值，查看unValues[0]；当>1时，表示数值为离散的，需要查看unValues数组
// MVD_VALUE_A         unValues[MVD_MAX_VALUE_NUM];可以设置的数据，当nValueNum>=1时，可以进行引用此数组确定可以设置的值。
// MVD_VALUE_A         unValueDef;                 参数的默认值(针对所有参数值的数据类型都有效）
// MVD_VALUE_A         unValueCur;                 参数的当前值(针对所有参数值的数据类型都有效）
// MVD_VALUE_A         unValueMin;                 参数的可设置的最小值（只对参数值的数据类型为MVD_VALUE_TYPE_INT，MVD_VALUE_TYPE_INT64，MVD_VALUE_TYPE_FLOAT，并且nValueNum=0有效）
// MVD_VALUE_A         unValueMax;                 参数的可设置的最大值（只对参数值的数据类型为MVD_VALUE_TYPE_INT，MVD_VALUE_TYPE_INT64，MVD_VALUE_TYPE_FLOAT，并且nValueNum=0有效）
// MVD_VALUE_A         unValueInc;                 参数的设置步长（只对参数值的数据类型为MVD_VALUE_TYPE_INT，MVD_VALUE_TYPE_INT64，MVD_VALUE_TYPE_FLOAT有效）
// char               *pszParamDesc;               参数的描述(针对所有参数值的数据类型都有效）
//-----------------------------------------------------------------------------
typedef struct _tag_MVD_GET_PARAME_VALUE_A
{
	MVD_VALUE_TYPE      enParamType;                // 参数值的数据类型，这个类型决定MVD_VALUE中需要引用的成员
	MVD_ACCESS_MODE     enAccessMode;               // 参数访问模式
	int                 nValueNum;                  // 参数可以设置的数值数目，当=0时，表示数组为连续型，需要查看[unValueMin, unValueMax]确定参数设置范围，不得引用unValues数组；当=1时，表示只能有一个值，查看unValues[0]；当>1时，表示数值为离散的，需要查看unValues数组
	MVD_VALUE_A         unValues[MVD_MAX_VALUE_NUM];// 可以设置的数据，当nValueNum>=1时，可以进行引用此数组确定可以设置的值。
	MVD_VALUE_A         unValueDef;                 // 参数的默认值(针对所有参数值的数据类型都有效）
	MVD_VALUE_A         unValueCur;                 // 参数的当前值(针对所有参数值的数据类型都有效）
	MVD_VALUE_A         unValueMin;                 // 参数的可设置的最小值（只对参数值的数据类型为MVD_VALUE_TYPE_INT，MVD_VALUE_TYPE_INT64，MVD_VALUE_TYPE_FLOAT，并且nValueNum=0有效）
	MVD_VALUE_A         unValueMax;                 // 参数的可设置的最大值（只对参数值的数据类型为MVD_VALUE_TYPE_INT，MVD_VALUE_TYPE_INT64，MVD_VALUE_TYPE_FLOAT，并且nValueNum=0有效）
	MVD_VALUE_A         unValueInc;                 // 参数的设置步长（只对参数值的数据类型为MVD_VALUE_TYPE_INT，MVD_VALUE_TYPE_INT64，MVD_VALUE_TYPE_FLOAT有效）
	char               *pszParamDesc;               // 参数的描述(针对所有参数值的数据类型都有效）
}MVD_GET_PARAME_VALUE_A;

typedef struct _tag_MVD_GET_PARAME_VALUE_W
{
	MVD_VALUE_TYPE      enParamType;                // 参数值的数据类型，这个类型决定MVD_VALUE中需要引用的成员
	MVD_ACCESS_MODE     enAccessMode;               // 参数访问模式
	int                 nValueNum;                  // 参数可以设置的数值数目，当=0时，表示数组为连续型，需要查看[unValueMin, unValueMax]确定参数设置范围，不得引用unValues数组；当=1时，表示只能有一个值，查看unValues[0]；当>1时，表示数值为离散的，需要查看unValues数组
	MVD_VALUE_W         unValues[MVD_MAX_VALUE_NUM];// 可以设置的数据，当nValueNum>=1时，可以进行引用此数组确定可以设置的值。
	MVD_VALUE_W         unValueDef;                 // 参数的默认值(针对所有参数值的数据类型都有效）
	MVD_VALUE_W         unValueCur;                 // 参数的当前值(针对所有参数值的数据类型都有效）
	MVD_VALUE_W         unValueMin;                 // 参数的可设置的最小值（只对参数值的数据类型为MVD_VALUE_TYPE_INT，MVD_VALUE_TYPE_INT64，MVD_VALUE_TYPE_FLOAT，并且nValueNum=0有效）
	MVD_VALUE_W         unValueMax;                 // 参数的可设置的最大值（只对参数值的数据类型为MVD_VALUE_TYPE_INT，MVD_VALUE_TYPE_INT64，MVD_VALUE_TYPE_FLOAT，并且nValueNum=0有效）
	MVD_VALUE_W         unValueInc;                 // 参数的设置步长（只对参数值的数据类型为MVD_VALUE_TYPE_INT，MVD_VALUE_TYPE_INT64，MVD_VALUE_TYPE_FLOAT有效）
	wchar_t            *pszParamDesc;               // 参数的描述(针对所有参数值的数据类型都有效）
}MVD_GET_PARAME_VALUE_W;

//-----------------------------------------------------------------------------
// 需要设置的参数信息，这个结构体由MVD_SetParam函数所使用
//-----------------------------------------------------------------------------
typedef struct _tag_MVD_SET_PARAME_VALUE_A
{
	MVD_VALUE_TYPE      enParamType;                // 参数值的数据类型，这个参数值类型需要通过MVD_GetParam函数来获取，必须要一致
	MVD_VALUE_A         unValue;                    // 参数需要设置的值，需要根据enParamType的实际类型，来赋值相应的成员
}MVD_SET_PARAME_VALUE_A;

typedef struct _tag_MVD_SET_PARAME_VALUE_W
{
	MVD_VALUE_TYPE      enParamType;                // 参数值的数据类型，这个参数值类型需要通过MVD_GetParam函数来获取，必须要一致
	MVD_VALUE_W         unValue;                    // 参数需要设置的值，需要根据enParamType的实际类型，来赋值相应的成员
}MVD_SET_PARAME_VALUE_W;

//-----------------------------------------------------------------------------
// 设置显示相关的参数信息，这个结构体由MVD_SetDisplayPosition，MVD_GetDisplayPosition函数所使用
//-----------------------------------------------------------------------------
typedef struct
{
	void *            hDisplayWnd;                 // 显示图像的窗口句柄
	int               nX;                          // 显示在窗口的位置x：相对窗口原点的X方向偏移，可参考StretchDIBits第二个参数
	int               nY;                          // 显示在窗口的位置y：相对窗口原点的Y方向偏移，可参考StretchDIBits第三个参数
	int               nWidth;                      // 显示在窗口上的宽度，如果大于图像像素宽度，则水平方向放大显示，小于则水平方向缩小显示，可参考StretchDIBits第四个参数
	int               nHeight;                     // 显示在窗口上的高度，如果大于图像像素高度，则垂直方向放大显示，小于则垂直方向缩小显示，可参考StretchDIBits第五个参数
}MVD_DISPLAY_POSITION_INFO;


//-----------------------------------------------------------------------------
// 这个结构定义了一帧数据输出时的相关信息
//-----------------------------------------------------------------------------
typedef struct
{
	unsigned int             uiWidth;                     // 根据软件的记录填写
	unsigned int             uiHeight;                    // 根据软件的记录填写
	enum MVD_PIXEL_FORMAT    enPixelFormat;               // 根据软件的记录填写像素的格式，参考"MVD_PixelFormat.h"
	unsigned int             uiTotalBytes;                // 根据软件的记录填写，需要读取的图像字节数，总共有多少个字节的数据

	unsigned __int64         ui64HostTimeStamp;           // 主机生成的时间戳，当前系统时钟的滴答计数，参考QueryPerformanceCounter
	unsigned __int64         ui64ElapseTimeMicrosecond;   // 主机计算获取这一帧的时间

	float                    fGain;
	float                    fExposureTime;

	unsigned int             uiRoiOffsetX;
	unsigned int             uiRoiOffsetY;
	unsigned int             uiRoiWidth;
	unsigned int             uiRoiHeight;

	unsigned int             uiTriggerIndex;              // 触发计数，是否需要区分外触发、软件触发计数？

	// 设备水印时标
	unsigned __int64         ui64FpgaTimeStamp;           // Fpga硬件时钟滴答计数

	unsigned int             uiFpgaFrequency;             // Fpga时钟周期，每秒钟有多少个时钟

	unsigned int             uiFrameId;                   // 这个是根据实际的GVSP头填充，帧号 
	unsigned int             uiLostPacket;                // 本帧丢包数
	unsigned  int            uiImageBytesRead;            // 实际读取的字节数

	unsigned __int64         ui64DeviceTimeStamp;         // 这个是根据实际的GVSPLEADER数据包填充，设备生成的时间戳
	unsigned int             uiImageSizeX;                // 这个是根据实际的GVSP头填充，对用户层不可见
	unsigned int             uiImageSizeY;                // 这个是根据实际的GVSP头填充，对用户层不可见
	enum MVD_PIXEL_FORMAT    enImagePixelFormat;          // 这个是根据实际的GVSP头填充，对用户层不可见

	unsigned int             uiPackageSize;               // 网络包的字节数，GVSP每次传输的包的大小（包括IP_HEADER,UDP_HEADER和数据)
	unsigned long            iaSrc;                       // 源IP地址，对用户层不可见
	unsigned long            iaDst;                       // 目的IP地址，对用户层不可见
	unsigned char            ucMacDst[6];                 // 目的Mac地址（接收端，网卡）
	unsigned char            ucMacSrc[6];                 // 源Mac地址（发送端，设备）

	unsigned short           usPortSrc;                   // 源端口，对用户层不可见
	unsigned short           usPortDst;                   // 目的端口，对用户层不可见

	unsigned int             uiReserved[64];
}MVD_FRAME_OUT_INFO;

//-----------------------------------------------------------------------------
// MVD_FRAME_OUT这个结构体用于采集一帧结束后返回给用户，用于MVD_GrabImage、MVD_SaveImage已经回调的第一个参数
//-----------------------------------------------------------------------------
typedef struct 
{
	MVD_FRAME_OUT_INFO    stFrameOutInfo;    // 为图像的详细信息
	unsigned char         ucFrameData[1];    // 为图像数据的第一个数据地址
}MVD_FRAME_OUT;

// 图像回调函数指针
typedef void(__stdcall *MVD_IMAGE_CALLBACK)(MVD_FRAME_OUT* pFrameOut, void* pUser);


// ch:保存图片参数 | en:Save image type
typedef struct _tag_MVD_SAVE_IMAGE_PARAM_A
{
	char                    *pszImageName;               // 保存文件的完整路径：如c:\MVD\2020-02-23.bmp
	MVD_IMAGE_FORMAT         enImageFormat;              // 参考enum MVD_IAMGE_TYPE定义
	unsigned int             nJpgQuality;                // 只有enImageFormat=MVD_IMAGE_FORMAT_JPG，此数据有效
}MVD_SAVE_IMAGE_PARAM_A;

typedef struct _tag_MVD_SAVE_IMAGE_PARAM_W
{
	wchar_t                 *pszImageName;              // 保存文件的完整路径：如c:\MVD\2020-02-23.bmp
	MVD_IMAGE_FORMAT         enImageFormat;              // 参考enum MVD_IAMGE_TYPE定义
	unsigned int             nJpgQuality;                // 只有enImageFormat=MVD_IMAGE_FORMAT_JPG，此数据有效
}MVD_SAVE_IMAGE_PARAM_W;

#pragma pack()


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ch:采集模式 | en:Acquisition mode
typedef enum _tag_MVD_ACQUISITION_MODE_
{
	MVD_ACQUISITION_MODE_SINGLE_FRAME = 0,              // ch:单帧模式 | en:Single Mode
	MVD_ACQUISITION_MODE_MUTLI_FRAME  = 1,              // ch:多帧模式 | en:Multi Mode
	MVD_ACQUISITION_MODE_CONTINUOUS   = 2,              // ch:持续采集模式 | en:Continuous Mode
}MVD_ACQUISITION_MODE;

typedef enum _tag_MVD_TRIGGER_MODE_
{
	MVD_TRIGGER_MODE_OFF = 0,                        // ch:关闭 | en:Off
	MVD_TRIGGER_MODE_ON  = 1,                        // ch:打开 | en:ON
}MVD_TRIGGER_MODE;

typedef enum _tag_MVD_TRIGGER_SOURCE_
{
	MVD_TRIGGER_SOURCE_SOFTWARE = 0,
	MVD_TRIGGER_SOURCE_LINE1    = 1
}MVD_MVD_TRIGGER_SOURCE;

typedef enum _tag_MVD_TRIGGER_ACTIVATION_
{
	MVD_TRIGGER_ACTIVATION_RISING_EDGE =0,
	MVD_TRIGGER_ACTIVATION_FALLING_EDGE = 1,
	MVD_TRIGGER_ACTIVATION_ANY_EDGE = 3,
	MVD_TRIGGER_ACTIVATION_LEVEL_HEIGH = 4,
	MVD_TRIGGER_ACTIVATION_LEVEL_LOW = 5
}MVD_TRIGGER_ACTIVATION;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#endif