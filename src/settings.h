#pragma once

#include <stdbool.h>
#include <stdint.h>
#include "zx.h"

/* Machine settings kept in the settings file (section "zx"), as esp32zx's NVS */
typedef struct {
    uint8_t model;          /* zx_model_t */
    uint8_t joystick;       /* zx_joystick_t */
    uint8_t tape_fast;      /* 1: standard blocks load at once */
} settings_t;

extern settings_t settings;

void settings_load(void);
void settings_save(void);
