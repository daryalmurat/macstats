/*
 * Apple System Management Control (SMC) Tool
 * Copyright (C) 2006 devnull
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef SMC_H
#define SMC_H

#include <cstdint>
#include <CoreFoundation/CoreFoundation.h>

#define VERSION               "0.01"

#define KERNEL_INDEX_SMC      2

#define SMC_CMD_READ_BYTES    5
#define SMC_CMD_WRITE_BYTES   6
#define SMC_CMD_READ_INDEX    8
#define SMC_CMD_READ_KEYINFO  9
#define SMC_CMD_READ_PLIMIT   11
#define SMC_CMD_READ_VERS     12

#define DATATYPE_FPE2         "fpe2"
#define DATATYPE_UINT8        "ui8 "
#define DATATYPE_UINT16       "ui16"
#define DATATYPE_UINT32       "ui32"
#define DATATYPE_SP78         "sp78"
#define DATATYPE_FLT          "flt "

// key values
#define SMC_KEY_CPU_TEMP      "TC0P"
#define SMC_KEY_FAN_SPEED     "F%dAc"
#define SMC_KEY_MIN_FAN_SPEED "F%dMn"
#define SMC_KEY_MAX_FAN_SPEED "F%dMx"
#define SMC_KEY_FAN_NUM       "FNum"
#define SMC_KEY_BATTERY_TEMP  "TB0T"

typedef struct {
    char                  major;
    char                  minor;
    char                  build;
    char                  reserved[1];
    u_int16_t                release;
} SMCKeyData_vers_t;

typedef struct {
    u_int16_t                version;
    u_int16_t                length;
    u_int32_t                cpuPLimit;
    u_int32_t                gpuPLimit;
    u_int32_t                memPLimit;
} SMCKeyData_pLimitData_t;

typedef struct {
    u_int32_t                dataSize;
    u_int32_t                dataType;
    char                  dataAttributes;
} SMCKeyData_keyInfo_t;

typedef char              SMCBytes_t[32];

typedef struct {
    u_int32_t                  key;
    SMCKeyData_vers_t       vers;
    SMCKeyData_pLimitData_t pLimitData;
    SMCKeyData_keyInfo_t    keyInfo;
    char                    result;
    char                    status;
    char                    data8;
    u_int32_t                  data32;
    SMCBytes_t              bytes;
} SMCKeyData_t;

typedef char              UInt32Char_t[5];

typedef struct {
    UInt32Char_t            key;
    u_int32_t                  dataSize;
    UInt32Char_t            dataType;
    SMCBytes_t              bytes;
} SMCVal_t;

typedef union _data {
    float f;
    char  b[4];
} fltUnion;

// prototypes
float SMCGetFanSpeed(int fanNum);
int SMCGetFanNumber(char *key);
double SMCGetTemperature(char *key);
const char* SMCGetBatteryHealth();
int SMCGetDesignCycleCount();
int SMCGetBatteryCharge();
int SMCGetBatteryMaxChargeCapacity();
int SMCGetBatteryCurrentChargeCapacity();
kern_return_t SMCOpen(void);
kern_return_t SMCClose();


#endif // SMC_H
