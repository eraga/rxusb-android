/*
 * Copyright (C) 2013 Klaus Reimer (k@ailis.de)
 * See LICENSE.md file for copying conditions
 */

#ifndef USB4JAVA_CONFIG_DESCRIPTOR_H
#define USB4JAVA_CONFIG_DESCRIPTOR_H

#include "usb4java.h"

void setConfigDescriptor(JNIEnv*, const struct libusb_config_descriptor*, jobject);
struct libusb_config_descriptor* unwrapConfigDescriptor(JNIEnv*, jobject);
void resetConfigDescriptor(JNIEnv*, jobject);

#endif
