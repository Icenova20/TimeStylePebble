
#ifndef PEBBLE_MOCK_H
#define PEBBLE_MOCK_H

#include <stdint.h>
#include <string.h>

// Mock types
typedef struct GDrawCommandImage GDrawCommandImage;

// Mock functions
void gdraw_command_image_destroy(GDrawCommandImage* image);
GDrawCommandImage* gdraw_command_image_create_with_resource(uint32_t resource_id);

int persist_exists(uint32_t key);
int persist_read_data(uint32_t key, void* buffer, size_t buffer_size);
int persist_write_data(uint32_t key, const void* buffer, size_t buffer_size);

#endif
