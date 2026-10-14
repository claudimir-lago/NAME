/*
 * ADS1220_WE_SoftSPI
 * Software-SPI adaptation of Wolfgang (Wolle) Ewald's ADS1220_WE library.
 * Original project: https://github.com/wollewald/ADS1220_WE
 * Original library copyright (c) 2022 Wolfgang (Wolle) Ewald.
 * Licensed under the MIT License; see ../LICENSE.
 * Modified to permit arbitrary GPIO assignment for SCLK, MOSI and MISO.
 */

#pragma once

#include <Arduino.h>

// Values intentionally match ADS1220_WE, so existing configuration calls can
// be moved to ADS1220_WE_SoftSPI without changing their arguments.
typedef enum ADS1220_MUX { ADS1220_MUX_0_1=0x00, ADS1220_MUX_0_2=0x10, ADS1220_MUX_0_3=0x20, ADS1220_MUX_1_2=0x30, ADS1220_MUX_1_3=0x40, ADS1220_MUX_2_3=0x50, ADS1220_MUX_1_0=0x60, ADS1220_MUX_3_2=0x70, ADS1220_MUX_0_AVSS=0x80, ADS1220_MUX_1_AVSS=0x90, ADS1220_MUX_2_AVSS=0xA0, ADS1220_MUX_3_AVSS=0xB0, ADS1220_MUX_REFPX_REFNX_4=0xC0, ADS1220_MUX_AVDD_M_AVSS_4=0xD0, ADS1220_MUX_AVDD_P_AVSS_2=0xE0 } ads1220Mux;
typedef enum ADS1220_GAIN { ADS1220_GAIN_1=0x00, ADS1220_GAIN_2=0x02, ADS1220_GAIN_4=0x04, ADS1220_GAIN_8=0x06, ADS1220_GAIN_16=0x08, ADS1220_GAIN_32=0x0A, ADS1220_GAIN_64=0x0C, ADS1220_GAIN_128=0x0E } ads1220Gain;
typedef enum ADS1220_DATA_RATE { ADS1220_DR_LVL_0=0x00, ADS1220_DR_LVL_1=0x20, ADS1220_DR_LVL_2=0x40, ADS1220_DR_LVL_3=0x60, ADS1220_DR_LVL_4=0x80, ADS1220_DR_LVL_5=0xA0, ADS1220_DR_LVL_6=0xC0 } ads1220DataRate;
typedef enum ADS1220_OP_MODE { ADS1220_NORMAL_MODE=0x00, ADS1220_DUTY_CYCLE_MODE=0x08, ADS1220_TURBO_MODE=0x10 } ads1220OpMode;
typedef enum ADS1220_CONV_MODE { ADS1220_SINGLE_SHOT=0x00, ADS1220_CONTINUOUS=0x04 } ads1220ConvMode;
typedef enum ADS1220_VREF { ADS1220_VREF_INT=0x00, ADS1220_VREF_REFP0_REFN0=0x40, ADS1220_VREF_REFP1_REFN1=0x80, ADS1220_VREF_AVDD_AVSS=0xC0 } ads1220VRef;
typedef enum ADS1220_FIR { ADS1220_NONE=0x00, ADS1220_50HZ_60HZ=0x10, ADS1220_50HZ=0x20, ADS1220_60HZ=0x30 } ads1220FIR;
typedef enum ADS1220_PSW { ADS1220_ALWAYS_OPEN=0x00, ADS1220_SWITCH=0x08 } ads1220PSW;
typedef enum ADS1220_IDAC_CURRENT { ADS1220_IDAC_OFF=0x00, ADS1220_IDAC_10_MU_A=0x01, ADS1220_IDAC_50_MU_A=0x02, ADS1220_IDAC_100_MU_A=0x03, ADS1220_IDAC_250_MU_A=0x04, ADS1220_IDAC_500_MU_A=0x05, ADS1220_IDAC_1000_MU_A=0x06, ADS1220_IDAC_1500_MU_A=0x07 } ads1220IdacCurrent;
typedef enum ADS1220_IDAC_ROUTING { ADS1220_IDAC_NONE=0x00, ADS1220_IDAC_AIN0_REFP1=0x01, ADS1220_IDAC_AIN1=0x02, ADS1220_IDAC_AIN2=0x03, ADS1220_IDAC_AIN3_REFN1=0x04, ADS1220_IDAC_REFP0=0x05, ADS1220_IDAC_REFN0=0x06 } ads1220IdacRouting;
typedef enum ADS1220_DRDY_MODE { ADS1220_DRDY=0x00, ADS1220_DOUT_DRDY=0x02 } ads1220DrdyMode;

class ADS1220_WE_SoftSPI {
public:
  static constexpr float ADS1220_RANGE = 8388607.0f;
  ADS1220_WE_SoftSPI(int cs, int drdy, int mosi, int miso, int sclk);
  uint8_t init(); uint8_t getLastInitRegister() const; void start(); void reset(); void powerDown();
  void setCompareChannels(ads1220Mux); void setGain(ads1220Gain); uint8_t getGainFactor();
  void bypassPGA(bool); bool isPGABypassed();
  void setDataRate(ads1220DataRate); void setOperatingMode(ads1220OpMode); void setConversionMode(ads1220ConvMode);
  void enableTemperatureSensor(bool); void enableBurnOutCurrentSources(bool);
  void setVRefSource(ads1220VRef); void setFIRFilter(ads1220FIR); void setLowSidePowerSwitch(ads1220PSW); void setIdacCurrent(ads1220IdacCurrent);
  void setIdac1Routing(ads1220IdacRouting); void setIdac2Routing(ads1220IdacRouting); void setDrdyMode(ads1220DrdyMode);
  // Half of an SPI clock period. 1 us gives about 500 kHz; 0 is fastest but platform-dependent.
  void setSPIClockSpeed(unsigned long clock); void setSoftSPIHalfPeriod_us(unsigned int halfPeriod);
  void setVRefValue_V(float); float getVRef_V(); void setAvddAvssAsVrefAndCalibrate(); void setRefp0Refn0AsVrefAndCalibrate(); void setRefp1Refn1AsVrefAndCalibrate(); void setIntVRef();
  void setNonBlockingMode(bool); bool getNonBlockingMode();
  float getVoltage_mV(); float getVoltage_muV(); int32_t getRawData(); float getTemperature();
private:
  static constexpr uint8_t RESET=0x06, START=0x08, PWRDOWN=0x02, RREG=0x20, WREG=0x40;
  int csPin, drdyPin, mosiPin, misoPin, sclkPin; unsigned int halfPeriod_us;
  uint8_t regValue, gain, lastInitRegister; float vRef; bool refMeasurement, doNotBypassPgaIfPossible, nonBlockingMode; ads1220ConvMode convMode;
  void select(); void deselect(); uint8_t transfer(uint8_t); void command(uint8_t); uint8_t readRegister(uint8_t); void writeRegister(uint8_t,uint8_t); void forcedBypassPGA(); uint32_t readResult(); int32_t getData();
};

// Define this before including the header when this library replaces
// ADS1220_WE and source-level compatibility is required.
#ifdef ADS1220_WE_SOFTSPI_USE_ORIGINAL_CLASS_NAME
using ADS1220_WE = ADS1220_WE_SoftSPI;
#endif
