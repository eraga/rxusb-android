/*
 * Copyright (C) 2013 Klaus Reimer (k@ailis.de)
 * See LICENSE.md file for copying conditions
 */

#ifndef USB4JAVA_DEVICE_DESCRIPTOR_H
#define USB4JAVA_DEVICE_DESCRIPTOR_H

#include "usb4java.h"

void setDeviceDescriptor(JNIEnv*, const struct libusb_device_descriptor*, jobject);
void resetDeviceDescriptor(JNIEnv*, jobject);

#endif
