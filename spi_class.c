
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


#define _XTAL_FREQ 6000000
#define UP RB0
#define DOWN RB1
#define SEND RB2

void spi_master_init();
void spi_write(uint8_t);




void main(void)
{
    
    spi_master_init();
    uint8_t Data = 0;
    TRISB = 0x07;  //RB0 TO RB2 INPUT
    TRISD = 0x00;  //OUTPUT
    PORTD = 0x00;
    
    
    while(1)
    {
        if(UP)
        {
            Data++;
            __delay_ms(250);
        }
        if(DOWN)
        {
            Data--;
            __delay_ms(250);
        }
        
        if(SEND)
        {
            spi_write(Data);
            __delay_ms(250);
        }
        PORTD = Data;
    }
    
    
}

void spi_master_init()
{
  
  SSPM0 = 0;  // 
  SSPM1 = 0;
  SSPM2 = 0;
  SSPM3 = 0;

  SSPEN = 1;    // Enable Synchronous Serial Port

  CKP = 0;    //Clock Polarity & 
  CKE = 0;   //Phase
  
  SMP = 0;  //Sampling Time
  
  TRISC5 = 0; // SDO -> Output
  TRISC4 = 1; // SDI -> Input
  TRISC3 = 0; // SCK -> Output

}
 
void spi_write(uint8_t Data)
{
  SSPBUF = Data; // Transfer The Data To The Buffer Register
  
}