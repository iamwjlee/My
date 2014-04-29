/*
 * A very simple circular buffer FIFO implementation
 * Copyright (c) 2000, 2001, 2002 Fabrice Bellard
 * Copyright (c) 2006 Roman Shaposhnik
 *
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
#include "common.h"
#include "q.h"

int q_test(void)
{
	u8 buf;
	u8 read;
	qBuffer *p=malloc(sizeof(qBuffer));
	q_init(p,10);
	print("q_size = %d",q_size(p));
	buf=1;
	q_write(p,&buf,1);
	buf=2;
	q_write(p,&buf,1);

	print("q_size = %d",q_size(p));
	q_read(p,&read,1);

	print("read = %d",read);
	print("q_size = %d",q_size(p));

	q_read(p,&read,1);
	print("read = %d",read);
	print("q_size = %d",q_size(p));

	if(q_read(p,&read,1)>0)
	{
	print("read = %d",read);
	print("q_size = %d",q_size(p));
	}

	if(q_read(p,&read,1)>0)
	{
	print("read = %d",read);
	print("q_size = %d",q_size(p));
	}
	
	q_free(p);
	free(p);

	return 0;
}
int q_init(qBuffer *f, int size)
{
    f->wptr = f->rptr =
    f->buffer = malloc(size);
    f->end = f->buffer + size;
    if (!f->buffer)
        return -1;
    return 0;
}

void q_free(qBuffer *f)
{
    free(f->buffer);
}

int q_size(qBuffer *f)
{
    int size = f->wptr - f->rptr;
    if (size < 0)
        size += f->end - f->buffer;
    return size;
}

/**
 * Get data from the fifo (returns -1 if not enough data).
 */
int q_read(qBuffer *f, u8 *buf, int buf_size)
{
    return q_generic_read(f, buf_size, NULL, buf);
}

/**
 * Resizes a FIFO.
 */
void q_realloc(qBuffer *f, unsigned int new_size) {
    unsigned int old_size= f->end - f->buffer;

    if(old_size < new_size){
        int len= q_size(f);
        qBuffer f2;

        q_init(&f2, new_size);
        q_read(f, f2.buffer, len);
        f2.wptr += len;
        free(f->buffer);
        *f= f2;
    }
}

void q_write(qBuffer *f, const u8 *buf, int size)
{
    do {
        int len = FFMIN(f->end - f->wptr, size);
        memcpy(f->wptr, buf, len);
        f->wptr += len;
        if (f->wptr >= f->end)
            f->wptr = f->buffer;
        buf += len;
        size -= len;
    } while (size > 0);
}


/** get data from the fifo (return -1 if not enough data) */
int q_generic_read(qBuffer *f, int buf_size, void (*func)(void*, void*, int), void* dest)
{
    int size = q_size(f);

    if (size < buf_size)
        return -1;
    do {
        int len = FFMIN(f->end - f->rptr, buf_size);
        if(func) func(dest, f->rptr, len);
        else{
            memcpy(dest, f->rptr, len);
            dest = (u8*)dest + len;
        }
        q_drain(f, len);
        buf_size -= len;
    } while (buf_size > 0);
    return 0;
}

/** discard data from the fifo */
void q_drain(qBuffer *f, int size)
{
    f->rptr += size;
    if (f->rptr >= f->end)
        f->rptr -= f->end - f->buffer;
}
