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

typedef struct qb
{
	char name[16];
	void *buffer;
	void *rptr,*wptr,*end;		

}qb_t;


int fifo_test(void);
int q_test(void);



int q_init(qb_t *f, int size);
int q_free(qb_t *f);
int q_size(qb_t *f);
int q_read(qb_t *f, void *buf, int buf_size);
void q_write(qb_t *f, const void *buf, int size);



#endif /* FFMPEG_FIFO_H */
