#include "Includes.h"  


void Init_Port(void) 
{
    DDRA_DDRA0 = 1;//������ƽӿ� ��ʾΪ���
    PORTA_PA0 = 0;
    DDRA_DDRA1 = 1; //������ƽӿ� 
    PORTA_PA1 = 0;
    
    DDRA_DDRA2 = 0;//����
    DDRA_DDRA3 = 0;
    DDRA_DDRA4 = 0;         
    
    DDRA_DDRA5 = 1;//���������
    PORTA_PA5 = 1;
     
       
    DDRB = 0xff;//�������ʾ
 //   PORTB = 0X00;
    
/*    DDRK_DDRK4 = 0;//���뿪
    DDRK_DDRK5 = 0;
    DDRK_DDRK2 = 0;
    DDRK_DDRK3 = 0;
    PORTK = 0xff;       */
    
    DDRJ_DDRJ0 = 0; 
}

void delay_ms(int16 n)
{
    uint i;
    for(;n>0;n--)
        for(i=64000;i>0;i--);
}
void beep(int16 bptm) 
{
    PORTA_PA5=0;
    delay_ms(bptm);
    PORTA_PA5=1;
} 