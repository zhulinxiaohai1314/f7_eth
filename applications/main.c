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
#include <packages/onenet-latest/inc/onenet.h>


#include <arpa/inet.h>         /* 包含 ip_addr_t 等地址相关的头文件 */
#include <netdev.h>            /* 包含全部的 netdev 相关操作接口函数 */
//#include <ntp.h>

#include "user.h"

#define DBG_TAG "main"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>


uint8_t led1_stat=0;

void KEY_Handle(void *args)
{
    rt_pin_write(LED1_PIN, led1_stat);
    led1_stat ++;
    led1_stat &=1;
//    onenet_mqtt_upload_digit("LED1", led1_stat);
//    rt_kprintf("key is pressed\r\n");
}


int main(void)
{
    int count = 1;
    struct netdev *netdev_Handle;
    /* 按键0引脚为输入模式 */
    rt_pin_mode(KEY0_PIN_NUM, PIN_MODE_INPUT_PULLUP);
    /* 绑定中断，下降沿沿模式，回调函数名为beep_on */
    rt_pin_attach_irq(KEY0_PIN_NUM, PIN_IRQ_MODE_FALLING, KEY_Handle, RT_NULL);
    /* 使能中断 */
    rt_pin_irq_enable(KEY0_PIN_NUM, PIN_IRQ_ENABLE);


    rt_pin_mode(LED1_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(LED0_PIN, PIN_MODE_OUTPUT);
    rt_pin_write(LED1_PIN, 1);



    //获取网卡对象
//    struct netdev* net = netdev_get_by_name("esp0");
//
//    //阻塞判断当前网络是否正常连接
//    while(netdev_is_internet_up(net) != 1)
//    {
//       rt_thread_mdelay(200);
//    }
//    //提示当前网络已就绪
//    rt_kprintf("network is ok!\n");


    netdev_Handle = netdev_get_first_by_flags(NETDEV_FLAG_UP);
    if (netdev_Handle == RT_NULL)
    {
        rt_kprintf("netdev_Handle get fail\r\n");


    }
    else
    {
        netdev_set_default(netdev_Handle);
        netdev_set_up(netdev_Handle);
        netdev_dhcp_enabled(netdev_Handle,RT_TRUE );
        /* 设置网卡 IP 地址 */
//        int netdev_set_ipaddr(struct netdev *netdev, const ip_addr_t *ipaddr);
//        /* 设置网卡网关地址 */
//        int netdev_set_gw(struct netdev *netdev, const ip_addr_t *gw);
//        /* 设置网卡子网掩码地址 */
//        int netdev_set_netmask(struct netdev *netdev, const ip_addr_t *netmask);
//        int netdev_set_dns_server(struct netdev *netdev, uint8_t dns_num, const ip_addr_t *dns_server);



    }



    onenet_mqtt_init();
    onenet_upload_cycle();
    while (count++)
    {
//        LOG_D("Hello RT-Thread!");
        rt_pin_write(LED0_PIN, count & 1);
        rt_thread_mdelay(1000);
    }
    return RT_EOK;
}
