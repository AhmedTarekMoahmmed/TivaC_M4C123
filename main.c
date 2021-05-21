#include "UART1_interface.h"

/* PORTF data register */
#define PORTFDAT (*((volatile unsigned int*)0x400253FC))
/* PORTF data direction register */
#define PORTFDIR (*((volatile unsigned int*)0x40025400))
/* PORTF Pull up register */
#define PORTFPUR (*((volatile unsigned int*)0x40025510))
/* PORTF digital enable register */
#define PORTFDEN (*((volatile unsigned int*)0x4002551C))
/* run mode clock gating register */
#define RCGCGPIO (*((volatile unsigned int*)0x400FE608))
/* coprocessor access control register */
#define SCB_CPAC (*((volatile unsigned int*)0xE000ED88))


int main(void)
{
  /* enable clock to GPIOF at clock gating register */
  RCGCGPIO |= 0x20;
  /* set PORTF pin3-1 as output pins */
  PORTFDIR = 0x08;
  /* set PORTF pin3-1 as digital pins */
  PORTFDEN = 0x18;
//PORTFDAT1 = 0xff;
  PORTFPUR = 0x10;
  
  
  u32 i,j=0;
  static u8 string[]="enter A";
  UART1_init();
  while(string[j] != '\0')
  {
    UART1_vidTransmit(string[j]);
    j++;
  }
while(1)
    {
      
     // UART1_vidTransmit('s');

     i= UART1_u8Receive();
     if(i=='a')
     {
      (PORTFDAT)|= (1<<1);
     }  
   /*  for(i=0; i<3; i++)
     {
        UART1_vidTransmit(string[i]);
      } 
  */
    }
  
  
  return 0;
}

