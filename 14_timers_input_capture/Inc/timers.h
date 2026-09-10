/*
 * timers.h
 *
 *  Created on: 10 Aug 2026
 *      Author: noork
 */


#ifndef TIMERS_H_
#define TIMERS_H_

#define SR_UIF (1U<<0)
#define SR_CC1IF (1U<<1)
void tim2_1hz_init(void);
void tim2_output_compare(void);
void tim3_input_capture(void);

#endif /* TIMERS_H_ */
