/*
 * Copyright (C) 2013 Klaus Reimer (k@ailis.de)
 * See LICENSE.md file for copying conditions
 */

#include "SsEndpointCompanionDescriptor.h"
#include "Interface.h"

void setSsEndpointCompanionDescriptor(JNIEnv* env,
    const struct libusb_ss_endpoint_companion_descriptor* descriptor, jobject object)
{
    SET_POINTER(env, descriptor, object, "ssEndpointCompanionDescriptorPointer");
}

struct libusb_ss_endpoint_companion_descriptor*
    unwrapSsEndpointCompanionDescriptor(JNIEnv* env, jobject descriptor)
{
    return (struct libusb_ss_endpoint_companion_descriptor *) unwrapPointer(
        env, descriptor, "ssEndpointCompanionDescriptorPointer");
}

void resetSsEndpointCompanionDescriptor(JNIEnv* env, jobject obj)
{
    RESET_POINTER(env, obj, "ssEndpointCompanionDescriptorPointer");
}

/**
 * byte bLength()
 */
JNIEXPORT jbyte JNICALL METHOD_NAME(SsEndpointCompanionDescriptor, bLength)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_ss_endpoint_companion_descriptor *descriptor =
        unwrapSsEndpointCompanionDescriptor(env, this);
    if (!descriptor) return 0;
    return (jbyte) descriptor->bLength;
}

/**
 * byte bDescriptorType()
 */
JNIEXPORT jbyte JNICALL METHOD_NAME(SsEndpointCompanionDescriptor,
    bDescriptorType)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_ss_endpoint_companion_descriptor *descriptor =
        unwrapSsEndpointCompanionDescriptor(env, this);
    if (!descriptor) return 0;
    return (jbyte) descriptor->bDescriptorType;
}

/**
 * byte bMaxBurst()
 */
JNIEXPORT jbyte JNICALL METHOD_NAME(SsEndpointCompanionDescriptor, bMaxBurst)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_ss_endpoint_companion_descriptor *descriptor =
        unwrapSsEndpointCompanionDescriptor(env, this);
    if (!descriptor) return 0;
    return (jbyte) descriptor->bMaxBurst;
}

/**
 * byte bmAttributes()
 */
JNIEXPORT jbyte JNICALL METHOD_NAME(SsEndpointCompanionDescriptor, bmAttributes)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_ss_endpoint_companion_descriptor *descriptor =
        unwrapSsEndpointCompanionDescriptor(env, this);
    if (!descriptor) return 0;
    return (jbyte) descriptor->bmAttributes;
}

/**
 * short wBytesPerInterval()
 */
JNIEXPORT jshort JNICALL METHOD_NAME(SsEndpointCompanionDescriptor, wBytesPerInterval)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_ss_endpoint_companion_descriptor *descriptor =
        unwrapSsEndpointCompanionDescriptor(env, this);
    if (!descriptor) return 0;
    return (jshort) descriptor->wBytesPerInterval;
}
