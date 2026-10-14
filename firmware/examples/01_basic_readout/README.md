# Example 01 — Basic readout

This is the simplest NAME acquisition example. It uses the blocking mode of `ADS1220_WE_SoftSPI`, so no interrupt service routine is required.

The example:

1. initializes the ADS1220 through software SPI;
2. configures the same input, gain, external reference, low-side switch, and 50/60 Hz FIR filter used in the deployed minimalistiCE implementation;
3. reads the ADS1220 differential voltage;
4. converts the reading to current in nA;
5. sends `time_ms,current_nA` as CSV through the serial port.

## Why the conversion factor is 200 nA/mV

R2 and R3 are both nominally 10 kOhm. Their Thevenin resistance is therefore 5 kOhm. The electrophoretic current produces a voltage displacement according to `DeltaV = I * 5 kOhm`, so the nominal conversion is `I = 200 nA/mV * DeltaV`.

The ADS1220 reads this signal differentially. Its second input is connected to the adjustable reference formed by RV1 with R4 and R5. With the NAME input left open, RV1 is adjusted until the differential reading is close to zero. No numerical subtraction of the nominal midpoint voltage is therefore required in the example.

The code uses:

```cpp
constexpr float NAME_NA_PER_MV = 200.0f;
constexpr float NAME_CAL_FACTOR = 1.0f;
```

`NAME_CAL_FACTOR` may be replaced by an experimentally obtained value when higher absolute accuracy is needed. The nominal conversion depends on the resistor values and on the ADS1220/reference accuracy.

See [`../../../docs/principle-of-operation.md`](../../../docs/principle-of-operation.md) for the full derivation and calibration notes.

## Pin assignment

The pin assignment shown corresponds to the Arduino UNO R4 Minima used in the minimalistiCE implementation and can be changed freely because the included library uses software SPI.

This example is intended as a clear starting point rather than as a complete CE instrument firmware.
