//---------------------------------------------------------------*
 //�ļ����ƣ�SCI.h-----------------------------------------------*
 //�ļ�˵�������ļ�Ϊ����ͨ�Ź�����ͷ�ļ�------------------------*
 //--------------------------------------------------------------*
 #ifndef SCI_H
 #define SCI_H
 
//ͷ�ļ�����:



//����������
  void OutPut_Data(void);
  void UART_Init (void);
  void uart_putchar ( uchar8 ch);
//  unsigned char uart_getchar(void); 
//  unsigned short CRC_CHECK(unsigned char *Buf, unsigned char CRC_CNT); 
  //void CRC16(unsigned char *Array ,unsigned int Len);
//  void Parameter_sent(void);
//��������
 extern int16 OutData[4];

 
#endif