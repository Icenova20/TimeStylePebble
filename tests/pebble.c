#include "pebble.h"
#include <stdlib.h>

void gdraw_command_set_fill_color(GDrawCommand *command, GColor color) {}
void gdraw_command_set_stroke_color(GDrawCommand *command, GColor color) {}

void *gdraw_command_image_get_command_list(GDrawCommandImage *img) { return NULL; }
void gdraw_command_list_iterate(void *list, void *cb, void *context) {}

time_t time_start_of_today() { return 0; }
HealthServiceAccessibilityMask health_service_metric_accessible(HealthMetric metric, time_t start, time_t end) { return 0; }
