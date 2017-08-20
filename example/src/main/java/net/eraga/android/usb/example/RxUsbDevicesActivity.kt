package net.eraga.android.usb.example

import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import net.eraga.rxusb.UsbService
import org.usb4java.*

class RxUsbDevicesActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)



        val usbService = UsbService.instance

        usbService.getDeviceList().forEach {
            println(it)
        }

    }
}
