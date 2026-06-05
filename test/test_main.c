#include <stdio.h>
#include "settings.h"

extern void test_Settings_updateDynamicSettings_configures_correctly(void);

int main() {
    printf("Running tests...\n");
    test_Settings_updateDynamicSettings_configures_correctly();
    printf("All tests passed!\n");
    return 0;
}
