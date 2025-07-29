/*
 * File:   UART_slave.c
 * Author: Rayen
 *
 * Created on 31 mai 2025, 13:05
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

void UART_RX_Init(void);
uint8_t UART_READ(void);
uint8_t UART_Buffer=0;

void main(void) {
    UART_RX_Init();
    TRISB=0;
    PORTB=0;
    while(1){
        //interruption 
    }
    return;
}
void UART_RX_Init(){
   BRGH=1;
   SPBRG = 25;
   
   SYNC=0;
   SPEN=1;
   
   TRISC6=1;
   TRISC7=1;
   
   RCIE=1;
   PEIE=1;
   GIE=1;
   
   CREN=1;// enable data continous reception
   
}

void __interrupt() ISR(void){
    if(RCIF==1){
        UART_Buffer= RCREG;
        PORTB= UART_Buffer;
        RCIF=0;
    }
}