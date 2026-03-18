#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

K_MUTEX_DEFINE(led_mutex);

extern void blinky(void *p1, void *p2, void *p3)
{
    struct gpio_dt_spec *led = (struct gpio_dt_spec *)p1;
    int period = (int)p2;
    int ret = 0;

    if (!device_is_ready(led->port)) {
        return;
    }

    ret = gpio_pin_configure_dt(led, GPIO_OUTPUT_ACTIVE);
    if (ret < 0) {
        return;
    }

    while (1) {
        if (k_mutex_lock(&led_mutex, K_MSEC(5)) == 0) {
            gpio_pin_toggle_dt(led);
            k_mutex_unlock(&led_mutex);
        }
        k_msleep(period);
    }
}