/*
 * Copyright (C) 2013 Klaus Reimer (k@ailis.de)
 * See LICENSE.md file for copying conditions
 */

#include "Usb20ExtensionDescriptor.h"

void setUsb20ExtensionDescriptor(JNIEnv* env,
    const struct libusb_usb_2_0_extension_descriptor* descriptor, jobject object)
{
    SET_POINTER(env, descriptor, object, "usb20ExtensionDescriptorPointer");
}

struct libusb_usb_2_0_extension_descriptor* unwrapUsb20ExtensionDescriptor(
    JNIEnv* env, jobject descriptor)
{
    return (struct libusb_usb_2_0_extension_descriptor *) unwrapPointer(env,
        descriptor, "usb20ExtensionDescriptorPointer");
}

void resetUsb20ExtensionDescriptor(JNIEnv* env, jobject obj)
{
    RESET_POINTER(env, obj, "usb20ExtensionDescriptorPointer");
}

/**
 * byte bLength()
 */
JNIEXPORT jbyte JNICALL METHOD_NAME(Usb20ExtensionDescriptor, bLength)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_usb_2_0_extension_descriptor *descriptor =
        unwrapUsb20ExtensionDescriptor(env, this);
    if (!descriptor) return 0;
    return (jbyte) descriptor->bLength;
}

/**
 * byte bDescriptorType()
 */
JNIEXPORT jbyte JNICALL METHOD_NAME(Usb20ExtensionDescriptor, bDescriptorType)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_usb_2_0_extension_descriptor *descriptor =
        unwrapUsb20ExtensionDescriptor(env, this);
    if (!descriptor) return 0;
    return (jbyte) descriptor->bDescriptorType;
}

/**
 * byte bDevCapabilityType()
 */
JNIEXPORT jbyte JNICALL METHOD_NAME(Usb20ExtensionDescriptor,
    bDevCapabilityType)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_usb_2_0_extension_descriptor *descriptor =
        unwrapUsb20ExtensionDescriptor(env, this);
    if (!descriptor) return 0;
    return (jbyte) descriptor->bDevCapabilityType;
}

/**
 * int bmAttributes()
 */
JNIEXPORT jint JNICALL METHOD_NAME(Usb20ExtensionDescriptor,
    bmAttributes)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_usb_2_0_extension_descriptor *descriptor =
        unwrapUsb20ExtensionDescriptor(env, this);
    if (!descriptor) return 0;
    return (jint) descriptor->bmAttributes;
}
