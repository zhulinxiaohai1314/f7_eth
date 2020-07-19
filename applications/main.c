/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-07-18     RT-Thread    first version
 */

#include <rtthread.h>
#include "PCF8574/pcf8574.h"

#include <drivers/pin.h>
#include <board.h>


#define DBG_TAG "main"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

#define LED0_PIN        GET_PIN(B, 1)
#define LED1_PIN        GET_PIN(B, 0)
#define KEY0_PIN_NUM    GET_PIN(H, 3)  /* PH3 */

void KEY_Handle(void *args)
{
    rt_kprintf("key is pressed\r\n");
}


int main(void)
{
    int count = 1;

    /* 按键0引脚为输入模式 */
       rt_pin_mode(KEY0_PIN_NUM, PIN_MODE_INPUT_PULLUP);
       /* 绑定中断，下降沿沿模式，回调函数名为beep_on */
       rt_pin_attach_irq(KEY0_PIN_NUM, PIN_IRQ_MODE_FALLING, KEY_Handle, RT_NULL);
       /* 使能中断 */
       rt_pin_irq_enable(KEY0_PIN_NUM, PIN_IRQ_ENABLE);


       rt_pin_mode(LED0_PIN, PIN_MODE_OUTPUT);


    while (count++)
    {
//        LOG_D("Hello RT-Thread!");
        rt_pin_write(LED0_PIN,count&1);
        rt_thread_mdelay(1000);
    }
    return RT_EOK;
}
