#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <time.h>

typedef uint32_t GColor;
typedef struct GDrawCommand GDrawCommand;
typedef struct GDrawCommandImage GDrawCommandImage;

void gdraw_command_set_fill_color(GDrawCommand *command, GColor color);
void gdraw_command_set_stroke_color(GDrawCommand *command, GColor color);

void *gdraw_command_image_get_command_list(GDrawCommandImage *img);
void gdraw_command_list_iterate(void *list, void *cb, void *context);

typedef int HealthMetric;
typedef int HealthServiceAccessibilityMask;
#define HealthServiceAccessibilityMaskAvailable 1

time_t time_start_of_today();
HealthServiceAccessibilityMask health_service_metric_accessible(HealthMetric metric, time_t start, time_t end);
