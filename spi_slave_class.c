// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdint.h>
//#include "config.h"

#define _XTAL_FREQ 6000000
void spi_slave_init();
uint8_t  spi_read();

uint8_t Data;

void main()
{
    spi_slave_init();
    TRISB = 0x00;
    while(1)
    {
        PORTB = Data;
    }
    return;
}

void spi_slave_init()
{
  // Set Spi Mode To Slave + SS Enabled
  SSPM0 = 0;
  SSPM1 = 0;
  SSPM2 = 1;
  SSPM3 = 0;
  // Enable The Synchronous Serial Port
  SSPEN = 1;
  // Configure The Clock Polarity & Phase (SPI Mode Num. 1)
  CKP = 0;
  CKE = 0;
  // Clear The SMP Bit
  SMP = 0;
  // Configure The IO Pins For SPI Master Mode
  TRISC5 = 0; // SDO -> Output
  TRISC4 = 1; // SDI -> Input
  TRISC3 = 1; // SCK -> Intput
  PCFG3 = 0; // Set SS (RA5/AN4) To Be Digital IO
  PCFG2 = 1;
  PCFG1 = 0;
  PCFG0 = 0;
  TRISA5 = 1; // SS -> Input
  // Enable Interrupts. Comment Them To Disable interrupts(NOT Recommended)
  SSPIE = 1;
  PEIE = 1;
  GIE = 1;
}
 

 
void __interrupt() ISR(void)
{
  if(SSPIF)
  {
    Data = SSPBUF; // Read The Buffer
    SSPIF = 0; // Clear The Interrupt Flag
  }
}