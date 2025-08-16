# O_C T4.1 - Ornament and Crime with Teensy 4.1

![](docs/main_with_expansions.jpg)


TODO - add short history here




![](docs/block_diagram.png)


TODO - explain technical stuff a bit...



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


# Changes:

Diode D6 added to protect U17 during unusual power startup.

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



