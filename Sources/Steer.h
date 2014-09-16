#ifndef STEER_H
#define STEER_H

 // void Ramp_Detection(void); 
  void Steer_PID(void);
  void GetExpectSpeed(void); 
  //--------传感器----------//
   extern uint32 inductor[7]; 
   extern int16 Pe[6];
   extern int16 E[6];
   extern int16 accelerometer;
   extern uint32 Max[6],Min[6];
   
   extern float a,b,c;
   extern float p1,p2,p3;
   extern float position[100];
   extern float positiony;
   extern int16 zhi_speed;
   extern int16 roadflag[5];
   extern int16 maxspeed10,maxspeed20,maxspeed21,maxspeed30,maxspeed31,maxspeed32;
   extern int16 minspeed01,minspeed02,minspeed03,minspeed12,minspeed13,minspeed23;
   extern uint16  slow_timer,add_timer;
   //extern int16 jiasu_xiaotozhi;

  //--------舵机------------//
  extern int16 Kp,Steer;//Laststeer;
//  extern float m,n,h;
  //extern float Kd;
   //--------弯道标志量---------//
  //extern uchar8  Out_flag;
  //extern uchar8   cure_flag;

 
  //------------坡道---------------//
  extern char8 Ramp_flag;
  extern char8 Bar_flag;
  extern int16 Rampflag[3];

  
   
#endif