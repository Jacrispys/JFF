#include "tamagotchi_setttings.h"

#define SCREENSAVER_SETTINGS 2
const char* const screensaver_settings_text[SCREENSAVER_SETTINGS] = {
    "Enabled",
    "Disabled",
};

const uint32_t screensaver_settings_value[SCREENSAVER_SETTINGS] = {0,1};

static void screensaver_settings_changed(VariableItem* item) {
    TamagotchiSettingsApp* app = variable_item_get_context(item);
    uint8_t index = variable_item_get_current_value_index(item);
    app->settings.screensaver_value = screensaver_settings_value[index];
    variable_item_set_current_value_text(item, screensaver_settings_text[app->settings.screensaver_value]);
}

static uint32_t tamagotchi_settings_app_exit(void* context) {
    UNUSED(context);
    return VIEW_NONE;
}

TamagotchiSettingsApp* tamagotchi_settings_app_alloc() {
    TamagotchiSettingsApp* app = malloc(sizeof(TamagotchiSettingsApp));

    // Records
    tamagotchi_settings_load(&app->settings);
    app->gui = furi_record_open(RECORD_GUI);

    app->view_dispatcher = view_dispatcher_alloc();
    view_dispatcher_enable_queue(app->view_dispatcher);
    view_dispatcher_set_event_callback_context(app->view_dispatcher, app);
    
    view_dispatcher_attach_to_gui(app->view_dispatcher, app->gui, ViewDispatcherTypeFullscreen);

    VariableItem* item;
    uint8_t value_index;

    // Item List
    app->variable_item_list =  variable_item_list_alloc();
    View* view = variable_item_list_get_view(app->variable_item_list);
    view_set_previous_callback(view, tamagotchi_settings_app_exit);


    item = variable_item_list_add(
        app->variable_item_list, "Screensaver", SCREENSAVER_SETTINGS, screensaver_settings_changed, app
    );
    value_index = value_index_uint32(
        app->settings.screensaver_value, screensaver_settings_value, SCREENSAVER_SETTINGS
        
    );
    variable_item_set_current_value_index(item, value_index);
    variable_item_set_current_value_text(item, screensaver_settings_text[value_index]);


    // View dispatcher
    view_set_previous_callback(
        variable_item_list_get_view(app->variable_item_list), tamagotchi_settings_app_exit
    );
    view_dispatcher_add_view(app->view_dispatcher, TamagotchiSettingsAppViewVarItemList, variable_item_list_get_view(app->variable_item_list));
    view_dispatcher_switch_to_view(app->view_dispatcher, 0);

    return app;

}



static void free_settings(TamagotchiSettingsApp* app) {
    furi_assert(app);

    view_dispatcher_remove_view(app->view_dispatcher, TamagotchiSettingsAppViewVarItemList);
    variable_item_list_free(app->variable_item_list);
    view_dispatcher_free(app->view_dispatcher);

    furi_record_close(RECORD_GUI);
    free(app);
}

int32_t tamagotchi_settings(void* p) {
    UNUSED(p);
    TamagotchiSettingsApp* app = tamagotchi_settings_app_alloc();
    view_dispatcher_run(app->view_dispatcher);
    tamagotchi_settings_save(&app->settings);
    free_settings(app);
    return 0;
}