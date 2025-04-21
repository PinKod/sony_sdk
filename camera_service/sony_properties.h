#ifndef SONY_PROPERTIES_TABLES_H
#define SONY_PROPERTIES_TABLES_H

#define lvFile    "cap.jpg"
#define tmplvFile "captmp.jpg"

#define SET_FOCUS_MODE_FILE  "focus_mode.set"
#define NFO_FOCUS_MODE_FILE  "focus_mode.nfo"
#define LIST_FOCUS_MODE_FILE "focus_mode.list"

#define SET_SHOOT_MODE_FILE  "shoot_mode.set"
#define NFO_SHOOT_MODE_FILE  "shoot_mode.nfo"
#define LIST_SHOOT_MODE_FILE "shoot_mode.list"

#define SET_ISO_FILE  "iso.set"
#define NFO_ISO_FILE  "iso.nfo"
#define LIST_ISO_FILE "iso.list"

#define SET_APERTURE_FILE  "aperture.set"
#define NFO_APERTURE_FILE  "aperture.nfo"
#define LIST_APERTURE_FILE "aperture.list"

#define SET_SHUTTER_SPEED_FILE  "shutter_speed.set"
#define NFO_SHUTTER_SPEED_FILE  "shutter_speed.nfo"
#define LIST_SHUTTER_SPEED_FILE "shutter_speed.list"

#define SET_EXPOSURE_BIAS_COMPENSATION_FILE  "exposure_bias_compensation.set"
#define NFO_EXPOSURE_BIAS_COMPENSATION_FILE  "exposure_bias_compensation.nfo"
#define LIST_EXPOSURE_BIAS_COMPENSATION_FILE "exposure_bias_compensation.list"







#define TEMPORARY_FILE        "tmp.txt"


// FOCUS MODE
//
//
// focus mode codes
#define FOCUS_MODE_CODE        265U
#define FOCUS_MODE_VALUE_TYPE        8194U
#define FOCUS_MODE_TABLE_COUNT 5
typedef unsigned short FOCUS_MODE_TYPE;
FOCUS_MODE_TYPE FOCUS_MODE_TABLE_API_CODES[FOCUS_MODE_TABLE_COUNT] = {
    2,
    4,
    3,
    6,
    1,
};
char* FOCUS_MODE_TABLE_API_LIST[FOCUS_MODE_TABLE_COUNT] = {
    "Single-shot_AF",
    "Automatic_AF",
    "Continuous_AF",
    "DMF",
    "Manual_Focus"};
//
//
// FOCUS MODE

// SHOOTING MODE
//
//
// shooting mode codes
#define SHOOT_MODE_CODE        261U
#define SHOOT_MODE_VALUE_TYPE  8194U
#define SHOOT_MODE_TABLE_COUNT 5
typedef unsigned short SHOOT_MODE_TYPE;
SHOOT_MODE_TYPE SHOOT_MODE_TABLE_API_CODES[SHOOT_MODE_TABLE_COUNT] = {
    32768U,
    2,
    3,
    4,
    1};
    // 32772,
    // 32776,
    // 32775,
    // 32773,
    // 32774};
char* SHOOT_MODE_TABLE_API_LIST[SHOOT_MODE_TABLE_COUNT] = {
    "Intelligent_Auto",
    "Program_Auto",
    "Aperture_Priority",
    "Shuter_Priority",
    "Manual_Exposure"};
    // "Sunset",
    // "Night Scene",
    // "Portrait",
    // "Sport Action",
    // "Macro",
    // "Landscape"};
//
//
// SHOOTING MODE



// APERTURE
//
//
// aperture codes
#define SHUTTER_SPEED_CODE        259U
#define SHUTTER_SPEED_VALUE_TYPE  8195U
#define SHUTTER_SPEED_TABLE_COUNT 54
typedef unsigned int SHUTTER_SPEED_TYPE;
SHUTTER_SPEED_TYPE SHUTTER_SPEED_TABLE_API_CODES[SHUTTER_SPEED_TABLE_COUNT] = {
    0,
    4294967295U,
    19660810,
    16384010,
    13107210,
    9830410,
    8519690,
    6553610,
    5242890,
    3932170,
    3276810,
    2621450,
    2097162,
    1638410,
    1310730,
    1048586,
    851978,
    655370,
    524298,
    393226,
    327690,
    262154,
    65539,
    65540,
    65541,
    65542,
    65544,
    65546,
    65549,
    65551,
    65556,
    65561,
    65566,
    65576,
    65586,
    65596,
    65616,
    65636,
    65661,
    65696,
    65736,
    65786,
    65856,
    65936,
    66036,
    66176,
    66336,
    66536,
    66786,
    67136,
    67536,
    68036,
    68736,
    69536};
char* SHUTTER_SPEED_TABLE_API_LIST[SHUTTER_SPEED_TABLE_COUNT] = {
    "BULB",
    "nthg", 
    "30",
    "25",
    "20",
    "15",
    "13",
    "10",
    "8",
    "6",
    "5",
    "4",
    "3.2",
    "2.5",
    "2",
    "1.6",
    "1.3",
    "1",
    "0.8",
    "0.6",
    "0.5",
    "0.4",
    "1/3",
    "1/4",
    "1/5",
    "1/6",
    "1/8",
    "1/10",
    "1/13",
    "1/15",
    "1/20",
    "1/25",
    "1/30",
    "1/40",
    "1/50",
    "1/60",
    "1/80",
    "1/100",
    "1/125",
    "1/160",
    "1/200",
    "1/250",
    "1/320",
    "1/400",
    "1/500",
    "1/640",
    "1/800",
    "1/1000",
    "1/1250",
    "1/1600",
    "1/2000",
    "1/2500",
    "1/3200",
    "1/4000"};
//
//
// APERTURE



// SHUTTER SPEED
//
//
// shutter speed codes
#define APERTURE_CODE        256U
#define APERTURE_VALUE_TYPE  8194U
#define APERTURE_TABLE_COUNT 17
typedef unsigned short APERTURE_TYPE;
APERTURE_TYPE APERTURE_TABLE_API_CODES[APERTURE_TABLE_COUNT] = {
    560,
    630,
    710,
    800,
    900,
    1000,
    1100,
    1300,
    1400,
    1600,
    1800,
    2000,
    2200,
    2500,
    2900,
    3200,
    3600};
char* APERTURE_TABLE_API_LIST[APERTURE_TABLE_COUNT] = {
    "F5.6",
    "F6.3",
    "F7.1",
    "F8.0",
    "F9.0",
    "F10",
    "F11",
    "F13",
    "F14",
    "F16",
    "F18",
    "F20",
    "F22",
    "F25",
    "F29",
    "F32",
    "F36"};
//
//
// SHUTTER SPEED



// ISO
//
//
// iso codes
#define ISO_CODE        260U
#define ISO_VALUE_TYPE  8195U
#define ISO_TABLE_COUNT 35
typedef unsigned int ISO_TYPE;
ISO_TYPE ISO_TABLE_API_CODES[ISO_TABLE_COUNT] = {
    16777215, 268435506, 268435520, 268435536,
    100, 125, 160, 200,
    250, 320, 400, 500,
    640, 800, 1000, 1250,
    1600, 2000, 2500, 3200,
    4000, 5000, 6400, 8000,
    10000, 12800, 16000, 20000,
    25600, 32000, 268475456, 268486656,
    268499456, 268515456, 268537856};
char* ISO_TABLE_API_LIST[ISO_TABLE_COUNT] = {
    "auto",
    "50", "64", "80",
    "100", "125", "160", "200",
    "250", "320", "400", "500",
    "640", "800", "1000", "1250",
    "1600", "2000", "2500", "3200",
    "4000", "5000", "6400", "8000",
    "10000", "12800", "16000", "20000",
    "25600", "32000", "40000", "51200",
    "64000", "80000", "102400"};
//
//
// ISO



// EXPOSURE BIAS COMPENSATION
//
//
// exposure bias compensation
#define EXPOSURE_BIAS_COMPENSATION_CODE        257U
#define EXPOSURE_BIAS_COMPENSATION_VALUE_TYPE  12290U
#define EXPOSURE_BIAS_COMPENSATION_TABLE_COUNT 31
typedef short EXPOSURE_BIAS_COMPENSATION_TYPE;
EXPOSURE_BIAS_COMPENSATION_TYPE EXPOSURE_BIAS_COMPENSATION_TYPE_TABLE_API_CODES[EXPOSURE_BIAS_COMPENSATION_TABLE_COUNT] = { 
    5000,
    4700,
    4300,
    4000,
    3700,
    3300,
    3000,
    2700,
    2300,
    2000,
    1700,
    1300,
    1000,
    700,
    300,
    0,
    -300,
    -700,
    -1000,
    -1300,
    -1700,
    -2000,
    -2300,
    -2700,
    -3000,
    -3300,
    -3700,
    -4000,
    -4300,
    -4700,
    -5000};
char* EXPOSURE_BIAS_COMPENSATION_TYPE_TABLE_API_LIST[EXPOSURE_BIAS_COMPENSATION_TABLE_COUNT] = {
    "5.0",
    "4.7",
    "4.3",
    "4.0",
    "3.7",
    "3.3",
    "3.0",
    "2.7",
    "2.3",
    "2.0",
    "1.7",
    "1.3",
    "1.0",
    "0.7",
    "0.3",
    "0",
    "-0.3",
    "-0.7",
    "-1.0",
    "-1.3",
    "-1.7",
    "-2.0",
    "-2.3",
    "-2.7",
    "-3.0",
    "-3.3",
    "-3.7",
    "-4.0",
    "-4.3",
    "-4.7",
    "-5.0"
};
//
//
// EXPOSURE BIAS COMPENSATION



// WHITE BALANCE
//
//
// white balance codes
#define WHITE_BALANCE_CODE        
#define WHITE_BALANCE_VALUE_TYPE  8195U
#define WHITE_BALANCE_TABLE_COUNT 35
typedef  WHITE_BALANCE_TYPE;
WHITE_BALANCE_TYPE WHITE_BALANCE_TABLE_API_CODES[WHITE_BALANCE_TABLE_COUNT] = {
    16777215, 268435506, 268435520, 268435536,
    100, 125, 160, 200,
    250, 320, 400, 500,
    640, 800, 1000, 1250,
    1600, 2000, 2500, 3200,
    4000, 5000, 6400, 8000,
    10000, 12800, 16000, 20000,
    25600, 32000, 268475456, 268486656,
    268499456, 268515456, 268537856};
char* WHITE_BALANCE_TABLE_API_LIST[WHITE_BALANCE_TABLE_COUNT] = {
    "auto",
    "50", "64", "80",
    "100", "125", "160", "200",
    "250", "320", "400", "500",
    "640", "800", "1000", "1250",
    "1600", "2000", "2500", "3200",
    "4000", "5000", "6400", "8000",
    "10000", "12800", "16000", "20000",
    "25600", "32000", "40000", "51200",
    "64000", "80000", "102400"};
//
//
// ISO


#endif // SONY_PROPERTIES_TABLES_H