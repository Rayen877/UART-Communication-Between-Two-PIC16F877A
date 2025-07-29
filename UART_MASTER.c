/*
 * File:   UART_master.c
 * Author: Rayen
 *
 * Created on 31 mai 2025, 12:42
 */
// CONFIG
#pragma config FOSC = XT  // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF  // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit
                          // (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF  // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF  // Flash Program Memory Write Enable bits 
                          // (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF   // Flash Program Memory Code Protection bit (Code protection off)


#include <xc.h>
#include <stdint.h>
#define _XTAL_FREQ 4000000

#define UP RB0
#define DOWN RB1
#define SEND RB2
void UART_TX_Init(void);
void UART_Write(uint8_t);


void main(void) {
   UART_TX_Init();
   uint8_t data=0;
   TRISB= 0x07; //RB 0 RB1 RB2 input
   TRISD= 0x00;
   PORTD= 0x00;
   while(1){
       if(UP){
           data++;
           __delay_ms(350);
       }
       if(DOWN){
          data--;
          __delay_ms(350); 
       }
       if(SEND){
           UART_Write(data);
           __delay_ms(350);
       }
       PORTD=data;
   }
   return;
}

void UART_TX_Init(void){
    BRGH=1;// high speed baudrate
    SPBRG=25;// baudrate 9600
    
    SYNC=0;
    SPEN=1;
    
    TRISC6=1;//tx
    TRISC7=1;//rx
    TXEN=1; //enable uart
}

void UART_Write(uint8_t data){
    while(!TRMT);//data shif is complete(TSR)
    TXREG=data; // TXREG transfer data to TSR to be shifted out
}