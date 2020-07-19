#include "pcf8574.h"
#include <rtthread.h>
#include <board.h>

#include "drv_soft_i2c.h"
#include "drivers/i2c.h"
#include "drivers/i2c_dev.h"
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
static struct rt_i2c_bus_device *i2c_bus = RT_NULL;     /* I2C总线设备句柄 */
#define PCF_I2C_BUS_NAME          "i2c2"  /* 传感器连接的I2C总线设备名称 */
//初始化PCF8574
uint8_t PCF8574_Init(void)
{
    uint8_t temp=0;
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOB_CLK_ENABLE();           //使能GPIOB时钟
    GPIO_Initure.Pin=GPIO_PIN_12;           //PB12
    GPIO_Initure.Mode=GPIO_MODE_INPUT;      //输入
    GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //高速
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);     //初始化

    i2c_bus = (struct rt_i2c_bus_device *)rt_device_find(PCF_I2C_BUS_NAME);
    if (i2c_bus == RT_NULL)
   {
       rt_kprintf("can't find %s device!\n", PCF_I2C_BUS_NAME);
   }
    return temp;
}

////读取PCF8574的8位IO值
////返回值:读到的数据
uint8_t PCF8574_ReadOneByte(void)
{
    rt_uint8_t buf;
    struct rt_i2c_msg msgs;
    msgs.addr = PCF8574_ADDR;
    msgs.flags = RT_I2C_RD;
    msgs.buf = &buf;
    msgs.len = 1;
    if (rt_i2c_transfer(i2c_bus, &msgs, 1) == 1)
   {
       return buf;
   }
   else
   {
       rt_kprintf("i2c2 read fail\r\n");
       return -RT_ERROR;
   }


}
//向PCF8574写入8位IO值
//DataToWrite:要写入的数据
void PCF8574_WriteOneByte(uint8_t DataToWrite)
{
    rt_uint8_t buf= DataToWrite; //cmd
    struct rt_i2c_msg msgs;

    msgs.addr = PCF8574_ADDR;
    msgs.flags = RT_I2C_WR;
    msgs.buf = &buf;
    msgs.len = 1;
    if (rt_i2c_transfer(i2c_bus, &msgs, 1) != 1)
   {
        rt_kprintf("i2c2 write fail\r\n");
   }
}

//设置PCF8574某个IO的高低电平
//bit:要设置的IO编号,0~7
//sta:IO的状态;0或1
void PCF8574_WriteBit(uint8_t bit,uint8_t sta)
{
    uint8_t data;
    data=PCF8574_ReadOneByte(); //先读出原来的设置
    if(sta==0)data&=~(1<<bit);
    else data|=1<<bit;
    PCF8574_WriteOneByte(data); //写入新的数据
}

//读取PCF8574的某个IO的值
//bit：要读取的IO编号,0~7
//返回值:此IO的值,0或1
uint8_t PCF8574_ReadBit(uint8_t bit)
{
    uint8_t data;
    data=PCF8574_ReadOneByte(); //先读取这个8位IO的值
    if(data&(1<<bit))return 1;
    else return 0;
}

#define DBG_TAG "beep"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>




void beep(int argc, char**argv)
{
    if (!rt_strcmp(argv[1], "on"))
    {
        BEEP_ON;  //控制蜂鸣器
        LOG_D("beep turn on\r\n");
    }
    else if (!rt_strcmp(argv[1], "off"))
    {
        BEEP_OFF;  //控制蜂鸣器
        LOG_D("beep turn off\r\n");
    }
    else
    {
        rt_kprintf("Please input'beep <on|off>'\n");
    }
 }
MSH_CMD_EXPORT(beep,beep <on|off>);

void phy_reset(void)
{
    if (i2c_bus == RT_NULL)
        PCF8574_Init();
//    rt_pin_mode(RESET_IO, PIN_MODE_OUTPUT);
//    rt_pin_write(RESET_IO, PIN_HIGH);
    ETH_RESET_0;
    rt_thread_mdelay(50);
    ETH_RESET_1;
//    rt_pin_write(RESET_IO, PIN_LOW);
    rt_thread_mdelay(50);
    ETH_RESET_0;
//    rt_pin_write(RESET_IO, PIN_HIGH);
}

