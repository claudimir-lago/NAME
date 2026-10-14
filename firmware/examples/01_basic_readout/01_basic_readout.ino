/*
  NAME - Nanoampere Meter for Electrophoresis
  Example 01: basic blocking current readout

  This example shows the minimum code required to read NAME with the ADS1220
  using ADS1220_WE_SoftSPI. It is intentionally independent of the rest of a
  CE instrument controller.

  The pin assignment below is the one used in the minimalistiCE implementation
  on an Arduino UNO R4 Minima. Change it to match your microcontroller wiring.

  NAME-specific example code: GPL-3.0-or-later.
  ADS1220_WE_SoftSPI is distributed separately under the MIT License.
*/

#include <ADS1220_WE_SoftSPI.h>

constexpr int ADS1220_CS_PIN   = A0;
constexpr int ADS1220_DRDY_PIN = 2;
constexpr int ADS1220_MOSI_PIN = A2;
constexpr int ADS1220_MISO_PIN = A3;
constexpr int ADS1220_SCLK_PIN = A1;

// NAME current conversion.
// R2 = R3 = 10 kOhm give a Thevenin resistance of 5 kOhm.
// Therefore I = DeltaV / 5 kOhm = 200 nA/mV * DeltaV.
// The ADS1220 reads the signal differentially, so the nominal midpoint
// voltage does not need to be subtracted in firmware.
constexpr float NAME_NA_PER_MV = 200.0f;

// Set this to an experimentally determined value when higher absolute
// accuracy is required. The nominal, uncalibrated value is 1.0.
constexpr float NAME_CAL_FACTOR = 1.0f;

ADS1220_WE_SoftSPI ads(
  ADS1220_CS_PIN,
  ADS1220_DRDY_PIN,
  ADS1220_MOSI_PIN,
  ADS1220_MISO_PIN,
  ADS1220_SCLK_PIN
);

void setup() {
  Serial.begin(115200);

  while (!ads.init()) {
    Serial.println("ADS1220 not found");
    delay(1000);
  }

  ads.setSPIClockSpeed(500000);
  ads.setCompareChannels(ADS1220_MUX_1_2);
  ads.setGain(ADS1220_GAIN_8);
  ads.setVRefSource(ADS1220_VREF_REFP1_REFN1);
  ads.setVRefValue_V(5.0);
  ads.setLowSidePowerSwitch(ADS1220_SWITCH);
  ads.setFIRFilter(ADS1220_50HZ_60HZ);

  Serial.println("time_ms,current_nA");
}

void loop() {
  // In the default blocking mode, getVoltage_mV() starts a single conversion
  // and waits for DRDY before reading the ADS1220 result.
  const float current_nA = ads.getVoltage_mV() * NAME_NA_PER_MV * NAME_CAL_FACTOR;

  Serial.print(millis());
  Serial.print(',');
  Serial.println(current_nA, 1);

  delay(75);
}
