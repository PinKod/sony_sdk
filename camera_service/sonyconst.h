char*    CFG_PM_NAME="Program mode";
#define  CFG_PM_ID 0x500E
#define  CFG_PM_CODE 0x9205
#define  CFG_PM_COUNT 7
#define  CFG_PM_TYPE PTP_DTC_UINT16
uint32_t CFG_PM_VALUES[CFG_PM_COUNT]={0    , 0x8000, 0x0002, 0x0003, 0x0004, 0x0001, 0x8053};
char*    CFG_PM_LIST[CFG_PM_COUNT]=  {"N/A", "iA"  , "P"   , "A"   , "S"   , "M"   , "Video"};





char*    CFG_FM_NAME="Focus mode";
#define  CFG_FM_ID 0x500A
#define  CFG_FM_CODE 0x9205
#define  CFG_FM_COUNT 3
#define  CFG_FM_TYPE PTP_DTC_UINT16
#define  CFG_FM_MF 0x0001
#define  CFG_FM_AF 0x0002
uint32_t CFG_FM_VALUES[CFG_FM_COUNT]={0    , 0x0001, 0x0002};
char*    CFG_FM_LIST[CFG_FM_COUNT]=  {"N/A", "MF"  , "AF-S"};

#define CFG_FOCUS_INACTIVE 0x01
#define CFG_FOCUS_FOCUSED 0x02
#define CFG_FOCUS_FAILED 0x03
#define CFG_FOCUS_SEARCHING 0x05
#define CFG_FOCUS_COMPLEX 0x06





char*    CFG_ISO_NAME="ISO";
#define  CFG_ISO_ID 0xD226
#define  CFG_ISO_CODE 0x9205
#define  CFG_ISO_COUNT 32
#define  CFG_ISO_TYPE PTP_DTC_UINT32
`uint32_t CFG_ISO_VALUES[CFG_ISO_COUNT]=
                          {0    , 0xFFFFFF,  50 ,  100 ,  125 ,  160 ,  200 ,  250 ,  320 ,  400 ,  500 ,  640 ,  800 ,  1000 ,  1600 ,  2000 ,
                            2500 ,  3200 ,  4000 ,  5000 ,  6400 ,  8000 ,  10000 ,  12800 ,  16000 ,  20000 ,  25600 ,   32000 ,  40000 ,  51200 };
char*    CFG_ISO_LIST[CFG_ISO_COUNT]=  
                          {"N/A", "AUTO"  , "50","100", "125", "160", "200", "250", "320", "400", "500", "640", "800", "1000", "1600", "2000",
                           "2500", "3200", "4000", "5000", "6400", "8000", "10000", "12800", "16000", "20000", "25600", " 32000", "40000", "51200"};





char*    CFG_SHUTTER_NAME="Shutter speed";
#define  CFG_SHUTTER_ID 0xD229
#define  CFG_SHUTTER_CODE 0x9205
#define  CFG_SHUTTER_COUNT 53
#define  CFG_SHUTTER_TYPE PTP_DTC_UINT32
uint32_t CFG_SHUTTER_VALUES[CFG_SHUTTER_COUNT]=
                              {0    , 0x012C000A, 0xFA000A, 0xC8000A, 0x96000A, 0x82000A, 0x64000A, 0x50000A, 0x3C000A, 0x32000A, 0x28000A, 0x20000A, 0x19000A, 
                               0x14000A, 0x10000A, 0xD000A, 0xA000A, 0x8000A, 0x6000A, 0x5000A, 0x4000A, 0x10003, 0x10004, 0x10005, 0x10006, 0x10008, 
                               0x1000A, 0x1000D, 0x1000F, 0x10014, 0x10019, 0x1001E, 0x10028, 0x10032, 0x1003C, 0x10050, 0x10064, 0x1007D, 0x100A0, 
                               0x100C8, 0x100FA, 0x10140, 0x10190, 0x101F4, 0x10280, 0x10320 , 0x103E8 , 0x104E2 , 0x10640 , 0x107D0 , 0x109C4, 
                               0x10C80 , 0x10FA0 };
char*    CFG_SHUTTER_LIST[CFG_SHUTTER_COUNT]=  
                              {"N/A", "30``"    , "25``"  , "20``"  , "15``"  , "13``"  , "10``"  , "8``"   , "6``"   , "5``"   , "4``"   , "3.2``" , "2.5``",
                               "2``"   , "1.6``" , "1.3``", "1``"  , "0.8``", "0.6``", "0.5``", "0.4``", "1/3"  , "1/4"  , "1/5"  , "1/6"  , "1/8"  ,
                               "1/10" , "1/13" , "1/15", "1/20"  , "1/25" , "1/30" , "1/40" , "1/50" , "1/60" , "1/80" , "1/100", "1/125", "1/160",
                               "1/200", "1/250", "1/320", "1/400", "1/500", "1/640", "1/800", "1/1000", "1/1250", "1/1600", "1/2000", "1/2500",
                               "1/3200", "1/4000"};




char*   CFG_APERTURE_NAME="Aperture"; //!!!
#define  CFG_APERTURE_ID 0x5007
#define  CFG_APERTURE_CODE 0x9207  //!!
#define  CFG_APERTURE_COUNT 25
#define  CFG_APERTURE_TYPE PTP_DTC_UINT16
#define  CFG_APERTURE_VALUP 0x0001
#define  CFG_APERTURE_VALDN 0xFFFF
uint32_t CFG_APERTURE_VALUES[CFG_APERTURE_COUNT]=
                              {0    ,  0x0b4,  0x0c8,  0x0dc,   0x0fa,  0x118 , 0x140 , 0x15E , 0x190 , 0x1C2 , 0x1F4, 0x230 , 0x276 , 0x2C6 , 0x320 , 0x384 , 0x3E8, 0x44C, 0x514, 
                               0x578, 0x640, 0x708, 0x7D0, 0x898, 0xfffe};
char*   CFG_APERTURE_LIST[CFG_APERTURE_COUNT]=  
                              {"N/A", "F1.8", "F2.0", "F2.2",  "F2.5",  "F2.8", "F3.2", "F3.5", "F4.0", "F4.5", "F5" , "F5.6", "F6.3", "F7.1", "F8.0", "F9.0", "F10", "F11", "F13", 
                               "F14", "F16", "F18", "F20", "F22", "AUTO"};




char*    CFG_EV_NAME="EV";//!!!!
#define CFG_EV_ID 0x5010
#define CFG_EV_CODE 0x9207 ///!!
#define CFG_EV_COUNT 32
#define CFG_EV_TYPE PTP_DTC_INT16
#define CFG_EV_VALUP 0x0001
#define CFG_EV_VALDN 0xFFFF

uint32_t CFG_EV_VALUES[CFG_EV_COUNT]=
                        {0    ,	 0xEC78 , 0xEDA4, 0xEF34, 0xF060, 0xF18C, 0xF31C, 0xF448, 0xF574, 0xF704, 0xF830, 0xF95C, 0xFAEC, 0xFC18, 0xFD44, 0xFED4,
                         0x0000, 0x012C, 0x02BC, 0x03E8, 0x0514, 0x06A4, 0x07D0, 0x08FC, 0x0A8C, 0x0BB8, 0x0CE4, 0x0E74, 0x0FA0, 0x10CC, 0x125C, 0x1388};
char*    CFG_EV_LIST[CFG_EV_COUNT]=  
                        {"N/A",	 "-5.0" , "-4.7", "-4.3", "-4.0", "-3.7", "-3.3", "-3.0", "-2.7", "-2.3", "-2.0", "-1.7", "-1.3", "-1.0", "-0.7", "-0.3",
                         " 0.0", "+0.3", "+0.7", "+1.0", "+1.3", "+1.7", "+2.0", "+2.3", "+2.7", "+3.0", "+3.3", "+3.7", "+4.0", "+4.3", "+4.7", "+5.0"};



char*    CFG_JQ_NAME="JPEG quality";
#define  CFG_JQ_ID 0x5004
#define  CFG_JQ_CODE 0x9205
#define  CFG_JQ_COUNT 5
#define  CFG_JQ_TYPE PTP_DTC_UINT8
uint32_t CFG_JQ_VALUES[CFG_JQ_COUNT]={0    , 0x10  , 0x04    , 0x03  , 0x02};
char*    CFG_JQ_LIST[CFG_JQ_COUNT]=  {"N/A", "RAW" , "X.Fine", "Fine", "STD" };



char*    CFG_WB_NAME="White balance";
#define  CFG_WB_ID 0x5005
#define  CFG_WB_CODE 0x9205
#define  CFG_WB_COUNT 5
#define  CFG_WB_TYPE PTP_DTC_UINT16
uint32_t CFG_WB_VALUES[CFG_JQ_COUNT]={0    , 0x0002 , 0x0004    , 0x8011  , 0x8010  };
char*    CFG_WB_LIST[CFG_JQ_COUNT]=  {"N/A", "Auto" , "Daylight", "Shade" , "Cloudy"};

