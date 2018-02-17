# GALBinaryTo7Seg
**8 bit binary displayed as hex on two 7 segment displays (a bus monitor)**

** This write-up is  work in progress - more details to follow **

This CUPL code programs a GAL16V8 to drive two COMMON ANODE 7 segment displays so that they display the hex representation of the 8-bit input in real time (no clocking-in or latching). This is ideal for monitoring 8-bit buses in real time - the GAL logic cells effectively act as a fast look-up table running at the nS level - unlike a microcontroller, which would respond at the mSec/uSec level. 

There is support circuitry needed to make the whole unit; a schematic and further instructions will be posted later, but in summary (in case you want to work it out for yourself!), you will need:

* 1 x GAL16V8 (Microchip (Atmel) or New old stock from eBay, Aliexpress or UTSource)
* 1 x 0.22uF capacitor
* 2 x 7 segment displays COMMON ANODE
* 14 x 390 ohm resistors
* 2 x 2N3906 general purpose PNP transistors
* 2 x 1K8 resistors
* A clock source (to alternate the displays by turning on the transistors one at a time) - something > 100Hz
* 1 x 74LS373 8-bit buffer (optional - see below)

You will also need a GAL programmer (the TL866 can do it - that's what I use. IMPORTANT: Untick 'Encrypt Ch' otherwise the GAL may not program correctly.). Use the .JED file here as the source for the programmer. If you want to edit/change the source PLD file, you will need a copy of WinCUPL (free from https://www.microchip.com/design-centers/programmable-logic/spld-cpld/tools/software/wincupl) or another CUPL editor.

The general wiring is as follows (you can extrapolate from the .PLD and .DOC files too - they're plain text files with more info)..

* The 8-bit binary is input on GAL pins 1-8 (5V TTL level)
* The clock that toggles the PNP transistors is input on pin 9. 
* An inverse of this clock is output from pin 12.
* The 7 segment outputs (in standard nomenclature for segments a-g) are output from pins 19 back to 13

* Wire the display connections in parallel (a to a, b to b etc.) as only one is on at a time.
* Connect the 7 segment display paired wiring to GAL pins 19-13 through 390 ohm resistors. 
* Connect the two PNP transistors to drive the common anodes - emitters to 5V, collectors to the LED common anodes (one per common anode).
* Connect (via 1K8 resistors), one transistor base to the same GAL pin as the input clock (pin 9), the other to pin 12 - this means the transistors are driven on alternately.
* Connect the capacitor across the GAL supply rails, as close to the chip as possible.

*If when you wire everything up the hex digits are the wrong way round, transpose the transistor base connections to the GAL.*

**Optional extra - 74LS373**

If you feed the 8-bit input to the GAL through a 74LS373 8-bit latch, this chip will free-run (no clock needed), but will freeze its output when pin 11 ('C') is taken low - so you can use this as a trigger to halt the display if you need to check a value at a specific time.

A schematic will follow shortly.
