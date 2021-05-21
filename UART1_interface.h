#ifndef UART1_interface_h
#define UART1_interface_h

    /*  Configuration Section   */
#define BAUD_RATE               9600
#define SYS_CLK                 16000000
#define CLK_DIV                 16000000



    /*  Interfacing Section     */
typedef unsigned char           u8;
typedef long int                u32;

void UART1_init(void);
void delayUs(u32 n);
void UART1_vidTransmit(u8 Copy_u8Data);
u32 UART1_u8Receive(void);


#endif