#ifndef SDK_EE_EEREGS_H
#define SDK_EE_EEREGS_H

// This file contains only defines so we don't need to extern wrap it

#include <common.h>

#define T_MODE_CLKS_M		(0x03<< 0)
#define T_MODE_GATE_M		(0x01<< 2)
#define T_MODE_GATS_M		(0x01<< 3)
#define T_MODE_GATM_M		(0x03<< 4)
#define T_MODE_ZRET_M		(0x01<< 6)
#define T_MODE_CUE_M		(0x01<< 7)
#define T_MODE_CMPE_M		(0x01<< 8)
#define T_MODE_OVFE_M		(0x01<< 9)
#define T_MODE_EQUF_M		(0x01<<10)
#define T_MODE_OVFF_M		(0x01<<11)

#define T0_COUNT        ((volatile u32*)(0x10000000))
#define T0_MODE         ((volatile u32*)(0x10000010))
#define T0_COMP         ((volatile u32*)(0x10000020))
#define T0_HOLD         ((volatile u32*)(0x10000030))
#define T1_COUNT        ((volatile u32*)(0x10000800))
#define T1_MODE         ((volatile u32*)(0x10000810))
#define T1_COMP         ((volatile u32*)(0x10000820))
#define T1_HOLD         ((volatile u32*)(0x10000830))
#define T2_COUNT        ((volatile u32*)(0x10001000))
#define T2_MODE         ((volatile u32*)(0x10001010))
#define T2_COMP         ((volatile u32*)(0x10001020))
#define T3_COUNT        ((volatile u32*)(0x10001800))
#define T3_MODE         ((volatile u32*)(0x10001810))
#define T3_COMP         ((volatile u32*)(0x10001820))

#endif
