# ADS1220_WE_SoftSPI

`ADS1220_WE_SoftSPI` is the software-SPI ADS1220 interface used with NAME.
It is derived from Wolfgang (Wolle) Ewald's open-source
[`ADS1220_WE`](https://github.com/wollewald/ADS1220_WE) Arduino library.

The adaptation replaces the dependence on the microcontroller's hardware SPI
pins with software SPI, allowing `SCLK`, `MOSI`, and `MISO` to be assigned to
arbitrary GPIO pins. This is particularly useful when NAME is added to an
existing CE instrument whose hardware SPI interface is already occupied or
whose PCB wiring requires different pins.

## Constructor

```cpp
ADS1220_WE_SoftSPI ads(cs, drdy, mosi, miso, sclk);
```

The configuration enums intentionally use the same values as `ADS1220_WE`, so
calls such as the following remain familiar:

```cpp
ads.setCompareChannels(ADS1220_MUX_1_2);
ads.setGain(ADS1220_GAIN_8);
ads.setVRefSource(ADS1220_VREF_REFP1_REFN1);
```

## SPI timing

The library provides two ways to configure software-SPI speed:

```cpp
ads.setSPIClockSpeed(500000);
```

or directly:

```cpp
ads.setSoftSPIHalfPeriod_us(1);
```

Because software SPI timing depends on the microcontroller and Arduino core,
actual clock frequency may differ somewhat from the requested value.

## Installation

Copy this `ADS1220_WE_SoftSPI` folder into your Arduino libraries directory, or
install it as a ZIP library after packaging this folder by itself.

The NAME examples in `firmware/examples/` use:

```cpp
#include <ADS1220_WE_SoftSPI.h>
```

## Origin and license

The original `ADS1220_WE` library was written by Wolfgang (Wolle) Ewald and is
released under the MIT License. This software-SPI adaptation preserves that
license. See `LICENSE` in this directory.

Original project: https://github.com/wollewald/ADS1220_WE

This bundled library is a third-party-derived component and is therefore not
covered by the repository's GPL license for NAME-specific firmware examples.
