#include "UART1_interface.h"


#define UARTDR                  (volatile u32*)0x4000D000
#define UARTIBRD                (volatile u32*)0x4000D024
#define UARTFBRD                (volatile u32*)0x4000D028
/*         RCGCUART register enables the clock to the UART                       */
#define RCGCUART                (volatile u32*)0x400FE618
/*        Disable UARTCTL while modifying the UART registers                    */
#define UARTCTL                 (volatile u32*)0x4000D030
/*        Use UARTLCRH register to set the number of bits
            per character(data length) in a frame                               */
#define UARTLCRH                (volatile u32*)0x4000D02C
#define RCGCGPIO		(volatile u32*)0x400FE608
#define GPIOB_DEN               (volatile u32*)0x4000551C
#define GPIOAFSEL               (volatile u32*)0x40005420
#define GPIOPCTL                (volatile u32*)0x4000552C
#define GPIOF_DIR  		(volatile u32*)0x40025400
#define GPIOF_DATA       	(volatile u32*)0x40025000
#define GPIOF_DEN	        (volatile u32*)0x4002551C
                                           
#define UARTFR                  (volatile u32*)0x4000D018
/*UART1 Clock*/
//#define UARTCC                  (volatile u8*)0x400FE                   

#define RXE                     (u8)9
#define TXE                     (u8)8
/*        HSE=1 makes the prescaler is "/8" instead of
             the default "/16" which fastens the system                         */
#define HSE                     (u8)5
#define UARTEN                  (u8)0
#define D1                      (u8)1
#define WLEN_1                  (u8)6
#define WLEN_0                  (u8)5
#define PORTB_EN                (u8)1
#define PB0                     (u8)0
#define PB1                     (u8)1

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

void UART1_init(void)
{
    /*    Enable clock to UART1                                                 */
  *(RCGCUART)|= (1<<D1);
    /*    Enable GPIO for UART1                                                 */
    /*    Enable GPIO For PORTF                                                 */
  *(RCGCGPIO)|= (1<<PORTB_EN) | (1<<5);
      
    /*    Disable UART                                                          */
  *(UARTCTL)= 0;

    /*    Configure the baud rate(integer part)                                 */
  //*(UARTIBRD)=  SYS_CLK/(BAUD_RATE*CLK_DIV);
  *(UARTIBRD)= 104;
  
    /*    Configure the baud rate(fractional part)                              */
  //*(UARTFBRD)= (float)((SYS_CLK%(BAUD_RATE*CLK_DIV))*64)+0.5;
  *(UARTFBRD)= 11;
  
    /*    Configure Data register tx and rx 8 data bits                         */
  *(UARTLCRH)|= (1<<WLEN_1) | (1<<WLEN_0); 
  
    /*    Enable the UART(UARTEN), Tx & Rx bits                                 */
  *(UARTCTL)|= (1<<UARTEN) | (1<<TXE) | (1<RXE);
  
   /*      Configure PB0 & PB1 as digital                                       */
  *(GPIOB_DEN)|= (1<<PB1) | (1<<PB0);
  
   /*      Use PB0 & PB1 as alternative function                                */
  *(GPIOAFSEL)= 0x03;
    
   /*      Configure PB0 and PB1 for UART                                       */
  *(GPIOPCTL)= 0x11;
  
  
  delayUs(1);
//  *(GPIOF_DIR) = 0x0E; /* configure Port F to control the LEDs */
// *(GPIOF_DEN) = 0x0E;
//  *(GPIOF_DATA) = 0;
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

void UART1_vidTransmit(u8 Copy_u8Data)
{
 
    while( (*(UARTFR)&(1<<5)) !=0 )
  //while ( (*(UARTFR) & 0x20) !=0)
  {
   /*               Do Nothing till Data Buffer is empty                        */
  }
  //*(UARTFR)=0; 
  *(UARTDR)= Copy_u8Data;   
   
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

u32 UART1_u8Receive(void)
{
  u32 Local_u32data;
  
  while ( (*(UARTFR) & 0x10) !=0)
  {
   /*          Do Nothing till Data Register is received something              */    
  }
  
  Local_u32data =*(UARTDR) ;
  return Local_u32data;
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void delayUs(u32 n)
{
u32 i, j;
for(i = 0 ; i < n; i++)
  {
    for(j = 0; j < 3; j++)
      {
        /*                          do nothing                                  */
      }
  }
}
  