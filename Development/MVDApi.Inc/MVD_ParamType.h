//-----------------------------------------------------------------------------
// ��Ȩ�����Ӽ�

// �ļ����ƣ�MVD_ParamType.h
// ��Ҫ������SDK�����ӿڲ������������Ͷ���

// �������ڣ�2020-2-24
// ��ǰ�汾��V1.0
// ���ߣ�Mike
// ˵������׺_A�Ƿ�UNICODE�Ľṹ�嶨�壬_W�ǿ��ֽ��ַ�������UNICODE���


// �޸����ڣ� 
// ��ǰ�汾��
// ���ߣ�
// ˵����
//-----------------------------------------------------------------------------

#ifndef __MVD_PARAM_TYPE_H__
#define __MVD_PARAM_TYPE_H__




//��ƽ̨����
//Cross Platform Definition
#ifdef WIN32
typedef __int64          int64_t;
typedef unsigned __int64 uint64_t;
#else
#include <stdint.h>
#endif

// ���֧�ֵ��豸��Ŀ
#define MVD_MAX_DEVICE_NUM          256    
// ��Ϣ�ַ�����Buffer�ֽڴ�С
#define MVD_BUFFER_SIZE             64
// ��ɢ����������ж��ٸ���ɢֵ
#define MVD_MAX_VALUE_NUM           64
// ֧��ʹ���ַ���������ַ���Ŀ�����ﷵ�ص��ַ������ַ��������ᳬ������ֵ��
#define MVD_MAX_STRING_CHARACTERS   512

//-----------------------------------------------------------------------------
// �豸�ӿ�ö������
//-----------------------------------------------------------------------------
typedef enum
{
	MVD_DEVICE_INTERFACE_TYPE_UNKNOWN = 0x00000000,    // �豸�ӿ����Ͳ���ʶ��
	MVD_DEVICE_INTERFACE_TYPE_USB     = 0x00000001,    // �豸�ӿ�����ΪUSB2.0��USB3.0
	MVD_DEVICE_INTERFACE_TYPE_GIGE    = 0x00000002     // �豸�ӿ�����Ϊǧ����
}MVD_DEVICE_INTERFACE_TYPE;

//-----------------------------------------------------------------------------
// ����ͼ���ʽ��ö������
//-----------------------------------------------------------------------------
typedef enum
{
	MVD_IMAGE_FORMAT_UNKNOWN = 0,  // �����ļ���չ������
	MVD_IMAGE_FORMAT_BMP = 1,      // ����ΪBMP��ʽ
	MVD_IMAGE_FORMAT_JPG = 2,      // ����ΪJPG��ʽ
	MVD_IMAGE_FORMAT_PNG = 3,      // ����ΪPNG��ʽ
	MVD_IMAGE_FORMAT_TIF = 4,      // ����ΪTIF��ʽ
}MVD_IMAGE_FORMAT;

//-----------------------------------------------------------------------------
// ��ѯ��Ϣö�����ͣ��ڵ���MVD_QueryInfo����ʱ����Ϊ�ڶ�����������
//-----------------------------------------------------------------------------
typedef enum
{
	MVD_QUERY_INFO_TYPE_SDK_VERSION = 0,            // ��ѯSDK�汾����Ϣ�������κ�ʱ�̲�ѯ��MVD_QueryInfo������һ������������
	MVD_QUERY_INFO_TYPE_PARAM_NAMES = 1,            // MVD_Initial���óɹ�֮�󼴲�ѯ��������֧�ֵĲ��������б���Щ����������ΪMVD_GetParam��MVD_SetParam�Ĳ���pchParamName���д��ݡ�
	MVD_QUERY_INFO_TYPE_COMMAND_NAMES = 2,          // MVD_Initial���óɹ�֮�󼴲�ѯ��������֧�ֵ����������б���Щ�������ƿ���ͨ��MVD_ExecuteCommand��������
	MVD_QUERY_INFO_TYPE_GRAB_FPS = 3,               // MVD_Initial���óɹ�֮�󼴲�ѯ�����ص�ǰ�Ĳɼ�֡��
	MVD_QUERY_INFO_TYPE_DISPLAY_FPS = 4,            // MVD_Initial���óɹ�֮�󼴲�ѯ�����ص�ǰ��ʾ֡��
	MVD_QUERY_INFO_TYPE_IS_OPEN,                    // MVD_Initial���óɹ�֮�󼴲�ѯ�������豸�Ƿ��
	MVD_QUERY_INFO_TYPE_IS_GRABBING_START,          // MVD_Initial���óɹ�֮�󼴲�ѯ�������Ƿ�ɼ��Ѿ���ʼ
	MVD_QUERY_INFO_TYPE_IS_CALLBACK_GRAB,           // MVD_Initial���óɹ�֮�󼴲�ѯ�������Ƿ�ص��ɼ��Ѿ���ʼ
}MVD_QUERY_INFO_TYPE;

// ������ڲ�ѯMVD_QUERY_INFO_TYPE_DRIVER_TYPEʱ���ܷ��ص�ֵ
typedef enum
{
	MVD_DRIVER_TYPE_UNKNOWN = 0,
	MVD_DRIVER_TYPE_FILTER = 1,                     // ��Filter������ȡ
	MVD_DRIVER_TYPE_SOCKET = 0                      // ��Socket��ȡ
};

//-----------------------------------------------------------------------------
// ��ֵ���������ͣ�Ϊ��ʹһ���ӿڿ���֧�ֶ����������͵Ļ�ȡ�����ö������ö������
// ����ֵ����ΪMVD_VALUE_TYPE_INTʱ����Ҫ����MVD_VALUE�е�nValue��Ա
// ����ֵ����ΪMVD_VALUE_TYPE_INT64ʱ����Ҫ����MVD_VALUE�е�nValue64��Ա
// ����ֵ����ΪMVD_VALUE_TYPE_FLOATʱ����Ҫ����MVD_VALUE�е�fValue��Ա
// ����ֵ����ΪMVD_VALUE_TYPE_STRINGʱ����Ҫ����MVD_VALUE�е�pszValue��Ա
//-----------------------------------------------------------------------------
typedef enum
{
	MVD_VALUE_TYPE_UNKNOWN = 0,
	MVD_VALUE_TYPE_INT = 1,              // 32λ������������
	MVD_VALUE_TYPE_INT64 = 2,            // 32λ������������
	MVD_VALUE_TYPE_FLOAT = 3,             // ������������
	MVD_VALUE_TYPE_STRING = 4,            // �ַ�����������
}MVD_VALUE_TYPE;

typedef enum
{
	MVD_ACCESS_MODE_RW = 0,                // �����ɶ�д
	MVD_ACCESS_MODE_RO = 1                 // ����ֻ��
}MVD_ACCESS_MODE;

#pragma pack(1)

//-----------------------------------------------------------------------------
// �豸�ӿ�����ΪMVD_DEVICE_INTERFACE_TYPE_USB���豸��Ϣ�ṹ��
//-----------------------------------------------------------------------------
typedef struct _tag_MVD_DEVICE_INFO_USB
{
	unsigned short          usVendorId;                                // ch:��Ӧ��ID�� | en:Vendor ID Number
	unsigned short          usProductId;                               // ch:��ƷID�� | en:Device ID Number
	unsigned int            nDeviceNumber;                             // ch:�豸���к�  | en:Device Serial Number
	char                    chDeviceGUID[MVD_BUFFER_SIZE];             // ch:�豸GUID�� | en:Device GUID Number
	char                    chVendorName[MVD_BUFFER_SIZE];             // ch:��Ӧ������ | en:Vendor Name
	char                    chModelName[MVD_BUFFER_SIZE];              // ch:�ͺ����� | en:Model Name
	char                    chFamilyName[MVD_BUFFER_SIZE];             // ch:�������� | en:Family Name
	char                    szDeviceVersion[MVD_BUFFER_SIZE];          // ch:�豸�汾�� | en:Device Version
	char                    chManufacturerName[MVD_BUFFER_SIZE];       // ch:���������� | en:Manufacturer Name
	char                    chSerialNumber[MVD_BUFFER_SIZE];           // ch:���к� | en:Serial Number
	char                    chUserDefinedName[MVD_BUFFER_SIZE];        // ch:�û��Զ������� | en:User Defined Name
	unsigned int            nbcdUSB;                                   // ch:֧�ֵ�USBЭ�� | en:Support USB Protocol
	unsigned int            nReserved[3];                              // ch:�����ֽ� | en:Reserved bytes

	unsigned short          usFirmwareVersion;
	unsigned short          usFpgaVersion;
	unsigned int            uiDeviceMode;

	unsigned int            usSerials;

	// USB��������/Hub
}MVD_DEVICE_INFO_USB, *PMVD_DEVICE_INFO_USB;

//-----------------------------------------------------------------------------
// �豸�ӿ�����ΪMVD_DEVICE_INTERFACE_TYPE_GIGE���豸��Ϣ�ṹ�壬������˵����Ϊ�����ֽ���
//-----------------------------------------------------------------------------
typedef struct _tag_MVD_DEVICE_INFO_GIGE_A
{
	unsigned int        uiDeviceMode;
	unsigned char       ucDeviceMac[8];
	unsigned short      usDeviceMacAddressH;
	unsigned int        uiDeviceMacAddressL;
	unsigned int        uiDeviceIpConfigOptions;
	unsigned int        uiDeviceIpConfigCurrent;       // IP configuration:bit31-static bit30-dhcp bit29-lla      
	unsigned int        uiDeviceIpCurrent;             // ����IP��ַΪ192.168.111.1����uiDeviceIpCurrent=0x016FA8C0        
	unsigned int        uiDeviceSubnetMaskCurrent;     // ����IP��ַΪ255.255.255.0����uiDeviceSubnetMaskCurrent=0x00ffffff      
	unsigned int        uiDeviceGatewayDefault;        // ����IP��ַΪ192.168.111.254����uiDeviceGatewayDefault=0xfe6fa8c0
	char                szDeviceManufacturerName[MVD_BUFFER_SIZE];
	char                szDeviceModelName[MVD_BUFFER_SIZE];
	char                szDeviceVersion[MVD_BUFFER_SIZE];
	char                szDeviceManufacturerSpecificInfo[MVD_BUFFER_SIZE];
	char                szDeviceSerialNumber[MVD_BUFFER_SIZE];
	char                szDeviceUserDefinedName[MVD_BUFFER_SIZE];

	// ������������Ϣ
	unsigned char       ucAdapterMac[8];
	unsigned long       ulAdapterIp;
	unsigned long       ulAdapterSubnetMask;
	char                szAdapterFriendlyName[MVD_MAX_STRING_CHARACTERS];
	char                szAdapterDescription[MVD_MAX_STRING_CHARACTERS];

	// ����ĺ���ɾ��
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
	unsigned int        uiDeviceIpCurrent;             //����IP��ַΪ192.168.111.1����uiDeviceIpCurrent=0x016FA8C0        
	unsigned int        uiDeviceSubnetMaskCurrent;     //����IP��ַΪ255.255.255.0����uiDeviceSubnetMaskCurrent=0x00ffffff      
	unsigned int        uiDeviceGatewayDefault;        //����IP��ַΪ192.168.111.254����uiDeviceGatewayDefault=0xfe6fa8c0
	wchar_t             szDeviceManufacturerName[MVD_BUFFER_SIZE];
	wchar_t             szDeviceModelName[MVD_BUFFER_SIZE];
	wchar_t             szDeviceVersion[MVD_BUFFER_SIZE];
	wchar_t             szDeviceManufacturerSpecificInfo[MVD_BUFFER_SIZE];
	wchar_t             szDeviceSerialNumber[MVD_BUFFER_SIZE];
	wchar_t             szDeviceUserDefinedName[MVD_BUFFER_SIZE];

	// ������������Ϣ
	unsigned char       ucAdapterMac[8];
	unsigned long       ulAdapterIp;
	unsigned long       ulAdapterSubnetMask;
	wchar_t             szAdapterFriendlyName[MVD_MAX_STRING_CHARACTERS];
	wchar_t             szAdapterDescription[MVD_MAX_STRING_CHARACTERS];

	// ����ĺ���ɾ��
	unsigned char       ucAdapterIp[6];
	unsigned char       ucAdapterDns[6];

}MVD_DEVICE_INFO_GIGE_W, *PMVD_DEVICE_INFO_GIGE_W;

//-----------------------------------------------------------------------------
// �豸��Ϣ�ṹ�壬���ݲ�ͬ���豸�ӿ����͵��豸
//-----------------------------------------------------------------------------
typedef struct _tag_MVD_DEVICE_INFO_A
{
	MVD_DEVICE_INTERFACE_TYPE    DeviceInterfaceType;    // �豸�Ľӿ�����

	union
	{
		MVD_DEVICE_INFO_USB    stDeviceInfoUsb;            // DeviceInterfaceTypeΪMVD_DEVICE_INTERFACE_TYPE_USBʱ���豸��Ϣ
		MVD_DEVICE_INFO_GIGE_A stDeviceInfoGige;           // DeviceInterfaceTypeΪMVD_DEVICE_INTERFACE_TYPE_GIGEʱ���豸��Ϣ
	}Info;
}MVD_DEVICE_INFO_A, *PMVD_DEVICE_INFO_A;

typedef struct _tag_MVD_DEVICE_INFO_W
{
	MVD_DEVICE_INTERFACE_TYPE    DeviceInterfaceType;    // �豸�Ľӿ�����

	union
	{
		MVD_DEVICE_INFO_USB    stDeviceInfoUsb;            // DeviceInterfaceTypeΪMVD_DEVICE_INTERFACE_TYPE_USBʱ���豸��Ϣ
		MVD_DEVICE_INFO_GIGE_W stDeviceInfoGige;           // DeviceInterfaceTypeΪMVD_DEVICE_INTERFACE_TYPE_GIGEʱ���豸��Ϣ
	}Info;
}MVD_DEVICE_INFO_W, *PMVD_DEVICE_INFO_W;


//-----------------------------------------------------------------------------
// �豸��Ϣ�б�ṹ�壬��MVD_Initial����ʱ��д��
//-----------------------------------------------------------------------------
typedef struct _tag_MVD_DEVICE_INFO_LIST_A
{
	unsigned int        uiDeviceNum;                         // ���ҵ����豸��Ŀ
	PMVD_DEVICE_INFO_A  pDeviceInfo[MVD_MAX_DEVICE_NUM];     // ��Ӧ���豸��Ϣ�б�
}MVD_DEVICE_INFO_LIST_A;

typedef struct _tag_MVD_DEVICE_INFO_LIST_W
{
	unsigned int        uiDeviceNum;                         // ���ҵ����豸��Ŀ
	PMVD_DEVICE_INFO_W  pDeviceInfo[MVD_MAX_DEVICE_NUM];     // ��Ӧ���豸��Ϣ�б�
}MVD_DEVICE_INFO_LIST_W;

//-----------------------------------------------------------------------------
// ʵ�ʵ���ֵ��Ϊ��ʹһ���ӿڿ���֧�ֶ����������͵Ļ�ȡ�����ö����������������
// ��Ҫ����MVD_VALUE_TYPE�����ͽ���Ӧ�õ����á�
// ����ֵ����ΪMVD_VALUE_TYPE_INTʱ����Ҫ����MVD_VALUE�е�nValue��Ա
// ����ֵ����ΪMVD_VALUE_TYPE_INT64ʱ����Ҫ����MVD_VALUE�е�nValue64��Ա
// ����ֵ����ΪMVD_VALUE_TYPE_FLOATʱ����Ҫ����MVD_VALUE�е�fValue��Ա
// ����ֵ����ΪMVD_VALUE_TYPE_STRINGʱ����Ҫ����MVD_VALUE�е�pszValue��Ա
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
// ���շ��صĲ�ѯ��Ϣ���������ṹ����MVD_QueryInfo������ʹ��
// MVD_VALUE_TYPE      enInfoType                     ��Ϣֵ�����ͣ���Ҫ���ݴ����ͣ�������Ӧ��unValues�еĳ�Ա
// int                 nValueNum                      ��Ϣֵ����Чֵ������Ҳ����unValues��������Ч��Ԫ��
// MVD_VALUE_A         unValues[MVD_MAX_VALUE_NUM]    ��Ϣʵ��ֵ������enInfoType��ʵ�����ͣ�ʹ����Ӧ�ĳ�Ա
//-----------------------------------------------------------------------------
typedef struct
{
	MVD_VALUE_TYPE      enInfoType;                     // ��Ϣֵ������
	int                 nValueNum;                      // ��Ϣֵ����Чֵ����
	MVD_VALUE_A         unValues[MVD_MAX_VALUE_NUM];    // ��Ϣʵ��ֵ������enInfoType��ʵ�����ͣ�ʹ����Ӧ�ĳ�Ա
}MVD_QUERY_INFO_A;

typedef struct
{
	MVD_VALUE_TYPE      enInfoType;                     // ��Ϣֵ������
	int                 nValueNum;                      // ��Ϣֵ����Чֵ����
	MVD_VALUE_W         unValues[MVD_MAX_VALUE_NUM];    // ��Ϣʵ��ֵ������enInfoType��ʵ�����ͣ�ʹ����Ӧ�ĳ�Ա
}MVD_QUERY_INFO_W;

//-----------------------------------------------------------------------------
// ���շ��صĲ�����Ϣ������ṹ����MVD_GetParam������ʹ��
// ��ȡ������Ϣ���������ֵ����Сֵ��Ĭ��ֵ�������������õ�������Χ����ɢֵ��Ϣ
// MVD_VALUE_TYPE      enParamType     ����ֵ���������ͣ�������;���MVD_VALUE����Ҫ���õĳ�Ա
// int                 nValueNum;                  �����������õ���ֵ��Ŀ����=0ʱ����ʾ����Ϊ�����ͣ���Ҫ�鿴[unValueMin, unValueMax]ȷ���������÷�Χ����������unValues���飻��=1ʱ����ʾֻ����һ��ֵ���鿴unValues[0]����>1ʱ����ʾ��ֵΪ��ɢ�ģ���Ҫ�鿴unValues����
// MVD_VALUE_A         unValues[MVD_MAX_VALUE_NUM];�������õ����ݣ���nValueNum>=1ʱ�����Խ������ô�����ȷ���������õ�ֵ��
// MVD_VALUE_A         unValueDef;                 ������Ĭ��ֵ(������в���ֵ���������Ͷ���Ч��
// MVD_VALUE_A         unValueCur;                 �����ĵ�ǰֵ(������в���ֵ���������Ͷ���Ч��
// MVD_VALUE_A         unValueMin;                 �����Ŀ����õ���Сֵ��ֻ�Բ���ֵ����������ΪMVD_VALUE_TYPE_INT��MVD_VALUE_TYPE_INT64��MVD_VALUE_TYPE_FLOAT������nValueNum=0��Ч��
// MVD_VALUE_A         unValueMax;                 �����Ŀ����õ����ֵ��ֻ�Բ���ֵ����������ΪMVD_VALUE_TYPE_INT��MVD_VALUE_TYPE_INT64��MVD_VALUE_TYPE_FLOAT������nValueNum=0��Ч��
// MVD_VALUE_A         unValueInc;                 ���������ò�����ֻ�Բ���ֵ����������ΪMVD_VALUE_TYPE_INT��MVD_VALUE_TYPE_INT64��MVD_VALUE_TYPE_FLOAT��Ч��
// char               *pszParamDesc;               ����������(������в���ֵ���������Ͷ���Ч��
//-----------------------------------------------------------------------------
typedef struct _tag_MVD_GET_PARAME_VALUE_A
{
	MVD_VALUE_TYPE      enParamType;                // ����ֵ���������ͣ�������;���MVD_VALUE����Ҫ���õĳ�Ա
	MVD_ACCESS_MODE     enAccessMode;               // ��������ģʽ
	int                 nValueNum;                  // �����������õ���ֵ��Ŀ����=0ʱ����ʾ����Ϊ�����ͣ���Ҫ�鿴[unValueMin, unValueMax]ȷ���������÷�Χ����������unValues���飻��=1ʱ����ʾֻ����һ��ֵ���鿴unValues[0]����>1ʱ����ʾ��ֵΪ��ɢ�ģ���Ҫ�鿴unValues����
	MVD_VALUE_A         unValues[MVD_MAX_VALUE_NUM];// �������õ����ݣ���nValueNum>=1ʱ�����Խ������ô�����ȷ���������õ�ֵ��
	MVD_VALUE_A         unValueDef;                 // ������Ĭ��ֵ(������в���ֵ���������Ͷ���Ч��
	MVD_VALUE_A         unValueCur;                 // �����ĵ�ǰֵ(������в���ֵ���������Ͷ���Ч��
	MVD_VALUE_A         unValueMin;                 // �����Ŀ����õ���Сֵ��ֻ�Բ���ֵ����������ΪMVD_VALUE_TYPE_INT��MVD_VALUE_TYPE_INT64��MVD_VALUE_TYPE_FLOAT������nValueNum=0��Ч��
	MVD_VALUE_A         unValueMax;                 // �����Ŀ����õ����ֵ��ֻ�Բ���ֵ����������ΪMVD_VALUE_TYPE_INT��MVD_VALUE_TYPE_INT64��MVD_VALUE_TYPE_FLOAT������nValueNum=0��Ч��
	MVD_VALUE_A         unValueInc;                 // ���������ò�����ֻ�Բ���ֵ����������ΪMVD_VALUE_TYPE_INT��MVD_VALUE_TYPE_INT64��MVD_VALUE_TYPE_FLOAT��Ч��
	char               *pszParamDesc;               // ����������(������в���ֵ���������Ͷ���Ч��
}MVD_GET_PARAME_VALUE_A;

typedef struct _tag_MVD_GET_PARAME_VALUE_W
{
	MVD_VALUE_TYPE      enParamType;                // ����ֵ���������ͣ�������;���MVD_VALUE����Ҫ���õĳ�Ա
	MVD_ACCESS_MODE     enAccessMode;               // ��������ģʽ
	int                 nValueNum;                  // �����������õ���ֵ��Ŀ����=0ʱ����ʾ����Ϊ�����ͣ���Ҫ�鿴[unValueMin, unValueMax]ȷ���������÷�Χ����������unValues���飻��=1ʱ����ʾֻ����һ��ֵ���鿴unValues[0]����>1ʱ����ʾ��ֵΪ��ɢ�ģ���Ҫ�鿴unValues����
	MVD_VALUE_W         unValues[MVD_MAX_VALUE_NUM];// �������õ����ݣ���nValueNum>=1ʱ�����Խ������ô�����ȷ���������õ�ֵ��
	MVD_VALUE_W         unValueDef;                 // ������Ĭ��ֵ(������в���ֵ���������Ͷ���Ч��
	MVD_VALUE_W         unValueCur;                 // �����ĵ�ǰֵ(������в���ֵ���������Ͷ���Ч��
	MVD_VALUE_W         unValueMin;                 // �����Ŀ����õ���Сֵ��ֻ�Բ���ֵ����������ΪMVD_VALUE_TYPE_INT��MVD_VALUE_TYPE_INT64��MVD_VALUE_TYPE_FLOAT������nValueNum=0��Ч��
	MVD_VALUE_W         unValueMax;                 // �����Ŀ����õ����ֵ��ֻ�Բ���ֵ����������ΪMVD_VALUE_TYPE_INT��MVD_VALUE_TYPE_INT64��MVD_VALUE_TYPE_FLOAT������nValueNum=0��Ч��
	MVD_VALUE_W         unValueInc;                 // ���������ò�����ֻ�Բ���ֵ����������ΪMVD_VALUE_TYPE_INT��MVD_VALUE_TYPE_INT64��MVD_VALUE_TYPE_FLOAT��Ч��
	wchar_t            *pszParamDesc;               // ����������(������в���ֵ���������Ͷ���Ч��
}MVD_GET_PARAME_VALUE_W;

//-----------------------------------------------------------------------------
// ��Ҫ���õĲ�����Ϣ������ṹ����MVD_SetParam������ʹ��
//-----------------------------------------------------------------------------
typedef struct _tag_MVD_SET_PARAME_VALUE_A
{
	MVD_VALUE_TYPE      enParamType;                // ����ֵ���������ͣ��������ֵ������Ҫͨ��MVD_GetParam��������ȡ������Ҫһ��
	MVD_VALUE_A         unValue;                    // ������Ҫ���õ�ֵ����Ҫ����enParamType��ʵ�����ͣ�����ֵ��Ӧ�ĳ�Ա
}MVD_SET_PARAME_VALUE_A;

typedef struct _tag_MVD_SET_PARAME_VALUE_W
{
	MVD_VALUE_TYPE      enParamType;                // ����ֵ���������ͣ��������ֵ������Ҫͨ��MVD_GetParam��������ȡ������Ҫһ��
	MVD_VALUE_W         unValue;                    // ������Ҫ���õ�ֵ����Ҫ����enParamType��ʵ�����ͣ�����ֵ��Ӧ�ĳ�Ա
}MVD_SET_PARAME_VALUE_W;

//-----------------------------------------------------------------------------
// ������ʾ��صĲ�����Ϣ������ṹ����MVD_SetDisplayPosition��MVD_GetDisplayPosition������ʹ��
//-----------------------------------------------------------------------------
typedef struct
{
	void *            hDisplayWnd;                 // ��ʾͼ��Ĵ��ھ��
	int               nX;                          // ��ʾ�ڴ��ڵ�λ��x����Դ���ԭ���X����ƫ�ƣ��ɲο�StretchDIBits�ڶ�������
	int               nY;                          // ��ʾ�ڴ��ڵ�λ��y����Դ���ԭ���Y����ƫ�ƣ��ɲο�StretchDIBits����������
	int               nWidth;                      // ��ʾ�ڴ����ϵĿ�ȣ��������ͼ�����ؿ�ȣ���ˮƽ����Ŵ���ʾ��С����ˮƽ������С��ʾ���ɲο�StretchDIBits���ĸ�����
	int               nHeight;                     // ��ʾ�ڴ����ϵĸ߶ȣ��������ͼ�����ظ߶ȣ���ֱ����Ŵ���ʾ��С����ֱ������С��ʾ���ɲο�StretchDIBits���������
}MVD_DISPLAY_POSITION_INFO;


//-----------------------------------------------------------------------------
// ����ṹ������һ֡�������ʱ�������Ϣ
//-----------------------------------------------------------------------------
typedef struct
{
	unsigned int             uiWidth;                     // ��������ļ�¼��д
	unsigned int             uiHeight;                    // ��������ļ�¼��д
	enum MVD_PIXEL_FORMAT    enPixelFormat;               // ��������ļ�¼��д���صĸ�ʽ���ο�"MVD_PixelFormat.h"
	unsigned int             uiTotalBytes;                // ��������ļ�¼��д����Ҫ��ȡ��ͼ���ֽ������ܹ��ж��ٸ��ֽڵ�����

	unsigned __int64         ui64HostTimeStamp;           // �������ɵ�ʱ�������ǰϵͳʱ�ӵĵδ�������ο�QueryPerformanceCounter
	unsigned __int64         ui64ElapseTimeMicrosecond;   // ���������ȡ��һ֡��ʱ��

	float                    fGain;
	float                    fExposureTime;

	unsigned int             uiRoiOffsetX;
	unsigned int             uiRoiOffsetY;
	unsigned int             uiRoiWidth;
	unsigned int             uiRoiHeight;

	unsigned int             uiTriggerIndex;              // �����������Ƿ���Ҫ�����ⴥ�����������������

	// �豸ˮӡʱ��
	unsigned __int64         ui64FpgaTimeStamp;           // FpgaӲ��ʱ�ӵδ����

	unsigned int             uiFpgaFrequency;             // Fpgaʱ�����ڣ�ÿ�����ж��ٸ�ʱ��

	unsigned int             uiFrameId;                   // ����Ǹ���ʵ�ʵ�GVSPͷ��䣬֡�� 
	unsigned int             uiLostPacket;                // ��֡������
	unsigned  int            uiImageBytesRead;            // ʵ�ʶ�ȡ���ֽ���

	unsigned __int64         ui64DeviceTimeStamp;         // ����Ǹ���ʵ�ʵ�GVSPLEADER���ݰ���䣬�豸���ɵ�ʱ���
	unsigned int             uiImageSizeX;                // ����Ǹ���ʵ�ʵ�GVSPͷ��䣬���û��㲻�ɼ�
	unsigned int             uiImageSizeY;                // ����Ǹ���ʵ�ʵ�GVSPͷ��䣬���û��㲻�ɼ�
	enum MVD_PIXEL_FORMAT    enImagePixelFormat;          // ����Ǹ���ʵ�ʵ�GVSPͷ��䣬���û��㲻�ɼ�

	unsigned int             uiPackageSize;               // ��������ֽ�����GVSPÿ�δ���İ��Ĵ�С������IP_HEADER,UDP_HEADER������)
	unsigned long            iaSrc;                       // ԴIP��ַ�����û��㲻�ɼ�
	unsigned long            iaDst;                       // Ŀ��IP��ַ�����û��㲻�ɼ�
	unsigned char            ucMacDst[6];                 // Ŀ��Mac��ַ�����նˣ�������
	unsigned char            ucMacSrc[6];                 // ԴMac��ַ�����Ͷˣ��豸��

	unsigned short           usPortSrc;                   // Դ�˿ڣ����û��㲻�ɼ�
	unsigned short           usPortDst;                   // Ŀ�Ķ˿ڣ����û��㲻�ɼ�

	unsigned int             uiReserved[64];
}MVD_FRAME_OUT_INFO;

//-----------------------------------------------------------------------------
// MVD_FRAME_OUT����ṹ�����ڲɼ�һ֡�����󷵻ظ��û�������MVD_GrabImage��MVD_SaveImage�Ѿ��ص��ĵ�һ������
//-----------------------------------------------------------------------------
typedef struct 
{
	MVD_FRAME_OUT_INFO    stFrameOutInfo;    // Ϊͼ�����ϸ��Ϣ
	unsigned char         ucFrameData[1];    // Ϊͼ�����ݵĵ�һ�����ݵ�ַ
}MVD_FRAME_OUT;

// ͼ��ص�����ָ��
typedef void(__stdcall *MVD_IMAGE_CALLBACK)(MVD_FRAME_OUT* pFrameOut, void* pUser);


// ch:����ͼƬ���� | en:Save image type
typedef struct _tag_MVD_SAVE_IMAGE_PARAM_A
{
	char                    *pszImageName;               // �����ļ�������·������c:\MVD\2020-02-23.bmp
	MVD_IMAGE_FORMAT         enImageFormat;              // �ο�enum MVD_IAMGE_TYPE����
	unsigned int             nJpgQuality;                // ֻ��enImageFormat=MVD_IMAGE_FORMAT_JPG����������Ч
}MVD_SAVE_IMAGE_PARAM_A;

typedef struct _tag_MVD_SAVE_IMAGE_PARAM_W
{
	wchar_t                 *pszImageName;              // �����ļ�������·������c:\MVD\2020-02-23.bmp
	MVD_IMAGE_FORMAT         enImageFormat;              // �ο�enum MVD_IAMGE_TYPE����
	unsigned int             nJpgQuality;                // ֻ��enImageFormat=MVD_IMAGE_FORMAT_JPG����������Ч
}MVD_SAVE_IMAGE_PARAM_W;

#pragma pack()


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ch:�ɼ�ģʽ | en:Acquisition mode
typedef enum _tag_MVD_ACQUISITION_MODE_
{
	MVD_ACQUISITION_MODE_SINGLE_FRAME = 0,              // ch:��֡ģʽ | en:Single Mode
	MVD_ACQUISITION_MODE_MUTLI_FRAME  = 1,              // ch:��֡ģʽ | en:Multi Mode
	MVD_ACQUISITION_MODE_CONTINUOUS   = 2,              // ch:�����ɼ�ģʽ | en:Continuous Mode
}MVD_ACQUISITION_MODE;

typedef enum _tag_MVD_TRIGGER_MODE_
{
	MVD_TRIGGER_MODE_OFF = 0,                        // ch:�ر� | en:Off
	MVD_TRIGGER_MODE_ON  = 1,                        // ch:�� | en:ON
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