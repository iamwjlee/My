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

typedef struct msg
{
	char key;
	int type;

}msg_t;



int q_size(qb_t *f)
{
    int size = f->wptr - f->rptr;
    if (size < 0)
        size += f->end - f->buffer;
    return size;
}


int q_read(qb_t *f, void *buf, int buf_size)
{
 //   return q_generic_read(f, buf_size, NULL, buf);
   int size = q_size(f);

    if (size < buf_size)
        return 1;
    do {
        int len = FFMIN(f->end - f->rptr, buf_size);
        memcpy(buf, f->rptr, len);
        buf = (u8*)buf + len;
        //q_drain(f, len);
	    f->rptr += len;
		if (f->rptr >= f->end)
			f->rptr -= f->end - f->buffer;



        buf_size -= len;
    } while (buf_size > 0);
    return 0;


}
void q_write(qb_t *f, const void *buf, int size)
{
    do {
        int len = FFMIN(f->end - f->wptr, size);
        memcpy(f->wptr, buf, len);
        f->wptr += len;
        if (f->wptr >= f->end)
            f->wptr = f->buffer;
        buf = (u8*)buf + len;
        size -= len;
    } while (size > 0);
}

int q_free(qb_t *p)
{

	free(p->buffer);
	free(p);
	return 0;
}

int msg_q_init(int size)
{
	qb_t *p = malloc(sizeof(qb_t));
	p->buffer = (msg_t *)malloc(sizeof(msg_t)*size);
	p->wptr=p->rptr=p->buffer;	
	p->end = (msg_t *)p->buffer + size;


	return 0;
}

int fifo_test(void)
{
	int size= 10;
	u8 buf;
	qb_t *p = malloc(sizeof(qb_t));
	p->buffer = (u8 *)malloc(size);
	
	p->wptr=p->rptr=p->buffer;	
	p->end = (msg_t *)p->buffer + size;

	print("fifo test");
	buf=1;
	q_write(p,&buf,1);
	buf=2;
	q_write(p,&buf,1);

	if(!q_read(p,&buf,1))
		print("read[%d] qsize[%d]",buf,q_size(p));
	if(!q_read(p,&buf,1))
		print("read[%d] qsize[%d]",buf,q_size(p));
	if(!q_read(p,&buf,1))
		print("read[%d] qsize[%d]",buf,q_size(p));

	//q_free(p->buffer);
	q_free(p);

	return 0;
}
int q_test(void)
{
	msg_t my_msg;
	int i=0;
	int size = 5;
	print("size of msg_t [%d] sizeof qb_t[%d]",sizeof(msg_t),sizeof(qb_t));
	qb_t *p = malloc(sizeof(qb_t));
	p->buffer = (msg_t *)malloc(sizeof(msg_t)*size);
	p->wptr=p->rptr=p->buffer;	
	p->end = (msg_t *)p->buffer + size;

	my_msg.key=31;
	my_msg.type=1;
	q_write(p,&my_msg,sizeof(msg_t));
	my_msg.key=32;
	my_msg.type=2;
	q_write(p,&my_msg,sizeof(msg_t));
	my_msg.key=33;
	my_msg.type=3;
	q_write(p,&my_msg,sizeof(msg_t));

	if(!q_read(p,&my_msg,sizeof(msg_t)))
		print("q_read %d %d",my_msg.key,my_msg.type);

	if(!q_read(p,&my_msg,sizeof(msg_t)))
		print("q_read %d %d",my_msg.key,my_msg.type);
	if(!q_read(p,&my_msg,sizeof(msg_t)))
		print("q_read %d %d",my_msg.key,my_msg.type);
	if(!q_read(p,&my_msg,sizeof(msg_t)))
		print("q_read %d %d",my_msg.key,my_msg.type);

	i++;
	q_free(p);
	return 0;
}


