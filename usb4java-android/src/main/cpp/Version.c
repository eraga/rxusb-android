/*
 * Copyright (C) 2013 Klaus Reimer (k@ailis.de)
 * See LICENSE.md file for copying conditions
 */

#include "Version.h"

jobject wrapVersion(JNIEnv* env, const struct libusb_version* pointer)
{
    return wrapPointer(env, pointer, CLASS_PATH("Version"), "versionPointer");
}

const struct libusb_version* unwrapVersion(JNIEnv* env, jobject version)
{
    return (struct libusb_version *) unwrapPointer(env, version,
        "versionPointer");
}

/**
 * int major()
 */
JNIEXPORT jint JNICALL METHOD_NAME(Version, major)
(
    JNIEnv *env, jobject this
)
{
    const struct libusb_version *version = unwrapVersion(env, this);
    if (!version) return 0;
    return version->major;
}

/**
 * int minor()
 */
JNIEXPORT jint JNICALL METHOD_NAME(Version, minor)
(
    JNIEnv *env, jobject this
)
{
    const struct libusb_version *version = unwrapVersion(env, this);
    if (!version) return 0;
    return version->minor;
}

/**
 * int micro()
 */
JNIEXPORT jint JNICALL METHOD_NAME(Version, micro)
(
    JNIEnv *env, jobject this
)
{
    const struct libusb_version *version = unwrapVersion(env, this);
    if (!version) return 0;
    return version->micro;
}

/**
 * int nano()
 */
JNIEXPORT jint JNICALL METHOD_NAME(Version, nano)
(
    JNIEnv *env, jobject this
)
{
    const struct libusb_version *version = unwrapVersion(env, this);
    if (!version) return 0;
    return version->nano;
}

/**
 * String rc()
 */
JNIEXPORT jstring JNICALL METHOD_NAME(Version, rc)
(
    JNIEnv *env, jobject this
)
{
    const struct libusb_version *version = unwrapVersion(env, this);
    if (!version) return NULL;
    return (*env)->NewStringUTF(env, version->rc);
}
