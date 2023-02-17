#pragma once
#include <furi.h>
#include <gui/gui.h>
#include <gui/modules/variable_item_list.h>
#include <gui/view_dispatcher.h>
#include <lib/toolbox/value_index.h>
#include "value_index.h"
#include "tamagotchi_settings_manager.h"

typedef struct {
    Gui* gui;
    ViewDispatcher* view_dispatcher;
    VariableItemList* variable_item_list;
    TamagotchiSettings settings;
} TamagotchiSettingsApp;


typedef enum {
    TamagotchiSettingsAppViewVarItemList,
} TamagotchiSettingsAppView;
