#ifndef __MVDAPI_RETURN_CODE_H__
#define __MVDAPI_RETURN_CODE_H__

/// -----------------------------------------------------------------------------
///
/// @file    MVDAPI_ReturnCode.h
/// @author  Mike
/// @version 0.1
/// @date    2020.08.06
/// @brief   MVDAPI应用开发接口函数返回码定义头文件
/// @see     GetReturnCodeString
///
/// -----------------------------------------------------------------------------


#define MVD_SUCCESS          0X00000000L    ///< 成功

#define MVD_E_FAIL           0X80000001L    ///< 一般错误
#define MVD_E_NOT_SUPPORT    0x80000002L    ///< 不支持
#define MVD_E_INVALID_DEVICE 0x80000004L    ///< 无效的设备
#define MVD_E_INVALID_PARAM  0x80000008L    ///< 无效参数
#define MVD_E_INVALID_HANDLE 0x80000010L    ///< 无效句柄 
#define MVD_E_NULL_POINTER   0x80000020L    ///< 空指针
#define MVD_E_MALLOC         0x80000040L    ///< 分配内存失败
#define MVD_E_CONFLICT       0x80000080L    ///< 设置有冲突



#endif