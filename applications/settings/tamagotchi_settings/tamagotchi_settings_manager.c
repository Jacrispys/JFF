#include "tamagotchi_settings_manager.h"

#include <furi.h>
#include <../lib/toolbox/saved_struct.h>
#include <storage/storage.h>

#define TAMAGOTCHI_SETTINGS_PATH INT_PATH(TAMAGOTCHI_SETTINGS_FILE_NAME)
#define TAMAGOTCHI_SETTINGS_VERSION (0)
#define TAMAGOTCHI_SETTINGS_MAGIC (0x19)

bool tamagotchi_settings_load(TamagotchiSettings* tamagotchi_settings) {
    furi_assert(tamagotchi_settings);

    return saved_struct_load(TAMAGOTCHI_SETTINGS_PATH, tamagotchi_settings,
                             sizeof(TamagotchiSettings),
                             TAMAGOTCHI_SETTINGS_MAGIC,
                             TAMAGOTCHI_SETTINGS_VERSION);

}

bool tamagotchi_settings_save(TamagotchiSettings* tamagotchi_settings) {
    furi_assert(tamagotchi_settings);

    return saved_struct_save(TAMAGOTCHI_SETTINGS_PATH, tamagotchi_settings,
                             sizeof(TamagotchiSettings),
                             TAMAGOTCHI_SETTINGS_MAGIC,
                             TAMAGOTCHI_SETTINGS_VERSION);

}