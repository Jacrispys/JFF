#pragma once
#include <furi.h>
#include <gui/modules/variable_item_list.h>
#include <gui/view_dispatcher.h>
#include <lib/toolbox/value_index.h>

#define MAX_TEST_SETTINGS 1

typedef struct {
    TestApp* test;
    Gui* gui;
    ViewDispatcher* view_dispatcher;
    VariableItemList* variable_item_list;
} TestApp;