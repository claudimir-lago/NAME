/*
  NAME - Nanoampere Meter for Electrophoresis
  Example 02: non-blocking current readout using DRDY interrupt

  This example extracts the NAME acquisition strategy used in the minimalistiCE
  firmware while removing unrelated C4D, pressure, high-voltage and user-interface
  code.

  NAME-specific example code: GPL-3.0-or-later.
  ADS1220_WE_SoftSPI is distributed separately under the MIT License.
*/

#include <ADS1220_WE_SoftSPI.h>

constexpr int ADS1220_CS_PIN   = A0;
constexpr int ADS1220_DRDY_PIN = 2;
constexpr int ADS1220_MOSI_PIN = A2;
constexpr int ADS1220_MISO_PIN = A3;
constexpr int ADS1220_SCLK_PIN = A1;

constexpr float NAME_NA_PER_MV = 200.0f;
constexpr float NAME_CAL_FACTOR = 1.0f;
constexpr unsigned long SAMPLE_INTERVAL_MS = 75;

ADS1220_WE_SoftSPI ads(
  ADS1220_CS_PIN,
  ADS1220_DRDY_PIN,
  ADS1220_MOSI_PIN,
  ADS1220_MISO_PIN,
  ADS1220_SCLK_PIN
);

volatile bool dataReady = false;
unsigned long lastSample_ms = 0;

void dataReadyISR() {
  dataReady = true;
}

void startConversion() {
  dataReady = false;
  ads.start();
}

void setup() {
  Serial.begin(115200);

  while (!ads.init()) {
    Serial.println("ADS1220 not found");
    delay(1000);
  }

  ads.setSPIClockSpeed(500000);
  ads.setNonBlockingMode(true);
  ads.setCompareChannels(ADS1220_MUX_1_2);
  ads.setGain(ADS1220_GAIN_8);
  ads.setVRefSource(ADS1220_VREF_REFP1_REFN1);
  ads.setVRefValue_V(5.0);
  ads.setLowSidePowerSwitch(ADS1220_SWITCH);
  ads.setFIRFilter(ADS1220_50HZ_60HZ);

  attachInterrupt(
    digitalPinToInterrupt(ADS1220_DRDY_PIN),
    dataReadyISR,
    FALLING
  );

  Serial.println("time_ms,current_nA");
  lastSample_ms = millis();
  startConversion();
}

void loop() {
  // The working minimalistiCE firmware services NAME about every 75 ms.
  // Waiting for both the scheduled time and DRDY preserves that cadence while
  // leaving the main loop free for other instrument tasks.
  if ((millis() - lastSample_ms) < SAMPLE_INTERVAL_MS || !dataReady) {
    return;
  }

  const unsigned long sampleTime_ms = millis();
  const float current_nA = ads.getVoltage_mV() * NAME_NA_PER_MV * NAME_CAL_FACTOR;

  Serial.print(sampleTime_ms);
  Serial.print(',');
  Serial.println(current_nA, 1);

  lastSample_ms = sampleTime_ms;
  startConversion();
}
