
#include "pebble.h"

void gdraw_command_image_destroy(GDrawCommandImage* image) {}
GDrawCommandImage* gdraw_command_image_create_with_resource(uint32_t resource_id) { return NULL; }

int persist_exists(uint32_t key) { return 0; }
int persist_read_data(uint32_t key, void* buffer, size_t buffer_size) { return 0; }
int persist_write_data(uint32_t key, const void* buffer, size_t buffer_size) { return 0; }
