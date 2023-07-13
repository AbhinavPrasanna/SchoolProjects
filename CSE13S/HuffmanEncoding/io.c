#include "io.h"
#include "code.h"
#include "stdio.h"

#include <fcntl.h>
#include <unistd.h>

static uint8_t buffer[BLOCK];
static uint32_t bit_index = 0;
uint64_t bytes_read = 0;
static uint32_t end_buffer = 0;
uint64_t bytes_written = 0;

int read_bytes(int infile, uint8_t *buf, int nbytes) {
    int total = 0;
    int bytes = -2;
    bool bytecheck = (bytes > 0 || bytes == -2);
    bool totalcheck = (total != nbytes);
    while (bytecheck && totalcheck) {
        bytes = read(infile, buf, nbytes - total);
        total += bytes;
        bytecheck = (bytes > 0 || bytes == -2);
        totalcheck = total != nbytes;
    }
    bytes_read += total;
    return total;
}

int write_bytes(int outfile, uint8_t *buf, int nbytes) {
    int total = 0;
    int bytes = -2;
    bool bytecheck = (bytes > 0 || bytes == -2);
    bool totalcheck = (total != nbytes);
    while (bytecheck && totalcheck) {
        bytes = write(outfile, buf, nbytes - total);
        total += bytes;
        bytecheck = (bytes > 0 || bytes == -2);
        totalcheck = (total != nbytes);
    }
    bytes_written += total;
    return total;
}

bool read_bit(int infile, uint8_t *bit) {
    if (bit_index == 0) {
        end_buffer = read_bytes(infile, buffer, BLOCK) * 8;
    }
    uint32_t bitposition = bit_index % 8;
    uint32_t byteposition = bit_index / 8;
    *bit = ((buffer[byteposition] >> bitposition) & 1);
    bit_index++;
    bit_index %= (BLOCK * 8);
    if (bit_index > end_buffer) {
        return false;
    }
    return true;
}

void write_code(int outfile, Code *c) {
    uint32_t index = 0;
    uint32_t bitposition = 0;
    uint32_t byteposition = 0;
    uint8_t bit = 0;
    bool bitcheck = false;
    while (index < c->top) {
        bitposition = bit_index % 8;
        byteposition = bit_index / 8;
        bit = ((buffer[byteposition] >> bitposition) & 1);
        bitcheck = (bit == 1);
        if (bitcheck) {
            bitposition = bit_index % 8;
            byteposition = bit_index / 8;
            buffer[byteposition] |= (1 << bitposition);
        } else {
            bitposition = bit_index % 8;
            byteposition = bit_index / 8;
            buffer[byteposition] &= ~(1 << bitposition);
        }
        index++;
        bit_index += 1;
        if (bit_index == 8 * BLOCK) {
            write_bytes(outfile, buffer, BLOCK);
            bit_index = 0;
        }
    }
}

void flush_codes(int outfile) {
    uint8_t mask = (1 << (bit_index % 8)) - 1;
    uint32_t bytes = bit_index / 8;
    if (mask) {
        bytes++;
        buffer[bytes] = buffer[bytes] & mask;
    }
    write_bytes(outfile, buffer, bytes);
}
