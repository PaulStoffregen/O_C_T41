## Front Panel

There are 4 choices for the front panel. Two are "ornate" with swirly background decorations (they look great in purple), and two have flat backgrounds without texture.

All are dual-sided/invertable in case you want to use the module with the jacks at the top and the screen at the bottom.

In each pair, you will find a USB-A and USB-C label which indicates the shape of the cutout for the host socket.

- If you choose a panel with a USB-A host port, you may need to provide a comment with your order: a note to the fabricator stating that the rectangular cutout in the EdgeCuts/KO layer overlapping the oblong hole near the "Host" silkscreen label IS intentional.
- The cutout in the finished product should be rectangular to accomodate a USB-A socket, the overlapping PTH is only there to ensure the cutout gets plated. If there is a better way to accomplish this in KiCad, please open an Issue with your recommendations!

        Note: In the batch I purchased from OSHPark, they did not cut out the rectangular USB slots, just the oblong drill holes. I had to finish them myself with a rotary tool and a file but they turned out petty much ok. It was tedious and I had to be very careful, and the result wasn't as sleek as those done at the fab shop, but nobody can tell from across the room. JLCPCB has cut them properly and plated the slots every time.


## Expanders

If you choose a panel with a USB-C host port, you may use the same 2 HP expander PCB on both sides, but you must pay attention to the resistor requirements for the USB-C CC pins:

- The DEV port requires **pull-downs**: connect the CC pins to ground through resistors with the USB-C standard value of 5.1k Ohms.

- The HOST port requires **pull-ups**: connect the CC pins to VBUS through resistors with a value corresponding to the VBUS voltage on the Teensy. (Rev3.x is designed with 4.2 Volts on VBUS, but you may hack your module to use 5 Volts which will change the resistors used here.)
    - For the default 4.2 Volts, use 45.3k Ohm resistors
    - For 5 Volt-modded modules, use the USB-C standard 56k Ohm.

The USB-A expander doesn't care about all that.

There is a jumper pad on the backside of both expanders near the MIDI jack. Bridging the pads with solder will connect the MIDI shield pin to ground. Only do this for the MIDI Out jack.

If you flip your module, you may have to swap the expanders to the opposite side, and reconnect some wires. Just pay attention what connects where, and use the labels on the front panel as a guide.

