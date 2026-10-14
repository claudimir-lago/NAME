# Interfacing NAME

This document summarizes the external electrical connections of the current NAME hardware revision.

## J1 — Electrophoretic-current input

J1 is the two-pin connection between NAME and the capillary electrophoresis instrument.

| Pin | Function | Description |
|---|---|---|
| 1 | Shield | Cable shield connection. |
| 2 | Current input | Connect to the **low-voltage electrode** of the capillary electrophoresis system. |

The NAME current input is intended to be inserted on the low-voltage side of the CE electrical path. The high-voltage architecture and electrical safety of the host CE instrument must be evaluated independently before installation.

## J2 — Power supply

J2 powers the NAME board.

| Pin | Function | Description |
|---|---|---|
| 1 | VCC | Supply voltage, **3 to 5 V**. |
| 2 | GND | Ground. |

The firmware configuration of the ADS1220 voltage reference must be consistent with the supply/reference arrangement used in the host instrument.

## J3 — Digital interface

J3 provides the ADS1220 digital interface to the host microcontroller.

| Pin | Signal | Description |
|---|---|---|
| 1 | DRDY | ADS1220 data-ready output. |
| 2 | MISO | Software-SPI data from ADS1220 to the microcontroller. |
| 3 | MOSI | Software-SPI data from the microcontroller to ADS1220. |
| 4 | SCLK | Software-SPI clock. |
| 5 | CS | ADS1220 chip select. |
| 6 | CLK | Reserved / not used in the current NAME implementation. |

The reference firmware uses `ADS1220_WE_SoftSPI`, so MISO, MOSI, SCLK, and CS are not restricted to the microcontroller's default hardware-SPI pins.

## Minimal installation sequence

1. Connect J2 to a regulated 3–5 V supply and ground suitable for the host instrument.
2. Connect J3 to the selected microcontroller GPIOs and configure the same pins in firmware.
3. Connect J1 pin 2 to the low-voltage electrode of the CE system and J1 pin 1 to the cable shield as appropriate for the instrument wiring.
4. With the NAME current input open so that the input current is approximately zero, adjust RV1 until the differential ADS1220 reading is as close to zero as practical.
5. Verify polarity with a known test current before routine use. If improved absolute accuracy is required, determine and apply a calibration factor as described in [`principle-of-operation.md`](principle-of-operation.md).

## Important note

NAME is intended for use in capillary electrophoresis instrumentation, where hazardous high voltages may be present elsewhere in the system. The NAME input should be connected only as described for the low-voltage side of the CE system. See [`safety.md`](safety.md) for the current safety notes.
