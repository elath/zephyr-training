/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
// #include "blinky.h"

// K_THREAD_STACK_ARRAY_DEFINE(thread_stacks, NUM_THREADS, STACK_SIZE);
// struct k_thread thread_data[2];

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS0   1000

/* The devicetree node identifier for the "training_led" alias. */
#define LED0_NODE DT_ALIAS(training_led)

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

static void my_thread_handler(void *dummy1, void *dummy2, void *dummy3) {
	int ret;

	if (!device_is_ready(led.port)) {
		return;
	}

	ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return;
	}

	while (1) {
		gpio_pin_toggle_dt(&led);
		k_sleep(K_SECONDS(1));
	}
}

K_THREAD_DEFINE(my_thread, 1024,
				my_thread_handler, NULL, NULL, NULL,
				K_LOWEST_APPLICATION_THREAD_PRIO, 0, 0);

/* Main function */
int main(void)
{
	while (1)
	{
		k_msleep(1000);
	}
}