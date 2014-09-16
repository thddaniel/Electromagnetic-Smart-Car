#include "Includes.h"  

void ReadInductors()         
{
    int ad_temp[7][10]={0};     //AD��ʱ�����洢   
    int i,j,k,temp;  
    
    for(i=0; i<=9; i++)  //�ɼ�10��   
    {  
        while(!ATD0STAT2_CCF0);  //�ȴ�ת������      
        ad_temp[0][i] = ATD0DR0;  //��ȡת���Ľ��   
            
        while(!ATD0STAT2_CCF1);  //�ȴ�ת������      
        ad_temp[1][i] = ATD0DR1;  //��ȡת���Ľ��   
          
        while(!ATD0STAT2_CCF2);  //�ȴ�ת������      
        ad_temp[2][i] = ATD0DR2;  //��ȡת���Ľ��   
          
        while(!ATD0STAT2_CCF3);  //�ȴ�ת������      
        ad_temp[3][i] = ATD0DR3;  //��ȡת���Ľ��   
               
        while(!ATD0STAT2_CCF4);  //�ȴ�ת������      
        ad_temp[4][i] = ATD0DR4;  //��ȡת���Ľ��   
        
        while(!ATD0STAT2_CCF5);  //�ȴ�ת������      
        ad_temp[5][i] = ATD0DR5;  //��ȡת���Ľ�� 
        
        while(!ATD0STAT2_CCF6);  //�ȴ�ת������      
        ad_temp[6][i] = ATD0DR6;  //��ȡת���Ľ��     
               
    }  

	 /*****************ȡ10  ��ֵ�е��м�ֵ******************/ 
	 for(i=0;i<9;i++)//ð�ݷ�����С�������� 
	 { 
		 for(j=0;j<9-i;j++) 
		 {	
			 for(k=0;k<7;k++)
			 {
				 if(ad_temp[k][j]>ad_temp[k][j+1])
				 {	 
					 temp=ad_temp[k][j]; 
					 ad_temp[k][j]=ad_temp[k][j+1]; 
					 ad_temp[k][j+1]=temp; 
				  } 
			 }
		  } 
	 } 
	/*��ȥ��Сֵ�����ֵ*/   
    for(i=0; i<7; i++)   
    {  
        int sum=0;  
        for(j=1;j<9;j++) 
        {
             sum += ad_temp[i][j];
        }
        inductor[i]=sum/8; 
     } 
}
/*********************************************
//�������ʾ ͨ������ 2��3 С��340ʱ���ֵ���ᳬ��900
//char code table[16] = {0x3f,0x06,0x5b,0x4f,0x66,
//                       0x6d,0x7d,0x07,0x7f,0x6f,
//                       0x77,0x7c,0x39,0x5e,0x79,0x71};
// X/Y=5/8 
********************************************/
void GetPosition() 
{ 
//    static char8 tmp0,tmp1; 
    //uint32 Max=1001,Min=0;
    //uint32 Min=0;
    uint16 lmax,psum;
    float gp;
    uchar8 num,i;
	int16 jj;
	float a,b,c;
   // float positiony;
    ReadInductors(); 
   /*if(inductor[0]>=1000){inductor[0]=1000;}  
   if(inductor[1]>=1000){inductor[1]=1000;}
   if(inductor[2]>=1000){inductor[2]=1000;}
   if(inductor[3]>=1000){inductor[3]=1000;}
   if(inductor[4]>=1000){inductor[4]=1000;}
   if(inductor[5]>=1000){inductor[5]=1000;} */
   for(i=0;i<6;i++) {
      if(inductor[i]>Max[i])
        Max[i]=inductor[i];
      if(inductor[i]<Min[i])
        Min[i]=inductor[i];
   }
    Pe[0] = (int16)((inductor[0]-Min[0])*100/(Max[0]-Min[0]+1));    
    Pe[1] = (int16)((inductor[1]-Min[1])*100/(Max[1]-Min[1]+1));
    Pe[2] = (int16)((inductor[2]-Min[2])*100/(Max[2]-Min[2]+1));
    Pe[3] = (int16)((inductor[3]-Min[3])*100/(Max[3]-Min[3]+1));
    Pe[4] = (int16)((inductor[4]-Min[4])*100/(Max[4]-Min[4]+1));
    Pe[5] = (int16)((inductor[5]-Min[5])*100/(Max[5]-Min[5]+1));    
   
    for(i=99;i>0;i--) 
  	{ position[i]=position[i-1];  }  
  	  	
  	jj = Pe[5]-Pe[0];
    positiony = fabsf(jj);
    for(i=1 ;i<5 ;i++) 
  	{ E[i] = Pe[i]*(1+0.004*positiony);} 	
  	
    a = -0.0007*Pe[3]+0.0013*Pe[4]-0.0013*Pe[1]+0.0007*Pe[2]; 
    b =  0.0067*Pe[3]-0.0067*Pe[4]-0.0067*Pe[1]+0.0067*Pe[2];
    c =  0.0167*Pe[3]-0.1333*Pe[4]+0.1333*Pe[1]-0.0167*Pe[2];
    
    lmax=E[1]; 
  	num=1; 
  	for(i=2;i<5;i++) 
  	{ 
    	if(E[i]>lmax) //ȡ���ֵ 
    	{ 
      	lmax=E[i]; 
      	num=i; 
    	} 
  	}
 	  if(num==3) //�����x����ĵ�1 ��AD ���
  	{ 
  	   /* if(Pe[3]-Pe[4]>4) 
  	    {*/
  	        gp = (Pe[4]-132.7)/5.975;
  	        position[0]=gp;
  	        if(position[0]<=-20)
  	            position[0]=-20;
/*  	    }
  	    else
  	    {  
  	       if((4*b*b-12*a*c)<0) 
  	       {
  	          p1 = (-2*b)/(6*a);	
    	        p2 = (-2*b)/(6*a); 
  	       } 
  	       else 
  	       { 
          		  p1 = (-2*b+sqrt(4*b*b-12*a*c))/(6*a);	
          	    p2 = (-2*b-sqrt(4*b*b-12*a*c))/(6*a);
  	      }
    	    p3 = 6*p1*a+2*b;	
    	    if(p3<0) position[0]=p1;
    	    else position[0]=p2;    
  	    }	      */
  	} 
  	else if(num==4) //�����x����ĵ�2 ��AD ���
  	{ 
  	     p1 = (-2*b+sqrt(4*b*b-12*a*c))/(6*a);	
  	     p2 = (-2*b-sqrt(4*b*b-12*a*c))/(6*a);
  	     p3 = 6*p1*a+2*b;	
  	     if(p3<0) position[0]=p1;
  	     else position[0]=p2;
  	} 
  	else	if(num==1) //�����x����ĵ�3 ��AD ���
  	{ 
  	     p1 = (-2*b+sqrt(4*b*b-12*a*c))/(6*a);	
  	     p2 = (-2*b-sqrt(4*b*b-12*a*c))/(6*a);
  	
  	     p3 = 6*p1*a+2*b;	
  	     if(p3<0) position[0]=p1;
  	     else position[0]=(p2);
  	}  
   	else  if(num==2)//�����x����ĵ�4 ��AD ���
  	{
  	   // if(Pe[2]-Pe[1]>4) 
  	   // {  
  	       gp = (132.7-Pe[1])/5.975;
  	   //    gp = (110.7-Pe[1])/5.975;
  	       position[0]=gp;
  	       if(position[0]>=20)
  	        position[0]=20;
  	   // }
  	 /*   else
  	    {  //Ϊʲô��ʱִ����������ָ��ʱ����֣�P1 �� P2 = 0 ��,���Ե�������
  	       //ԭ�� 4*b*b-12*a*c С�� 0  �����ų��� 
  	       if((4*b*b-12*a*c)<0) 
  	       {
  	          p1 = (-2*b)/(6*a);	
    	        p2 = (-2*b)/(6*a); 
  	       } 
  	       else 
  	       {    
  	          p1 = (-2*b+sqrt(4*b*b-12*a*c))/(6*a);	
    	        p2 = (-2*b-sqrt(4*b*b-12*a*c))/(6*a); 
  	       }    
    	    p3 = 6*p1*a+2*b;	
    	    if(p3<0) position[0]=p1;
    	    else position[0]=p2;    
  	    }	*/    
  	}     
  
    psum = Pe[1]+Pe[2]+Pe[3]+Pe[4];
  	if(psum <75) 
  	{	  
         if(position[1]<0)
            position[0]=-20;
         else if(position[1]>0)
            position[0]=20;
         //Out_flag=1;
   }
   //else
   //{
      //Out_flag=0;
   //}	 
   position[0] = (position[0]+position[1])/2; 
}

/*
void Ramp_Detection(void) 
{
      ReadInductors(); 
      accelerometer = (487-inductor[6])*0.9; 
     if(accelerometer<=4)
        Rampflag[0]=0;
     else if(accelerometer<=7&&accelerometer>4)
        Rampflag[0]=1;
     else if(accelerometer>7&&accelerometer<=15)
        Rampflag[0]=2;
    if(Rampflag[0]!=Rampflag[1]) 
    { 
      Rampflag[2]=Rampflag[1]; 
      Rampflag[1]=Rampflag[0]; 
    }
    if(Rampflag[1]==2 &&Rampflag[2]==1)
      SpeedSet=maxspeed2; 
    else if(Rampflag[1]==1 &&Rampflag[2]==2)
       SpeedSet=minspeed1; 
}
*/

void GetExpectSpeed(void) 
{
 
    static int16 zhidaoflag;
    static int16 xiaowanflag;
    static int16 dawandaoflag;
    static int16 jiwanflag;

    static int16 jiansu_zhitoxiao,jiansu_zhitoda,jiansu_xiaotoda; 
    static int16 jiasu_jitozhi,jiasu_datozhi,jiasu_jitoda,jiasu_datoxiao,jiansu_datoji,jiasu_jitoxiao,jiasu_xiaotozhi;  //3-0

   
    if(fabsf(position[0])<7) 
        zhidaoflag++;        //0-0
    else 
        zhidaoflag=0; 
    if(zhidaoflag>6000) zhidaoflag=6000;
       
    
    if((fabsf(position[0])>=7)&&(fabsf(position[0])<=10))  //1-1
         xiaowanflag++; 
     else 
        xiaowanflag=0; 
    if(xiaowanflag>6000) xiaowanflag=6000;
    
    if((fabsf(position[0])>10)&&(fabsf(position[0])<=14))  //2-2
         dawandaoflag++; 
     else 
        dawandaoflag=0; 
    if(dawandaoflag>6000) dawandaoflag=6000;
    
    if((fabsf(position[0])>14)&&(fabsf(position[0])<=20))  //3-3
         jiwanflag++; 
     else 
        jiwanflag=0; 
    if(jiwanflag>6000) jiwanflag=6000;
     
         
    
    if(jiwanflag>3) 
          roadflag[0]=3; 
    else if(dawandaoflag>5)   
          roadflag[0]=2;
    else if(xiaowanflag>5)   
          roadflag[0]=1; 
    else if(zhidaoflag>5) 
          roadflag[0]=0; 
 

    //0010 1101 2212
    if(roadflag[0]!=roadflag[1]) 
    { 
      roadflag[4]=roadflag[3];
      roadflag[3]=roadflag[2]; 
      roadflag[2]=roadflag[1]; 
      roadflag[1]=roadflag[0]; 
    }
    //ֱ��:0 С��:1  ����:2 ���� 
   
    //ֱ����С��
   if(roadflag[2]==0&&roadflag[1]==1)                                     
        jiansu_zhitoxiao++;
    else   jiansu_zhitoxiao=0; 
     //С���뼱��
    if(roadflag[2]==1&&roadflag[1]==2) 
        jiansu_xiaotoda++;
    else jiansu_xiaotoda=0; 
     //�����뼱��
    if(roadflag[2]==2&&roadflag[1]==3) 
        jiansu_datoji++;
    else jiansu_datoji=0; 
    //ֱ�������
    if(roadflag[2]==0&&roadflag[1]==2) 
        jiansu_zhitoda++;
    else jiansu_zhitoda=0; 
 
    
    //����
    //С���ֱ��
    if(roadflag[2]==1&&roadflag[1]==0)
        jiasu_xiaotozhi++;
    else jiasu_xiaotozhi=0;
    if(jiansu_datoji>=6000)  jiansu_datoji=6000;
    //�����С��
    if(roadflag[2]==2&&roadflag[1]==1)
        jiasu_datoxiao++;
    else jiasu_datoxiao=0;   
    //���䵽����
     if(roadflag[2]==3&&roadflag[1]==2)
        jiasu_jitoda++;
    else jiasu_jitoda=0;  
    //2-0   
    if(roadflag[2]==2&&roadflag[1]==0)
        jiasu_datozhi++;
    else jiasu_datozhi=0; 
    if(roadflag[2]==3&&roadflag[1]==0)
        jiasu_jitozhi++;
    else jiasu_jitozhi=0;
    if(roadflag[2]==3&&roadflag[1]==1)
        jiasu_jitoxiao++;
    else jiasu_jitoxiao=0;
    
    
     
    
    if(roadflag[2]==0&&roadflag[1]==0) 
        SpeedSet=zhi_speed;       //0-0
    else if(jiansu_zhitoxiao<slow_timer&&roadflag[2]==0&&roadflag[1]==1) 
        SpeedSet=minspeed01;      //0-1
    else if(jiansu_zhitoda<slow_timer&&roadflag[2]==0&&roadflag[1]==2) 
        SpeedSet=minspeed02;       //0-2  
    else if(roadflag[2]==0&&roadflag[1]==3) 
       SpeedSet=minspeed03;        //0-3 
         
    else if(jiansu_xiaotoda<slow_timer&&roadflag[2]==1&&roadflag[1]==2) 
        SpeedSet=minspeed12;        //1-2
    else if(roadflag[2]==1&&roadflag[1]==3) 
        SpeedSet=minspeed13;        //1-3
    
    else if(jiansu_datoji<slow_timer&&roadflag[2]==2&&roadflag[1]==3) 
        SpeedSet=minspeed23;        //2-3
 


    else if(jiasu_xiaotozhi>add_timer&&roadflag[2]==1&&roadflag[1]==0)
        SpeedSet=maxspeed10;        //1-0

    else if(jiasu_datozhi>add_timer&&roadflag[2]==2&&roadflag[1]==0)
       SpeedSet=maxspeed20;          //2-0
    else if(jiasu_datoxiao>add_timer&&roadflag[2]==2&&roadflag[1]==1)
        SpeedSet=maxspeed21;         //2-1
        
    else if(jiasu_jitozhi>add_timer&&roadflag[2]==3&&roadflag[1]==0)
        SpeedSet=maxspeed30;        //3-0  
    else if(jiasu_jitoxiao>add_timer&&roadflag[2]==3&&roadflag[1]==1)
        SpeedSet=maxspeed31;        //3-1      
    else if(jiasu_jitoda>add_timer&&roadflag[2]==3&&roadflag[1]==2)
        SpeedSet=maxspeed32;        //3-2



}      

void Steer_PID(void) 
{   
    GetPosition();
    Steer =(int16)(6300-(Kp*position[0]+300*(position[0]-position[1]))); 
    
    if(Steer>=6950) Steer=6950;
    else if(Steer<=5650) Steer=5650;
    PWMDTY23 = Steer;       
}
