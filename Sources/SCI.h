//---------------------------------------------------------------*
 //文件名称：SCI.h-----------------------------------------------*
 //文件说明：该文件为串口通信构件的头文件------------------------*
 //--------------------------------------------------------------*
 #ifndef SCI_H
 #define SCI_H
 
//头文件包含:



//构建声明区
  void OutPut_Data(void);
  void UART_Init (void);
  void uart_putchar ( uchar8 ch);
//  unsigned char uart_getchar(void); 
//  unsigned short CRC_CHECK(unsigned char *Buf, unsigned char CRC_CNT); 
  //void CRC16(unsigned char *Array ,unsigned int Len);
//  void Parameter_sent(void);
//声明变量
 extern int16 OutData[4];

 
#endif