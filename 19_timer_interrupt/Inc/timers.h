/*
 * timers.h
 *
 *  Created on: 10 Aug 2026
 *      Author: noork
 */


#ifndef TIMERS_H_
#define TIMERS_H_
#define DIER_UIE (1<<0)

void tim2_1hz_interrupt(void);
		void tim2_1hz_init(void);
		#define SR_UIF (1U<<0)

#endif /* TIMERS_H_ */
