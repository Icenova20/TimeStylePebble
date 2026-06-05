#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "settings.h"

// settings and dynamicSettings are already declared in settings.h and instantiated in settings.c

void test_Settings_updateDynamicSettings_configures_correctly(void) {
    printf("  Testing default values...\n");
    // Test base case (no widgets that override)
    settings.widgets[0] = EMPTY;
    settings.widgets[1] = EMPTY;
    settings.widgets[2] = EMPTY;
    settings.sidebarColor = GColorWhite;
    settings.sidebarTextColor = GColorBlack;

    Settings_updateDynamicSettings();

    assert(dynamicSettings.disableWeather == true);
    assert(dynamicSettings.updateScreenEverySecond == false);
    assert(dynamicSettings.enableAutoBatteryWidget == true);
    assert(dynamicSettings.enableBeats == false);
    assert(dynamicSettings.enableAltTimeZone == false);
    assert(dynamicSettings.iconFillColor == GColorWhite);
    assert(dynamicSettings.iconStrokeColor == GColorBlack);

    printf("  Testing WEATHER_CURRENT widget...\n");
    settings.widgets[0] = WEATHER_CURRENT;
    Settings_updateDynamicSettings();
    assert(dynamicSettings.disableWeather == false);

    printf("  Testing WEATHER_FORECAST_TODAY widget...\n");
    settings.widgets[0] = EMPTY;
    settings.widgets[1] = WEATHER_FORECAST_TODAY;
    Settings_updateDynamicSettings();
    assert(dynamicSettings.disableWeather == false);

    printf("  Testing WEATHER_UV_INDEX widget...\n");
    settings.widgets[1] = EMPTY;
    settings.widgets[2] = WEATHER_UV_INDEX;
    Settings_updateDynamicSettings();
    assert(dynamicSettings.disableWeather == false);

    printf("  Testing SECONDS widget...\n");
    settings.widgets[2] = EMPTY;
    settings.widgets[0] = SECONDS;
    Settings_updateDynamicSettings();
    assert(dynamicSettings.updateScreenEverySecond == true);

    printf("  Testing BATTERY_METER widget...\n");
    settings.widgets[0] = BATTERY_METER;
    Settings_updateDynamicSettings();
    assert(dynamicSettings.enableAutoBatteryWidget == false);

    printf("  Testing BEATS widget...\n");
    settings.widgets[0] = BEATS;
    Settings_updateDynamicSettings();
    assert(dynamicSettings.enableBeats == true);

    printf("  Testing ALT_TIME_ZONE widget...\n");
    settings.widgets[0] = ALT_TIME_ZONE;
    Settings_updateDynamicSettings();
    assert(dynamicSettings.enableAltTimeZone == true);

    printf("  Testing sidebar color GColorBlack...\n");
    settings.sidebarColor = GColorBlack;
    settings.sidebarTextColor = GColorOrange;
    Settings_updateDynamicSettings();
    assert(dynamicSettings.iconFillColor == GColorBlack);
    assert(dynamicSettings.iconStrokeColor == GColorOrange);
}
