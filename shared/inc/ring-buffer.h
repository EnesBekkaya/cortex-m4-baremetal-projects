#ifndef INC_RİNG_BUFFER_H
#define INC_RİNG_BUFFER_H

#include "common-defines.h"

typedef struct ring_buffer_t{
    uint8_t* buffer;
    uint32_t mask;
    uint32_t read_index;
    uint32_t wrtie_index;
}ring_buffer_t;

void ring_buffer_setup(ring_buffer_t* rb, uint8_t* buffer, uint32_t length);
bool ring_buffer_read(ring_buffer_t* rb, uint8_t* byte);
bool ring_buffer_write(ring_buffer_t* rb, uint8_t byte);
bool ring_buffer_empty(ring_buffer_t* rb);
#endif