# Firmware and Arduino integration

NAME does not require a dedicated controller. The ADS1220 can be read by the
microcontroller already used by a CE instrument.

The reference implementation included here is derived from the working
minimalistiCE firmware and uses a software-SPI adaptation of the `ADS1220_WE`
library.

## Included library

`libraries/ADS1220_WE_SoftSPI/` allows the ADS1220 `SCLK`, `MOSI`, and `MISO`
signals to be assigned to arbitrary GPIO pins rather than to the fixed hardware
SPI interface. This makes NAME easier to add to an existing instrument.

The library is derived from Wolfgang Ewald's `ADS1220_WE` project and retains
its MIT License. It is therefore licensed separately from the NAME-specific GPL
firmware examples.

## Examples

- `examples/01_basic_readout/` — minimal blocking acquisition.
- `examples/02_nonblocking_readout/` — interrupt-driven acquisition based on
  the strategy used in minimalistiCE.

The examples output CSV records containing elapsed time and electrophoretic
current in nA.

## Related project

The acquisition strategy was extracted from firmware developed for
[minimalistiCE](https://github.com/lab-laia/minimalistiCE), an open CE
instrument developed in the same laboratory.
