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




#define TEMPORARY_FILE        "tmp.txt"


// FOCUS MODE
//
//
// focus mode codes
#define FOCUS_MODE_CODE        265U
#define FOCUS_MODE_TYPE        8194U
#define FOCUS_MODE_TABLE_COUNT 5
unsigned int FOCUS_MODE_TABLE_API_CODES[FOCUS_MODE_TABLE_COUNT] = {
    2,
    4,
    3,
    6,
    1,
};
char* FOCUS_MODE_TABLE_API_LIST[FOCUS_MODE_TABLE_COUNT] = {
    "Single-shot AF",
    "Automatic AF",
    "Continuous AF",
    "DMF",
    "Manual Focus"};
//
//
// FOCUS MODE

// SHOOTING MODE
//
//
// shooting mode codes
#define SHOOT_MODE_CODE        261U
#define SHOOT_MODE_VALUE_TYPE  8194U
#define SHOOT_MODE_TABLE_COUNT 11
unsigned int SHOOT_MODE_TABLE_API_CODES[SHOOT_MODE_TABLE_COUNT] = {
    32768,
    2,
    3,
    4,
    1,
    7,
    32772,
    32776,
    32775,
    32773,
    32774};
char* SHOOT_MODE_TABLE_API_LIST[SHOOT_MODE_TABLE_COUNT] = {
    "Intelligent Auto",
    "Program Auto",
    "Aperture Priority",
    "Shuter Priority",
    "Manual Exposure",
    "Sunset",
    "Night Scene",
    "Portrait",
    "Sport Action",
    "Macro",
    "Landscape"};
//
//
// SHOOTING MODE




// ISO
//
//
// iso codes
#define ISO_CODE        260U
#define ISO_VALUE_TYPE  8195U
#define ISO_TABLE_COUNT 35
unsigned int ISO_TABLE_API_CODES[ISO_TABLE_COUNT] = {
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

#endif // SONY_PROPERTIES_TABLES_H