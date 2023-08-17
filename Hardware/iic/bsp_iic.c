#include "bsp_iic.h"
#include "systick.h"
void iic_gpio_config(void){
    rcu_periph_clock_enable(RCU_SCL);
    rcu_periph_clock_enable(RCU_SDA);

    gpio_mode_set(PORT_SCL,GPIO_MODE_OUTPUT,GPIO_PUPD_PULLUP,GPIO_SCL);
    gpio_output_options_set(PORT_SCL,GPIO_OTYPE_OD,GPIO_OSPEED_MAX,GPIO_SCL);

    SDA_OUT();
    gpio_output_options_set(PORT_SDA,GPIO_OTYPE_OD,GPIO_OSPEED_MAX,GPIO_SDA);
}
void IIC_HW_Test(void){
    SDA_OUT();
    SDA(SET);
    SCL(SET);
    delay_1ms(1000);
    SDA(RESET);
    SCL(RESET);
}
void IIC_Start(void){
    SDA_OUT();
    SDA(SET);
    SCL(SET);
    delay_1us(5);
    SDA(RESET);
    delay_1us(5);
    SCL(RESET);
    delay_1us(5);
}
void IIC_Stop(void){
    SDA_OUT();
    SCL(RESET);
    SDA(RESET);
    SCL(SET);
    delay_1us(5);
    SDA(SET);
    delay_1us(5);
}
void IIC_Send_Nack(void){
    SDA_OUT();
    SCL(RESET);
    SDA(RESET);
    SDA(SET);
    SCL(SET);
    delay_1us(5);
    SCL(RESET);
    SDA(RESET);
}
void IIC_Send_Ack(void){
    SDA_OUT();
    SCL(RESET);
    SDA(SET);
    SDA(RESET);
    SCL(SET);
    delay_1us(5);
    SCL(RESET);
    SDA(SET);
}
uint8_t IIC_WaitAck(void){
    uint8_t ack_flag=10;
    SCL(RESET);
    SDA(SET);
    SDA_IN();
    delay_1us(5);
    SCL(SET);
    delay_1us(5);

    while ((SDA_GET()==nack)&&(ack_flag)){
        ack_flag--;
        delay_1us(5);
    }
    if (ack_flag<=0){
        IIC_Stop();
        return nack;
    } else{
        SCL(RESET);
        SDA_OUT();
    }
    return ack;

}
void IIC_Send_Byte(uint8_t data){
    SDA_OUT();
    SCL(RESET);
    for (int i = 0; i < 8; i++) {
        SDA((data&0x80)>>7);
        delay_1us(1);
        SCL(SET);
        delay_1us(5);
        SCL(RESET);
        delay_1us(5);
        data<<=1;
    }

}
uint8_t IIC_Read_Byte(void){
    uint8_t receive=0;
    SDA_IN();
    for (int i = 0; i < 8; ++i) {
        SCL(RESET);
        delay_1us(5);
        SCL(SET);
        delay_1us(5);
        receive<<=1;
        if (SDA_GET()){
            receive |=SET;
        }
    }
    SCL(RESET);
    return receive;

}
