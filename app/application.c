#include <application.h>

#include <bc_rf_ook.h>
// LED instance
bc_led_t led;

// Button instance
bc_button_t button;

void button_event_handler(bc_button_t *self, bc_button_event_t event, void *event_param)
{
        if (event == BC_BUTTON_EVENT_CLICK)
    {
        bc_led_pulse(&led, 200);

        bc_rf_ook_set_bitlength(700);
        bc_rf_ook_send_hex_string("b65b2db6db6cb6c8");

        //static const uint8_t on_1[] = {0x96, 0x4b, 0x6d, 0xb6, 0xdb, 0x6c, 0xb6, 0xc8};
        //bc_rf_ook_send(on_1, sizeof(on_1));
    }

    if (event == BC_BUTTON_EVENT_HOLD)
    {
        bc_led_pulse(&led, 200);
        //bc_rf_ook_set_bitrate(4854);
        bc_rf_ook_set_bitlength(206);

        bc_rf_ook_send_hex_string("ffffff8e8e888ee88e88eeeee888ee8e888888e8888888e888888888e8888eee8ee88e8e0");

        while(bc_rf_is_busy());
        bc_timer_start();
        bc_timer_delay(5000);
        bc_timer_stop();

        bc_rf_ook_send_hex_string("ffffff8e8e888ee88e88eeeee888ee8e888888e8888888e8888888888e88e88e88e88eee0");
    }

    // Logging
    bc_log_info("Button event handler - event: %i", event);
}

void application_init(void)
{
    // Initialize logging
    bc_log_init(BC_LOG_LEVEL_DUMP, BC_LOG_TIMESTAMP_ABS);

    // Initialize LED
    bc_led_init(&led, BC_GPIO_LED, false, false);
    bc_led_pulse(&led, 2000);

    // Initialize button
    bc_button_init(&button, BC_GPIO_BUTTON, BC_GPIO_PULL_DOWN, false);
    bc_button_set_event_handler(&button, button_event_handler, NULL);
    bc_button_set_hold_time(&button, 600);

    // Initialize microsecond timer
    bc_timer_init();
    bc_rf_ook_init(BC_GPIO_P17);

    // Enable GND on P15
    bc_gpio_init(BC_GPIO_P15);
    bc_gpio_set_mode(BC_GPIO_P15, BC_GPIO_MODE_OUTPUT);
    bc_gpio_set_output(BC_GPIO_P15, 0);
    // Enable VCC on P16
    bc_gpio_init(BC_GPIO_P16);
    bc_gpio_set_mode(BC_GPIO_P16, BC_GPIO_MODE_OUTPUT);
    bc_gpio_set_output(BC_GPIO_P16, 1);
}


/*
static const uint8_t on_1[] = {0x96, 0x4b, 0x6d, 0xb6, 0xdb, 0x6c, 0xb6, 0xc8};
static const uint8_t on_2[] = {0x96, 0x4b, 0x6d, 0xb6, 0xd9, 0x6c, 0xb6, 0x48};
static const uint8_t on_3[] = {0x96, 0x4b, 0x6d, 0xb6, 0xdb, 0x2c, 0xb6, 0xd8};
static const uint8_t on_4[] = {0x96, 0x4b, 0x6d, 0xb6, 0xd9, 0x2c, 0xb6, 0x58};

static const uint8_t off_1[] = {0x96, 0x4b, 0x6d, 0xb6, 0xdb, 0x6d, 0xb6, 0xd8};
static const uint8_t off_2[] = {0x96, 0x4b, 0x6d, 0xb6, 0xd9, 0x6d, 0xb6, 0x58};
static const uint8_t off_3[] = {0x96, 0x4b, 0x6d, 0xb6, 0xdb, 0x2d, 0xb6, 0xc8};
static const uint8_t off_4[] = {0x96, 0x4b, 0x6d, 0xb6, 0xd9, 0x2d, 0xb6, 0x48};
*/


