/*
 * This file is part of FFmpeg.
 *
 * FFmpeg is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * FFmpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with FFmpeg; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

/**
 * @file fifo.h
 * A very simple circular buffer FIFO implementation.
 */

#ifndef FFMPEG_FIFO_H
#define FFMPEG_FIFO_H

#include <stdint.h>

#define FFMAX(a,b) ((a) > (b) ? (a) : (b))
#define FFMIN(a,b) ((a) > (b) ? (b) : (a))

typedef struct qBuffer {
    u8 *buffer;
    u8 *rptr, *wptr, *end;
}qBuffer;



int q_test(void);
/**
 * Initializes an AVFifoBuffer.
 * @param *f AVFifoBuffer to initialize
 * @param size of FIFO
 * @return <0 for failure >=0 otherwise
 */
int q_init(qBuffer *f, int size);

/**
 * Frees an AVFifoBuffer.
 * @param *f AVFifoBuffer to free
 */
void q_free(qBuffer *f);

/**
 * Returns the amount of data in bytes in the AVFifoBuffer, that is the
 * amount of data you can read from it.
 * @param *f AVFifoBuffer to read from
 * @return size
 */
int q_size(qBuffer *f);

/**
 * Reads data from an AVFifoBuffer.
 * @param *f AVFifoBuffer to read from
 * @param *buf data destination
 * @param buf_size number of bytes to read
 */
int q_read(qBuffer *f, u8 *buf, int buf_size);

/**
 * Feeds data from an AVFifoBuffer to a user supplied callback.
 * @param *f AVFifoBuffer to read from
 * @param buf_size number of bytes to read
 * @param *func generic read function
 * @param *dest data destination
 */
int q_generic_read(qBuffer *f, int buf_size, void (*func)(void*, void*, int), void* dest);

/**
 * Writes data into an AVFifoBuffer.
 * @param *f AVFifoBuffer to write to
 * @param *buf data source
 * @param size data size
 */
void q_write(qBuffer *f, const u8 *buf, int size);

/**
 * Resizes an AVFifoBuffer.
 * @param *f AVFifoBuffer to resize
 * @param size new AVFifoBuffer size in bytes
 */
void q_realloc(qBuffer *f, unsigned int size);

/**
 * Reads and discards the specified amount of data from an AVFifoBuffer.
 * @param *f AVFifoBuffer to read from
 * @param size amount of data to read in bytes
 */
void q_drain(qBuffer *f, int size);

static inline u8 q_peek(qBuffer *f, int offs)
{
    u8 *ptr = f->rptr + offs;
    if (ptr >= f->end)
        ptr -= f->end - f->buffer;
    return *ptr;
}
#endif /* FFMPEG_FIFO_H */
