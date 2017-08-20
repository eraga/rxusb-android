/*
 * Copyright (C) 2013 Klaus Reimer (k@ailis.de)
 * Copyright (C) 2013 Luca Longinotti (l@longi.li)
 * See LICENSE.md file for copying conditions
 */

#ifndef USB4JAVA_TRANSFER_H
#define USB4JAVA_TRANSFER_H

#include "usb4java.h"

struct transfer_data
{
    jobject transferObject;
    jobject callbackObject;
    jmethodID callbackObjectMethod;
    jobject callbackUserDataObject;
    size_t maxNumIsoPackets;
};

void cleanupGlobalReferences(JNIEnv*, jobject);
void cleanupCallbackEnable(JNIEnv*, jobject);

jobject wrapTransfer(JNIEnv*, const struct libusb_transfer*);
struct libusb_transfer* unwrapTransfer(JNIEnv*, jobject);
void resetTransfer(JNIEnv*, jobject);

#endif
