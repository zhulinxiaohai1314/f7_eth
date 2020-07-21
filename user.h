/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-07-21     zhuli       the first version
 */
#ifndef USER_H_
#define USER_H_

#include <rtthread.h>
#include "PCF8574/pcf8574.h"

#include <drivers/pin.h>
#include <board.h>

#define LED0_PIN        GET_PIN(B, 1)
#define LED1_PIN        GET_PIN(B, 0)
#define KEY0_PIN_NUM    GET_PIN(H, 3)  /* PH3 */

extern uint8_t led1_stat;

#define LED1_ON  {led1_stat=1; rt_pin_write(LED1_PIN, 0);}
#define LED1_OFF {led1_stat=0; rt_pin_write(LED1_PIN, 1);}


#endif /* USER_H_ */
