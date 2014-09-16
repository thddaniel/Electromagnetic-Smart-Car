#ifndef  NOKIA_H
#define  NOKIA_H

  #define SCLK PORTB_PB0
  #define SDIN	PORTB_PB1      
  #define DC PORTB_PB7
  #define CE PORTB_PB5
  #define RST PORTB_PB6  
  #define BL PORTB_PB2
  
     void LCD_init(void);
     void LCD_clear(void); 
     void deplay(void);
  
#endif