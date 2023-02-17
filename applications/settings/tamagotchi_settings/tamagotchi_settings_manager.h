#pragma once

#include "tamagotchi_settings_filename.h"

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint8_t screensaver_value;
} TamagotchiSettings;

bool tamagotchi_settings_load(TamagotchiSettings* tamagotchi_settings);

bool tamagotchi_settings_save(TamagotchiSettings* tamagotchi_settings);

#ifdef __cplusplus
}
#endif
