/*
 * Copyright (c) 2009 Lukas Mejdrech
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 * - The name of the author may not be used to endorse or promote products
 *   derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/** @addtogroup libc
 *  @{
 */

/** @file
 * Dynamic first in first out positive integer queue.
 * Possitive integer values only.
 */

#ifndef LIBC_DYNAMIC_FIFO_H_
#define LIBC_DYNAMIC_FIFO_H_

/** Type definition of the dynamic fifo queue.
 * @see dyn_fifo
 */
typedef struct dyn_fifo	dyn_fifo_t;

/** Dynamic first in first out positive integer queue.
 * Possitive integer values only.
 * The queue automatically resizes if needed.
 */
struct dyn_fifo {
	/** Stored item field. */
	int *items;
	/** Actual field size. */
	int size;
	/** First item in the queue index. */
	int head;
	/** Last item in the queue index. */
	int tail;
	/** Consistency check magic value. */
	int magic_value;
};

extern int dyn_fifo_initialize(dyn_fifo_t *, int);
extern int dyn_fifo_destroy(dyn_fifo_t *);
extern int dyn_fifo_push(dyn_fifo_t *, int, int);
extern int dyn_fifo_pop(dyn_fifo_t *);
extern int dyn_fifo_value(dyn_fifo_t *);

#endif

/** @}
 */
