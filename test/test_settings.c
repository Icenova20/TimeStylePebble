#include "pebble.h"
#include "settings.h"
#include <stdio.h>
#include <assert.h>

void test_sidebar_color_black() {
    // Test Case 1: Set settings.sidebarColor = GColorBlack
    settings.sidebarColor = GColorBlack;
    settings.sidebarTextColor = GColorWhite;

    Settings_updateDynamicSettings();

    // verify dynamicSettings.iconFillColor == GColorBlack and dynamicSettings.iconStrokeColor == settings.sidebarTextColor
    assert(gcolor_equal(dynamicSettings.iconFillColor, GColorBlack));
    assert(gcolor_equal(dynamicSettings.iconStrokeColor, GColorWhite));
    printf("test_sidebar_color_black passed\n");
}

void test_sidebar_color_non_black() {
    // Test Case 2: Set settings.sidebarColor = GColorOrange
    settings.sidebarColor = GColorOrange;
    settings.sidebarTextColor = GColorWhite;

    Settings_updateDynamicSettings();

    // verify dynamicSettings.iconFillColor == GColorWhite and dynamicSettings.iconStrokeColor == GColorBlack
    assert(gcolor_equal(dynamicSettings.iconFillColor, GColorWhite));
    assert(gcolor_equal(dynamicSettings.iconStrokeColor, GColorBlack));
    printf("test_sidebar_color_non_black passed\n");
}

int main() {
    printf("Running settings tests...\n");

    test_sidebar_color_black();
    test_sidebar_color_non_black();

    printf("All tests passed!\n");
    return 0;
}
