/*
 * ADS1220_WE_SoftSPI
 * Software-SPI adaptation of Wolfgang (Wolle) Ewald's ADS1220_WE library.
 * Original project: https://github.com/wollewald/ADS1220_WE
 * Original library copyright (c) 2022 Wolfgang (Wolle) Ewald.
 * Licensed under the MIT License; see ../LICENSE.
 * Modified to permit arbitrary GPIO assignment for SCLK, MOSI and MISO.
 */

#include "ADS1220_WE_SoftSPI.h"

ADS1220_WE_SoftSPI::ADS1220_WE_SoftSPI(int cs, int drdy, int mosi, int miso, int sclk)
  : csPin(cs), drdyPin(drdy), mosiPin(mosi), misoPin(miso), sclkPin(sclk), halfPeriod_us(5) {}

uint8_t ADS1220_WE_SoftSPI::init() {
  vRef=2.048f; gain=1; refMeasurement=false; convMode=ADS1220_SINGLE_SHOT; doNotBypassPgaIfPossible=false;
  pinMode(csPin, OUTPUT); digitalWrite(csPin, HIGH); pinMode(mosiPin, OUTPUT); pinMode(sclkPin, OUTPUT); digitalWrite(sclkPin, LOW); pinMode(misoPin, INPUT);
  if(drdyPin >= 0) pinMode(drdyPin, INPUT);
  reset(); start(); bypassPGA(true); uint8_t ctrl=readRegister(0); lastInitRegister=ctrl; bypassPGA(false); nonBlockingMode=false;
  return ctrl == 1;
}
uint8_t ADS1220_WE_SoftSPI::getLastInitRegister() const { return lastInitRegister; }
void ADS1220_WE_SoftSPI::select(){ digitalWrite(csPin, LOW); }
void ADS1220_WE_SoftSPI::deselect(){ digitalWrite(csPin, HIGH); }
uint8_t ADS1220_WE_SoftSPI::transfer(uint8_t out) {
  uint8_t in=0;
  for(int8_t bit=7; bit>=0; --bit) { // ADS1220 requires SPI mode 1: sample on falling edge.
    digitalWrite(mosiPin, (out >> bit) & 1); if(halfPeriod_us) delayMicroseconds(halfPeriod_us);
    digitalWrite(sclkPin, HIGH); if(halfPeriod_us) delayMicroseconds(halfPeriod_us);
    digitalWrite(sclkPin, LOW); in = (in << 1) | (digitalRead(misoPin) ? 1 : 0);
  }
  return in;
}
void ADS1220_WE_SoftSPI::command(uint8_t c){ select(); transfer(c); deselect(); }
void ADS1220_WE_SoftSPI::start(){ command(START); }
void ADS1220_WE_SoftSPI::reset(){ command(RESET); delay(1); }
void ADS1220_WE_SoftSPI::powerDown(){ command(PWRDOWN); }
uint8_t ADS1220_WE_SoftSPI::readRegister(uint8_t r){ select(); transfer(RREG | (r<<2)); regValue=transfer(0); deselect(); return regValue; }
void ADS1220_WE_SoftSPI::writeRegister(uint8_t r,uint8_t v){ select(); transfer(WREG | (r<<2)); transfer(v); deselect(); }
void ADS1220_WE_SoftSPI::setCompareChannels(ads1220Mux m){ if(m==ADS1220_MUX_REFPX_REFNX_4||m==ADS1220_MUX_AVDD_M_AVSS_4){gain=1;refMeasurement=true;}else{uint8_t x=readRegister(0);gain=1<<((x&0x0E)>>1);refMeasurement=false;} regValue=readRegister(0);regValue=(regValue&~0xF1)|m|(!doNotBypassPgaIfPossible&1);writeRegister(0,regValue);if(m>=0x80&&m<=0xD0){if(gain>4)gain=4;forcedBypassPGA();} }
void ADS1220_WE_SoftSPI::setGain(ads1220Gain g){ regValue=readRegister(0);ads1220Mux m=(ads1220Mux)(regValue&0xF0);writeRegister(0,(regValue&~0x0E)|g);gain=1<<(g>>1);if(m>=0x80&&m<=0xD0){if(gain>4)gain=4;forcedBypassPGA();} }
uint8_t ADS1220_WE_SoftSPI::getGainFactor(){return gain;}
void ADS1220_WE_SoftSPI::bypassPGA(bool b){regValue=readRegister(0);doNotBypassPgaIfPossible=!b;writeRegister(0,(regValue&~1)|b);}
bool ADS1220_WE_SoftSPI::isPGABypassed(){return readRegister(0)&1;}
void ADS1220_WE_SoftSPI::setDataRate(ads1220DataRate x){regValue=readRegister(1);writeRegister(1,(regValue&~0xE0)|x);}
void ADS1220_WE_SoftSPI::setOperatingMode(ads1220OpMode x){regValue=readRegister(1);writeRegister(1,(regValue&~0x18)|x);}
void ADS1220_WE_SoftSPI::setConversionMode(ads1220ConvMode x){convMode=x;regValue=readRegister(1);writeRegister(1,(regValue&~4)|x);}
void ADS1220_WE_SoftSPI::enableTemperatureSensor(bool x){regValue=readRegister(1);writeRegister(1,x?(regValue|2):(regValue&~2));}
void ADS1220_WE_SoftSPI::enableBurnOutCurrentSources(bool x){regValue=readRegister(1);writeRegister(1,x?(regValue|1):(regValue&~1));}
void ADS1220_WE_SoftSPI::setVRefSource(ads1220VRef x){regValue=readRegister(2);writeRegister(2,(regValue&~0xC0)|x);}
void ADS1220_WE_SoftSPI::setFIRFilter(ads1220FIR x){regValue=readRegister(2);writeRegister(2,(regValue&~0x30)|x);}
void ADS1220_WE_SoftSPI::setLowSidePowerSwitch(ads1220PSW x){regValue=readRegister(2);writeRegister(2,(regValue&~8)|x);}
void ADS1220_WE_SoftSPI::setIdacCurrent(ads1220IdacCurrent x){regValue=readRegister(2);writeRegister(2,(regValue&~7)|x);delayMicroseconds(200);}
void ADS1220_WE_SoftSPI::setIdac1Routing(ads1220IdacRouting x){regValue=readRegister(3);writeRegister(3,(regValue&~0xE0)|(x<<5));}
void ADS1220_WE_SoftSPI::setIdac2Routing(ads1220IdacRouting x){regValue=readRegister(3);writeRegister(3,(regValue&~0x1C)|(x<<2));}
void ADS1220_WE_SoftSPI::setDrdyMode(ads1220DrdyMode x){regValue=readRegister(3);writeRegister(3,(regValue&~2)|x);}
void ADS1220_WE_SoftSPI::setSPIClockSpeed(unsigned long c){halfPeriod_us=c?((500000UL+c-1)/c):0;}
void ADS1220_WE_SoftSPI::setSoftSPIHalfPeriod_us(unsigned int x){halfPeriod_us=x;}
void ADS1220_WE_SoftSPI::setVRefValue_V(float x){vRef=x;} float ADS1220_WE_SoftSPI::getVRef_V(){return vRef;} void ADS1220_WE_SoftSPI::setIntVRef(){setVRefSource(ADS1220_VREF_INT);vRef=2.048f;}
void ADS1220_WE_SoftSPI::setNonBlockingMode(bool x){nonBlockingMode=x;} bool ADS1220_WE_SoftSPI::getNonBlockingMode(){return nonBlockingMode;}
uint32_t ADS1220_WE_SoftSPI::readResult(){if(convMode==ADS1220_SINGLE_SHOT&&!nonBlockingMode)start();if(!nonBlockingMode&&drdyPin>=0)while(digitalRead(drdyPin)==HIGH){}select();uint32_t x=transfer(0);x=(x<<8)|transfer(0);x=(x<<8)|transfer(0);deselect();return x<<8;}
int32_t ADS1220_WE_SoftSPI::getData(){return (int32_t)readResult()>>8;}
float ADS1220_WE_SoftSPI::getVoltage_mV(){float r=getData();return r/ADS1220_RANGE*(refMeasurement?2.048f:vRef)*1000.0f/gain;} float ADS1220_WE_SoftSPI::getVoltage_muV(){return getVoltage_mV()*1000.0f;} int32_t ADS1220_WE_SoftSPI::getRawData(){return getData();}
float ADS1220_WE_SoftSPI::getTemperature(){enableTemperatureSensor(true);uint16_t r=readResult()>>18;enableTemperatureSensor(false);if(r>>13){r=~(r-1)&0x3777;return r*-0.03125f;}return r*0.03125f;}
void ADS1220_WE_SoftSPI::forcedBypassPGA(){regValue=readRegister(0);writeRegister(0,regValue|1);}
void ADS1220_WE_SoftSPI::setAvddAvssAsVrefAndCalibrate(){bool b=nonBlockingMode;nonBlockingMode=false;setVRefSource(ADS1220_VREF_AVDD_AVSS);setCompareChannels(ADS1220_MUX_AVDD_M_AVSS_4);float x=0;for(uint8_t i=0;i<10;i++)x+=getVoltage_mV();vRef=x*4/10000.0f;nonBlockingMode=b;}
void ADS1220_WE_SoftSPI::setRefp0Refn0AsVrefAndCalibrate(){bool b=nonBlockingMode;nonBlockingMode=false;setVRefSource(ADS1220_VREF_REFP0_REFN0);setCompareChannels(ADS1220_MUX_REFPX_REFNX_4);float x=0;for(uint8_t i=0;i<10;i++)x+=getVoltage_mV();vRef=x*4/10000.0f;nonBlockingMode=b;}
void ADS1220_WE_SoftSPI::setRefp1Refn1AsVrefAndCalibrate(){bool b=nonBlockingMode;nonBlockingMode=false;setVRefSource(ADS1220_VREF_REFP1_REFN1);setCompareChannels(ADS1220_MUX_REFPX_REFNX_4);float x=0;for(uint8_t i=0;i<10;i++)x+=getVoltage_mV();vRef=x*4/10000.0f;nonBlockingMode=b;}
