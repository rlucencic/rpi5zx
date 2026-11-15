#include "emu/settings.h"
#include "settings.h"

#define NAMESPACE   "zx"

settings_t settings;

void settings_load(void)
{
    settings.model = ZX_MODEL_128;
    settings.joystick = ZX_JOYSTICK_KEMPSTON;
    settings.tape_fast = 1;
    int32_t v;
    if (emu_setting_get_int(NAMESPACE, "model", &v) && v >= 0 && v < ZX_MODEL_COUNT) {
        settings.model = v;
    }
    if (emu_setting_get_int(NAMESPACE, "joystick", &v) && v >= 0 && v < ZX_JOYSTICK_COUNT) {
        settings.joystick = v;
    }
    if (emu_setting_get_int(NAMESPACE, "tape_fast", &v)) {
        settings.tape_fast = v != 0;
    }
}

void settings_save(void)
{
    emu_setting_set_int(NAMESPACE, "model", settings.model);
    emu_setting_set_int(NAMESPACE, "joystick", settings.joystick);
    emu_setting_set_int(NAMESPACE, "tape_fast", settings.tape_fast);
}
