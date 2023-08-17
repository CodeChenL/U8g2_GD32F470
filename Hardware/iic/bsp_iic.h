//
// Created by lenovo on 2023/8/16.
//

#ifndef BSP_IIC_H
#define BSP_IIC_H

#include "gd32f4xx.h"
#define RCU_SDA RCU_GPIOB
#define PORT_SDA GPIOB
#define GPIO_SDA GPIO_PIN_9

#define RCU_SCL RCU_GPIOB
#define PORT_SCL GPIOB
#define GPIO_SCL GPIO_PIN_8

#define ack RESET
#define nack SET

#define SDA_OUT() gpio_mode_set(PORT_SDA,GPIO_MODE_OUTPUT,GPIO_PUPD_PULLUP,GPIO_SDA)

#define SDA_IN() gpio_mode_set(PORT_SDA,GPIO_MODE_OUTPUT,GPIO_PUPD_PULLUP,GPIO_SDA)

#define SDA_GET() gpio_input_bit_get(PORT_SDA,GPIO_SDA)

#define SDA(x) gpio_bit_write(PORT_SDA,GPIO_SDA,(x?SET:RESET))
#define SCL(x) gpio_bit_write(PORT_SCL,GPIO_SCL,(x?SET:RESET))
void iic_gpio_config(void);
void IIC_HW_Test(void);
void IIC_Start(void);
void IIC_Stop(void);
void IIC_Send_Nack(void);
void IIC_Send_Ack(void);
uint8_t IIC_WaitAck(void);
void IIC_Send_Byte(uint8_t data);
uint8_t IIC_Read_Byte(void);
#endif //BSP_IIC_H
