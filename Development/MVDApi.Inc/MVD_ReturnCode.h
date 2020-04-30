#ifndef _MVD_RETURN_CODE_H_
#define _MVD_RETURN_CODE_H_

#define MVD_SUCCESS              0x00000000  ///< �ɹ����޴��� | en:Successed, no error

#define MVD_E_CONDITIONS         0x80000010  /// ��������������
//ͨ�ô����붨��:��Χ0x80000000-0x800000FF | en:
#define MVD_E_HANDLE             0x80000000  ///< �������Ч�ľ�� | en:Error or invalid handle
#define MVD_E_SUPPORT            0x80000001  ///< ��֧�ֵĹ��� | en:Not supported function
#define MVD_E_BUFOVER            0x80000002  ///< �������� | en:Cache is full
#define MVD_E_CALLORDER          0x80000003  ///< ��������˳����� | en:Function calling order error
#define MVD_E_PARAMETER          0x80000004  ///< ����Ĳ��� | en:Incorrect parameter
#define MVD_E_RESOURCE           0x80000006  ///< ��Դ����ʧ�� | en:Applying resource failed
#define MVD_E_NODATA             0x80000007  ///< ������ | en:No data
#define MVD_E_PRECONDITION       0x80000008  ///< ǰ���������󣬻����л����ѷ����仯 | en:Precondition error, or running environment changed
#define MVD_E_VERSION            0x80000009  ///< �汾��ƥ�� | en:Version mismatches
#define MVD_E_NOENOUGH_BUF       0x8000000A  ///< ������ڴ�ռ䲻�� | en:Insufficient memory
#define MVD_E_ABNORMAL_IMAGE     0x8000000B  ///< �쳣ͼ�񣬿����Ƕ�������ͼ������ | en:Abnormal image, maybe incomplete image because of lost packet
#define MVD_E_LOAD_LIBRARY       0x8000000C  ///< ��̬����DLLʧ�� | en:Load library failed
#define MVD_E_NOOUTBUF           0x8000000D  ///< û�п�����Ļ��� | en:No Avaliable Buffer
#define MVD_E_SOCKET             0x8000000E  ///< ������� | en:Socket error
#define MVD_E_UNKNOW             0x800000FF  ///< δ֪�Ĵ��� | en:Unknown error

// GenICamϵ�д���:��Χ0x80000100-0x800001FF | en:GenICam Series Error Codes: Range from 0x80000100 to 0x800001FF
#define MVD_E_GC_GENERIC         0x80000100  ///< ͨ�ô��� | en:General error
#define MVD_E_GC_ARGUMENT        0x80000101  ///< �����Ƿ� | en:Illegal parameters
#define MVD_E_GC_RANGE           0x80000102  ///< ֵ������Χ | en:The value is out of range
#define MVD_E_GC_PROPERTY        0x80000103  ///< ���� | en:Property
#define MVD_E_GC_RUNTIME         0x80000104  ///< ���л��������� | en:Running environment error
#define MVD_E_GC_LOGICAL         0x80000105  ///< �߼����� | en:Logical error
#define MVD_E_GC_ACCESS          0x80000106  ///< �ڵ������������ | en:Node accessing condition error
#define MVD_E_GC_TIMEOUT         0x80000107  ///< ��ʱ | en:Timeout
#define MVD_E_GC_DYNAMICCAST     0x80000108  ///< ת���쳣 | en:Transformation exception
#define MVD_E_GC_UNKNOW          0x800001FF  ///< GenICamδ֪���� | en:GenICam unknown error

//GigE_STATUS��Ӧ�Ĵ�����:��Χ0x80000200-0x800002FF | en:GigE_STATUS Error Codes: Range from 0x80000200 to 0x800002FF
#define MVD_E_NOT_IMPLEMENTED    0x80000200  ///< ������豸֧�� | en:The command is not supported by device
#define MVD_E_INVALID_ADDRESS    0x80000201  ///< ���ʵ�Ŀ���ַ������ | en:The target address being accessed does not exist
#define MVD_E_WRITE_PROTECT      0x80000202  ///< Ŀ���ַ����д | en:The target address is not writable
#define MVD_E_ACCESS_DENIED      0x80000203  ///< �豸�޷���Ȩ�� | en:No permission
#define MVD_E_BUSY               0x80000204  ///< �豸æ��������Ͽ� | en:Device is busy, or network disconnected
#define MVD_E_PACKET             0x80000205  ///< ��������ݴ��� | en:Network data packet error
#define MVD_E_NETER              0x80000206  ///< ������ش��� | en:Network error
// GigE������еĴ�����
#define MVD_E_IP_CONFLICT        0x80000221  ///< �豸IP��ͻ | en:Device IP conflict

//USB_STATUS��Ӧ�Ĵ�����:��Χ0x80000300-0x800003FF | en:USB_STATUS Error Codes: Range from 0x80000300 to 0x800003FF
#define MVD_E_USB_READ           0x80000300      ///< ��usb���� | en:Reading USB error
#define MVD_E_USB_WRITE          0x80000301      ///< дusb���� | en:Writing USB error
#define MVD_E_USB_DEVICE         0x80000302      ///< �豸�쳣 | en:Device exception
#define MVD_E_USB_GENICAM        0x80000303      ///< GenICam��ش��� | en:GenICam error
#define MVD_E_USB_BANDWIDTH      0x80000304      ///< ������  �ô��������� | en:Insufficient bandwidth, this error code is newly added
#define MVD_E_USB_DRIVER         0x80000305      ///< ������ƥ�����δװ���� | en:Driver mismatch or unmounted drive
#define MVD_E_USB_UNKNOW         0x800003FF      ///< USBδ֪�Ĵ��� | en:USB unknown error

//����ʱ��Ӧ�Ĵ�����:��Χ0x80000400-0x800004FF | en:Upgrade Error Codes: Range from 0x80000400 to 0x800004FF
#define MVD_E_UPG_FILE_MISMATCH     0x80000400 ///< �����̼���ƥ�� | en:Firmware mismatches
#define MVD_E_UPG_LANGUSGE_MISMATCH 0x80000401 ///< �����̼����Բ�ƥ�� | en:Firmware language mismatches
#define MVD_E_UPG_CONFLICT          0x80000402 ///< ������ͻ���豸�Ѿ����������ٴ��������������ش˴��� | en:Upgrading conflicted (repeated upgrading requests during device upgrade)
#define MVD_E_UPG_INNER_ERR         0x80000403 ///< ����ʱ����ڲ����ִ��� | en:Camera internal error during upgrade
#define MVD_E_UPG_UNKNOW            0x800004FF ///< ����ʱδ֪���� | en:Unknown error during upgrade

#endif // _MVD_RETURN_CODE_H_