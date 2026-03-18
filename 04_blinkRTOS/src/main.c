/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include "blinky.h"

#define STACK_SIZE 1024
#define PRIORITY 5
#define NUM_THREADS 2

K_THREAD_STACK_ARRAY_DEFINE(thread_stacks, NUM_THREADS, STACK_SIZE)
struct k_thread thread_data[2];

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS0   1000
#define SLEEP_TIME_MS1   900

/* The devicetree node identifier for the "training_led" alias. */
#define LED0_NODE DT_ALIAS(led_a)
#define LED1_NODE DT_ALIAS(led_b)

static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(LED1_NODE, gpios);

/* Main function */
int main(void)
{
	while (1)
	{
		k_thread_create(
				&thread_data[0],
				thread_stacks[0],
				STACK_SIZE,
				blinky,
				(void *)&led0,
				(void *)1000,
				NULL,
				K_LOWEST_APPLICATION_THREAD_PRIO,
				0,
				K_NO_WAIT);

		k_thread_create(
				&thread_data[1],
				thread_stacks[1],
				STACK_SIZE,
				blinky,
				(void *)&led1,
				(void *)950,
				NULL,
				K_LOWEST_APPLICATION_THREAD_PRIO,
				0,
				K_NO_WAIT);

		k_msleep(10000);
		// k_yield();
	}
}