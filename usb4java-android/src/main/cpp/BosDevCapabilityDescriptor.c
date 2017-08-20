/*
 * Copyright (C) 2013 Klaus Reimer (k@ailis.de)
 * See LICENSE.md file for copying conditions
 */

#include "BosDevCapabilityDescriptor.h"

jobject wrapBosDevCapabilityDescriptor(JNIEnv *env,
    const struct libusb_bos_dev_capability_descriptor *descriptor)
{
    return wrapPointer(env, descriptor,
        CLASS_PATH("BosDevCapabilityDescriptor"),
        "/bosDevCapabilityDescriptorPointer");
}

jobjectArray wrapBosDevCapabilityDescriptors(JNIEnv *env, int count,
    struct libusb_bos_dev_capability_descriptor * const *descriptors)
{
    jobjectArray array = (jobjectArray) (*env)->NewObjectArray(env,
        count, (*env)->FindClass(env, CLASS_PATH("BosDevCapabilityDescriptor")),
        NULL);

    for (int i = 0; i < count; i++)
        (*env)->SetObjectArrayElement(env, array, i,
            wrapBosDevCapabilityDescriptor(env, descriptors[i]));

    return array;
}

struct libusb_bos_dev_capability_descriptor*
    unwrapBosDevCapabilityDescriptor(JNIEnv *env, jobject descriptor)
{
    return (struct libusb_bos_dev_capability_descriptor *) unwrapPointer(env,
        descriptor, "bosDevCapabilityDescriptorPointer");
}

/**
 * byte bLength()
 */
JNIEXPORT jbyte JNICALL METHOD_NAME(BosDevCapabilityDescriptor, bLength)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_bos_dev_capability_descriptor* descriptor =
        unwrapBosDevCapabilityDescriptor(env, this);
    if (!descriptor) return 0;
    return (jbyte) descriptor->bLength;
}

/**
 * byte bDescriptorType()
 */
JNIEXPORT jbyte JNICALL METHOD_NAME(BosDevCapabilityDescriptor,
    bDescriptorType)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_bos_dev_capability_descriptor* descriptor =
        unwrapBosDevCapabilityDescriptor(env, this);
    if (!descriptor) return 0;
    return (jbyte) descriptor->bDescriptorType;
}

/**
 * byte bDevCapabilityType()
 */
JNIEXPORT jbyte JNICALL METHOD_NAME(BosDevCapabilityDescriptor,
    bDevCapabilityType)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_bos_dev_capability_descriptor* descriptor =
        unwrapBosDevCapabilityDescriptor(env, this);
    if (!descriptor) return 0;
    return (jbyte) descriptor->bDevCapabilityType;
}

/**
 * ByteBuffer devCapabilityData()
 */
JNIEXPORT jobject JNICALL METHOD_NAME(BosDevCapabilityDescriptor,
    devCapabilityData)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_bos_dev_capability_descriptor *descriptor =
        unwrapBosDevCapabilityDescriptor(env, this);
    if (!descriptor) return NULL;
    return NewDirectReadOnlyByteBuffer(env, descriptor->dev_capability_data,
        descriptor->bLength - 3);
}
