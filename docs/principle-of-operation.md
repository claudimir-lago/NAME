# Principle of operation

NAME (Nanoampere Meter for Electrophoresis) measures the electrophoretic current flowing in a capillary electrophoresis instrument and provides a differential signal suitable for digitization with the ADS1220.

## Current-to-voltage conversion

In the NAME circuit, R2 and R3 are nominally 10 kOhm. R2 is connected to +Vcc and R3 to GND. Seen from their midpoint, the pair can be replaced by its Thevenin equivalent:

- `Vth = Vcc / 2`
- `Rth = R2 || R3 = 5 kOhm`

For a 5 V supply, the quiescent voltage is therefore 2.5 V. A positive electrophoretic current raises the sensing-node voltage above 2.5 V, while a negative current lowers it below 2.5 V.

The current-dependent voltage displacement is

`DeltaV = I * Rth`

and therefore, for `Rth = 5 kOhm`,

`I = DeltaV / 5 kOhm = 200 uA/V * DeltaV = 200 nA/mV * DeltaV`.

Thus, the nominal NAME conversion factor is:

`NAME_NA_PER_MV = 200.0`

## Differential zero adjustment

The ADS1220 is used in differential mode. Its second input is connected to the midpoint of trimmer RV1 and resistors R4 and R5. This provides an adjustable reference close to the quiescent sensing-node voltage.

To adjust zero:

1. leave the NAME current input open, so the input current is approximately zero;
2. observe the ADS1220 differential reading;
3. adjust RV1 until the converted reading is as close to zero as practical.

Because the measurement is differential, firmware does not need to subtract the nominal 2.5 V midpoint explicitly.

## Accuracy and calibration

The factor `200 nA/mV` is the nominal conversion derived from the resistor values. The actual conversion accuracy depends on the tolerance and stability of the resistors, the ADS1220, the reference voltage, and the analog implementation. The present design uses 1% resistors, so applications requiring higher absolute accuracy should use an experimentally determined calibration factor.

A transparent firmware implementation is:

```cpp
constexpr float NAME_NA_PER_MV = 200.0f;
constexpr float NAME_CAL_FACTOR = 1.0f;

float current_nA = ads.getVoltage_mV()
                 * NAME_NA_PER_MV
                 * NAME_CAL_FACTOR;
```

After applying a known current, `NAME_CAL_FACTOR` can be adjusted so the reported current matches the reference value.

## Reference implementations

### minimalistiCE implementation

The working minimalistiCE firmware initializes the ADS1220 conversion scale with:

```cpp
ads.setVRefValue_V(5.0);
```

and performs the NAME conversion explicitly:

```cpp
float current_nA = ads.getVoltage_mV() * 200.0f;
```

This is the clearest approach for an instructional example because the electrical conversion remains visible in the firmware.

### Mark44 implementation

In one ESP32-S3-based instrument operating from 3.3 V, the conversion and an experimentally obtained calibration factor were folded into the value supplied to the ADS1220 library:

```cpp
ads.setVRefValue_V(3.0 * 200.0 * 0.989);
```

With this deliberate rescaling, the numeric result of `getVoltage_mV()` corresponds directly to current in nA. The factor `0.989` was obtained experimentally by applying a known current and comparing it with the uncorrected reading.

This method is compact and convenient in a deployed instrument, but the explicit conversion used in the NAME examples is preferred for documentation because it keeps the physical meaning of each factor clear.
## Frequency response and filtering

The current-sensing node has a nominal Thevenin resistance of 5 kOhm. Together with the 10 nF capacitor connected at this node, it forms a first-order low-pass network with the nominal corner frequency

`fc = 1 / (2*pi*R*C) = 1 / (2*pi*5 kOhm*10 nF) ≈ 3.18 kHz`.

Additional analog filtering is provided by the 100 nF capacitor connected between the differential inputs of the ADS1220. Because this capacitor is connected between the two ADC inputs rather than simply from the sensing node to ground, its exact contribution depends on the differential impedance seen from both inputs. It therefore should not be described as an exact tenfold reduction of the 3.18 kHz corner frequency without considering the complete differential network. In practice, it provides substantial additional attenuation of higher-frequency components.

The effective measurement bandwidth is further reduced by the digital filtering of the ADS1220. The reference firmware enables combined 50/60 Hz rejection with:

```cpp
ads.setFIRFilter(ADS1220_50HZ_60HZ);
```

The resulting useful bandwidth therefore depends not only on the analog RC networks but also on the ADS1220 conversion settings and digital filter response. For this reason, no single overall cutoff frequency is assigned here without a complete measurement or transfer-function characterization of the configured system.

NAME is intended to measure the slowly varying effective electrophoretic current rather than fast current transients. High-frequency current fluctuations have little practical significance for the intended measurement of net electrophoretic migration and contribute little to the accumulated charge when their mean value is close to zero. Consequently, the analog and digital low-pass filtering helps reject noise and interference while preserving the current information relevant to electrophoretic monitoring and charge-domain analysis.

