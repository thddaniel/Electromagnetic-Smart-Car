#include "Includes.h"  
//�жϵ�ʱ�����������ִ�е�ʱ��
void Init_AD(void)
{
      ATD0CTL1=0x20; //ETRIGSEL SRES1 SRES0 SMP_DIS ETRIGCH3 ETRIGCH2 ETRIGCH1 ETRIGCH0
                     //  0        1     0        0      0         0        0        0  
                     //SRES1=0��SRES0=0ѡ�� 8λ 01 ѡ��10λ 10ѡ��12λ
      ATD0CTL2=0xd0;  //ADPU AFFC AWAl ETRIGLE ETRIGP ETRIGE ASCIE ASCIF
                     // 1    1    0    0       0       0     0       0
                     //AFFC=0 ��־λ�ֶ���0 =1 �Զ���0
                     //AWAI=1 �ȴ�ģʽ�¿�ת�� =0 �ȴ�ģʽ�½�ֹת��
                     //ETRIGLE��ETRIGP ������ʽѡ�� 
                     //ASCIE �����ж�ʹ��   ASCIF  ����AD�жϱ�־
      ATD0CTL3=0xc0;   // DJM S8C S4C S2C S1C FIFO FRZ1 FRZ0
                     //    1    0   1   1    0    0    0   0
                     //DJM=0 ��������ڽ���Ĵ����� �ȴ���ATD0DR0H����λ��
                     //DJM=1 �Ҷ���                   �ȴ���ATD0DR0L����λ��
                     // S8C~~S1C ת�����г��� ��Ҫת����ͨ���� ������8
                     //FIFO=0�� ����Ĵ���ӳ�䵽ת������   �����ΰ����ݴ���ATD0DR0��ATD0DRn 
                     //FIFO =1  ��û�� ��ANnͨ�����ݴ���ATD0DRn 
                                     //ͬʱ���ΰ����ݴ���ATD0DR0��ATD0DRn 
      ATD0CTL4=0x64;  // SMP2 SMP1 SMP0   PRS4~~PRS0  
                     //  1     1     0      10011
                     //��������ѡ�� T=1/20*Fad     
                     // ADʱ��Ƶ��Fad=Fbus/2/(PRS+1)=60M/2/5=6M
                     // ���A/Dʱ��=2.0MHz(��СA/D CLOCK=0.5MHz)
      ATD0CTL5=0xb0; //  0 SC  SCAN MUIT CD CC CB CA
                     //  1  0   1    1    0 0  0  0   
                     //SC=0 CD~CA����ѡ��0��15��ͨ�� ����ʼת��ͨ��ѡ�� 
                     //SC=1ѡ������ͨ��
                     //�����0��ͨ����ʼת��
                     //SCAN=0 ����ת�� =1 �������ת��
                     //MUIT=1 ��ͨ��ת�� =0 ��ͨ��ת��
      ATD0DIEN=0x00;  //��������ʹ�� �����ֹ����
}