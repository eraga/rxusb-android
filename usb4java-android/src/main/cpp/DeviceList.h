/*
 * Copyright (C) 2013 Klaus Reimer (k@ailis.de)
 * See LICENSE.md file for copying conditions
 */

#ifndef USB4JAVA_DEVICE_LIST_H
#define USB4JAVA_DEVICE_LIST_H

#include "usb4java.h"

void setDeviceList(JNIEnv*, libusb_device* const *, jint, jobject);
libusb_device** unwrapDeviceList(JNIEnv*, jobject);
void resetDeviceList(JNIEnv*, jobject);

#endif
