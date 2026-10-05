#include "common.h"
#include <eac/real/core/timer.h>
#include <sdk/ee/eeregs.h>

// EE clock frequency in hertz. TODO better spot pl0x
#define EE_FREQUENCY 147456000

// TODO header
extern i16 D_002C5994; // this is iCountTicks
extern i32 D_002C5AB4; // this is TIMERhz
extern int bIsTimerInited;
extern void REAL_addexit(void(*exitfunc)());

// TODO sdk AddIntcHandler2
void func_002642C0(int interupt, void(*handler)(void*), void* user);

static void tmrint(void*);

#ifndef SKIP_ASM
INCLUDE_ASM("asm/nonmatchings/eac/real/realcore/ps2/inittmr", TIMER_init);
#else
int TIMER_init(int hz)
{
    i32 timerCount;
    i32 divisor;
    i32 timerRate;
    i16 ticksExtended;

    if(!bIsTimerInited)
    {
        // Default to 100hz timer frequency if the library user
        // passes 0hz.
        if(hz == 0)
        {
            hz = 100;
        }

        // Compute the EE timer tick rate based on the timer rate.
        // Depending on how fast the timer should tick, this computes
        // an appropiate divisor for the timer periphial.
        if(hz < 3150)
        {
            if(hz < 196)
            {
                // The best rate is timer frequency div 256.
                timerRate = (EE_FREQUENCY/256);
                timerCount = (hz / 2) + (EE_FREQUENCY/256);
                divisor = 2;
            }
            else
            {
                // The best rate is timer frequency div 256.
                timerRate = (EE_FREQUENCY/16);
                timerCount = (hz / 2) + (EE_FREQUENCY/16);
                divisor = 1;
            }
        }
        else
        {
            // div 1 (in other words, no division)
            timerRate = EE_FREQUENCY;
            timerCount = (hz / 2) + EE_FREQUENCY;
            divisor = 0;
        }

        D_002C5994 = (timerCount / hz);
        ticksExtended = (timerCount / hz) & 0xffff;
        D_002C5AB4 = timerRate / ticksExtended;

        // Setup EE timer periphial
        *T1_COUNT = 0;
        *T1_COMP = (timerCount / hz);
        *T1_MODE = divisor | (T_MODE_CMPE_M | T_MODE_CUE_M);

        // Setup timer interrupt
        func_002642C0(10, tmrint, (void*)0);

        bIsTimerInited = 1;
        REAL_addexit(TIMER_restore);
    }

    return D_002C5AB4;
}
#endif

INCLUDE_ASM("asm/nonmatchings/eac/real/realcore/ps2/inittmr", TIMER_restore);

INCLUDE_ASM("asm/nonmatchings/eac/real/realcore/ps2/inittmr", tmrint);

INCLUDE_ASM("asm/nonmatchings/eac/real/realcore/ps2/inittmr", SaveFloatRegs);

INCLUDE_ASM("asm/nonmatchings/eac/real/realcore/ps2/inittmr", RestoreFloatRegs);
