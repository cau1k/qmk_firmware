#include "caulk.h"
#include "quantum.h"
#include "pointing_device.h"
#include "wpm.h"

#define HK_WPM_MAX 999

typedef enum {
    HK_OLED_SCREEN_STATUS = 0,
    HK_OLED_SCREEN_BLANK,
} hk_oled_screen_t;

static hk_oled_screen_t hk_oled_screen = HK_OLED_SCREEN_STATUS;
static uint16_t         last_wpm        = 0xFFFF;
static uint8_t          last_layer      = 0xFF;
static bool             last_auto_mouse = false;
static bool             force_redraw    = true;
static bool             blank_rendered  = false;
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_left()) {
        return rotation;
    }
    return OLED_ROTATION_270;
}

void hk_oled_toggle_screen(void) {
    hk_oled_screen = (hk_oled_screen == HK_OLED_SCREEN_STATUS) ? HK_OLED_SCREEN_BLANK : HK_OLED_SCREEN_STATUS;
    force_redraw = true;
    blank_rendered = false;
}

static void render_wpm(uint16_t wpm) {
    char wpm_buf[4] = {0};
    wpm_buf[0] = (wpm >= 100) ? (char)('0' + (wpm / 100)) : ' ';
    wpm_buf[1] = (wpm >= 10) ? (char)('0' + ((wpm / 10) % 10)) : ' ';
    wpm_buf[2] = (char)('0' + (wpm % 10));
    wpm_buf[3] = '\0';

    oled_set_cursor(0, 0);
    oled_write(wpm_buf, false);
    oled_set_cursor(0, 1);
    oled_write_P(PSTR("WPM"), false);
}

static void render_layer(uint8_t layer) {
    char layer_buf[4] = {'L', '0', '0', '\0'};
    if (layer > 99) {
        layer = 99;
    }
    layer_buf[1] = (char)('0' + (layer / 10));
    layer_buf[2] = (char)('0' + (layer % 10));

    oled_set_cursor(0, 2);
    oled_write(layer_buf, false);
}

static void render_auto_mouse(bool enabled) {
#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
    oled_set_cursor(0, 3);
    oled_write_P(enabled ? PSTR("AM ON") : PSTR("AMOFF"), false);
#else
    (void)enabled;
#endif
}

static void render_status_screen(void) {
    uint16_t wpm = get_current_wpm();
    if (wpm > HK_WPM_MAX) {
        wpm = HK_WPM_MAX;
    }

    uint8_t layer = get_highest_layer(layer_state);
    bool auto_mouse_enabled = false;
#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
    auto_mouse_enabled = get_auto_mouse_enable();
#endif

    if (!force_redraw && wpm == last_wpm && layer == last_layer && auto_mouse_enabled == last_auto_mouse) {
        return;
    }

    if (force_redraw) {
        oled_clear();
    }

    render_wpm(wpm);
    render_layer(layer);
    render_auto_mouse(auto_mouse_enabled);

    last_wpm = wpm;
    last_layer = layer;
    last_auto_mouse = auto_mouse_enabled;
    force_redraw = false;
}

bool oled_task_user(void) {
    if (is_keyboard_left()) {
        return false;
    }

    oled_on();

    if (hk_oled_screen == HK_OLED_SCREEN_BLANK) {
        if (!blank_rendered) {
            oled_clear();
            blank_rendered = true;
        }
        return false;
    }

    blank_rendered = false;
    render_status_screen();
    return false;
}
