#include "pebble.h"

bool gcolor_equal(GColor color1, GColor color2) {
  return color1.argb == color2.argb;
}

bool persist_exists(uint32_t key) { (void)key; return false; }
void persist_write_bool(uint32_t key, bool value) { (void)key; (void)value; }
int persist_read_int(uint32_t key) { (void)key; return 0; }
void persist_read_data(uint32_t key, void* data, size_t size) { (void)key; (void)data; (void)size; }
void persist_write_data(uint32_t key, void* data, size_t size) { (void)key; (void)data; (void)size; }
void persist_write_int(uint32_t key, int value) { (void)key; (void)value; }
