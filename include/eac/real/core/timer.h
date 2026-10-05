#ifndef REALCORE_TIMER_H
#define REALCORE_TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

    int TIMER_init(int hz);
    void TIMER_restore();


#ifdef __cplusplus
}
#endif

#endif
