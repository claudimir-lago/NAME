# Example 02 — Non-blocking readout

This example is a simplified extraction of the ADS1220/NAME portion of the
minimalistiCE firmware. It removes the C4D ADC handling, pressure control,
high-voltage control, LEDs, communication protocol and other instrument tasks.

The ADS1220 is configured in non-blocking mode. Its `DRDY` output generates an
interrupt when a conversion is ready, after which the main loop reads the ADC,
converts the result to nA, and starts the next conversion.

The deployed minimalistiCE firmware performs its acquisition task at about
75 ms intervals; the example retains that value as a clearly named constant.
The main loop remains available for other instrument tasks while it waits for
both the scheduled sampling time and the ADS1220 `DRDY` signal.

The pin assignment corresponds to the Arduino UNO R4 Minima implementation in
minimalistiCE and can be changed because `ADS1220_WE_SoftSPI` uses software SPI.
