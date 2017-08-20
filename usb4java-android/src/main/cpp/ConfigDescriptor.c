/*
 * Copyright (C) 2013 Klaus Reimer (k@ailis.de)
 * See LICENSE.md file for copying conditions
 */

#include "ConfigDescriptor.h"
#include "Interface.h"

void setConfigDescriptor(JNIEnv* env,
    const struct libusb_config_descriptor* descriptor, jobject object)
{
    SET_POINTER(env, descriptor, object, "configDescriptorPointer");
}

struct libusb_config_descriptor* unwrapConfigDescriptor(JNIEnv* env,
    jobject descriptor)
{
    return (struct libusb_config_descriptor*) unwrapPointer(env, descriptor,
        "configDescriptorPointer");
}

void resetConfigDescriptor(JNIEnv* env, jobject obj)
{
    RESET_POINTER(env, obj, "configDescriptorPointer");
}

/**
 * byte bLength()
 */
JNIEXPORT jbyte JNICALL METHOD_NAME(ConfigDescriptor, bLength)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_config_descriptor *descriptor =
        unwrapConfigDescriptor(env, this);
    if (!descriptor) return 0;
    return (jbyte) descriptor->bLength;
}

/**
 * byte bDescriptorType()
 */
JNIEXPORT jbyte JNICALL METHOD_NAME(ConfigDescriptor, bDescriptorType)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_config_descriptor *descriptor =
        unwrapConfigDescriptor(env, this);
    if (!descriptor) return 0;
    return (jbyte) descriptor->bDescriptorType;
}

/**
 * short wTotalLength()
 */
JNIEXPORT jshort JNICALL METHOD_NAME(ConfigDescriptor, wTotalLength)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_config_descriptor *descriptor =
        unwrapConfigDescriptor(env, this);
    if (!descriptor) return 0;
    return (jshort) descriptor->wTotalLength;
}

/**
 * byte bNumInterfaces()
 */
JNIEXPORT jbyte JNICALL METHOD_NAME(ConfigDescriptor, bNumInterfaces)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_config_descriptor *descriptor =
        unwrapConfigDescriptor(env, this);
    if (!descriptor) return 0;
    return (jbyte) descriptor->bNumInterfaces;
}

/**
 * byte bConfigurationValue()
 */
JNIEXPORT jbyte JNICALL METHOD_NAME(ConfigDescriptor, bConfigurationValue)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_config_descriptor *descriptor =
        unwrapConfigDescriptor(env, this);
    if (!descriptor) return 0;
    return (jbyte) descriptor->bConfigurationValue;
}

/**
 * byte iConfiguration()
 */
JNIEXPORT jbyte JNICALL METHOD_NAME(ConfigDescriptor, iConfiguration)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_config_descriptor *descriptor =
        unwrapConfigDescriptor(env, this);
    if (!descriptor) return 0;
    return (jbyte) descriptor->iConfiguration;
}

/**
 * byte bmAttributes()
 */
JNIEXPORT jbyte JNICALL METHOD_NAME(ConfigDescriptor, bmAttributes)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_config_descriptor *descriptor =
        unwrapConfigDescriptor(env, this);
    if (!descriptor) return 0;
    return (jbyte) descriptor->bmAttributes;
}

/**
 * byte bMaxPower()
 */
JNIEXPORT jbyte JNICALL METHOD_NAME(ConfigDescriptor, bMaxPower)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_config_descriptor *descriptor =
        unwrapConfigDescriptor(env, this);
    if (!descriptor) return 0;
    return (jbyte) descriptor->MaxPower;
}

/**
 * Interface[] iface()
 */
JNIEXPORT jobjectArray JNICALL METHOD_NAME(ConfigDescriptor, iface)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_config_descriptor *descriptor = unwrapConfigDescriptor(
        env, this);
    if (!descriptor) return NULL;
    return wrapInterfaces(env, descriptor->bNumInterfaces,
        descriptor->interface);
}

/**
 * ByteBuffer extra()
 */
JNIEXPORT jobject JNICALL METHOD_NAME(ConfigDescriptor, extra)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_config_descriptor *descriptor =
        unwrapConfigDescriptor(env, this);
    if (!descriptor) return NULL;
    return NewDirectReadOnlyByteBuffer(env, descriptor->extra, descriptor->extra_length);
}

/**
 * int extraLength()
 */
JNIEXPORT jint JNICALL METHOD_NAME(ConfigDescriptor, extraLength)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_config_descriptor *descriptor =
        unwrapConfigDescriptor(env, this);
    if (!descriptor) return 0;
    return descriptor->extra_length;
}
