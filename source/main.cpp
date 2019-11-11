// Copyright (c) 2017-2019 elecro
//
// Licensed under the BSD 3-Clause License
// <LICENSE.md or https://opensource.org/licenses/BSD-3-Clause>.
// This file may not be copied, modified, or distributed except
// according to those terms.

#include <mbed.h>
#include <ble/BLE.h>

#include "blue.hpp"

DigitalOut led1(LED1, 1);
Serial usb(USBTX, USBRX);

EventQueue queue;

void led_blinker(void)
{
    /*
    static int counter = 0;
    usb.printf("Ping %d\r\n", counter);
    */
    led1 = !led1;
}

/* Print out device MAC address to the console */
static void blue_PrintMacAddress(void)
{
    Gap::AddressType_t addr_type;
    Gap::Address_t address;

    BLE::Instance().gap().getAddress(&addr_type, address);

    usb.printf("DEVICE MAC ADDRESS: ");
    for (int i = 5; i >= 1; i--){
        usb.printf("%02x:", address[i]);
    }
    usb.printf("%02x\r\n", address[0]);
}

static void blue_InitDone(BLE::InitializationCompleteCallbackContext* params)
{
    BLE& ble = params->ble;
    ble_error_t error = params->error;

    /* Make sure there was no error when initializing the BLE interface. */
    if (error != BLE_ERROR_NONE)
    {
        usb.printf("[BLUE] failed to initialize the BLE. (%d)\r\n", error);
        return;
    }

    /* Make sure that the BLE instance is the default instance. */
    if (ble.getInstanceID() != BLE::DEFAULT_INSTANCE)
    {
        usb.printf("[BLUE] invalid BLE instance detected.\r\n");
        return;
    }

    blue_PrintMacAddress();

#ifdef BLE_SCAN
    blue_StartScan(ble);
#endif
#ifdef BLE_CONN
    blue_AddConnectionCallbacks(ble);
#endif
#ifdef BLE_SRV_COUNT
    blue_CounterService(ble, queue);
#endif
}

/* All events from the BLE should be queue on our own event queue. */
static void blue_ScheduleEventsProcessing(BLE::OnEventsToProcessCallbackContext* context)
{
    BLE& ble = BLE::Instance();
    queue.call(Callback<void()>(&ble, &BLE::processEvents));
}

int main()
{
    led1 = !led1;
    wait(5);
    led1 = !led1;

    usb.printf("%s: Starting device\r\n", __FUNCTION__);

    /* Initialize BLE */
    BLE& ble = BLE::Instance();

    ble.onEventsToProcess(blue_ScheduleEventsProcessing);
    ble.init(blue_InitDone);

    queue.call_every(500, led_blinker);
    queue.dispatch_forever();

    return 0;
}
