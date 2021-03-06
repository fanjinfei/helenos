/*
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

#ifndef BOOT_sparc32_ASM_H_
#define BOOT_sparc32_ASM_H_

#include <typedefs.h>

extern uintptr_t boot_ctx_table;

static inline uint32_t asi_u32_read(unsigned int asi, uintptr_t va)
{
	uint32_t v;
	
	asm volatile (
		"lda [%[va]] %[asi], %[v]\n"
		: [v] "=r" (v)
		: [va] "r" (va),
		  [asi] "i" (asi)
	);
	
	return v;
}

static inline void asi_u32_write(unsigned int asi, uintptr_t va, uint32_t v)
{
	asm volatile (
		"sta %[v], [%[va]] %[asi]\n"
		:: [v] "r" (v),
		   [va] "r" (va),
		   [asi] "i" (asi)
		: "memory"
	);
}

extern void jump_to_kernel(void *, bootinfo_t *);

#endif
