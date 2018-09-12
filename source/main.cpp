// Copyright (c) 2017 elecro
//
// Licensed under the BSD 3-Clause License
// <LICENSE.md or https://opensource.org/licenses/BSD-3-Clause>.
// This file may not be copied, modified, or distributed except
// according to those terms.

#include <mbed.h>

DigitalOut led1(LED1, 1);
Serial usb(USBTX, USBRX);

EventQueue queue;

void led_blinker(void)
{
    led1 = !led1;
}

int main()
{
    usb.printf("%s: Starting device", __FUNCTION__);

    queue.call_every(500, led_blinker);
    queue.dispatch_forever();

    return 0;
}
