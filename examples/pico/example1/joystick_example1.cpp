/**
 * Copyright (c) 2020 SparkFun Electronics
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include <string.h>

#include "pico/stdlib.h"
#include "qwiic_joystick.h"

JOYSTICK myJoystick;


int main() {

     // setup stdio. Output device is controlled in CMakeLists.txt file
    stdio_init_all();

	printf("Starting JOYSTICK Test\n\n");

    // Init the system 

    if(!myJoystick.begin()){
    	printf("Error starting the qwiic joystick device. Aboarting\n");
  		return 0;
    }

    while (1) {

        printf("X: %d \tY: %d\tButton: %d\n", myJoystick.getHorizontal(), myJoystick.getVertical(), myJoystick.getButton());

        sleep_ms(500);

    }

    return 0;
}
