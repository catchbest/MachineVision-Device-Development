#ifndef __MVDAPI_RETURN_CODE_H__
#define __MVDAPI_RETURN_CODE_H__

/// -----------------------------------------------------------------------------
///
/// @file    MVDAPI_ReturnCode.h
/// @author  Mike
/// @version 0.1
/// @date    2020.08.06
/// @brief   MVDAPIӦ�ÿ����ӿں��������붨��ͷ�ļ�
/// @see     GetReturnCodeString
///
/// -----------------------------------------------------------------------------


#define MVD_SUCCESS          0X00000000L    ///< �ɹ�

#define MVD_E_FAIL           0X80000001L    ///< һ�����
#define MVD_E_NOT_SUPPORT    0x80000002L    ///< ��֧��
#define MVD_E_INVALID_DEVICE 0x80000004L    ///< ��Ч���豸
#define MVD_E_INVALID_PARAM  0x80000008L    ///< ��Ч����
#define MVD_E_INVALID_HANDLE 0x80000010L    ///< ��Ч��� 
#define MVD_E_NULL_POINTER   0x80000020L    ///< ��ָ��
#define MVD_E_MALLOC         0x80000040L    ///< �����ڴ�ʧ��
#define MVD_E_CONFLICT       0x80000080L    ///< �����г�ͻ



#endif