#include "Includes.h"


/*********速度***************/
int16 roadflag[5];
int16 Speed,zhi_speed;
int16 maxspeed10,maxspeed20,maxspeed21,maxspeed30,maxspeed31,maxspeed32;
int16 minspeed01,minspeed02,minspeed03,minspeed12,minspeed13,minspeed23;
//int16 jiasu_xiaotozhi;

                                 
uint16 slow_timer,add_timer;
int16 pulse;
int16 SpeedSet;
uint32 Max[6]={750,750,750,750,750,750},Min[6]={30,30,30,30,30,30};

                                                                            
/*********舵机**************/
int16 Steer;
int16 Kp;
/*********传感器************/
uint32 inductor[7]={0}; 
int16 Pe[6]={0};
int16 E[6]={0};
int16 accelerometer=0;
float positiony;
float position[100]={0};
float p1,p2,p3;

//-----------弯道标志量------------//
//uchar8  Out_flag=0;
//uchar8  cure_flag=0;
//------------停车标志---------------//
int16 Stop_flag=0;
//-----------串口变量-----------//
int16 OutData[4]={0};
//-------------坡道-------------//
char8 Ramp_flag=0;
char8 Bar_flag=0; 
int16 Rampflag[3]={0};

float abs1(float z)              
{
   if(z>=0) 
    return z;
   else
    return -z;
}
/*********************************************************
//y=ax2+ bx+ c
//a>0时，开口向上，y有最小值，对称轴x=-b/2a
//a<0时，开口向下，y有最大值，对称轴x=-b/2a
//a的绝对值决定抛物线开口方向及大小，绝对值越大，开口越小，绝对值越小，开口越大
//ab同号，对称轴在y轴右左边;ab异号，对称轴在y轴右边
//c决定抛物线与y轴的交点，c>0交于y的正半轴，c<0交于y的负半轴
// y=mx2+ nx+ h
// m越大越陡，n越大越陡变化率越大，h越大 开始起点越高越大  
*********************************************************/
void Mode()
{
   if(PORTK_PK3==0&&PORTK_PK2==0&&PORTK_PK1==0&&PORTK_PK0==0)    //可以跑完 但是有点太切内道两轮会出去
    {           //7.8V
               //SpeedSet = 90;
        
    if(roadflag[2]==0&&roadflag[1]==0) Kp= 32;    
    else if(roadflag[2]==0&&roadflag[1]==1) Kp= 35;
    else if(roadflag[2]==0&&roadflag[1]==2) Kp = 44;
    else if(roadflag[2]==0&&roadflag[1]==3) Kp = 50;
    
    else if(roadflag[2]==1&&roadflag[1]==0)  Kp= 36;
    else if(roadflag[2]==1&&roadflag[1]==2)  Kp= 40;
    else if(roadflag[2]==1&&roadflag[1]==3)  Kp = 43;
    
    else if(roadflag[2]==2&&roadflag[1]==0)  Kp = 37;
    else if(roadflag[2]==2&&roadflag[1]==1)  Kp= 39;
    else if(roadflag[2]==2&&roadflag[1]==3)  Kp= 47;
    
    else if(roadflag[2]==3&&roadflag[1]==0)  Kp = 48; 
    else if(roadflag[2]==3&&roadflag[1]==1)  Kp = 44;
    else if(roadflag[2]==3&&roadflag[1]==2)  Kp = 43;
    
      slow_timer=30;add_timer=100;
      minspeed01 = 90;    //0-1
      minspeed12 = 80;   //1-2
      minspeed23 = 70;   //2-3
      minspeed02 = 65;   //0-2
      minspeed03 = 60;    //0-3 
      minspeed13 = 65;    //1-3
       
      maxspeed20 = 75;    //2-0
      maxspeed32 = 80;   //3-2                                  
      maxspeed21 = 85;   //2-1
      maxspeed10 = 90;    //1-0
      zhi_speed = 100;  //0-0

    }
    if(PORTK_PK3==0&&PORTK_PK2==0&&PORTK_PK1==0&&PORTK_PK0==1) 
    {
    
      /*
      if(roadflag[2]==0&&roadflag[1]==0) Kp= 35;  
      
      else if((roadflag[2]==0&&roadflag[1]==1)||(roadflag[2]==1&&roadflag[1]==0)) Kp= 37;
      else if((roadflag[2]==2&&roadflag[1]==0))  Kp = 37;
      else if((roadflag[2]==3&&roadflag[1]==1))  Kp = 37;
      else if((roadflag[2]==1&&roadflag[1]==2)||(roadflag[2]==2&&roadflag[1]==1)) Kp= 38;
      else if((roadflag[2]==1&&roadflag[1]==3))  Kp = 46;
      else if((roadflag[2]==0&&roadflag[1]==2))  Kp = 47;
      else if((roadflag[2]==2&&roadflag[1]==3)||(roadflag[2]==3&&roadflag[1]==2)) Kp= 48;
    
      slow_timer=40;add_timer=35;
      minspeed_1=115;    //0-1
      minspeed0 = 100;   //1-2
      minspeed1 = 75;   //2-3
      minspeed2 = 60;   //0-2
      //minspeed_1_1=94;minspeed0_1=89;minspeed1_1=74;minspeed2_1=79;
      minspeed3 = 60;    //0-3 
      minspeed4 = 65;
      
      maxspeed3 = 90;    //2-0
      maxspeed2 = 90;   //3-2
      maxspeed1 = 110;   //2-1
      maxspeed0 = 130;    //1-0
      zhi_speed = 140;  //0-*/
 
    }
    if(PORTK_PK3==0&&PORTK_PK2==0&&PORTK_PK1==1&&PORTK_PK0==0) 
    {
      
    /*  if(roadflag[2]==0&&roadflag[1]==0) Kp= 35;  
      
      else if((roadflag[2]==0&&roadflag[1]==1)||(roadflag[2]==1&&roadflag[1]==0)) Kp= 33;
      else if((roadflag[2]==2&&roadflag[1]==0))  Kp = 35;
      else if((roadflag[2]==3&&roadflag[1]==1))  Kp = 36;
      else if((roadflag[2]==1&&roadflag[1]==2)||(roadflag[2]==2&&roadflag[1]==1)) Kp= 38;
      else if((roadflag[2]==1&&roadflag[1]==3))  Kp = 40;
      else if((roadflag[2]==0&&roadflag[1]==2)) Kp = 42;
      else if((roadflag[2]==2&&roadflag[1]==3)||(roadflag[2]==3&&roadflag[1]==2)) Kp= 48;
      slow_timer=40;add_timer=35;
      minspeed_1=115;    //0-1
      minspeed0 = 100;   //1-2
      minspeed1 = 75;   //2-3
      minspeed2 = 70;   //0-2
      minspeed3 = 60;    //0-3
      minspeed4 = 60;    //1-3
      
      maxspeed3 = 90;    //2-0
      maxspeed2 = 100;   //3-2
      maxspeed1 = 150;   //2-1
      maxspeed0 = 170;    //1-0
      zhi_speed = 200;  //0-0    */
    }
    
    if(PORTK_PK3==0&&PORTK_PK2==1&&PORTK_PK1==0&&PORTK_PK0==0) 
    {
               
      if(roadflag[2]==0&&roadflag[1]==0) Kp= 32;    
      else if(roadflag[2]==0&&roadflag[1]==1) Kp= 35;
      else if(roadflag[2]==0&&roadflag[1]==2) Kp = 44;
      else if(roadflag[2]==0&&roadflag[1]==3) Kp = 54;
      
      else if(roadflag[2]==1&&roadflag[1]==0)  Kp= 36;
      else if(roadflag[2]==1&&roadflag[1]==2)  Kp= 40;
      else if(roadflag[2]==1&&roadflag[1]==3)  Kp = 43;
      
      else if(roadflag[2]==2&&roadflag[1]==0)  Kp = 37;
      else if(roadflag[2]==2&&roadflag[1]==1)  Kp= 39;
      else if(roadflag[2]==2&&roadflag[1]==3)  Kp= 47;
      
      else if(roadflag[2]==3&&roadflag[1]==0)  Kp = 45; 
      else if(roadflag[2]==3&&roadflag[1]==1)  Kp = 44;
      else if(roadflag[2]==3&&roadflag[1]==2)  Kp = 43;
      
      slow_timer=30;add_timer=100;
      minspeed01 = 100;    //0-1
      minspeed02 = 75;   //0-2
      minspeed03 = 70;    //0-3 
      
      minspeed12 = 90;   //1-2
      minspeed13 = 80;    //1-3
      
      minspeed23 = 75;   //2-3
      
      maxspeed10 = 120;    //2-0
      maxspeed20 = 120;   //3-2                                  
      maxspeed21 = 100;   //2-1
      maxspeed30 = 120;
      maxspeed31 = 90;
      maxspeed32 = 90;    
      zhi_speed = 120;  //0-0
          

    } 
/*    if(PORTK_PK3==1&&PORTK_PK2==0&&PORTK_PK1==0&&PORTK_PK0==0) 
    {
         for(i=0;i<3;i++) 
          { 
            for(j=0;j<3;j++) 
                ExpectSpeed[i][j]=ExpectSpeed5[i][j]; 
          } 
          quanspeed=70;  maxspeed0=75;   maxspeed1=80;  maxspeed2=90;                    
          midspeed=80;
          minspeed0=60;  minspeed1=50;  
          slow_timer = 50;
    }
    if(PORTK_PK3==0&&PORTK_PK2==1&&PORTK_PK1==1&&PORTK_PK0==0) //最小出弯
    {
         for(i=0;i<3;i++) 
          { 
            for(j=0;j<3;j++) 
                ExpectSpeed[i][j]=ExpectSpeed0[i][j]; 
          }  
          quanspeed=60; maxspeedd3=55; maxspeed2=60;   maxspeed1=60;  maxspeed0=60;                   
          midspeed=60;
          minspeed0=55;  minspeed1 =55;minspeed2=60;  
          slow_timer = 100; add_timer=0;
    }  */
/*    if(PORTK_PK3==0&&PORTK_PK2==1&&PORTK_PK1==1&&PORTK_PK0==1)  //最小出弯加速
    {
         for(i=0;i<3;i++) 
          { 
            for(j=0;j<3;j++) 
                ExpectSpeed[i][j]=ExpectSpeed0[i][j]; 
          } 
    }
    //仅供调车用、、、、
    if(PORTK_PK3==1&&PORTK_PK2==1&&PORTK_PK1==1&&PORTK_PK0==1) 
    {
        OutData[0] = (int16)(Pe[1]); 
        OutData[1] = (int16)(Pe[2]); 
        OutData[2] = (int16)(Pe[3]);
        OutData[3] = (int16)(Pe[4]);
        OutPut_Data();
        deplay();  
        SpeedSet = 200;     
    }          */
//    if(PORTK_PK3 == 1) {
   
 //   }  
}
void main(void) 
{
    DisableInterrupts;
    PLL_Init_64M();
    UART_Init();
    Init_Port(); 
    Init_AD();
    Init_PWM();
  //  LCD_init(); 
  //  LCD_clear(); 
  //  RST = 1; 
    PAT_Init();
   
    
 //   PWMDTY23 =6300 ;
//    DDRA_DDRA7 = 1;
    EnableInterrupts;
    for(;;)
    {      
       Mode();
    //   uart_putchar('a');
    /*    OutData[0] = (int16)(roadflag[2]); 
        OutData[1] = (int16)(roadflag[3]); 
        OutData[2] = (int16)(Steer);
        OutData[3] = (int16)(roadflag[1]);
        OutPut_Data(); */ 
   //    Ramp_Detection();
      GetExpectSpeed();
      Steer_PID();
      stop_car();
      //Motor(1800);
    } 
}
