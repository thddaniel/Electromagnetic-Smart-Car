#include "Includes.h"  
//中断的时间大于主函数执行的时间
void Init_AD(void)
{
      ATD0CTL1=0x20; //ETRIGSEL SRES1 SRES0 SMP_DIS ETRIGCH3 ETRIGCH2 ETRIGCH1 ETRIGCH0
                     //  0        1     0        0      0         0        0        0  
                     //SRES1=0、SRES0=0选择 8位 01 选择10位 10选择12位
      ATD0CTL2=0xd0;  //ADPU AFFC AWAl ETRIGLE ETRIGP ETRIGE ASCIE ASCIF
                     // 1    1    0    0       0       0     0       0
                     //AFFC=0 标志位手动清0 =1 自动清0
                     //AWAI=1 等待模式下可转换 =0 等待模式下禁止转换
                     //ETRIGLE、ETRIGP 触发方式选择 
                     //ASCIE 结束中断使能   ASCIF  结束AD中断标志
      ATD0CTL3=0xc0;   // DJM S8C S4C S2C S1C FIFO FRZ1 FRZ0
                     //    1    0   1   1    0    0    0   0
                     //DJM=0 左对齐存放在结果寄存器中 先存入ATD0DR0H（高位）
                     //DJM=1 右对齐                   先存入ATD0DR0L（低位）
                     // S8C~~S1C 转换序列长度 即要转换的通道数 这里是8
                     //FIFO=0， 结果寄存器映射到转换序列   即依次把数据存入ATD0DR0～ATD0DRn 
                     //FIFO =1  则没有 即ANn通道数据存入ATD0DRn 
                                     //同时依次把数据存入ATD0DR0～ATD0DRn 
      ATD0CTL4=0x64;  // SMP2 SMP1 SMP0   PRS4~~PRS0  
                     //  1     1     0      10011
                     //采样周期选择 T=1/20*Fad     
                     // AD时钟频率Fad=Fbus/2/(PRS+1)=60M/2/5=6M
                     // 最大A/D时钟=2.0MHz(最小A/D CLOCK=0.5MHz)
      ATD0CTL5=0xb0; //  0 SC  SCAN MUIT CD CC CB CA
                     //  1  0   1    1    0 0  0  0   
                     //SC=0 CD~CA用于选择0～15号通道 即起始转换通道选择 
                     //SC=1选择特殊通道
                     //这里从0号通道开始转换
                     //SCAN=0 单次转换 =1 多次连续转换
                     //MUIT=1 多通道转换 =0 单通道转换
      ATD0DIEN=0x00;  //数字输入使能 这里禁止输入
}