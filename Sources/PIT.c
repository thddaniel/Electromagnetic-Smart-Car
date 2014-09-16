#include "Includes.h"  


//改成PT1口
                            //范围(256/(BUS_Fre/1000)-((256*65536)/(BUS_Fre/1000))ms
void PIT_ms_Init_CH0(void)  //interrupt enable
{                                        //使能Micro Timer0并设为
    PITCFLMT_PITE = 0;      //禁止PIT模块//定时中断通道0关 
    PITCE  |= 0X02;         //定时器通道1使能
    PITMUX &= 0XFD;      //使用Micro Timer0
    
    PITMTLD0 = 19;        //8位定时器初值设定  64分频，为1MHz，为1us    //0.625us
    PITLD1 = 63999 ;       //16位定时器初值设定     ((15625-1) + 1) * 0.625us = 10ms
                            //16位定时器初值设定     ((8000-1) + 1) * 0.625us = 5ms 本程序用此句计算
                            //PIT中断允许控制寄存器
                            
    PITCFLMT_PITE = 1;      //使能PIT模块               //定时器通道0使能
    PITTF = 0X0F;           //先清标志位
    PITINTE|=0X02;          //中断使能。0通道产生溢出标志PTF0=1时，产生中断请求
    
}
//计数器时间：（PITMTLD0+1)*(PITLD0+1)/fBUS     10*64000/64000000=10ms
//245*654/32*10e6=5ms
void PAT_Init(void)
{
   
    TIOS&=(~0x80);    //设置第7位为输入捕捉   相应的位为0时设置为输入捕获，反之为输出比较
    TSCR1_TEN=1;
    PACTL_PAEN=1;     //允许脉冲计数系统
    PACTL_PAMOD=0;    //事件计数模式
    PACTL_PEDGE=1;    //为1时为上升沿时，PACNT加一

    PACNT=0x0000;      //读和写是一定要对整个字来操作
    PIT_ms_Init_CH0();  
}
