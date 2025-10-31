# O_C T4.1 - Ornament and Crime with Teensy 4.1

![](docs/main_with_expansions.jpg)

While porting the Ornament and Crime code to run on Teensy 4, the question kept
coming up "what can a 600 MHz processor let me do".  Turns out the extra memory
allows [Phazerville firmware](https://github.com/djphazer/O_C-Phazerville)
to support all applets in a single image.  But the
original hardware designed for Teensy 3.2 limits what Teensy 4.0 can do.  The
necessity to share a single SPI port's bandwidth between the display and DAC
chip is the main limit.

![](docs/block_diagram.png)

O_C T4.1 was born to allow Teensy 4.1 to be fully utilized by Phazerville
firmware.  Control Voltage (CV) input and output was doubled to 8 signals.
An ADC chip was added for higher quality CV input, free from the on-chip
digital noise of a CPU.  Most importantly, three fully independent SPI port
are used for the display, CV inputs, and CV outputs.  Technically, the CV
input SPI is "FlexIO" which adds control of an analog mux chip.  All 3 have
fully independent bandwidth.

Audio input and output were also added, using fully independent bandwidth
of the I2S (digital audio) port.  Serial for MIDI, 480 Mbit/sec USB host,
and I2C for future expansion are also available on connectors meant for
expansion modules.

Additional memory can be added to Teensy 4.1, in the form of a PSRAM chip
give extra memory useful for audio effects, and a SD card for non-volatile
storage.  As with everything else, these have fully independent bandwidth.
Everything has optimal access for Teensy 4.1.  Phazerville leverages
optimized drivers with Direct Memory Access (DMA) for all of these peripherals.
O_C T4.1 truly is optimized to let Ornament and Crime make the most of
the powerful Teensy 4.1 processor!


# Attribution ShareAlike

Huge thanks & credit to mxmxmx who designed to the original Ornament and Crime module
so many years ago when Teensy 3.2 was new.

In 2023 mxmxmx waived the non-commercial license term for O_C T4.1, so the open source
license is now CC BY-SA 4.0.  Paul Stoffregen is not concerned about attribution,
but any O_C T4.1 Ornament and Crime product should give appropriate credit to mxmxmx.

If you see commercially sold O_C T4.1 without even a tiny footnote for attribution,
please send the vendor a gentle and polite reminder that attribution to mxmxmx is
required.


# Rev 3 issues:

Solder pads (7 pins) for the display should be raised approximately 1mm, towards the
top edge of the board.  To make the display fit, usually the 7 header pins need to
be bent slightly.

**3 beta testers had Teensy I/O pins damaged**, mostly encoders and pushbuttons.  If you build Rev 3, **USE A SOCKET** between Teensy and the CPU board.

Audio input clipping on 1 channel distorts other channel input - TODO: document resistors to change amplifier gain

Control board should allow more clearance for external trigger headers / wires


# Changes

Thanks to recent work by Beau Seidon, the files are now fully converted to KiCad for easier
editing to spin your own design.  Diode D6 added to protect U17 during unusual power startup.
Gerber files o_c_3_analog_new_jlc.zip and o_c_3_cpu_new_jlc.zip have been built and tested,
so you can simply build from known-good files.  Or you can use the KiCad files to make your
own design.

Capacitors C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12 are not needed by newer Phazerville firmware.


# MIDI

![](docs/expansion_panel.jpg)

![](docs/midi_din5_pinout.png)

![](docs/midi_din5_wiring.png)

![](docs/midi_din5_wiring2.jpg)


# Teensy Voltage and USB Host

O_C T4.1 rev3 uses a switching power supply to step down +12V modular power to
4.25V to run Teensy 4.1.  This voltage was chosen to reduce the load placed on
your +12V modular power rail.

However, when using USB host, Teensy 4.1 will supply about 4.1 volts to your
USB device.  This is below the 4.4V requirement of the USB 2.0 specification,
but most lower power USB devices which use a linear or step-down switcher to
3.3V typically can work.

If you want full 5 volt USB host power output, you have 2 options.

The best option is a powered USB hub, which also gives you the ability to
connect multiple USB devices!  If designing an add-on module, the USB hub chip
and power delivered to USB device would be best sourced from the modular +5V
power rail, generally meant for digital circuitry.  USB hub chips with
"Multiple Transaction Translators" (MTT) give better performance than "Single
Transaction Translator".  CH334 from WCH is a very low cost MTT hub chip
to consider, usually in stock at LCSC.

Or you can modify the O_C T4.1 power supply to provide 5V rather than 4.25V.
The trade off is O_C T4.1 will consume more power, because Teensy 4.1 uses
a linear regulator.  If using power hungry USB devices, they will also be
powered via the modular +12V rail, generally meant for analog circuitry.
The small step-down regulator on O_C T4.1 rev3 is limited to 600mA.  Teensy
4.1 typically consumes 110mA, but if a SD card is used it will also draw
current, leaving less available for USB devices.
To modify for 5V, if using the old gerber files add D6 by soldering on top
of C59.  Then increase R127 to 27K to change the power supply voltage.  If
using MIDI OUT, change R139 and R140 to 120 ohms for proper MIDI current.


# USB Host

![](docs/usb_host_teensy41.jpg)

![](docs/usb_host_right_angle_header.jpg)

![](docs/usb_host_gamepad.jpg)

![](docs/usb_host_midi_LPD8.jpg)

[USB Host Cable at SparkFun](https://www.sparkfun.com/usb-host-cable-for-teensy-4-1-and-teensy-3-6.html) - For connecting MIDI instruments, Gamepad controllers, maybe other stuff as software support develops...

[USB Device Cable at AdaFruit](https://www.adafruit.com/product/937) - For connecting to your PC or Mac, for upgrading [Phazerville firmware](https://github.com/djphazer/O_C-Phazerville), O_C can act as a MIDI device, and to run the [screen capture program](https://github.com/PaulStoffregen/Phazerville-Screen-Capture).

![](docs/expansion_panel_back.jpg)


# Additional Memory

![](docs/psram_chip.jpg)

![](docs/psram_chip2.jpg)


# External Trigger

Normally the 4 trigger inputs are connected (shared) to CV1-CV4.


![](pcb/external_triggers.png)

You can modify the hardware to separate the triggers from CV1-CV4.

Cut JP1-JP4 apart to disconnect the triggers from CV1-CV4.  Then
wire external trigger jacks to J24 and J25.  100K resistors are
also recommended between each trigger input and GND, to prevent
false triggering when the cable is "floating".

![](docs/ext_trigger_pcb2.jpg)

![](docs/ext_trigger_pcb.png)

![](docs/ext_trigger_schematic_default.png)

![](docs/ext_trigger_schematic.png)


# Test Points For Troubleshooting

The control board has 14 test points to help you diagnose hardware problems.
Use a DC voltmeter with the negative lead connected to AGND, then carefully
touch the test points with the positive lead with care not to accidentally
also touch nearby parts.

Tests can be done with the analog board connected or removed.  If signals
which connect to the analog board read zero or a very low number, short
circuits or other problems might be on the analog board.  Removing it and
checking whether the voltages returns to normal may help localize the issue.

Testing the voltages in this order usually makes the most sense.

## 11.2V and -11.2V (TP13 and TP12)

These are your Eurorack power after passing through the D1 diodes which
allow plugging the 10 pin power cable in either direction.  Normally
you would expect to see a slightly smaller (absolute) number for 11.2V
than -11.2V because more current is consumed from +12V.  But the actual
numbers you see will depend on your Eurorack power supply.

## 4.25V (TP5)

Main input power for Teensy 4.1, the 1.3 inch display, and MIDI:
This is created by U13, L1, L2, R126, R127, R128, R129, C53, C74, C92.

## DIGITAL 3.3V (TP8)

Main digital power: Teensy 4.1 creates this 3.3V power for digital
circuitry using the 4.25V main power.

## 0.1V (TP15)

Identification voltage for O_C T4.1 rev 3 hardware: Phazerville
firmware reads this voltage at startup to "know" which circuit board
you have built.  The voltage is created by R121 and R130.

Optionally R202 can be soldered to increase the ID voltage.  Normally
this would only be done if substantially modifying the hardware to
another configuration
[Phazerville firmware](https://github.com/djphazer/O_C-Phazerville)
supports.

## 6.1V (TP6)

Analog input power: this is the power input to voltage regulators
which power sensitive analog circuitry.  It is created by diode
D2 and C69.  The exact voltage depends on your Eurorack power supply
and D2.  Any voltage between 6.7V to 5.5V is acceptable, because the
analog voltage regulators will create the actual analog power from
this unregulated input.

Diode D2 runs warm during normal operation.

## 5.0V and 3.3V (TP10 and TP7)

Analog power for analog input and output chips.  5.0V is created by
U14, C72, C76, C91, and 3.3V is created by U15, C60, C71, C78.

## 2.5V REF (TP3)

Primary 2.5V reference: This is the main reference voltage that is
the fundamental source for accuracy of all Control Voltage (CV) inputs
and outputs.  It is created by U19, C62, C79.  This voltage does not
turn on automatically at startup.  Phazerville fireware must configure
and enable it.  If you see no voltage, Teensy may not be running, or
Phazerville may be reading incorrect ID voltage which could cause it
to attempt use of a different chip, like the one used on original
Ornament and Crime with only 4 CV outputs.

## 1.8V (TP11)

Analog ADC power: This powers the ADC chip used for all 8 CV inputs.
It is created by U16, C58, C80.  This power is kept off until the
2.5V REF is active, because the U17 ADC chip has a self calibration
feature which only works properly if its other power sources start
up earlier.

## 5.0V REF (TP2)

Analog ADC reference: This is the voltage reference used by the ADC
chip for accuracy of all CV inputs.  It is created from 2.5V REF by
U26, R118, R136, R137, C59, C92, C93, L3, D6.

## 1.25V (TP9)

Analog CV Output Bias: All CV output amplifiers on the analog board
use this voltage to convert the DAC chip (U19) positive-only voltages
to Control Voltage which may be positive or negative.  It is created
by R133, R134, R61.

Optionally R200 can be soldered to modify CV output voltage range.
Normally this modification would be used with
[Squares and Circles](https://github.com/eh2k/squares-and-circles)
firmware.

## -5.0V (TP1)

Analog CV Input Offset: All CV input amplifiers on the analog board
use this offset voltage to convert Control Voltage (might can be
positive or negative) to the positive-only range of the ADC input
chips (U17 and U18).  It is created by U26, R135, R138.

Optionally R201 can be soldered to modify CV input voltage range.
Normally this modification would be used with
[Squares and Circles](https://github.com/eh2k/squares-and-circles)
firmware.

## 1.5V (TP14)

Trigger Threshold: All 4 trigger inputs use this voltage to define
the difference between off and on.  Actual triggering uses ~10%
hysteresis, so the off-to-on threshold will be slightly higher than
this voltage, and the on-to-off wil be slightly lower.  Hysteresis
is meant to prevent false triggering with analog signals close to
the threshold, especially if they have slight noise or modulation.



