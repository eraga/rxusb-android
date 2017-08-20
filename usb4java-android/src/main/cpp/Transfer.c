/*
 * Copyright (C) 2013 Klaus Reimer (k@ailis.de)
 * Copyright (C) 2013 Luca Longinotti (l@longi.li)
 * See LICENSE.md file for copying conditions
 */

#include <stdlib.h>
#include "Transfer.h"
#include "DeviceHandle.h"
#include "IsoPacketDescriptor.h"

static void LIBUSB_CALL cleanupCallback(struct libusb_transfer *transfer);
static void LIBUSB_CALL transferCallback(struct libusb_transfer *transfer);

jobject wrapTransfer(JNIEnv* env, const struct libusb_transfer* transfer)
{
    return wrapPointer(env, transfer, CLASS_PATH("Transfer"),
        "transferPointer");
}

struct libusb_transfer* unwrapTransfer(JNIEnv* env, jobject transfer)
{
    return (struct libusb_transfer *) unwrapPointer(env, transfer,
        "transferPointer");
}

void resetTransfer(JNIEnv* env, jobject object)
{
    jclass cls;
    jfieldID field;

    RESET_POINTER(env, object, "transferPointer");

    cls = (*env)->GetObjectClass(env, object);
    field = (*env)->GetFieldID(env, cls, "transferBuffer",
        "Ljava/nio/ByteBuffer;");
    (*env)->SetObjectField(env, object, field, NULL);
}

/**
 * void setDevHandle(DeviceHandle)
 */
JNIEXPORT void JNICALL METHOD_NAME(Transfer, setDevHandle)
(
    JNIEnv *env, jobject this, jobject handle
)
{
    struct libusb_transfer *transfer;
    libusb_device_handle *dev_handle;

    dev_handle = unwrapDeviceHandle(env, handle);
    if (!dev_handle && handle) return;
    transfer = unwrapTransfer(env, this);
    if (!transfer) return;

    transfer->dev_handle = dev_handle;
}

/**
 * DeviceHandle devHandle()
 */
JNIEXPORT jobject JNICALL METHOD_NAME(Transfer, devHandle)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_transfer *transfer = unwrapTransfer(env, this);
    if (!transfer) return NULL;

    return wrapDeviceHandle(env, transfer->dev_handle);
}

/**
 * void setFlags(byte)
 */
JNIEXPORT void JNICALL METHOD_NAME(Transfer, setFlags)
(
    JNIEnv *env, jobject this, jbyte flags
)
{
    struct libusb_transfer *transfer = unwrapTransfer(env, this);
    if (!transfer) return;

    transfer->flags = (uint8_t) flags;
}

/**
 * byte flags()
 */
JNIEXPORT jbyte JNICALL METHOD_NAME(Transfer, flags)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_transfer *transfer = unwrapTransfer(env, this);
    if (!transfer) return 0;

    return (jbyte) transfer->flags;
}

/**
 * void setEndpoint(byte)
 */
JNIEXPORT void JNICALL METHOD_NAME(Transfer, setEndpoint)
(
    JNIEnv *env, jobject this, jbyte endpoint
)
{
    struct libusb_transfer *transfer = unwrapTransfer(env, this);
    if (!transfer) return;

    transfer->endpoint = (unsigned char) endpoint;
}

/**
 * byte endpoint()
 */
JNIEXPORT jbyte JNICALL METHOD_NAME(Transfer, endpoint)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_transfer *transfer = unwrapTransfer(env, this);
    if (!transfer) return 0;

    return (jbyte) transfer->endpoint;
}

/**
 * void setType(byte)
 */
JNIEXPORT void JNICALL METHOD_NAME(Transfer, setType)
(
    JNIEnv *env, jobject this, jbyte type
)
{
    struct libusb_transfer *transfer = unwrapTransfer(env, this);
    if (!transfer) return;

    transfer->type = (unsigned char) type;
}

/**
 * byte type()
 */
JNIEXPORT jbyte JNICALL METHOD_NAME(Transfer, type)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_transfer *transfer = unwrapTransfer(env, this);
    if (!transfer) return 0;

    return (jbyte) transfer->type;
}

/**
 * void setTimeout(long)
 */
JNIEXPORT void JNICALL METHOD_NAME(Transfer, setTimeout)
(
    JNIEnv *env, jobject this, jlong timeout
)
{
    struct libusb_transfer *transfer = unwrapTransfer(env, this);
    if (!transfer) return;

    transfer->timeout = (unsigned int) timeout;
}

/**
 * long timeout()
 */
JNIEXPORT jlong JNICALL METHOD_NAME(Transfer, timeout)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_transfer *transfer = unwrapTransfer(env, this);
    if (!transfer) return 0;

    return transfer->timeout;
}

/**
 * int status()
 */
JNIEXPORT jint JNICALL METHOD_NAME(Transfer, status)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_transfer *transfer = unwrapTransfer(env, this);
    if (!transfer) return 0;

    return transfer->status;
}

/**
 * void setLengthNative(int)
 */
JNIEXPORT void JNICALL METHOD_NAME(Transfer, setLengthNative)
(
    JNIEnv *env, jobject this, jint length
)
{
    struct libusb_transfer *transfer = unwrapTransfer(env, this);
    if (!transfer) return;

    transfer->length = length;
}

/**
 * int length()
 */
JNIEXPORT jint JNICALL METHOD_NAME(Transfer, length)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_transfer *transfer = unwrapTransfer(env, this);
    if (!transfer) return 0;

    return transfer->length;
}

/**
 * int actualLength()
 */
JNIEXPORT jint JNICALL METHOD_NAME(Transfer, actualLength)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_transfer *transfer = unwrapTransfer(env, this);
    if (!transfer) return 0;

    return transfer->actual_length;
}

void cleanupGlobalReferences(JNIEnv *env, jobject obj)
{
    struct libusb_transfer *transfer;
    struct transfer_data *transferData;

    transfer = unwrapTransfer(env, obj);
    if (!transfer) return;

    transferData = ((struct transfer_data *) transfer->user_data);

    // Cleanup all global references, if any currently exist.
    if (transferData->callbackObject != NULL)
    {
        (*env)->DeleteGlobalRef(env, transferData->callbackObject);
    }

    if (transferData->callbackUserDataObject != NULL)
    {
        (*env)->DeleteGlobalRef(env, transferData->callbackUserDataObject);
    }

    if (transferData->transferObject != NULL)
    {
        (*env)->DeleteGlobalRef(env, transferData->transferObject);
    }
}

void cleanupCallbackEnable(JNIEnv *env, jobject obj)
{
    struct transfer_data *transferData;
    struct libusb_transfer *transfer;

    transfer = unwrapTransfer(env, obj);
    if (!transfer) return;

    transferData = ((struct transfer_data *) transfer->user_data);

    transferData->transferObject = (*env)->NewGlobalRef(env, obj);

    transfer->callback = &cleanupCallback;

    transferData->callbackObject = NULL;
    transferData->callbackObjectMethod = 0;
}

static void LIBUSB_CALL cleanupCallback(struct libusb_transfer *transfer)
{
    JNIEnv *env;
    jint result;
    struct transfer_data *transferData;
    jobject jTransfer;

    THREAD_BEGIN(env, result);

    transferData = ((struct transfer_data *) transfer->user_data);

    // The saved reference to the Java Transfer object.
    jTransfer = transferData->transferObject;

    // Cleanup Java Transfer object too, if requested.
    if (transfer->flags & LIBUSB_TRANSFER_FREE_TRANSFER)
    {
        cleanupGlobalReferences(env, jTransfer);
        resetTransfer(env, jTransfer);
        free(transferData);
    }

    THREAD_END(result);
}

static void LIBUSB_CALL transferCallback(struct libusb_transfer *transfer)
{
    JNIEnv *env;
    jint result;
    struct transfer_data *transferData;
    jobject jCallback;
    jmethodID jCallbackMethod;
    jobject jTransfer;

    THREAD_BEGIN(env, result);

    transferData = ((struct transfer_data *) transfer->user_data);

    // The saved references to the Java TransferCallback object.
    jCallback = transferData->callbackObject;
    jCallbackMethod = transferData->callbackObjectMethod;

    // The saved reference to the Java Transfer object.
    jTransfer = transferData->transferObject;

    // Read flags before calling the Java method, as it could
    // free the Transfer itself.
    if (transfer->flags & LIBUSB_TRANSFER_FREE_TRANSFER)
    {
        // Call back into Java.
        (*env)->CallVoidMethod(env, jCallback, jCallbackMethod, jTransfer);

        // Cleanup Java Transfer object too, if requested.
        cleanupGlobalReferences(env, jTransfer);
        resetTransfer(env, jTransfer);
        free(transferData);
    }
    else
    {
        // Call back into Java.
        (*env)->CallVoidMethod(env, jCallback, jCallbackMethod, jTransfer);
    }

    THREAD_END(result);
}

/**
 * void setCallback(TransferCallback)
 */
JNIEXPORT void JNICALL METHOD_NAME(Transfer, setCallback)
(
    JNIEnv *env, jobject this, jobject callback
)
{
    struct transfer_data *transferData;
    struct libusb_transfer *transfer;

    transfer = unwrapTransfer(env, this);
    if (!transfer) return;

    transferData = ((struct transfer_data *) transfer->user_data);

    if (transferData->transferObject != NULL)
    {
        (*env)->DeleteGlobalRef(env, transferData->transferObject);
    }

    if (transferData->callbackObject != NULL)
    {
        (*env)->DeleteGlobalRef(env, transferData->callbackObject);
    }

    if (callback != NULL)
    {
        jclass cls;
        jmethodID method;

        transferData->transferObject = (*env)->NewGlobalRef(env, this);

        transfer->callback = &transferCallback;

        cls = (*env)->GetObjectClass(env, callback);
        method = (*env)->GetMethodID(env, cls, "processTransfer",
            "(L"CLASS_PATH("Transfer;)V"));

        transferData->callbackObject = (*env)->NewGlobalRef(env, callback);
        transferData->callbackObjectMethod = method;
    }
    else
    {
        cleanupCallbackEnable(env, this);
    }
}

/**
 * TransferCallback callback()
 */
JNIEXPORT jobject JNICALL METHOD_NAME(Transfer, callback)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_transfer *transfer = unwrapTransfer(env, this);
    if (!transfer) return NULL;

    return ((struct transfer_data *) transfer->user_data)->callbackObject;
}

/**
 * void setUserData(Object)
 */
JNIEXPORT void JNICALL METHOD_NAME(Transfer, setUserData)
(
    JNIEnv *env, jobject this, jobject userData
)
{
    struct transfer_data *transferData;
    struct libusb_transfer *transfer;

    transfer = unwrapTransfer(env, this);
    if (!transfer) return;

    transferData = ((struct transfer_data *) transfer->user_data);

    if (transferData->callbackUserDataObject != NULL)
    {
        (*env)->DeleteGlobalRef(env, transferData->callbackUserDataObject);
    }

    if (userData != NULL)
    {
        transferData->callbackUserDataObject = (*env)->NewGlobalRef(env,
            userData);
    }
    else
    {
        transferData->callbackUserDataObject = NULL;
    }
}

/**
 * Object userData()
 */
JNIEXPORT jobject JNICALL METHOD_NAME(Transfer, userData)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_transfer *transfer = unwrapTransfer(env, this);
    if (!transfer) return NULL;

    return ((struct transfer_data *) transfer->user_data)->callbackUserDataObject;
}

/**
 * void setBufferNative(ByteBuffer)
 */
JNIEXPORT void JNICALL METHOD_NAME(Transfer, setBufferNative)
(
    JNIEnv *env, jobject this, jobject buffer
)
{
    struct libusb_transfer *transfer;
    unsigned char *buffer_ptr = NULL;
    if (buffer)
    {
        buffer_ptr = (*env)->GetDirectBufferAddress(env, buffer);
        VALIDATE_DIRECT_BUFFER(env, buffer_ptr, "buffer", return);
    }

    transfer = unwrapTransfer(env, this);
    if (!transfer) return;

    transfer->buffer = buffer_ptr;
}

/**
 * void setNumIsoPackets(int)
 */
JNIEXPORT void JNICALL METHOD_NAME(Transfer, setNumIsoPackets)
(
    JNIEnv *env, jobject this, jint numIsoPackets
)
{
    struct libusb_transfer *transfer = unwrapTransfer(env, this);
    if (!transfer) return;

    // Check that calls to setNumIsoPackets() never set a number exceeding
    // the maximum, which was originally set at allocTransfer() time.
    if (((struct transfer_data *) transfer->user_data)->maxNumIsoPackets
        < (size_t) numIsoPackets)
    {
        illegalArgument(env,
            "numIsoPackets exceeds maximum allowed number set with allocTransfer()");
        return;
    }

    transfer->num_iso_packets = numIsoPackets;
}

/**
 * int numIsoPackets()
 */
JNIEXPORT jint JNICALL METHOD_NAME(Transfer, numIsoPackets)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_transfer *transfer = unwrapTransfer(env, this);
    if (!transfer) return 0;

    return transfer->num_iso_packets;
}

/**
 * IsoPacketDescriptor[] isoPacketDesc()
 */
JNIEXPORT jobjectArray JNICALL METHOD_NAME(Transfer, isoPacketDesc)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_transfer *transfer = unwrapTransfer(env, this);
    if (!transfer) return NULL;

    return wrapIsoPacketDescriptors(env, transfer->num_iso_packets,
        transfer->iso_packet_desc);
}

/**
 * void setStreamId(int)
 */
JNIEXPORT void JNICALL METHOD_NAME(Transfer, setStreamId)
(
    JNIEnv *env, jobject this, jint streamId
)
{
    struct libusb_transfer *transfer = unwrapTransfer(env, this);
    if (!transfer) return;

    libusb_transfer_set_stream_id(transfer, (uint32_t) streamId);
}

/**
 * int streamId()
 */
JNIEXPORT jint JNICALL METHOD_NAME(Transfer, streamId)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_transfer *transfer = unwrapTransfer(env, this);
    if (!transfer) return 0;

    return (jint) libusb_transfer_get_stream_id(transfer);
}
