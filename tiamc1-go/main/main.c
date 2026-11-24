
#include <stdint.h>
#include <stdbool.h>

#include "rg_system.h"
#include "rg_display.h"
#include "rg_input.h"

#define SCREEN_W 280
#define SCREEN_H 240

static int player_x = 130;
static int player_y = 110;

static void draw_screen(void)
{
    // Black background
    rg_display_clear(0x0000);

    // Test frame
    rg_display_clear_rect(0, 0, SCREEN_W, 8, 0xFFFF);
    rg_display_clear_rect(0, SCREEN_H - 8,
                          SCREEN_W, 8, 0xFFFF);

    // Player: green square
    rg_display_clear_rect(player_x, player_y,
                          16, 16, 0x07E0);

    // Red and blue test blocks
    rg_display_clear_rect(20, 30, 32, 32, 0xF800);
    rg_display_clear_rect(228, 30, 32, 32, 0x001F);
}

void app_main(void)
{
    rg_config_t config = {0};

    config.sampleRate = 0;
    config.frameRate = 30;
    config.storageRequired = false;
    config.romRequired = false;

    rg_system_init(&config);

    rg_display_set_geometry(SCREEN_W, SCREEN_H, NULL);
    rg_display_set_scaling(RG_DISPLAY_SCALING_OFF);

    draw_screen();

    while (true)
    {
        uint32_t keys = rg_input_read_gamepad();

        if ((keys & RG_KEY_LEFT) && player_x > 0)
            player_x -= 2;

        if ((keys & RG_KEY_RIGHT) && player_x < SCREEN_W - 16)
            player_x += 2;

        if ((keys & RG_KEY_UP) && player_y > 8)
            player_y -= 2;

        if ((keys & RG_KEY_DOWN) && player_y < SCREEN_H - 24)
            player_y += 2;

        if (keys & RG_KEY_MENU)
            rg_system_exit();

        draw_screen();
        rg_system_tick(0);
    }
}
