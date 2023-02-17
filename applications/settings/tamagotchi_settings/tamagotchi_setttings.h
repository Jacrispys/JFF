#pragma once
#include <furi.h>
#include <gui/gui.h>
#include <gui/modules/variable_item_list.h>
#include <gui/view_dispatcher.h>
#include <lib/toolbox/value_index.h>

#define MAX_TAMAGOTCHI_SETTINGS 1

typedef struct {
    Gui* gui;
    ViewDispatcher* view_dispatcher;
    VariableItemList* variable_item_list;
    bool screensaver_value;
} TamagotchiSettingsApp;

typedef enum {
    TamagotchiSettingsAppViewVarItemList,
} TamagotchiSettingsAppView;
