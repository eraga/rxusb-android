package net.eraga.android.usb.example

import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import org.usb4java.*

class LibUsbDevicesActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_lib_usb_devices)

        val context = org.usb4java.Context()

        if (LibUsb.init(context) != LibUsb.SUCCESS)
            throw LibUsbException("Unable to initialize libusb.", 0)

        val list = DeviceList()

        if (LibUsb.getDeviceList(null, list) < 0)
            throw LibUsbException("Unable to get device list", LibUsb.getDeviceList(null, list))


        list.forEach {
            val descriptor = DeviceDescriptor()
            var result = LibUsb.getDeviceDescriptor(it, descriptor)
            if (result == 0) {

                println("=============")
                println(it)
                println(descriptor)

                val handle = DeviceHandle()
                result = LibUsb.open(it, handle)
                if (result == LibUsb.SUCCESS) {


                    val config = ConfigDescriptor()
                    LibUsb.getConfigDescriptor(it, 0, config)
                    println("Interfaces " + config.bNumInterfaces())

                    LibUsb.close(handle)
                }
            }
        }
    }
}
