# RxUsb Android backend

RxUsb is a high level reactive facade. Read more about RxUsb [here](https://github.com/eraga/rxusb).

RxUsb for Android brings two kinds of implementations: using LibUsb and Native Android USB.



## RxUsb backed by LibUsb and android



The default system configuration on most Android devices will not allow
access to USB. There are several options for changing this.

### If you have control of the system image

Modify the `ueventd.rc` used in the image to change the permissions on
`/dev/bus/usb/*/*`. If using this approach then it is advisable to
create a new Android permission to protect access to these files.
It is not advisable to give all applications read and write permissions
to these files.

The following example will give all applications read and write permissions
for all USB devices.

```bash
# vi /ueventd.rc
```

find line starting with `/dev/bus/usb/* ` and edit it to have `0666` in second column:
```
/dev/bus/usb/*            0666   root       usb
```


### If you can't modify the image but device is rooted


### All other cases

In most cases it is still possible to obtain permission with
`android.hardware.usb.UsbManager`.

The difficulties in this method is that there is no guarantee
that it will continue to work in the future Android versions, it
requires invoking Java APIs and running code to match each
`android.hardware.usb.UsbDevice` to a libusb_device.
