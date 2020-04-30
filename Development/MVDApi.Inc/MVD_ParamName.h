#ifndef __MVD_PARAM_NAME_H__
#define __MVD_PARAM_NAME_H__

//-----------------------------------------------------------------------------
//                定义参数名称字符串，这个可以不必与GENICAM SFNC一致
//-----------------------------------------------------------------------------
#define MVD_PARAM_NAMES_NUM    13

// 定义参数名称字符串
#define MVD_PARAM_NAME_ROI_WIDTH_A                      "roi_width"
#define MVD_PARAM_NAME_ROI_HEIGHT_A                     "roi_height"
#define MVD_PARAM_NAME_ROI_OFFSET_X_A                   "roi_offset_x"
#define MVD_PARAM_NAME_ROI_OFFSET_Y_A                   "roi_offset_y"
#define MVD_PARAM_NAME_EXPOSURE_TIME_A                  "exposure_time"
#define MVD_PARAM_NAME_ACQUSITION_MODE_A                "aquisition_mode"    // 采集模式
#define MVD_PARAM_NAME_TRIGGER_MODE_A                   "trigger_mode"       // 触发模式
#define MVD_PARAM_NAME_TRIGGER_SOURCE_A                 "trigger_source"     // 选择当触发模式为on时的触发源
#define MVD_PARAM_NAME_TRIGGER_ACTIVATION_A             "trigger_activation"
#define MVD_PARAM_NAME_REVERSE_X_A                      "reverse_x"          // 水平翻转
#define MVD_PARAM_NAME_REVERSE_Y_A                      "reverse_y"          // 垂直翻转
#define MVD_PARAM_NAME_STREAM_PACKET_SIZE_A             "packet_size"

#define MVD_PARAM_NAME_DRIVER_TYPE_A                    "driver_type"

// 定义参数名称字符串（宽字符型）wchar_t
#define MVD_PARAM_NAME_ROI_WIDTH_W                      L"roi_width"
#define MVD_PARAM_NAME_ROI_HEIGHT_W                     L"roi_height"
#define MVD_PARAM_NAME_ROI_OFFSET_X_W                   L"roi_offset_x"
#define MVD_PARAM_NAME_ROI_OFFSET_Y_W                   L"roi_offset_y"
#define MVD_PARAM_NAME_EXPOSURE_TIME_W                  L"exposure_time"
#define MVD_PARAM_NAME_ACQUSITION_MODE_W                L"aquisition_mode"    // 采集模式
#define MVD_PARAM_NAME_TRIGGER_MODE_W                   L"trigger_mode"       // 触发模式
#define MVD_PARAM_NAME_TRIGGER_SOURCE_W                 L"trigger_source"     // 选择当触发模式为on时的触发源
#define MVD_PARAM_NAME_TRIGGER_ACTIVATION_W             L"trigger_activation"
#define MVD_PARAM_NAME_REVERSE_X_W                      L"reverse_x"          // 水平翻转
#define MVD_PARAM_NAME_REVERSE_Y_W                      L"reverse_y"          // 垂直翻转

#define MVD_PARAM_NAME_STREAM_PACKET_SIZE_W             L"packet_size"
#define MVD_PARAM_NAME_DRIVER_TYPE_W                    L"driver_type"


//-----------------------------------------------------------------------------
//                          定义命令名称字符串
//-----------------------------------------------------------------------------
#define MVD_COMMAND_NAMES_NUM    3

// 定义命令名称字符串
#define MVD_COMMAND_NAME_SOFTWARE_TRIGGER_A             "command_software_trigger"
#define MVD_COMMAND_NAME_ACQUISITION_START_A	        "command_acquisition_start"
#define MVD_COMMAND_NAME_ACQUISITION_STOP_A	            "command_acquisition_stop"

// 定义命令名称字符串（宽字符型）wchar_t
#define MVD_COMMAND_NAME_SOFTWARE_TRIGGER_W             L"command_software_trigger"
#define MVD_COMMAND_NAME_ACQUISITION_START_W	        L"command_acquisition_start"
#define MVD_COMMAND_NAME_ACQUISITION_STOP_W             L"command_acquisition_stop"

//-----------------------------------------------------------------------------
//                          定义参数描述字符串
//-----------------------------------------------------------------------------
// 定义参数描述的字符串
#define MVD_PARAM_NAME_ROI_WIDTH_DESC_A                 "region of interesting column size"
#define MVD_PARAM_NAME_ROI_HEIGHT_DESC_A                "region of interesting row size"
#define MVD_PARAM_NAME_ROI_OFFSET_X_DESC_A              "region of interesting column start"
#define MVD_PARAM_NAME_ROI_OFFSET_Y_DESC_A              "region of interesting row start"
#define MVD_PARAM_NAME_EXPOSURE_TIME_DESC_A             "exposure time in million second"
#define MVD_PARAM_NAME_EXPOSURE_TIME_RAW_DESC_A         "exposure time raw"
#define MVD_PARAM_NAME_ACQUISITION_MODE_DESC_A          "controls the mode of acquisition for the device. This mainly affects the number of frames captured in the Acquisition"
#define MVD_PARAM_NAME_TRIGGER_MODE_DESC_A              "trigger mode."
#define MVD_PARAM_NAME_TRIGGER_SOURCE_DESC_A            "trigger source when trigger mode is on"
#define MVD_PARAM_NAME_TRIGGER_ACTIVATION_DESC_A        "Specifies the activation mode of the trigger" 
#define MVD_PARAM_NAME_REVERSE_X_DESC_A                 "reverse x"
#define MVD_PARAM_NAME_REVERSE_Y_DESC_A                 "reverse y"
#define MVD_PARAM_NAME_PACKAGE_SIZE_DESC_A              "stream packet size"

#define MVD_PARAM_NAME_DRIVER_TYPE_DESC_A               "driver type using(filter driver or socket)"


// 定义参数描述的字符串（宽字符型）wchar_t
#define MVD_PARAM_NAME_ROI_WIDTH_DESC_W                 L"region of interesting column size"
#define MVD_PARAM_NAME_ROI_HEIGHT_DESC_W                L"region of interesting row size"
#define MVD_PARAM_NAME_ROI_OFFSET_X_DESC_W              L"region of interesting column start"
#define MVD_PARAM_NAME_ROI_OFFSET_Y_DESC_W              L"region of interesting row start"
#define MVD_PARAM_NAME_EXPOSURE_TIME_DESC_W             L"exposure time in million second"
#define MVD_PARAM_NAME_EXPOSURE_TIME_RAW_DESC_W         L"exposure time raw"
#define MVD_PARAM_NAME_ACQUISITION_MODE_DESC_W          L"controls the mode of acquisition for the device. This mainly affects the number of frames captured in the Acquisition"
#define MVD_PARAM_NAME_TRIGGER_MODE_DESC_W              L"trigger mode."
#define MVD_PARAM_NAME_TRIGGER_SOURCE_DESC_W            L"trigger source when trigger mode is on"
#define MVD_PARAM_NAME_TRIGGER_ACTIVATION_DESC_W        L"Specifies the activation mode of the trigger" 
#define MVD_PARAM_NAME_REVERSE_X_DESC_W                 L"reverse x"
#define MVD_PARAM_NAME_REVERSE_Y_DESC_W                 L"reverse y"
#define MVD_PARAM_NAME_PACKAGE_SIZE_DESC_W              L"stream packet size"


#define MVD_PARAM_NAME_DRIVER_TYPE_DESC_W               L"driver type using(filter driver or socket)"

//-----------------------------------------------------------------------------
//                          定义MVD_VALUE_TYPE_STRING类型参数所涉及的字符串
//-----------------------------------------------------------------------------
#define MVD_STRING_UNKNOWN_A                            "unknown"

// MVD_PARAM_NAME_ACQUSITION_MODE参数的值
#define MVD_STRING_SINGAL_FRAME_A                       "single_frame"
#define MVD_STRING_CONTINUOUS_A                         "continuous"
#define MVD_STRING_MULTI_FRAME_A                        "multi_frame"

// MVD_PARAM_NAME_TRIGGER_MODE参数的值
#define MVD_STRING_OFF_A                                "off"
#define MVD_STRING_ON_A                                 "on"

// MVD_PARAM_NAME_REVERSE_X，MVD_PARAM_NAME_REVERSE_Y参数的值
#define MVD_STRING_FALSE_A                              "false"
#define MVD_STRING_TRUE_A                               "true"

// MVD_PARAM_NAME_TRIGGER_SOURCE参数的值
#define MVD_STRING_SOFTWARE_A                           "software"
#define MVD_STRING_LINE1_A                              "line1"

// MVD_PARAM_NAME_TRIGGER_ACTIVATION参数的值
#define MVD_STRING_RISING_EDGE_A                        "rising_edge"
#define MVD_STRING_FALLING_EDGE_A                       "falling_edge"
#define MVD_STRING_ANY_EDGE_A                           "any_edge"
#define MVD_STRING_LEVEL_HIGH_A                         "level_high"
#define MVD_STRING_LEVEL_LOW_A                          "level_low"


#define MVD_STRING_UNKNOWN_W                           L"unknown"

// MVD_PARAM_NAME_ACQUSITION_MODE参数的值（宽字符型）wchar_t
#define MVD_STRING_SINGAL_FRAME_W                      L"single_frame"
#define MVD_STRING_CONTINUOUS_W                        L"continuous"
#define MVD_STRING_MULTI_FRAME_W                       L"multi_frame"

// MVD_PARAM_NAME_TRIGGER_MODE参数的值（宽字符型）wchar_t
#define MVD_STRING_OFF_W                               L"off"
#define MVD_STRING_ON_W                                L"on"

// MVD_PARAM_NAME_REVERSE_X，MVD_PARAM_NAME_REVERSE_Y参数的值（宽字符型）wchar_t
#define MVD_STRING_FALSE_W                             L"false"
#define MVD_STRING_TRUE_W                              L"true"

// MVD_PARAM_NAME_TRIGGER_SOURCE参数的值（宽字符型）wchar_t
#define MVD_STRING_SOFTWARE_W                          L"software"
#define MVD_STRING_LINE1_W                             L"line1"

// MVD_PARAM_NAME_TRIGGER_ACTIVATION参数的值（宽字符型）wchar_t
#define MVD_STRING_RISING_EDGE_W                       L"rising_edge"
#define MVD_STRING_FALLING_EDGE_W                      L"falling_edge"
#define MVD_STRING_ANY_EDGE_W                          L"any_edge"
#define MVD_STRING_LEVEL_HIGH_W                        L"level_high"
#define MVD_STRING_LEVEL_LOW_W                         L"level_low"

#define MVD_STRING_DRIVER_TYPE_FILTER_A                         "filter"
#define MVD_STRING_DRIVER_TYPE_SOCKET_A                         "socket"

#define MVD_STRING_DRIVER_TYPE_FILTER_W                         L"filter"
#define MVD_STRING_DRIVER_TYPE_SOCKET_W                         L"socket"

#endif