#include "Includes.h" 
/*------------------------------------------------
//舵机中间值为9000 100hz 右转极限值7950 但是最好给8025
//                        左转9975      40KHZ     600
//-----------------------------------------------*/
void Init_PWM(void)    
{
    PWME = 0X00;//禁止PWM
    PWMPRCLK = 0X00;//设置A的时钟频率为 64/2^0=645M  B的时钟频率为 64/2^0=64M
    PWMCLK = 0X0c;  //PWM时钟源选择,选择A SB时钟作为PWM通道的时钟源 
    PWMSCLB = 8;   //SB=64/2*8=4M
    PWMPOL = 0XFF;  //设置极性 开始输出高电平
    PWMCAE = 0X00;  //设置左对齐方式
    PWMCTL = 0XF0;  //PWM全部级联 
    
    PWMPER23=40000;      //舵机  Frequency=A/40000=100hz    12600/80000=0.1575  
  //  PWMDTY23=20000;
    
    PWME_PWME3=1;
    
    PWMPER01=4000;       //电机  Frequency=B/4000=15K     
   // PWMDTY01=500;
    PWME_PWME1=1;
}