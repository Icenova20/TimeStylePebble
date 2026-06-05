#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

int tests_run = 0;
int tests_passed = 0;

void test_beats(int hour, int min, int sec, int expected_beats, const char* name) {
    tests_run++;
    struct tm time_info;
    memset(&time_info, 0, sizeof(time_info));
    time_info.tm_year = 120; // 2020
    time_info.tm_mon = 0; // Jan
    time_info.tm_mday = 1; // 1st
    time_info.tm_hour = hour;
    time_info.tm_min = min;
    time_info.tm_sec = sec;
    time_info.tm_isdst = -1;

    int beats = time_get_beats(&time_info);
    if (beats == expected_beats) {
        printf("✅ PASS: %s\n", name);
        tests_passed++;
    } else {
        printf("❌ FAIL: %s - Expected %d, got %d\n", name, expected_beats, beats);
    }
}

int main() {
    printf("🧪 Running time_get_beats test suite...\n");

    // We set timezone to UTC to ensure mktime treats our struct tm as UTC.
    setenv("TZ", "UTC", 1);
    tzset();

    // Swatch Internet Time (BMT) is UTC + 1 hour.
    // 000 beats is midnight BMT.
    // 500 beats is noon BMT.
    // 1 beat is 86.4 seconds.

    test_beats(23, 0, 0, 0, "Midnight BMT (23:00:00 UTC) -> @000");
    test_beats(11, 0, 0, 500, "Noon BMT (11:00:00 UTC) -> @500");
    test_beats(22, 59, 59, 999, "Just before midnight BMT (22:59:59 UTC) -> @999");
    test_beats(5, 0, 0, 250, "06:00:00 BMT (05:00:00 UTC) -> @250");
    test_beats(17, 0, 0, 750, "18:00:00 BMT (17:00:00 UTC) -> @750");
    test_beats(23, 1, 26, 0, "Just before one beat BMT (23:01:26 UTC) -> @000");
    test_beats(23, 1, 27, 1, "Just after one beat (23:01:27 UTC) -> @001");

    printf("\n📊 Results: %d/%d tests passed.\n", tests_passed, tests_run);

    if (tests_passed == tests_run) {
        return 0;
    } else {
        return 1;
    }
}
