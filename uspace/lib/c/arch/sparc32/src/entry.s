#
# Copyright (c) 2006 Martin Decky
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
# - Redistributions of source code must retain the above copyright
#   notice, this list of conditions and the following disclaimer.
# - Redistributions in binary form must reproduce the above copyright
#   notice, this list of conditions and the following disclaimer in the
#   documentation and/or other materials provided with the distribution.
# - The name of the author may not be used to endorse or promote products
#   derived from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
# OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
# IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
# NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
# THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#

.section .init, "ax"

.org 0

.globl __entry

## User-space task entry point
#
# %o0 contains uarg
# %o1 contains pcb_ptr
#
__entry:
	#
	# Create the first stack frame.
	#
	
	save %sp, -176, %sp
	## XXX	flushw
	mov 7, %g1
	1:
		subcc %g1, 1, %g1
		bg 1b
		save %sp, -64, %sp
	
	mov 7, %g1
	1:
		subcc %g1, 1, %g1
		bg 1b
		restore
	
	## XXX end flush
	## add %g0, -0x7ff, %fp
	set 0x80000000, %fp
	
	# Pass pcb_ptr as the first argument to __main()
	mov %i1, %o0
	sethi %hi(_gp), %l7
	call __main
	or %l7, %lo(_gp), %l7
