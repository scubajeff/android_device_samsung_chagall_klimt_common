/*
 * Copyright (C) 2012 The Android Open Source Project
 * Copyright (C) 2014, The CyanogenMod Project <http://www.cyanogenmod.org>
 * Copyright (C) 2016, Schischu
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>

#define LOG_TAG "Chagall Klimt PowerHAL"
#include <utils/Log.h>

#include <hardware/hardware.h>
#include <hardware/power.h>

/* Have SEC Power HAL features */
#define HAVE_VENDOR_SEC

#define BOOSTPULSE_PATH "/sys/devices/system/cpu/cpufreq/interactive/boostpulse"

char tspPowerPath[255] = {0};
char tspWakeGesturePath[255] = {0};

char gkpPowerPath[255] = {0};
char tkpPowerPath[255] = {0};

static unsigned char wake_gesture_enabled = 0;

#ifdef HAVE_VENDOR_SEC
pthread_mutex_t boost_mutex   = PTHREAD_MUTEX_INITIALIZER;
int             boost_fd      = -1;
unsigned char   boost_failed  = 0;
#endif /*HAVE_VENDOR_SEC*/

static int write_string(char const *path, char* value)
{
  int fd;
  static int already_warned;

  already_warned = 0;

  //ALOGE("write_int called: path %s, value %d", path, value);
  fd = open(path, O_RDWR);

  if (fd >= 0) {
    int bytes = strlen(value);
    //ALOGE("write_int before write: path %s, value %s", path, buffer);
    int amt = write(fd, value, bytes);
    close(fd);
    return amt == -1 ? -errno : 0;
  }
  else {
    if (already_warned == 0) {
      ALOGE("write_int failed to open %s\n", path);
      already_warned = 1;
    }
    return -errno;
  }
}

static int write_int(char const *path, int value)
{
  char buffer[64];
  sprintf(buffer, "%d\n", value);

  return write_string(path, buffer);
}

static void power_init(struct power_module *module)
{
  int fd;
  int count;
  char path[255];
  char name[255];
  uint8_t i;

  for (i=0; i < 20; i++) {
    sprintf(path, "/sys/class/input/input%u/name", i);

    fd = open(path, O_RDONLY);
    if (fd >= 0) {
      count = read(fd, name, 254);
      if (count > 0) {
        name[count-1] = '\0';
        if (!strncmp("sec_touchscreen", name, 15)) {
          sprintf(tspPowerPath, "/sys/class/input/input%u/enabled", i);
          sprintf(tspWakeGesturePath, "/sys/class/input/input%u/wake_gesture", i);
        }
        else if (!strncmp("gpio-keys", name, 9)) {
          sprintf(gkpPowerPath, "/sys/class/input/input%u/enabled", i);
        }
        else if (!strncmp("sec_touchkey", name, 12)) {
          sprintf(tkpPowerPath, "/sys/class/input/input%u/enabled", i);
        }
        else {
          ALOGI("%s: Unknown device \"%s\"", __func__, name);
        }
      }
      else {
        ALOGW("%s: Could not read \"%s\"", __func__, path);
      }
    }
    else {
      ALOGW("%s: Could not open \"%s\"", __func__, path);
    }
  }

  ALOGI("%s: %s -> \"%s\"", __func__, "TSP_POWER", tspPowerPath);
  ALOGI("%s: %s -> \"%s\"", __func__, "TSP_WAKE_GESTURE", tspWakeGesturePath);
  ALOGI("%s: %s -> \"%s\"", __func__, "GKP_POWER", gkpPowerPath);
  ALOGI("%s: %s -> \"%s\"", __func__, "TKP_POWER", tkpPowerPath);

#ifdef HAVE_VENDOR_SEC
  write_int("/sys/devices/system/cpu/cpufreq/interactive/multi_enter_load",  360);
  write_int("/sys/devices/system/cpu/cpufreq/interactive/multi_enter_time",  99000);
  write_int("/sys/devices/system/cpu/cpufreq/interactive/multi_exit_load",   240);
  write_int("/sys/devices/system/cpu/cpufreq/interactive/multi_exit_time",   299000);
  write_int("/sys/devices/system/cpu/cpufreq/interactive/single_enter_load", 95);
  write_int("/sys/devices/system/cpu/cpufreq/interactive/single_enter_time", 199000);
  write_int("/sys/devices/system/cpu/cpufreq/interactive/single_exit_load",  60);
  write_int("/sys/devices/system/cpu/cpufreq/interactive/single_exit_time",  99000);
  write_int("/sys/devices/system/cpu/cpufreq/interactive/param_index",       0);
  write_int("/sys/devices/system/cpu/cpufreq/interactive/timer_rate",        20000);
  write_int("/sys/devices/system/cpu/cpufreq/interactive/timer_slack",       20000);
  write_int("/sys/devices/system/cpu/cpufreq/interactive/min_sample_time",   40000);
  write_int("/sys/devices/system/cpu/cpufreq/interactive/hispeed_freq",      600000);
  write_int("/sys/devices/system/cpu/cpufreq/interactive/go_hispeed_load",   99);

  write_string("/sys/devices/system/cpu/cpufreq/interactive/target_loads",        "70 600000:70 800000:75 1500000:80 1700000:90");
  write_string("/sys/devices/system/cpu/cpufreq/interactive/above_hispeed_delay", "20000 1000000:80000 1200000:100000 1700000:20000");

  write_int("/sys/devices/system/cpu/cpufreq/interactive/boostpulse_duration", 40000);
  write_int("/sys/devices/system/cpu/cpufreq/interactive/param_index",         1);
  write_int("/sys/devices/system/cpu/cpufreq/interactive/above_hispeed_delay", 19000);
  write_int("/sys/devices/system/cpu/cpufreq/interactive/go_hispeed_load",     95);
  write_int("/sys/devices/system/cpu/cpufreq/interactive/hispeed_freq",        650000);
  write_int("/sys/devices/system/cpu/cpufreq/interactive/min_sample_time",     59000);

  write_string("/sys/devices/system/cpu/cpufreq/interactive/target_loads", "58 800000:65 1400000:70 1700000:80");

  write_int("/sys/devices/system/cpu/cpufreq/interactive/timer_rate",          20000);
  write_int("/sys/devices/system/cpu/cpufreq/interactive/param_index",         2);
  write_int("/sys/devices/system/cpu/cpufreq/interactive/above_hispeed_delay", 19000);
  write_int("/sys/devices/system/cpu/cpufreq/interactive/go_hispeed_load",     90);
  write_int("/sys/devices/system/cpu/cpufreq/interactive/hispeed_freq",        1300000);
  write_int("/sys/devices/system/cpu/cpufreq/interactive/min_sample_time",     79000);

  write_string("/sys/devices/system/cpu/cpufreq/interactive/target_loads", "55 800000:65 1500000:70");

  write_int("/sys/devices/system/cpu/cpufreq/interactive/timer_rate",          20000);
  write_int("/sys/devices/system/cpu/cpufreq/interactive/param_index",         3);
  write_int("/sys/devices/system/cpu/cpufreq/interactive/above_hispeed_delay", 19000);
  write_int("/sys/devices/system/cpu/cpufreq/interactive/go_hispeed_load",     85);
  write_int("/sys/devices/system/cpu/cpufreq/interactive/hispeed_freq",        1400000);
  write_int("/sys/devices/system/cpu/cpufreq/interactive/min_sample_time",     99000);

  write_string("/sys/devices/system/cpu/cpufreq/interactive/target_loads", "50 1200000:60 1600000:70");

  write_int("/sys/devices/system/cpu/cpufreq/interactive/timer_rate",  20000);
  write_int("/sys/devices/system/cpu/cpufreq/interactive/param_index", 0);
#endif /*HAVE_VENDOR_SEC*/

}

static void power_set_interactive(struct power_module *module, int on)
{
    ALOGE("%s: %s input devices", __func__, on ? "enabling" : "disabling");

    if (on)
        write_int(tspPowerPath, 1);
    else if (on == 0 && wake_gesture_enabled == 0)
        write_int(tspPowerPath, 0);

    if (wake_gesture_enabled) {
      if (on)
        write_int(tspWakeGesturePath, 0);
      else
        write_int(tspWakeGesturePath, 1);
    }
    
    
    if (on) {
        write_int(gkpPowerPath, 1);
        write_int(tkpPowerPath, 1);
    }
    else {
        //write_int(GKP_POWER, 0); /*Do not power down as home key is wakeupsignal*/
        write_int(tkpPowerPath, 0);
    }
}

static void power_hint(struct power_module *module, power_hint_t hint,
                       void *data) {
    switch (hint) {
        case POWER_HINT_VSYNC:
            //ALOGE("%s: vsync", __func__);
            break;
        case POWER_HINT_INTERACTION:
            //ALOGE("%s: interaction", __func__);

#ifdef HAVE_VENDOR_SEC
            pthread_mutex_lock(&boost_mutex);
            if (boost_fd == -1)
            {
                boost_fd = open(BOOSTPULSE_PATH, O_WRONLY);
                
                if (boost_fd < 0 && boost_failed == 0)
                {
                     ALOGE("Error opening %s: %s\n", BOOSTPULSE_PATH, strerror(errno));
                     boost_failed = 1;
                }
            }

            pthread_mutex_unlock(&boost_mutex);

            if (boost_fd >= 0)
            {
                if (write(boost_fd, "1", 1) < 0)
                {
                    ALOGE("Error writing to %s: %s\n", BOOSTPULSE_PATH, strerror(errno));
                }
            }
#endif /*HAVE_VENDOR_SEC*/

            break;
        case POWER_HINT_LOW_POWER:
            //ALOGE("%s: low power", __func__);
            break;
        default:
            break;
    }
}

static void power_set_feature(struct power_module *module, feature_t feature, int state)
{
    switch (feature) {
        case POWER_FEATURE_DOUBLE_TAP_TO_WAKE:
            ALOGE("%s: %s double tap to wake", __func__, state ? "enabling" : "disabling");
            wake_gesture_enabled = state>0?1:0;
            break;
        default:
            break;
    }
}

static struct hw_module_methods_t power_module_methods = {
    .open = NULL,
};

struct power_module HAL_MODULE_INFO_SYM = {
    .common = {
        .tag                = HARDWARE_MODULE_TAG,
        .module_api_version = POWER_MODULE_API_VERSION_0_3,
        .hal_api_version    = HARDWARE_HAL_API_VERSION,
        .id                 = POWER_HARDWARE_MODULE_ID,
        .name               = "Chagall Klimt Power HAL",
        .author             = "The CyanogenMod Project",
        .methods            = &power_module_methods,
    },

    .init = power_init,
    .setInteractive = power_set_interactive,
    .powerHint = power_hint,
    .setFeature = power_set_feature,
};
