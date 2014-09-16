#include "Includes.h"  

void Motor(int16 Speed)   
{
    if (Speed >= 0)      //电机正转     
    {      
        PORTA_PA0 = 0;
        PORTA_PA1 = 1;
        PWMDTY01 = Speed;      //电机频率：10K 
    } 
    else 
    {    //电机反转
        PORTA_PA0 = 1;
        PORTA_PA1 = 0;
        PWMDTY01 = -Speed;
    }
}

int16 MotorPid(int16 SpeedSet1) 
{                                            
    float S_Kp=13;  //15
    float S_Ki=2;   //1.7
    float S_Kd=10.0;
    static int16 e_speed[3];
    float Speedsum;
 /*   float S_Kp=13;    //if(Out_flag ==0) SpeedSet = 350; else SpeedSet=290;  制动快 
    float S_Ki=0.9;        // Steer kp=50  kd=10    
    float S_Kd=23;  */
    e_speed[2]=e_speed[1];
    e_speed[1]=e_speed[0];
    e_speed[0]=SpeedSet1-pulse;//SpeedSet-pulse;
    Speedsum = S_Kp*(e_speed[0]-e_speed[1])+S_Ki*e_speed[0]
              +S_Kd*(e_speed[0]-2*e_speed[1]+e_speed[2]);
    Speed += (int16)Speedsum;
    if(Speed>3000) Speed=3000;
    else if(Speed<0) Speed=0;     
    return Speed;
} 
/**********************INTERRUPT*************************/
// (PACNT/100)*(编码器齿数/连接轮齿数)*连接轮周长/测速周期==speed                                                   **/
// 编码器齿数=26  连接轮齿数=76 连接轮周长=160mm
// 30ms  95*3=285         25ms  237.5    10ms  95
//20ms  190               5ms 47.5        
//   10*160/100/77=0.2  PACNT=73 2m/s
/********************************************************/                                                
#pragma CODE_SEG __NEAR_SEG NON_BANKED//中断函数置于非分页区内
interrupt VectorNumber_Vpit1 void  Interrupt_PIT_CH0(void) 
{
    int16 ii;  
    PITTF_PTF1 = 1;   //清楚中断标志，为下次中断做准备
    pulse=PACNT;
  //  GetExpectSpeed();
  //  Ramp_Detection();
 //   
    if((Stop_flag==0)||(Stop_flag==1))
    { 
      ii= MotorPid(SpeedSet);
      Motor(ii);
    }
    if(Stop_flag>=2) 
    {
       for(;;)
       {
          ii= MotorPid(0);
          Motor(ii);
          Steer_PID();
        }
    }       
    PACNT=0X0000;//PORTA_PA7 = 1;     
}   
    
void stop_car(void) 
{
    static int16 b1,Last_b1;    
    b1 = PTJ_PTJ0;
    if((b1==0) && (Last_b1==1)) 
    {
        delay_ms(1);
        Stop_flag++;
    }
    Last_b1 = b1;     
}





