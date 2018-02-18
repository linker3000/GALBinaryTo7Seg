/*
 * File:   main.c
 * Author: Nigel Kendrick (linker3000@gmail.com)
 *
 * Created on 18 February 2018, 12:29
 * 
 * This version: 0.1
 * 
 * Target device: PIC12F675
 * Environment  : MPLAB X V4.10
 * Compiler     : XC8 V1.45
 * 
 * This program toggles GP4 on a PIC12F675 to produce a clock signal based 
 * on the specified delay parameters. A useful timer replacement where ultra-
 * high accuracy is not needed.
 * 
 * Circuit requirements (excluding power): 
 * 
 * 0.1uF decoupling capacitor across the power rails near to the PIC.
 * MCLR (pin 4) connected to +5V (VDD) via 10K pullup resistor.
 * 
 */

#include <xc.h>
#define _XTAL_FREQ 4000000  // PIC12F675 has internal 4MHz oscillator - needs 
                            // to be correct for delay function.
// BEGIN CONFIG
#pragma config FOSC = INTRCIO // Oscillator Selection bits (Internal)
#pragma config WDTE = ON // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON // Brown-out Reset Enable bit (BOR enabled)
#pragma config CPD = OFF // Data EEPROM Memory Code Protection bit 
#pragma config CP = OFF // Flash Program Memory Code Protection bit 
#pragma config MCLRE = ON // MCLR should be tied to VCC via 10K resistor.
  // Do not turn MCLRE OFF when internal oscillator is used as this makes the
  // 12F675 unprogrammable! (Damn, that would save a 10K resistor!)

//END CONFIG

void main() {
  TRISIO = 0; // Set all I/O as output
  ANSEL = 0;  // Set all pints to digital
  while(1)
  {
    GPIO = (1<<4); // GP4 (12F675 pin 3) ON
    __delay_ms(5); // 5mS Second Delay = 100Hz clock
    CLRWDT();
    GPIO = 0;      // GP4 (12F675 pin 3) OFF
    __delay_ms(5); // 5mS Second Delay = 100Hz clock
    CLRWDT();
  }
}
