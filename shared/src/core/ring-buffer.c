#include "ring-buffer.h"



void ring_buffer_setup(ring_buffer_t* rb, uint8_t* buffer, uint32_t length){
    rb->buffer = buffer;
    rb->mask = length-1;
    rb->read_index = 0;
    rb->wrtie_index = 0;
}

bool ring_buffer_read(ring_buffer_t* rb, uint8_t* byte){
    uint32_t local_read_index = rb->read_index;
    uint32_t local_write_index = rb->wrtie_index;

    if(local_read_index == local_write_index){
        return false;
    }
    *byte = rb->buffer[local_read_index];
    local_read_index = (local_read_index + 1) & rb->mask;
    rb->read_index = local_read_index;
    return true;
}
bool ring_buffer_write(ring_buffer_t* rb, uint8_t byte){
    uint32_t local_read_index = rb->read_index;
    uint32_t local_write_index = rb->wrtie_index;

    uint32_t next_write_index = (local_write_index + 1) & rb->mask;

     if(local_read_index == next_write_index){
        return false;
    }

    rb->buffer[local_write_index] = byte;
    rb->wrtie_index = next_write_index;
    return true;
}
bool ring_buffer_empty(ring_buffer_t* rb){
    return (rb->read_index == rb->wrtie_index);
}