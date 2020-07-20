#ifndef __PCF8574_H
#define __PCF8574_H
#include "pcf8574.h"
#include <rtthread.h>
#include <board.h>
//////////////////////////////////////////////////////////////////////////////////
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F7开发板
//PCF8574驱动代码
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2016/1/13
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved
//////////////////////////////////////////////////////////////////////////////////

#define PCF8574_INT  HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_12)//PCF8574 INT脚

#define PCF8574_ADDR    (0X40>>1)    //PCF8574地址(左移了一位)

//PCF8574各个IO的功能
#define BEEP_IO         0       //蜂鸣器控制引脚   P0
#define AP_INT_IO       1       //AP3216C中断引脚   P1
#define DCMI_PWDN_IO    2       //DCMI的电源控制引脚   P2
#define USB_PWR_IO      3       //USB电源控制引脚 P3
#define EX_IO           4       //扩展IO,自定义使用    P4
#define MPU_INT_IO      5       //MPU9250中断引脚   P5
#define RS485_RE_IO     6       //RS485_RE引脚        P6
#define ETH_RESET_IO    7       //以太网复位引脚       P7

#define BEEP_ON         PCF8574_WriteBit(BEEP_IO,0)  //控制蜂鸣器
#define BEEP_OFF        PCF8574_WriteBit(BEEP_IO,1)  //控制蜂鸣器
#define ETH_RESET_1        PCF8574_WriteBit(ETH_RESET_IO,1)  //控制蜂鸣器
#define ETH_RESET_0        PCF8574_WriteBit(ETH_RESET_IO,0)  //控制蜂鸣器

uint8_t PCF8574_Init(void);
uint8_t PCF8574_ReadOneByte(void);
void PCF8574_WriteOneByte(uint8_t DataToWrite);
void PCF8574_WriteBit(uint8_t bit,uint8_t sta);
uint8_t PCF8574_ReadBit(uint8_t bit);
#endif

