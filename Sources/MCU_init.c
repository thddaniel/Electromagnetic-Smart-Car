/**********************************
//PLLCLK=2*OSCCLK*(SYNR+1)/(REFDV+1)
//锁相环时钟=2*16*(1+1)/(1+1)=32MHz
************************************/
#include "Includes.h"      //芯片初始化头文件

 void PLL_Init_64M(void)
{   
    CLKSEL=0X00;             //disengage PLL to system
   
    SYNR = 0x40 | 0x07;       // VCOFRQ[7:6];SYNDIV[5:0]
                             // fVCO= 2*fOSC*(SYNDIV + 1)/(REFDIV + 1)
                             // fPLL= fVCO/(2 × POSTDIV) 
                             // fBUS= fPLL/2 
                             // VCOCLK Frequency Ranges  VCOFRQ[7:6]
                             // 32MHz <= fVCO <= 48MHz    00
                             // 48MHz <  fVCO   <= 80MHz    01
                             // Reserved                  10
                             // 80MHz <  fVCO <= 120MHz   11 
                                               
    REFDV=0x80 | 0x01;       // REFFRQ[7:6];REFDIV[5:0]
                             // fREF=fOSC/(REFDIV + 1)
                             // REFCLK Frequency Ranges  REFFRQ[7:6]
                             // 1MHz <= fREF <=  2MHz       00
                             // 2MHz <  fREF <=  6MHz       01
                             // 6MHz <  fREF <= 12MHz       10
                             // fREF >  12MHz               11                         
                             // pllclock=2*osc*(1+SYNR)/(1+REFDV)=160MHz;
    PLLCTL_PLLON=1;          //turn on PLL
    _asm(nop); 
    _asm(nop);
    POSTDIV=0x00;            // 4:0, fPLL= fVCO/(2xPOSTDIV)
                             // If POSTDIV = $00 then fPLL is identical to fVCO (divide by one).
                             //BUS CLOCK=64MHz         
    _asm(nop);
    while(!(CRGFLG_LOCK==1));//when pll is steady ,then use it;
    CLKSEL_PLLSEL =1;        //engage PLL to system; 
}