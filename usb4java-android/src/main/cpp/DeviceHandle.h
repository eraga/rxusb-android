/*
 * Copyright (C) 2013 Klaus Reimer (k@ailis.de)
 * See LICENSE.md file for copying conditions
 */

#ifndef USB4JAVA_DEVICE_HANDLE_H
#define USB4JAVA_DEVICE_HANDLE_H

#include "usb4java.h"

void setDeviceHandle(JNIEnv*, const libusb_device_handle*, jobject);
jobject wrapDeviceHandle(JNIEnv*, const libusb_device_handle*);
libusb_device_handle* unwrapDeviceHandle(JNIEnv*, jobject);
void resetDeviceHandle(JNIEnv*, jobject);

#endif
