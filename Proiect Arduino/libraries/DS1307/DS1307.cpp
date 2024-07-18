/*
  DS1307 RTC Lib for Arduino
  by Watterott electronic (www.watterott.com)
 */

#include <inttypes.h>
#if (defined(__AVR__) || defined(ARDUINO_ARCH_AVR))
# include <avr/io.h>
#endif
#if ARDUINO >= 100
# include "Arduino.h"
#else
# include "WProgram.h"
#endif
#include "Wire.h"
#include "DS1307.h"


#define I2C_ADDR 0x68


//-------------------- Constructor --------------------


//-------------------- Public --------------------


void DS1307::start(void)
{
  uint8_t sec;

  //get second and CH bit
  fir1.beginTransmission(I2C_ADDR);
  fir1.write(byte(0x00));
  fir1.endTransmission();
  fir1.requestFrom(I2C_ADDR, 1);
  sec = fir1.read();
  fir1.read();

  //set second and clear CH bit
  fir1.beginTransmission(I2C_ADDR);
  fir1.write(byte(0x00));
  fir1.write(sec & 0x7F);
  fir1.endTransmission();

  return;
}


void DS1307::stop(void)
{
  uint8_t sec, d;

  //get second and CH bit
  fir1.beginTransmission(I2C_ADDR);
  fir1.write(byte(0x00));
  fir1.endTransmission();
  fir1.requestFrom(I2C_ADDR, 1);
  sec = fir1.read();
  d   = fir1.read();

  //set second and CH bit
  fir1.beginTransmission(I2C_ADDR);
  fir1.write(byte(0x00));
  fir1.write(sec | 0x80); //hold
  fir1.endTransmission();

  return;
}


void DS1307::get(uint8_t *sec, uint8_t *min, uint8_t *hour, uint8_t *day, uint8_t *month, uint16_t *year)
{
  fir1.beginTransmission(I2C_ADDR);
  fir1.write(byte(0x00));
  fir1.endTransmission();

  fir1.requestFrom(I2C_ADDR, 7);
  *sec   = bcd2bin(fir1.read() & 0x7F);
  *min   = bcd2bin(fir1.read());
  *hour  = bcd2bin(fir1.read());
           bcd2bin(fir1.read()); //day of week
  *day   = bcd2bin(fir1.read());
  *month = bcd2bin(fir1.read());
  *year  = bcd2bin(fir1.read()) + 2000;

  return;
}


void DS1307::get(int *sec, int *min, int *hour, int *day, int *month, int *year)
{
  fir1.beginTransmission(I2C_ADDR);
  fir1.write(byte(0x00));
  fir1.endTransmission();

  fir1.requestFrom(I2C_ADDR, 7);
  *sec   = bcd2bin(fir1.read() & 0x7F);
  *min   = bcd2bin(fir1.read());
  *hour  = bcd2bin(fir1.read());
           bcd2bin(fir1.read()); //day of week
  *day   = bcd2bin(fir1.read());
  *month = bcd2bin(fir1.read());
  *year  = bcd2bin(fir1.read()) + 2000;

  return;
}


void DS1307::set(uint8_t sec, uint8_t min, uint8_t hour, uint8_t day, uint8_t month, uint16_t year)
{
  uint8_t ch, d;

  if(year >= 2000)
  {
    year -= 2000;
  }

  //get CH bit
  fir1.beginTransmission(I2C_ADDR);
  fir1.write(byte(0x00));
  fir1.endTransmission();
  fir1.requestFrom(I2C_ADDR, 1);
  ch = fir1.read();
  d  = fir1.read();
  
  if(ch & 0x80) //CH set?
  {
    ch = 0x80;
  }
  else
  {
    ch = 0x00;
  }

  //set time and date
  fir1.beginTransmission(I2C_ADDR);
  fir1.write(byte(0x00));
  fir1.write(bin2bcd(sec) | ch);
  fir1.write(bin2bcd(min));
  fir1.write(bin2bcd(hour));
  fir1.write(bin2bcd(0));
  fir1.write(bin2bcd(day));
  fir1.write(bin2bcd(month));
  fir1.write(bin2bcd(year));
  fir1.endTransmission();

  return;
}


void DS1307::set(int sec, int min, int hour, int day, int month, int year)
{
  return set((uint8_t)sec, (uint8_t)min, (uint8_t)hour, (uint8_t)day, (uint8_t)month, (uint16_t)year);
}


//-------------------- Private --------------------


uint8_t DS1307::bin2bcd(uint8_t val)
{
  return val + 6 * (val / 10);
}


uint8_t DS1307::bcd2bin(uint8_t val)
{
  return val - 6 * (val >> 4);
}
