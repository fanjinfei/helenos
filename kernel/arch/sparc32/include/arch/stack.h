/*
 * Copyright (c) 2005 Jakub Jermar
 * Copyright (c) 2013 Jakub Klama
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

/** @addtogroup sparc32
 * @{
 */
/** @file
 */

#ifndef KERN_sparc32_STACK_H_
#define KERN_sparc32_STACK_H_

#include <config.h>

#define MEM_STACK_SIZE  STACK_SIZE

#define STACK_ITEM_SIZE  4
#define STACK_ALIGNMENT  8

/**
 * 16-extended-word save area for %i[0-7] and %l[0-7] registers.
 */
#define STACK_WINDOW_SAVE_AREA_SIZE  (16 * STACK_ITEM_SIZE)

/**
 * Six extended words for first six arguments.
 */
#define STACK_ARG_SAVE_AREA_SIZE  (6 * STACK_ITEM_SIZE)

/**
 * Offsets of arguments on stack.
 */
#define STACK_ARG0  0
#define STACK_ARG1  4
#define STACK_ARG2  8
#define STACK_ARG3  12
#define STACK_ARG4  16
#define STACK_ARG5  20
#define STACK_ARG6  24

#endif

/** @}
 */
