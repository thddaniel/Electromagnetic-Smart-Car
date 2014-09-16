//------------------------------------------------------------*
//文件名：SCI.c-----------------------------------------------*
//文件说明：串口通信的初始化和数据位的相关设置----------------*
//------------------------------------------------------------*

//头文件包含
#include "Includes.h"  


//构建函数实现区
void UART_Init (void)
{
    SCI0BD = 416; //9600bps  Baud Rate=BusClock/(16*SCIBD)  
    SCI0CR1 =0x00; //设置串口接收端连接到外部,等待时正常工作，无奇偶校验！
    SCI0CR2 =0x2C;//接收中断；发送使能和接收使能
} 

void uart_putchar ( uchar8 ch)
{
  if (ch == '\n')  
  {
      while(!(SCI0SR1&0x80)) ;     
      SCI0DRL= 0x0d;       				 //output'CR'
	    return;
   }
   while(!(SCI0SR1&0x80)) ; 		 //keep waiting when not empty  
   SCI0DRL=ch;
}


unsigned short CRC_CHECK(unsigned char *Buf, unsigned char CRC_CNT)
{
    unsigned short CRC_Temp;
    unsigned char i,j;
    CRC_Temp = 0xffff;

    for (i=0;i<CRC_CNT; i++){      
        CRC_Temp ^= Buf[i];
        for (j=0;j<8;j++) {
            if (CRC_Temp & 0x01)
                CRC_Temp = (CRC_Temp >>1 ) ^ 0xa001;
            else
                CRC_Temp = CRC_Temp >> 1;
        }
    }
    return(CRC_Temp);
}

void OutPut_Data(void)
{
  int temp[4] = {0};
  unsigned int temp1[4] = {0};
  unsigned char databuf[10] = {0};
  unsigned char i;
  unsigned short CRC16 = 0;
  for(i=0;i<4;i++)
   {
    
    temp[i]  =(int) OutData[i];
    temp1[i] = (unsigned int)temp[i];   //强硬转换成无符号整形
    
   }
   
  for(i=0;i<4;i++) 
  {
    databuf[i*2]   = (unsigned char)(temp1[i]%256);
    databuf[i*2+1] = (unsigned char)(temp1[i]/256);
  }
  
  CRC16 = CRC_CHECK(databuf,8);
  databuf[8] = CRC16%256;
  databuf[9] = CRC16/256;
  
  for(i=0;i<10;i++)
    uart_putchar(databuf[i]);
}  
