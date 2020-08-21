#ifndef __MVDAPI_TYPE_DEFINE_H__
#define __MVDAPI_TYPE_DEFINE_H__

/// -----------------------------------------------------------------------------
///
/// @file    MVDAPI_TypeDefine.h
/// @author  Mike.Guo
/// @version 0.1
/// @date    2020.08.06
/// @brief   MVDAPIӦ�ÿ����ӿ��������Ͷ���ͷ�ļ�
///
/// -----------------------------------------------------------------------------


#include <tchar.h>

typedef int MVD_ReturnCode;         ///< MVDAPI����������

#define MVD_MAX_DEVICE_NUM   32     ///< MVDAPI���֧�ֵ��豸��Ŀ

///-----------------------------------------------------------------------------
/// ����ö�����ͣ�GetLanguage��SetLanguage
///-----------------------------------------------------------------------------
enum MVD_LANGUAGE
{
	L_CHS = 0,    ///< ����
	L_ENG = 1     ///< Ӣ��
};

///-----------------------------------------------------------------------------
/// �豸�ӿ�ö������
///-----------------------------------------------------------------------------
enum MVD_DEVICE_INTERFACE_TYPE
{
	DIT_ALL  = 0x00000000,    ///< ����֧�ֵ��豸�ӿ�
	DIT_USB  = 0x00000001,    ///< �豸�ӿ�����ΪUSB2.0��USB3.0
	DIT_GIGE = 0x00000002     ///< �豸�ӿ�����Ϊǧ����
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
///  �豸��Ϣ�ṹ�壬���ݲ�ͬ���豸�ӿ����͵��豸
///-----------------------------------------------------------------------------
struct MVD_DEVICE_INFORMATION
{
	unsigned int    uiDeviceModel;            ///< �豸�ͺ�
	TCHAR           szModelName[64];          ///< �ͺ�����
	unsigned int    uiSerialNumber;           ///< �豸���к�
	MVD_VERSION     FirmwareVersion;          ///< �̼��汾��
	MVD_VERSION     FpgaVersion;              ///< FPGA�汾��
	MVD_VERSION     HardwareVersion;          ///< Ӳ���汾

	TCHAR           szUserDefinedName[32];    ///< �û��Զ�������++0.4
	int             nReserved0[32];           ///< Common Information

	MVD_DEVICE_INTERFACE_TYPE    DeviceInterfaceType;    ///< �豸�Ľӿ�����

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

		int                          nReserved0[64];         ///< ������Ϣ��USB��GIGE������Ϣ
	}SpecialInfo;
};

//-----------------------------------------------------------------------------
//  �豸��Ϣ�б�ṹ�壬��MVD_Initial����ʱ��д��
//-----------------------------------------------------------------------------
typedef struct _tag_MVD_DEVICE_INFORMATION_LIST
{
	unsigned int             uiDeviceNum;                                 ///< ���ҵ����豸��Ŀ
	MVD_DEVICE_INFORMATION   *pDeviceInformation[MVD_MAX_DEVICE_NUM];     ///< ��Ӧ���豸��Ϣָ�룬���ָ��ָ��SDK��Ӧ�ĵ�ַ�����ɽ������ݵ��޸�
}MVD_DEVICE_INFORMATION_LIST, *PMVD_DEVICE_INFORMATION_LIST;

/// ��ȡģʽ(���ģʽ)
enum MVD_ADDRESS_MODE
{
	AM_1 = 0,     ///< ������ȡ
	AM_2 = 1,     ///< 2x2��ȡ1������
	AM_4 = 2,     ///< 4x4��ȡ1������
	AM_8 = 3,     ///< 8x8��ȡ1������
};

/// ROI(����Ȥ����)���ݽṹ����
typedef struct _tag_MVD_ROI_SIZE
{
	unsigned int     uiColSize;         ///< �ӳ�����Ԫ��Ŀ
	unsigned int     uiRowSize;         ///< �ӳ�����Ԫ��Ŀ
	MVD_ADDRESS_MODE ColAddressMode;    ///< ����Ԫ��ȡģʽ������ColSize�����Ͻ�����ȡ)
	MVD_ADDRESS_MODE RowAddressMode;    ///< ����Ԫ��ȡģʽ������RowSize�����Ͻ�����ȡ)

}MVD_ROI_SIZE, *PMVD_MVD_ROI_SIZE;

typedef struct _tag_MVD_ROI_OFFSET
{
	unsigned int     uiColStart;
	unsigned int     uiRowStart;
}MVD_ROI_START, *PMVD_ROI_START;

/// �û�Ԥ���鶨��
enum MVD_USER_PRESETTING
{
	UP_0 = 0,     ///< �û�Ԥ����0
	UP_1 = 1,     ///< �û�Ԥ����1
	UP_2 = 2,     ///< �û�Ԥ����2
	UP_3 = 3,     ///< �û�Ԥ����3
	UP_INVALID = -1    ///< ��ЧԤ����
};

/// ����ѡ����
enum MVD_GAIN_SELECTOR
{
	GS_GLOBAL = 0,                  ///< ȫ�����棬���ڲ�ɫ��ͬʱ���ں���������
	GS_RED = 1,                     ///< ������
	GS_GREEN = 2,                   ///< ������
	GS_BLUE = 3                     ///< ������
};

/// �Զ��ع�ģʽ
enum MVD_EXPOSURE_MODE
{
	EM_MANUAL = 0,          ///< �ֶ������ع�
	EM_AUTO_ONCE = 1,       ///< ��������Զ����ε����ع⣬���ú�����
	EM_AUTO_CONTINUOUS = 2, ///< ��������Զ����������ع⣬���ú�����
};

/// �Զ��ع�ص�����ʾ��ǰ�Զ��ع⴦��״̬
enum MVD_AUTO_EXPOSURE_STATUS
{
	AES_ONCE_SUCCESS = 0, 			///< ���ε��ڳɹ�
	AES_ONCE_FAIL_MAX_COUNT, 		///< ���ε���ʧ�ܣ�ʧ��ԭ��ﵽ�����ڴ�����������ڴ����Ǳ�ʾ����ʹ�ö���֡ͼ����Ϊһ�ε��ڣ�Ĭ��20֡��
	AES_ONCE_FAIL_WAVE, 			///< ���ε���ʧ�ܣ�ʧ��ԭ�����������
	AES_ONCE_FAIL_OVER_RANGE, 		///< ���ε���ʧ�ܣ�ʧ��ԭ���عⳬ�����÷�Χ
	AES_DOING, 						///< һ�ε�����ɣ��ع�ʱ�䷢���˱仯��������ȷ���ɹ���ʧ��
	AES_CONTINUOUS_SUCCESS,			///< �������ڳɹ�����ǰ�ﵽ��Ŀ��ֵ
	AES_CONTINUOUS_FAIL_WAVE, 		///< ��������ʧ�ܣ�ʧ��ԭ�����������
	AES_CONTINUOUS_FAIL_OVER_RANGE 	///< ��������ʧ�ܣ�ʧ��ԭ���عⳬ�����÷�Χ
};

/// ��ƽ��ģʽ
/// ����豸֧��Ӳ����ƽ�⣬����ѡ��Ӳ����ƽ��(��֤Ч��)
enum MVD_WHITE_BALANC_MODE
{
	WBM_DISABLE = 0,                  ///< ʹ��ƽ����Ч
	WBM_SOFTWARE_PRESETTING = 1,      ///< ���ɫ��Ԥ����
	WBM_SOFTWARE_AUTO_ONCE = 2,       ///< ����������Զ�����
	WBM_SOFTWARE_AUTO_CONTINUOUS = 3, ///< �����������������
	WBM_SOFTWARE_MANUAL = 4,          ///< �ֶ����������ƽ��Ч������
	WBM_HARDWARE_PRESETTING = 5,      ///< Ӳ��ɫ��Ԥ����
	WBM_HARDWARE_AUTO_ONCE = 6,       ///< Ӳ���������Զ�����
	WBM_HARDWARE_AUTO_CONTINUOUS = 7, ///< Ӳ�����������Զ�����
	WBM_HARDWARE_MANUAL = 8           ///< �ֶ�����Ӳ����ƽ��Ч������
};

/// ��ɫЧ��ģʽö������
/// ����豸֧��Ӳ����ɫЧ��������ѡ��Ӳ��Ч��ģʽ(��֤Ч��)
enum MVD_COLOR_CORRECTION_MODE
{
	CCM_DISABLE = 0,                  ///< ��ɫЧ����ʹ��
	CCM_SOFTWARE_PRESETTING = 1,      ///< �����ɫЧ��Ԥ��ֵģʽ���ο�SetColorCorrectionPresetting
	CCM_SOFTWARE_MANUAL = 2,          ///< �ֶ����������ɫЧ��ϵ������ģʽ���ο�SetColorCorrectionMatrix
	CCM_HARDWARE_PRESETTING = 3,      ///< Ӳ����ɫЧ��Ԥ��ֵģʽ���ο�SetColorCorrectionPresetting
	CCM_HARDWARE_MANUAL = 4           ///< �ֶ�����Ӳ����ɫЧ��ϵ������ģʽ���ο�SetColorCorrectionMatrix
};

/// ɫ�¶���ö������
enum MVD_COLOR_TEMPERATURE
{
	CT_5000K = 0,                         ///< ɫ��5000K
	CT_6500K = 1,                         ///< ɫ��6500K
	CT_2800K = 2                          ///< ɫ��2800K
};

/// ���ظ�ʽö������(С���ֽ���)
enum MVD_PIXEL_FORMAT
{
	PF_RAW8 = 0,    ///< 8bitԭʼ
	PF_GRAY8,       ///< 8bit�Ҷȣ����ںڰ��������ͬ��PF_RAW8)
	PF_RGB24,       ///< 24bit��RGB���У��ڴ�B�ڵ͵�ַ
	PF_RGB32,       ///< 32bit��RGBA���У��ڴ�B�ڵ͵�ַ
	PF_BGR24,       ///< 24bit��BGR���У��ڴ�R�ڵ͵�ַ
	PF_BGR32,       ///< 32bit��BGRA���У��ڴ�R�ڵ͵�ַ
	PF_RAW16,       ///< 16bitԭʼ(���е���Чλ��ͨ��GetAdcResolution������ȡ)
	PF_GRAY16,      ///< 16bit�Ҷȣ����ںڰ��������ͬ��PF_RAW16)
	PF_RGB48,       ///< 48bit, RGB���У��ڴ�B�ڵ͵�ַ��R,G,B��ռ2�ֽڣ���8λ�ڵ͵�ַ
	PF_RGB64,       ///< 64bit, RGBA���У��ڴ�B�ڵ͵�ַ��R,G,B��ռ2�ֽڣ���8λ�ڵ͵�ַ
	PF_BGR48,       ///< 48bit, BGR���У��ڴ�R�ڵ͵�ַ��R,G,B��ռ2�ֽڣ���8λ�ڵ͵�ַ
	PF_BGR64,       ///< 64bit, BGRA���У��ڴ�R�ڵ͵�ַ��R,G,B��ռ2�ֽڣ���8λ�ڵ͵�ַ

};

/// ѹ��8bitģʽ
enum MVD_ADC_COMPANDING_MODE
{
	ACM_EXTRACT = 0,     ///< Ӳ����ȡλģʽת��Ϊ8bit����
	ACM_LUT = 1          ///< Ӳ��ͨ��LUT���ұ�ת��Ϊ8bit����
};

/// ��ȡģʽ
enum MVD_EXTRACT_MODE
{
	EM_0_7 = 0,         ///< ��ȡ0-7λ
	EM_1_8 = 1,
	EM_2_9 = 2,
	EM_3_10 = 3,
	EM_4_11 = 4,        ///< ��ȡ4-11λ
};

enum MVD_FRAME_TRIGGER_MODE
{
	FTM_CONTINUOUS = 0,     ///< �Զ���������
	FTM_EXTERNAL = 1,       ///< ͨ���ⲿ�����źŴ���
	FTM_SOFTWARE = 2,       ///< ͨ����������
	FTM_FIXED = 3           ///< �̶�֡�ʴ���
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

/// �ɼ�ͼ��Ļ�����Ϣ
struct MVD_IMAGE_BASE_INFO
{
	int nImageWidth;            ///< ͼ�ο�ȣ����أ�
	int nImageHeight;           ///< ͼ�θ߶ȣ����أ�
	int nImageBitCount;         ///< λͼ��� 8/24/32
	int nImageBitsPerSample;    ///< ÿ�������ı����� 8/16
	int nTotalBytes;            ///< ͼ������ֽ���=nImageWidth*nImageHeight*(nImageBitCount/8)*(nImageBitsPerSample/8)

	int nReserved[32];
};

/// �ɼ�ͼ�����չ��Ϣ
struct MVD_IMAGE_EXTEND_INFO
{
	float                    fGain;                       ///< ���棬�Ŵ���
	float                    fExposureTimeUs;             ///< �ع�ʱ�䣨uS��
	int                      nReserved0[16];

	unsigned __int64         ui64HostTimeStamp;           ///< �������ɵ�ʱ�������ǰϵͳʱ�ӵĵδ�������ο�QueryPerformanceCounter
	unsigned __int64         ui64ElapseTimeMicrosecond;   ///< ���������ȡ��һ֡��ʱ��
	unsigned __int64         ui64DeviceTimeStamp;         ///< �豸ʱ������豸ʱ�ӵδ����
	unsigned int             uiDeviceFrequency;           ///< �豸ʱ���ʱ��Ƶ��(Hz), Fpgaʱ��Ƶ�ʣ�ÿ�����ж��ٸ�ʱ�ӵδ����

	unsigned int             uiTriggerCounter;            ///< �����ⴥ���źż������Ƿ���Ҫ�����ⴥ������������������Ƿ����������أ���ƽ��
	unsigned int             uiFrameCounter;              ///< ����֡����
	unsigned int             uiFrameId;                   ///< ֡ID
	unsigned int             uiLostPacket;                ///< ��������
	unsigned int             uiImageBytesRead;            ///< ʵ�ʶ�ȡ���ֽ���

	int                      nReserved1[32];
};

/// �ɼ�ͼ�����Ϣ�����ݣ���һ���������ڴ��ַ�ռ䣬ucImageData����Ĵ�С����ImageBaseInfo��nTotalBytesֵ��
typedef struct
{
	MVD_IMAGE_BASE_INFO     ImageBaseInfo;     ///< �ɼ�ͼ��Ļ�����Ϣ��
	MVD_IMAGE_EXTEND_INFO   ImageExtendInfo;   ///< �ɼ�ͼ�����չ��Ϣ��
	// unsigned char           ucImageData[1];    ///< Ϊͼ��ĵ�һ�����ݣ���һ���ɿ��ڶ�̬����ģ���ImageExtendInfo������һ���ڴ��ַ���ڴ��С����ImageBaseInfo��nTotalBytesֵ��
}MVD_GRAB_IMAGE_INFO;

#pragma pack(pop)

///-----------------------------------------------------------------------------
/// ����ͼ���ʽ��ö������
///-----------------------------------------------------------------------------
typedef enum
{
	SIF_UNKNOWN = 0,  ///< �����ļ���չ������
	SIF_BMP = 1,      ///< ����ΪBMP��ʽ
	SIF_JPG = 2,      ///< ����ΪJPG��ʽ
	SIF_PNG = 3,      ///< ����ΪPNG��ʽ
	SIF_TIF = 4,      ///< ����ΪTIF��ʽ
}MVD_SAVE_IMAGE_FORMAT;

/// ����ͼ��������Ϣ
typedef struct _tag_MVD_SAVE_IMAGE_INFORMATION
{
	TCHAR                    *pszImageName;               ///< �����ļ�������·������c:\MVD\2020-02-23.bmp
	MVD_SAVE_IMAGE_FORMAT    SaveImageFormat;            ///< �ο�enum MVD_IAMGE_TYPE����
	unsigned int             nJpgQuality;                ///< ֻ��enImageFormat=MVD_IMAGE_FORMAT_JPG����������Ч
}MVD_SAVE_IMAGE_INFORMATION;



/// ��ƽ��ص�����ָ�붨��
typedef void(__stdcall *PMVD_WHITE_BALANCE_CALLBACK)(OUT int nDeviceIndex, OUT float fMatrixR, OUT float fMatrixG, OUT float fMatrixB, OUT void *lpContext);
/// �Զ��ع�ص�����ָ�붨��
typedef void(__stdcall *PMVD_AUTO_EXPOSURE_CALLBACK)(OUT int nDeviceIndex, OUT MVD_AUTO_EXPOSURE_STATUS Status, OUT float fExpsoureTimeUs, OUT void *lpContext);
/// �ɼ�ͼ��ص�����ָ�붨��
typedef void(__stdcall *PMVD_GRABBING_CALLBACK)(OUT int nDeviceIndex, OUT MVD_GRAB_IMAGE_INFO* pGrabImageInfo, OUT unsigned char *pGrabImageData,  OUT void* lpContext);


#endif