#include "test_app.h"


#define TEST_SETTINGS 2
const char* const test_settings_text[TEST_SETTINGS] = {
    "Test 1",
    "Test 2",
};

static void test_settings_changed(VariableItem* item) {
    TestApp* app = variable_item_get_context(item);
    uint8_t index = variable_item_get_current_value_index(item);

    variable_item_set_current_value_text(item, test_settings_text[index]);
}

static uint32_t test_app_exit(void* context) {
    UNUSED(context);
    return VIEW_NONE;
}

TestApp* test_app_alloc(uint32_t first_scene) {
    TestApp* app = malloc(sizeof(TestApp));

    // Records
    app -> gui = furi_record_open(RECORD_GUI);

    // Item List
    app->variable_item_list =  variable_item_list_alloc();
    View* view = variable_item_list_get_view(app->variable_item_list);
    view_set_previous_callback(view, test_app_exit);

    VariableItem* item;

    item = variable_item_list_add(
        app->variable_item_list, "Test Setting", TEST_SETTINGS, test_settings_changed, app
    );


    // View dispatcher
    app -> view_dispatcher = view_dispatcher_alloc();
    view_dispatcher_enable_queue(app->view_dispatcher);
    view_dispatcher_attach_to_gui(app->view_dispatcher, app->gui, ViewDispatcherTypeFullscreen);
    view_dispatcher_add_view(app->view_dispatcher, 0, view);
    view_dispatcher_switch_to_view(app->view_dispatcher, 0);

    return app;

}



static void free_settings(TestApp* app) {
    furi_assert(app);

    view_dispatcher_remove_view(app->view_dispatcher, TestAppViewVarItemList);
    variable_item_list_free(app->variable_item_list);
    view_dispatcher_free(app->view_dispatcher);

    furi_record_close(RECORD_GUI);
    free(app);
}

int32_t test_app(void* p) {
    UNUSED(p);
    TestApp* app = test_app_alloc();
    view_dispatcher_run(app->view_dispatcher);
    free_settings(app);
    return 0;
}