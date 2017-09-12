/* // device/libs/telephony/ril_unsol_commands.h
**
** Copyright 2006, The Android Open Source Project
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
**     http:// www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
*/
    {SAMSUNG_UNSOL_RESPONSE_BASE, NULL, WAKE_PARTIAL}, // 11000
    {RIL_UNSOL_RELEASE_COMPLETE_MESSAGE, responseVoid, WAKE_PARTIAL}, // 11001
    {RIL_UNSOL_STK_SEND_SMS_RESULT, responseInts, WAKE_PARTIAL}, // 11002
    {RIL_UNSOL_STK_CALL_CONTROL_RESULT, responseString, WAKE_PARTIAL}, // 11003
    {11004, NULL, WAKE_PARTIAL}, // 11004
    {RIL_UNSOL_ACB_INFO_CHANGED, responseInts, WAKE_PARTIAL}, // 11005
    {11006, NULL, WAKE_PARTIAL}, // 11006
    {11007, NULL, WAKE_PARTIAL}, // 11007
    {RIL_UNSOL_DEVICE_READY_NOTI, responseVoid, WAKE_PARTIAL}, // 11008
    {RIL_UNSOL_GPS_NOTI, responseVoid, WAKE_PARTIAL}, // 11009
    {RIL_UNSOL_AM, responseString, WAKE_PARTIAL}, // 11010
    {RIL_UNSOL_DUN_PIN_CONTROL_SIGNAL, responseVoid, WAKE_PARTIAL}, // 11011
    {RIL_UNSOL_DATA_SUSPEND_RESUME, responseInts, WAKE_PARTIAL}, // 11012
    {RIL_UNSOL_SAP, responseRaw, WAKE_PARTIAL}, // 11013
    {11014, NULL, WAKE_PARTIAL},
    {11015, NULL, WAKE_PARTIAL}, // 11015
    {11016, NULL, WAKE_PARTIAL}, // 11016
    {RIL_UNSOL_WB_AMR_STATE, responseInts, WAKE_PARTIAL}, // 11017
    {11018, NULL, WAKE_PARTIAL}, // 11018
    {11019, NULL, WAKE_PARTIAL}, // 11019
    {RIL_UNSOL_UART, responseRaw, WAKE_PARTIAL}, // 11020
    {RIL_UNSOL_SIM_PB_READY, responseVoid, WAKE_PARTIAL}, // 11021
    {11022, NULL, WAKE_PARTIAL}, // 11022
    {11023, NULL, WAKE_PARTIAL}, // 11023
    {RIL_UNSOL_VE, responseRaw, WAKE_PARTIAL}, // 11024
    {11025, NULL, WAKE_PARTIAL}, // 11025
    {RIL_UNSOL_FACTORY_AM, responseVoid, WAKE_PARTIAL}, // 11026
    {10027, NULL, WAKE_PARTIAL}, // 11027
    {RIL_UNSOL_MODIFY_CALL, responseVoid, WAKE_PARTIAL}, // 11028
    {RIL_UNSOL_SRVCC_HANDOVER, responseVoid, WAKE_PARTIAL}, // 11029
    {RIL_UNSOL_CS_FALLBACK, responseInts, WAKE_PARTIAL}, // 11030
    {11031, NULL, WAKE_PARTIAL}, // 11031
    {RIL_UNSOL_VOICE_SYSTEM_ID, responseInts, WAKE_PARTIAL}, // 11032
    {11033, NULL, WAKE_PARTIAL}, // 11033
    {RIL_UNSOL_IMS_RETRYOVER, responseVoid, WAKE_PARTIAL}, // 11034
    {RIL_UNSOL_PB_INIT_COMPLETE, responseVoid, WAKE_PARTIAL}, // 11035
    {11036, NULL, WAKE_PARTIAL}, // 11036
    {RIL_UNSOL_HYSTERESIS_DCN, responseVoid, WAKE_PARTIAL}, // 11037
    {RIL_UNSOL_CP_POSITION, responseVoid, WAKE_PARTIAL}, // 11038
    {11039, NULL, WAKE_PARTIAL}, // 11039
    {11040, NULL, WAKE_PARTIAL}, // 11040
    {11041, NULL, WAKE_PARTIAL}, // 11041
    {11042, NULL, WAKE_PARTIAL}, // 11042
    {RIL_UNSOL_HOME_NETWORK_NOTI, responseVoid, WAKE_PARTIAL}, // 11043
    {11044, NULL, WAKE_PARTIAL}, // 11044
    {11045, NULL, WAKE_PARTIAL}, // 11045
    {11046, NULL, WAKE_PARTIAL}, // 11046
    {11047, NULL, WAKE_PARTIAL}, // 11047
    {11048, NULL, WAKE_PARTIAL}, // 11048
    {11049, NULL, WAKE_PARTIAL}, // 11049
    {11050, NULL, WAKE_PARTIAL}, // 11050
    {11051, NULL, WAKE_PARTIAL}, // 11051
    {11052, NULL, WAKE_PARTIAL}, // 11052
    {11053, NULL, WAKE_PARTIAL}, // 11053
    {RIL_UNSOL_STK_CALL_STATUS, responseInts, WAKE_PARTIAL}, // 11054
    {11055, NULL, WAKE_PARTIAL}, // 11055
    {RIL_UNSOL_MODEM_CAP, responseRaw, WAKE_PARTIAL}, // 11056
    {RIL_UNSOL_SIM_SWAP_STATE_CHANGED, responseInts, WAKE_PARTIAL}, // 11057
    {RIL_UNSOL_SIM_COUNT_MISMATCHED, responseInts, WAKE_PARTIAL}, // 11058
    {11059, NULL, WAKE_PARTIAL}, // 11059
    {RIL_UNSOL_DUN, responseString, WAKE_PARTIAL}, // 11060
    {RIL_UNSOL_IMS_PREFERENCE_CHANGED, responseInts, WAKE_PARTIAL}, // 11061
    {RIL_UNSOL_SIM_APPLICATION_REFRESH, responseInts, WAKE_PARTIAL}, // 11062
    {RIL_UNSOL_UICC_APPLICATION_STATUS, responseVoid, WAKE_PARTIAL}, // 11063
    {RIL_UNSOL_VOICE_RADIO_BEARER_HO_STATUS, responseInts, WAKE_PARTIAL}, // 11064
    {RIL_UNSOL_CLM_NOTI, responseVoid, WAKE_PARTIAL}, // 11065
    {RIL_UNSOL_SIM_ICCID_NOTI, responseString, WAKE_PARTIAL}, // 11066
    {RIL_UNSOL_TIMER_STATUS_CHANGED_NOTI, responseInts, WAKE_PARTIAL}, // 11067
