/*
 * Copyright (c) 2012 Jan Vesely
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

/** @addtogroup amdm37xdrvclockcontrolcm
 * @{
 */
/** @file
 * @brief Clock Control Clock Management IO register structure.
 */
#ifndef AMDM37x_CLOCK_CONTROL_CM_H
#define AMDM37x_CLOCK_CONTROL_CM_H
#include <sys/types.h>
#include <macros.h>

/* AM/DM37x TRM p.485 */
#define CLOCK_CONTROL_CM_BASE_ADDRESS  0x48004d00
#define CLOCK_CONTROL_CM_SIZE  8192

/** Clock control register map
 *
 * Periph DPLL == DPLL4
 * Core DPLL == DPLL3
 */
typedef struct {
	ioport32_t clken_pll;
#define CLOCK_CONTROL_CM_CLKEN_PLL_PWRDN_EMU_PERIPH_FLAG   (1 << 31)
#define CLOCK_CONTROL_CM_CLKEN_PLL_PWRDN_CAM_FLAG   (1 << 30)
#define CLOCK_CONTROL_CM_CLKEN_PLL_PWRDN_DSS1_FLAG   (1 << 29)
#define CLOCK_CONTROL_CM_CLKEN_PLL_PWRDN_TV_FLAG   (1 << 28)
#define CLOCK_CONTROL_CM_CLKEN_PLL_PWRDN_96M_FLAG   (1 << 27)
#define CLOCK_CONTROL_CM_CLKEN_PLL_EN_PERIPH_DPLL_DRIFTGUARD_FLAG   (1 << 19)
#define CLOCK_CONTROL_CM_CLKEN_PLL_EN_PERIPH_DPLL_MASK   (0x7 << 16)
#define CLOCK_CONTROL_CM_CLKEN_PLL_EN_PERIPH_DPLL_LP_STOP   (0x1 << 16)
#define CLOCK_CONTROL_CM_CLKEN_PLL_EN_PERIPH_DPLL_LOCK   (0x7 << 16)
#define CLOCK_CONTROL_CM_CLKEN_PLL_PWRDN_EMU_CORE_FLAG   (1 << 12)
#define CLOCK_CONTROL_CM_CLKEN_PLL_EN_CORE_DPLL_LPMODE_FLAG   (1 << 10)
#define CLOCK_CONTROL_CM_CLKEN_PLL_EN_CORE_DPLL_DRIFTGUARD_FLAG   (1 << 3)
#define CLOCK_CONTROL_CM_CLKEN_PLL_EN_CORE_DPLL_MASK   (0x7)
#define CLOCK_CONTROL_CM_CLKEN_PLL_EN_CORE_DPLL_LP_BYPASS   (0x5)
#define CLOCK_CONTROL_CM_CLKEN_PLL_EN_CORE_DPLL_FAST_RELOCK   (0x6)
#define CLOCK_CONTROL_CM_CLKEN_PLL_EN_CORE_DPLL_LOCK   (0x7)

	ioport32_t clken2_pll;
#define CLOCK_CONTROL_CM_CLKEN2_PLL_EN_PERIPH2_DPLL_LPMODE_FLAG   (1 << 10)
#define CLOCK_CONTROL_CM_CLKEN2_PLL_EN_PERIPH2_DPLL_DRIFTGUARD_FLAG   (1 << 3)
#define CLOCK_CONTROL_CM_CLKEN2_PLL_EN_PERIPH2_DPLL_MASK   (0x7)
#define CLOCK_CONTROL_CM_CLKEN2_PLL_EN_PERIPH2_DPLL_LP_STOP   (0x1)
#define CLOCK_CONTROL_CM_CLKEN2_PLL_EN_PERIPH2_DPLL_LOCK   (0x7)

	PADD32[6];

	const ioport32_t idlest_ckgen;
#define CLOCK_CONTROL_CM_IDLEST_CKGEN_ST_EMU_PERIPH_CLK_FLAG   (1 << 13)
#define CLOCK_CONTROL_CM_IDLEST_CKGEN_ST_CAM_CLK_FLAG   (1 << 12)
#define CLOCK_CONTROL_CM_IDLEST_CKGEN_ST_DSS1_CLK_FLAG   (1 << 11)
#define CLOCK_CONTROL_CM_IDLEST_CKGEN_ST_TV_CLK_FLAG   (1 << 10)
#define CLOCK_CONTROL_CM_IDLEST_CKGEN_ST_FUNC96M_CLK_FLAG   (1 << 9)
#define CLOCK_CONTROL_CM_IDLEST_CKGEN_ST_EMU_CORE_CLK_FLAG   (1 << 8)
#define CLOCK_CONTROL_CM_IDLEST_CKGEN_ST_54M_CLK_FLAG   (1 << 5)
#define CLOCK_CONTROL_CM_IDLEST_CKGEN_ST_12M_CLK_FLAG   (1 << 4)
#define CLOCK_CONTROL_CM_IDLEST_CKGEN_ST_48M_CLK_FLAG   (1 << 3)
#define CLOCK_CONTROL_CM_IDLEST_CKGEN_ST_96M_CLK_FLAG   (1 << 2)
#define CLOCK_CONTROL_CM_IDLEST_CKGEN_ST_PERIPH_CLK_FLAG   (1 << 1)
#define CLOCK_CONTROL_CM_IDLEST_CKGEN_ST_CORE_CLK_FLAG   (1 << 0)

	const ioport32_t idlest2_ckgen;
#define CLOCK_CONTROL_CM_IDLEST2_CKGEN_ST_FUNC120M_CLK_FLAG   (1 << 3)
#define CLOCK_CONTROL_CM_IDLEST2_CKGEN_ST_120M_CLK_FLAG   (1 << 1)
#define CLOCK_CONTROL_CM_IDLEST2_CKGEN_ST_PERIPH2_CLK_FLAG   (1 << 0)

	PADD32[2];

	ioport32_t autoidle_pll;
#define CLOCK_CONTROL_CM_AUTOIDLE_PLL_AUTO_PERIPH_DPLL_MASK   (0x7 << 3)
#define CLOCK_CONTROL_CM_AUTOIDLE_PLL_AUTO_PERIPH_DPLL_DISABLED   (0x0 << 3)
#define CLOCK_CONTROL_CM_AUTOIDLE_PLL_AUTO_PERIPH_DPLL_AUTOMATIC   (0x1 << 3)
#define CLOCK_CONTROL_CM_AUTOIDLE_PLL_AUTO_CORE_DPLL_MASK   (0x7)
#define CLOCK_CONTROL_CM_AUTOIDLE_PLL_AUTO_CORE_DPLL_DISABLED   (0x0)
#define CLOCK_CONTROL_CM_AUTOIDLE_PLL_AUTO_CORE_DPLL_AUTOMATIC   (0x1)
#define CLOCK_CONTROL_CM_AUTOIDLE_PLL_AUTO_CORE_DPLL_AUTOMATIC_BYPASS   (0x5)

	ioport32_t autoidle2_pll;
#define CLOCK_CONTROL_CM_AUTOIDLE2_PLL_AUTO_PERIPH2_DPLL_MASK   (0x7)
#define CLOCK_CONTROL_CM_AUTOIDLE2_PLL_AUTO_PERIPH2_DPLL_DISABLED   (0x0)
#define CLOCK_CONTROL_CM_AUTOIDLE2_PLL_AUTO_PERIPH2_DPLL_AUTOMATIC   (0x1)

	PADD32[2];

	ioport32_t clksel1_pll;
#define CLOCK_CONTROL_CM_CLKSEL1_PLL_CORE_DPLL_CLKOUT_DIV_MASK   (0x1f << 27)
#define CLOCK_CONTROL_CM_CLKSEL1_PLL_CORE_DPLL_CLKOUT_DIV_CREATE(x)   (((x) & 0x1f) << 27)
#define CLOCK_CONTROL_CM_CLKSEL1_PLL_CORE_DPLL_CLKOUT_DIV_GET(x)   (((x) >> 27) & 0x1f)
#define CLOCK_CONTROL_CM_CLKSEL1_PLL_CORE_DPLL_MULT_MASK   (0x7ff << 16)
#define CLOCK_CONTROL_CM_CLKSEL1_PLL_CORE_DPLL_MULT_CREATE(x)   (((x) & 0x7ff) << 16)
#define CLOCK_CONTROL_CM_CLKSEL1_PLL_CORE_DPLL_MULT_GET(x)   (((x) >> 16) & 0x7ff)
#define CLOCK_CONTROL_CM_CLKSEL1_PLL_CORE_DPLL_DIV_MASK   (0x7f << 8)
#define CLOCK_CONTROL_CM_CLKSEL1_PLL_CORE_DPLL_DIV_CREATE(x)   (((x) & 0x7f) << 8)
#define CLOCK_CONTROL_CM_CLKSEL1_PLL_CORE_DPLL_DIV_GET(x)   (((x) >> 8) & 0x7f)
#define CLOCK_CONTROL_CM_CLKSEL1_PLL_SOURCE_96M_FLAG   (1 << 6)
#define CLOCK_CONTROL_CM_CLKSEL1_PLL_SOURCE_54M_FLAG   (1 << 5)
#define CLOCK_CONTROL_CM_CLKSEL1_PLL_SOURCE_48M_FLAG   (1 << 3)

	ioport32_t clksel2_pll;
#define CLOCK_CONTROL_CM_CLKSEL2_PLL_SD_DIV_MASK   (0xff << 24)
#define CLOCK_CONTROL_CM_CLKSEL2_PLL_SD_DIV_(x)   (((x) & 0xff) << 24)
#define CLOCK_CONTROL_CM_CLKSEL2_PLL_DCO_SEL_MASK   (0x7 << 21)
#define CLOCK_CONTROL_CM_CLKSEL2_PLL_DCO_SEL_500   (0x2 << 21)
#define CLOCK_CONTROL_CM_CLKSEL2_PLL_DCO_SEL_1000   (0x4 << 21)
#define CLOCK_CONTROL_CM_CLKSEL2_PLL_PERIPH_DPLL_MULT_MASK   (0xfff << 8)
#define CLOCK_CONTROL_CM_CLKSEL2_PLL_PERIPH_DPLL_MULT(x)   (((x) & 0xfff) << 8)
#define CLOCK_CONTROL_CM_CLKSEL2_PLL_PERIPH_DPLL_DIV_MASK   (0x7f)
#define CLOCK_CONTROL_CM_CLKSEL2_PLL_PERIPH_DPLL_DIV(x)   ((x) & 0x7f)

	ioport32_t clksel3_pll;
#define CLOCK_CONTROL_CM_CLKSEL3_PLL_DIV_96M_MASK   (0xf)
#define CLOCK_CONTROL_CM_CLKSEL3_PLL_DIV_96M(x)   ((x) & 0xf)

	ioport32_t clksel4_pll;
#define CLOCK_CONTROL_CM_CLKSEL4_PLL_PERIPH2_DPLL_MULT_MASK   (0x7ff << 8)
#define CLOCK_CONTROL_CM_CLKSEL4_PLL_PERIPH2_DPLL_MULT_CREATE(x)   (((x) & 0x7ff) << 8)
#define CLOCK_CONTROL_CM_CLKSEL4_PLL_PERIPH2_DPLL_MULT_GET(x)   (((x) >> 8) & 0x7ff)
#define CLOCK_CONTROL_CM_CLKSEL4_PLL_PERIPH2_DPLL_DIV_MASK   (0x7f)
#define CLOCK_CONTROL_CM_CLKSEL4_PLL_PERIPH2_DPLL_DIV_CREATE(x)   ((x) & 0x7f)
#define CLOCK_CONTROL_CM_CLKSEL4_PLL_PERIPH2_DPLL_DIV_GET(x)   ((x) & 0x7f)

	ioport32_t clksel5_pll;
#define CLOCK_CONTROL_CM_CLKSEL5_PLL_DIV120M_MASK   (0x1f)
#define CLOCK_CONTROL_CM_CLKSEL5_PLL_DIV120M_CREATE(x)   ((x) & 0x1f)
#define CLOCK_CONTROL_CM_CLKSEL5_PLL_DIV120M_GET(x)   ((x) & 0x1f)
} clock_control_cm_regs_t;

#endif
/**
 * @}
 */

