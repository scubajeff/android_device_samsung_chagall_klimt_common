#
# Copyright (C) 2015 Schischu
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

COMMON_PATH := device/samsung/chagall-klimt-common

# Ramdisk
PRODUCT_PACKAGES += \
    init.samsung.rc \
    init.universal5420.rc \
    init.universal5420.usb.rc \
    init.universal5420.wifi.rc \
    fstab.universal5420 \
    ueventd.universal5420.rc

# Keylayouts
PRODUCT_COPY_FILES += \
    $(COMMON_PATH)/keylayout/sec_touchkey.kl:system/usr/keylayout/sec_touchkey.kl \
    $(COMMON_PATH)/keylayout/gpio-keys.kl:system/usr/keylayout/gpio-keys.kl

# IDC
PRODUCT_COPY_FILES += \
    $(COMMON_PATH)/idc/Synaptics_HID_TouchPad.idc:system/usr/idc/Synaptics_HID_TouchPad.idc

# Audio
PRODUCT_PACKAGES += \
    audio.primary.universal5420 \
    audio.a2dp.default \
    audio.usb.default \
    audio.r_submix.default \
    tinymix

# Audio
PRODUCT_COPY_FILES += \
    $(COMMON_PATH)/audio/audio_effects.conf:system/etc/audio_effects.conf

# Media profile
PRODUCT_COPY_FILES += \
	frameworks/av/media/libstagefright/data/media_codecs_google_audio.xml:system/etc/media_codecs_google_audio.xml \
	frameworks/av/media/libstagefright/data/media_codecs_google_telephony.xml:system/etc/media_codecs_google_telephony.xml \
	frameworks/av/media/libstagefright/data/media_codecs_google_video.xml:system/etc/media_codecs_google_video.xml \
    $(COMMON_PATH)/media/media_codecs.xml:system/etc/media_codecs.xml \
    $(COMMON_PATH)/media/media_codecs_ffmpeg.xml:system/etc/media_codecs_ffmpeg.xml \
    $(COMMON_PATH)/media/media_codecs_performance.xml:system/etc/media_codecs_performance.xml \
    $(COMMON_PATH)/media/media_profiles.xml:system/etc/media_profiles.xml

# Permissions
PRODUCT_COPY_FILES += \
    frameworks/native/data/etc/android.hardware.camera.flash-autofocus.xml:system/etc/permissions/android.hardware.camera.flash-autofocus.xml \
    frameworks/native/data/etc/android.hardware.camera.front.xml:system/etc/permissions/android.hardware.camera.front.xml \
    frameworks/native/data/etc/android.hardware.consumerir.xml:system/etc/permissions/android.hardware.consumerir.xml \
    frameworks/native/data/etc/android.hardware.location.gps.xml:system/etc/permissions/android.hardware.location.gps.xml \
    frameworks/native/data/etc/android.hardware.wifi.xml:system/etc/permissions/android.hardware.wifi.xml \
    frameworks/native/data/etc/android.hardware.wifi.direct.xml:system/etc/permissions/android.hardware.wifi.direct.xml \
    frameworks/native/data/etc/android.hardware.sensor.accelerometer.xml:system/etc/permissions/android.hardware.sensor.accelerometer.xml \
    frameworks/native/data/etc/android.hardware.sensor.proximity.xml:system/etc/permissions/android.hardware.sensor.proximity.xml \
    frameworks/native/data/etc/android.hardware.sensor.light.xml:system/etc/permissions/android.hardware.sensor.light.xml \
    frameworks/native/data/etc/android.hardware.sensor.compass.xml:system/etc/permissions/android.hardware.sensor.compass.xml \
    frameworks/native/data/etc/android.hardware.sensor.gyroscope.xml:system/etc/permissions/android.hardware.sensor.gyroscope.xml \
	frameworks/native/data/etc/android.hardware.sensor.barometer.xml:system/etc/permissions/android.hardware.sensor.barometer.xml \
    frameworks/native/data/etc/android.hardware.sensor.stepdetector.xml:system/etc/permissions/android.hardware.sensor.stepdetector.xml \
    frameworks/native/data/etc/android.hardware.sensor.stepcounter.xml:system/etc/permissions/android.hardware.sensor.stepcounter.xml \
    frameworks/native/data/etc/android.hardware.touchscreen.multitouch.distinct.xml:system/etc/permissions/android.hardware.touchscreen.multitouch.distinct.xml \
    frameworks/native/data/etc/android.hardware.usb.accessory.xml:system/etc/permissions/android.hardware.usb.accessory.xml \
    frameworks/native/data/etc/android.hardware.usb.host.xml:system/etc/permissions/android.hardware.usb.host.xml \
    frameworks/native/data/etc/android.hardware.audio.low_latency.xml:system/etc/permissions/android.hardware.audio.low_latency.xml \
    frameworks/native/data/etc/android.hardware.bluetooth_le.xml:system/etc/permissions/android.hardware.bluetooth_le.xml \
    frameworks/native/data/etc/android.hardware.bluetooth.xml:system/etc/permissions/android.hardware.bluetooth.xml \
    frameworks/native/data/etc/android.software.webview.xml:system/etc/permissions/android.software.webview.xml \
    frameworks/native/data/etc/android.software.app_widgets.xml:system/etc/permissions/android.software.app_widgets.xml \
    frameworks/native/data/etc/android.software.freeform_window_management.xml:system/etc/permissions/android.software.freeform_window_management.xml
#    frameworks/native/data/etc/android.hardware.fingerprint.xml:system/etc/permissions/android.hardware.fingerprint.xml \

PRODUCT_AAPT_CONFIG := normal hdpi xhdpi xxhdpi
PRODUCT_AAPT_PREF_CONFIG := xhdpi

PRODUCT_CHARACTERISTICS := tablet

DEVICE_PACKAGE_OVERLAYS := \
    $(COMMON_PATH)/overlay-common

# Wifi
PRODUCT_COPY_FILES += \
    $(COMMON_PATH)/wifi/wpa_supplicant.conf:system/etc/wifi/wpa_supplicant.conf \
    $(COMMON_PATH)/wifi/wpa_supplicant_overlay.conf:system/etc/wifi/wpa_supplicant_overlay.conf \
    $(COMMON_PATH)/wifi/p2p_supplicant_overlay.conf:system/etc/wifi/p2p_supplicant_overlay.conf

PRODUCT_PACKAGES += \
    libwpa_client \
    hostapd \
    dhcpcd.conf \
    wpa_supplicant \
    hostapd_default.conf

# Live Wallpapers
PRODUCT_PACKAGES += \
    LiveWallpapersPicker \
    librs_jni

# Exchange
PRODUCT_PACKAGES += \
    Exchange

# OMX
PRODUCT_PACKAGES += \
    libcsc \
    libOMX.Exynos.WMV.Decoder \
    libOMX.Exynos.MPEG2.Decoder

# Camera
PRODUCT_PACKAGES += \
    camera.universal5420 \
    libhwjpeg
#As long as we have no source for this, do not install
#    libexynoscamera

# HW composer
PRODUCT_PACKAGES += \
    libion \
    gralloc.exynos5 \

# Stlport
PRODUCT_PACKAGES += \
    libstlport

PRODUCT_PACKAGES += \
    consumerir.universal5420

#PRODUCT_PACKAGES += \
    fingerprintd \
    fingerprint.universal5420 \
    ValidityService

#Needed for at least adb on userbuild
PRODUCT_PACKAGES += \
    keystore.exynos5

# Power
PRODUCT_PACKAGES += \
    power.universal5420

PRODUCT_PACKAGES += \
    lights.universal5420

# Filesystem management tools
PRODUCT_PACKAGES += \
    e2fsck

# If using cm vold we support exfat and ntfs
PRODUCT_PACKAGES += \
    libfuse \
    libexfat \
    fsck.exfat \
    mkfs.exfat \
	mount.exfat \
    libntfs-3g \
    fsck.ntfs \
    mkfs.ntfs \
	mount.ntfs

# Charger
PRODUCT_PACKAGES += \
    charger_res_images

# MobiCore setup
PRODUCT_PACKAGES += \
    libMcClient \
    libMcRegistry \
    libPaApi \
    libgdmcprov

# Network tools
PRODUCT_PACKAGES += \
    libpcap \
    tcpdump

# Radio (needed for audio controls even on wifi-only)
PRODUCT_PACKAGES += \
    libsecril-client \
    libsecril-client-sap

# Recovery
PRODUCT_PACKAGES += \
    init.recovery.universal5420.rc

# Sensors
PRODUCT_PACKAGES += \
    sensors.universal5420

PRODUCT_PACKAGES += \
    libnetcmdiface \
	wifiloader
#    macloader

PRODUCT_PROPERTY_OVERRIDES += \
    ro.sf.lcd_density=320

PRODUCT_PROPERTY_OVERRIDES += \
    ro.carrier=unknown

# CPU producer to CPU consumer not supported
PRODUCT_PROPERTY_OVERRIDES += \
    ro.bq.gpu_to_cpu_unsupported=1

# Dex2oat optimizations
ADDITIONAL_DEFAULT_PROPERTIES += \
    ro.sys.fw.dex2oat_thread_count=4

PRODUCT_PROPERTY_OVERRIDES += \
    dalvik.vm.dex2oat-filter=speed \
    dalvik.vm.dex2oat-swap=false

# Enable multi-window by default
PRODUCT_PROPERTY_OVERRIDES += \
    persist.sys.debug.multi_window=true

# Legacy stagefright media
PRODUCT_PROPERTY_OVERRIDES += \
    media.stagefright.legacyencoder=true \
    media.stagefright.less-secure=true


# set default USB configuration
# ORG
PRODUCT_DEFAULT_PROPERTY_OVERRIDES += \
    persist.sys.usb.config=mtp

# __popcountsi2 method, for the r7p0 egl blob
PRODUCT_PACKAGES += \
    libpopcountsi2

# Call Samsung LSI board support package
$(call inherit-product, hardware/samsung_slsi-cm/exynos5/exynos5.mk)
$(call inherit-product, hardware/samsung_slsi-cm/exynos5420/exynos5420.mk)

# Google boot animation
$(call inherit-product, vendor/google/google-vendor.mk)
