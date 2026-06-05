#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

typedef uint32_t GColor;
#define GColorBlack 0
#define GColorWhite 1
#define GColorOrange 2
#define gcolor_equal(a, b) ((a) == (b))

#define PBL_COLOR

#define persist_exists(key) false
#define persist_read_int(key) 0
#define persist_read_data(key, val, len)
#define persist_read_bool(key) false
#define persist_write_int(key, val)
#define persist_write_data(key, val, len)
#define persist_write_bool(key, val)

#define PERSIST_DATA_MAX_LENGTH 256

#define APP_LOG_LEVEL_DEBUG 0
#define APP_LOG(level, ...)
typedef struct GContext GContext;
#include <time.h>
