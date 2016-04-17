/*
 * Copyright (C) 2012 The Android Open Source Project
 * Copyright (C) 2016 Schischu
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

#define LOG_TAG "SEC PowerHAL"
#include <utils/Log.h>

#include <hardware/hardware.h>
#include <hardware/power.h>

#define BOOSTPULSE_PATH "/sys/devices/system/cpu/cpufreq/interactive/boostpulse"

typedef struct vendor_sec {
    pthread_mutex_t boost_mutex;
    int boost_fd;
    unsigned char boost_failed;
}

typedef struct power_sec_module {
    struct hw_module_t common;

    void (*init)(struct power_module *module);
    void (*setInteractive)(struct power_module *module, int on);
    void (*powerHint)(struct power_module *module, power_hint_t hint, void *data);

    struct vendor_sec sec;
} power_module_t;

/* OK 03/04/2016 */
static int sysfs_write(char const *path, char* value)
{
    int fd;
    int ret;

    fd = open(path, O_WRONLY);

    if (fd >= 0)
    {
        char buffer[20];

        ALOGD("sysfs_write +: %s: %s\n", path, value);

        int bytes = sprintf(buffer, "%d\n", value);
        int amt = write(fd, buffer, bytes);
        
        ALOGD("sysfs_write -: %s: %s\n", path, value);
        
        if (amt < 0)
        {
            ALOGE("!@sysfs_write : Error writing to %s: %s\n", path, strerror(errno));
        }

        close(fd);
    }
    else
    {
        ALOGE("sysfs_write : Error opening %s: %s\n", path, strerror(errno));
    }
    
    return 0;
}

/* OK 03/04/2016 */
static void power_hint(struct power_sec_module *module, power_hint_t hint,
                       void *data) {
    switch (hint) {
        case POWER_HINT_INTERACTION:
        {
            pthread_mutex_lock(&module->sec.boost_mutex);
            if (module->sec.boost_fd == -1)
            {
                module->sec.boost_fd = open(BOOSTPULSE_PATH, O_WRONLY);
                
                if (module->sec.boost_fd < 0 && module->sec.boost_failed == 0)
                {
                     ALOGE("Error opening %s: %s\n", BOOSTPULSE_PATH, strerror(errno));
                     module->sec.boost_failed = 1;
                }
            }

            pthread_mutex_unlock(&module->sec.boost_mutex);

            if (module->sec.boost_fd >= 0)
            {
                if (write(module->sec.boost_fd, "1", 1) < 0)
                {
                    ALOGE("Error writing to %s: %s\n", BOOSTPULSE_PATH, strerror(errno));
                }
            }

            break;
        }
        default:
            break;
    }

    return 0;
}

/* OK 03/04/2016 */
int power_init()
{
    sysfs_write("/sys/devices/system/cpu/cpufreq/interactive/multi_enter_load", "360");
    sysfs_write("/sys/devices/system/cpu/cpufreq/interactive/multi_enter_time", "99000");
    sysfs_write("/sys/devices/system/cpu/cpufreq/interactive/multi_exit_load", "240");
    sysfs_write("/sys/devices/system/cpu/cpufreq/interactive/multi_exit_time", "299000");
    sysfs_write("/sys/devices/system/cpu/cpufreq/interactive/single_enter_load", "95");
    sysfs_write("/sys/devices/system/cpu/cpufreq/interactive/single_enter_time", "199000");
    sysfs_write("/sys/devices/system/cpu/cpufreq/interactive/single_exit_load", "60");
    sysfs_write("/sys/devices/system/cpu/cpufreq/interactive/single_exit_time", "99000");
    sysfs_write("/sys/devices/system/cpu/cpufreq/interactive/param_index", "0");
    sysfs_write("/sys/devices/system/cpu/cpufreq/interactive/timer_rate", "20000");
    sysfs_write("/sys/devices/system/cpu/cpufreq/interactive/timer_slack", "20000");
    sysfs_write("/sys/devices/system/cpu/cpufreq/interactive/min_sample_time", "40000");
    sysfs_write("/sys/devices/system/cpu/cpufreq/interactive/hispeed_freq", "600000");
    sysfs_write("/sys/devices/system/cpu/cpufreq/interactive/go_hispeed_load", "99");
    sysfs_write("/sys/devices/system/cpu/cpufreq/interactive/target_loads", "70 600000:70 800000:75 1500000:80 1700000:90");
    sysfs_write("/sys/devices/system/cpu/cpufreq/interactive/above_hispeed_delay", "20000 1000000:80000 1200000:100000 1700000:20000");
    sysfs_write("/sys/devices/system/cpu/cpufreq/interactive/boostpulse_duration", "40000");
    sysfs_write("/sys/devices/system/cpu/cpufreq/interactive/param_index", "1");
    sysfs_write("/sys/devices/system/cpu/cpufreq/interactive/above_hispeed_delay", "19000");
    sysfs_write("/sys/devices/system/cpu/cpufreq/interactive/go_hispeed_load", "95");
    sysfs_write("/sys/devices/system/cpu/cpufreq/interactive/hispeed_freq", "650000");
    sysfs_write("/sys/devices/system/cpu/cpufreq/interactive/min_sample_time", "59000");
    sysfs_write("/sys/devices/system/cpu/cpufreq/interactive/target_loads", "58 800000:65 1400000:70 1700000:80");
    sysfs_write("/sys/devices/system/cpu/cpufreq/interactive/timer_rate", "20000");
    sysfs_write("/sys/devices/system/cpu/cpufreq/interactive/param_index", "2");
    sysfs_write("/sys/devices/system/cpu/cpufreq/interactive/above_hispeed_delay", "19000");
    sysfs_write("/sys/devices/system/cpu/cpufreq/interactive/go_hispeed_load", "90");
    sysfs_write("/sys/devices/system/cpu/cpufreq/interactive/hispeed_freq", "1300000");
    sysfs_write("/sys/devices/system/cpu/cpufreq/interactive/min_sample_time", "79000");
    sysfs_write("/sys/devices/system/cpu/cpufreq/interactive/target_loads", "55 800000:65 1500000:70");
    sysfs_write("/sys/devices/system/cpu/cpufreq/interactive/timer_rate", "20000");
    sysfs_write("/sys/devices/system/cpu/cpufreq/interactive/param_index", "3");
    sysfs_write("/sys/devices/system/cpu/cpufreq/interactive/above_hispeed_delay", "19000");
    sysfs_write("/sys/devices/system/cpu/cpufreq/interactive/go_hispeed_load", "85");
    sysfs_write("/sys/devices/system/cpu/cpufreq/interactive/hispeed_freq", "1400000");
    sysfs_write("/sys/devices/system/cpu/cpufreq/interactive/min_sample_time", "99000");
    sysfs_write("/sys/devices/system/cpu/cpufreq/interactive/target_loads", "50 1200000:60 1600000:70");
    sysfs_write("/sys/devices/system/cpu/cpufreq/interactive/timer_rate", "20000");
    sysfs_write("/sys/devices/system/cpu/cpufreq/interactive/param_index", "0");

    return 0;
}

/* OK 03/04/2016 */
static struct hw_module_methods_t power_module_methods = {
    .open = NULL,
};

/* OK 03/04/2016 */
struct power_sec_module HAL_MODULE_INFO_SYM = {
    .common = {
        .tag                = HARDWARE_MODULE_TAG, /*H W M T*/
        .module_api_version = POWER_MODULE_API_VERSION_0_2, /* 0 2*/
        .hal_api_version    = HARDWARE_HAL_API_VERSION, /*1 0*/
        .id                 = POWER_HARDWARE_MODULE_ID, /*"power"*/
        .name               = "SEC Power HAL",
        .author             = "The Android Open Source Project",
        .methods            = &power_module_methods,
    },

    .init = power_init,
    .setInteractive = NULL,
    .powerHint = power_hint,
    .sec = {
        .boost_mutex = PTHREAD_MUTEX_INITIALIZER,
        .boost_fd    = -1;
        .boost_failed  = 0;
    }
};
