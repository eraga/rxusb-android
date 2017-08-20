/*
 * Copyright (C) 2013 Klaus Reimer (k@ailis.de)
 * See LICENSE.md file for copying conditions
 */

#include "InterfaceDescriptor.h"
#include "Interface.h"
#include "EndpointDescriptor.h"

jobject wrapInterfaceDescriptor(JNIEnv *env,
    const struct libusb_interface_descriptor *descriptor)
{
    return wrapPointer(env, descriptor, CLASS_PATH("InterfaceDescriptor"),
        "interfaceDescriptorPointer");
}

jobjectArray wrapInterfaceDescriptors(JNIEnv *env, int count,
    const struct libusb_interface_descriptor *descriptors)
{
    jobjectArray array = (jobjectArray) (*env)->NewObjectArray(env,
        count, (*env)->FindClass(env, CLASS_PATH("InterfaceDescriptor")),
        NULL);
    for (int i = 0; i < count; i++)
        (*env)->SetObjectArrayElement(env, array, i,
            wrapInterfaceDescriptor(env, &descriptors[i]));

    return array;
}

struct libusb_interface_descriptor *unwrapInterfaceDescriptor(JNIEnv *env,
    jobject descriptor)
{
    return (struct libusb_interface_descriptor *) unwrapPointer(env,
        descriptor, "interfaceDescriptorPointer");
}

/**
 * byte bLength()
 */
JNIEXPORT jbyte JNICALL METHOD_NAME(InterfaceDescriptor, bLength)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_interface_descriptor* descriptor =
        unwrapInterfaceDescriptor(env, this);
    if (!descriptor) return 0;
    return (jbyte) descriptor->bLength;
}

/**
 * byte bDescriptorType()
 */
JNIEXPORT jbyte JNICALL METHOD_NAME(InterfaceDescriptor, bDescriptorType)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_interface_descriptor* descriptor =
        unwrapInterfaceDescriptor(env, this);
    if (!descriptor) return 0;
    return (jbyte) descriptor->bDescriptorType;
}

/**
 * byte bInterfaceNumber()
 */
JNIEXPORT jbyte JNICALL METHOD_NAME(InterfaceDescriptor, bInterfaceNumber)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_interface_descriptor* descriptor =
        unwrapInterfaceDescriptor(env, this);
    if (!descriptor) return 0;
    return (jbyte) descriptor->bInterfaceNumber;
}

/**
 * byte bAlternateSetting()
 */
JNIEXPORT jbyte JNICALL METHOD_NAME(InterfaceDescriptor, bAlternateSetting)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_interface_descriptor* descriptor =
        unwrapInterfaceDescriptor(env, this);
    if (!descriptor) return 0;
    return (jbyte) descriptor->bAlternateSetting;
}

/**
 * byte bNumEndpoints()
 */
JNIEXPORT jbyte JNICALL METHOD_NAME(InterfaceDescriptor, bNumEndpoints)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_interface_descriptor* descriptor =
        unwrapInterfaceDescriptor(env, this);
    if (!descriptor) return 0;
    return (jbyte) descriptor->bNumEndpoints;
}

/**
 * byte bInterfaceClass()
 */
JNIEXPORT jbyte JNICALL METHOD_NAME(InterfaceDescriptor, bInterfaceClass)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_interface_descriptor* descriptor =
        unwrapInterfaceDescriptor(env, this);
    if (!descriptor) return 0;
    return (jbyte) descriptor->bInterfaceClass;
}

/**
 * byte bInterfaceSubClass()
 */
JNIEXPORT jbyte JNICALL METHOD_NAME(InterfaceDescriptor, bInterfaceSubClass)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_interface_descriptor* descriptor =
        unwrapInterfaceDescriptor(env, this);
    if (!descriptor) return 0;
    return (jbyte) descriptor->bInterfaceSubClass;
}

/**
 * byte bInterfaceProtocol()
 */
JNIEXPORT jbyte JNICALL METHOD_NAME(InterfaceDescriptor, bInterfaceProtocol)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_interface_descriptor* descriptor =
        unwrapInterfaceDescriptor(env, this);
    if (!descriptor) return 0;
    return (jbyte) descriptor->bInterfaceProtocol;
}

/**
 * byte iInterface()
 */
JNIEXPORT jbyte JNICALL METHOD_NAME(InterfaceDescriptor, iInterface)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_interface_descriptor* descriptor =
        unwrapInterfaceDescriptor(env, this);
    if (!descriptor) return 0;
    return (jbyte) descriptor->iInterface;
}

/**
 * EndpointDescriptor[] endpoint()
 */
JNIEXPORT jobjectArray JNICALL METHOD_NAME(InterfaceDescriptor, endpoint)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_interface_descriptor *descriptor = unwrapInterfaceDescriptor(
        env, this);
    if (!descriptor) return NULL;
    return wrapEndpointDescriptors(env, descriptor->bNumEndpoints,
        descriptor->endpoint);
}

/**
 * ByteBuffer extra()
 */
JNIEXPORT jobject JNICALL METHOD_NAME(InterfaceDescriptor, extra)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_interface_descriptor *descriptor =
        unwrapInterfaceDescriptor(env, this);
    if (!descriptor) return NULL;
    return NewDirectReadOnlyByteBuffer(env, descriptor->extra,
        descriptor->extra_length);
}

/**
 * int extraLength()
 */
JNIEXPORT jint JNICALL METHOD_NAME(InterfaceDescriptor, extraLength)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_interface_descriptor* descriptor =
        unwrapInterfaceDescriptor(env, this);
    if (!descriptor) return 0;
    return descriptor->extra_length;
}
