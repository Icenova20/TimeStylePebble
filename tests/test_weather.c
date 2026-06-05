
#include <assert.h>
#include <stdio.h>
#include "../src/c/weather.h"

// Since pebble.h is mocked out, uint32_t is needed
#include <stdint.h>

extern uint32_t getConditionIcon(WeatherCondition conditionCode);

int main() {
    assert(getConditionIcon(CLEAR_DAY) == RESOURCE_ID_WEATHER_CLEAR_DAY);
    assert(getConditionIcon(CLEAR_NIGHT) == RESOURCE_ID_WEATHER_CLEAR_NIGHT);
    assert(getConditionIcon(CLOUDY_DAY) == RESOURCE_ID_WEATHER_CLOUDY);
    assert(getConditionIcon(HEAVY_RAIN) == RESOURCE_ID_WEATHER_HEAVY_RAIN);
    assert(getConditionIcon(HEAVY_SNOW) == RESOURCE_ID_WEATHER_HEAVY_SNOW);
    assert(getConditionIcon(LIGHT_RAIN) == RESOURCE_ID_WEATHER_LIGHT_RAIN);
    assert(getConditionIcon(LIGHT_SNOW) == RESOURCE_ID_WEATHER_LIGHT_SNOW);
    assert(getConditionIcon(PARTLY_CLOUDY_NIGHT) == RESOURCE_ID_WEATHER_PARTLY_CLOUDY_NIGHT);
    assert(getConditionIcon(PARTLY_CLOUDY) == RESOURCE_ID_WEATHER_PARTLY_CLOUDY);
    assert(getConditionIcon(RAINING_AND_SNOWING) == RESOURCE_ID_WEATHER_RAINING_AND_SNOWING);
    assert(getConditionIcon(THUNDERSTORM) == RESOURCE_ID_WEATHER_THUNDERSTORM);

    // Edge case / Default
    assert(getConditionIcon(WEATHER_GENERIC) == RESOURCE_ID_WEATHER_GENERIC);
    assert(getConditionIcon((WeatherCondition)999) == RESOURCE_ID_WEATHER_GENERIC);

    printf("All weather condition icon mapping tests passed!\n");
    return 0;
}
