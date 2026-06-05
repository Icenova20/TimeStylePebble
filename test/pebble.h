#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <stddef.h>

#define PBL_COLOR 1
#define PERSIST_DATA_MAX_LENGTH 256

typedef struct GColor8 {
  union {
    uint8_t argb;
    struct {
      uint8_t b:2;
      uint8_t g:2;
      uint8_t r:2;
      uint8_t a:2;
    };
  };
} GColor8;
typedef GColor8 GColor;

#define GColorBlack ((GColor8){.argb = 0b11000000})
#define GColorWhite ((GColor8){.argb = 0b11111111})
#define GColorOrange ((GColor8){.argb = 0b11111000})

bool gcolor_equal(GColor color1, GColor color2);

bool persist_exists(uint32_t key);
void persist_write_bool(uint32_t key, bool value);
int persist_read_int(uint32_t key);
void persist_read_data(uint32_t key, void* data, size_t size);
void persist_write_data(uint32_t key, void* data, size_t size);
void persist_write_int(uint32_t key, int value);

typedef struct GContext GContext;
