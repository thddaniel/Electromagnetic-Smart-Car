#include "Includes.h"  


//�ĳ�PT1��
                            //��Χ(256/(BUS_Fre/1000)-((256*65536)/(BUS_Fre/1000))ms
void PIT_ms_Init_CH0(void)  //interrupt enable
{                                        //ʹ��Micro Timer0����Ϊ
    PITCFLMT_PITE = 0;      //��ֹPITģ��//��ʱ�ж�ͨ��0�� 
    PITCE  |= 0X02;         //��ʱ��ͨ��1ʹ��
    PITMUX &= 0XFD;      //ʹ��Micro Timer0
    
    PITMTLD0 = 19;        //8λ��ʱ����ֵ�趨  64��Ƶ��Ϊ1MHz��Ϊ1us    //0.625us
    PITLD1 = 63999 ;       //16λ��ʱ����ֵ�趨     ((15625-1) + 1) * 0.625us = 10ms
                            //16λ��ʱ����ֵ�趨     ((8000-1) + 1) * 0.625us = 5ms �������ô˾����
                            //PIT�ж�������ƼĴ���
                            
    PITCFLMT_PITE = 1;      //ʹ��PITģ��               //��ʱ��ͨ��0ʹ��
    PITTF = 0X0F;           //�����־λ
    PITINTE|=0X02;          //�ж�ʹ�ܡ�0ͨ�����������־PTF0=1ʱ�������ж�����
    
}
//������ʱ�䣺��PITMTLD0+1)*(PITLD0+1)/fBUS     10*64000/64000000=10ms
//245*654/32*10e6=5ms
void PAT_Init(void)
{
   
    TIOS&=(~0x80);    //���õ�7λΪ���벶׽   ��Ӧ��λΪ0ʱ����Ϊ���벶�񣬷�֮Ϊ����Ƚ�
    TSCR1_TEN=1;
    PACTL_PAEN=1;     //�����������ϵͳ
    PACTL_PAMOD=0;    //�¼�����ģʽ
    PACTL_PEDGE=1;    //Ϊ1ʱΪ������ʱ��PACNT��һ

    PACNT=0x0000;      //����д��һ��Ҫ��������������
    PIT_ms_Init_CH0();  
}
