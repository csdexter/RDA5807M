/* Arduino RDA5807M Library
 * See the README file for author and licensing information. In case it's
 * missing from your distribution, use the one here as the authoritative
 * version: https://github.com/csdexter/RDA5807M/blob/master/README
 *
 * This library is for interfacing with a RDA Microelectronics RDA5807M
 * single-chip FM broadcast radio receiver.
 * See the example sketches to learn how to use the library in your code.
 *
 * This is the main code file for the library.
 * See the header file for better function documentation.
 */

#include "RDA5807M.h"
#include "RDA5807M-private.h"

#include <Wire.h>

void RDA5807M::begin(byte band) {
    Wire.begin();
    setRegister(RDA5807M_REG_CONFIG, RDA5807M_FLG_DHIZ | RDA5807M_FLG_DMUTE | 
                RDA5807M_FLG_BASS | RDA5807M_FLG_SEEKUP | RDA5807M_FLG_RDS | 
                RDA5807M_FLG_NEW | RDA5807M_FLG_ENABLE);
    updateRegister(RDA5807M_REG_TUNING, RDA5807M_BAND_MASK, band);
};

void RDA5807M::end(void) {
    setRegister(RDA5807M_REG_CONFIG, 0x00);
};

void RDA5807M::setRegister(byte reg, const word value) {
    Wire.beginTransmission(RDA5807M_I2C_ADDR_RANDOM);
    Wire.write(reg);
    Wire.write(highByte(value));
    Wire.write(lowByte(value));
    Wire.endTransmission(true);
};

word RDA5807M::getRegister(byte reg) {
    word result;

    Wire.beginTransmission(RDA5807M_I2C_ADDR_RANDOM);
    Wire.write(reg);
    Wire.endTransmission(false);
    Wire.requestFrom(RDA5807M_I2C_ADDR_RANDOM, 2, true);
    result = Wire.read() << 8;
    result |= Wire.read();
    Wire.endTransmission(true);

    return result;
};

void RDA5807M::setRegisterBulk(byte count, const word regs[]) {
    Wire.beginTransmission(RDA5807M_I2C_ADDR_SEQRDA);

    for(byte i=0; i < count; i++) {
        Wire.write(highByte(regs[i]));
        Wire.write(lowByte(regs[i]));
    };

    Wire.endTransmission(true);
};

void getRegisterBulk(byte count, word regs[]) {
    Wire.requestFrom(RDA5807M_I2C_ADDR_SEQRDA, count * 2, true);

    for(byte i=0; i < count; i++) {
        regs[count] = Wire.read() << 8;
        regs[count] |= Wire.read();
    };

    Wire.endTransmission(true);
};

bool RDA5807M::volumeUp(void) {
    byte volume = getRegister(RDA5807M_REG_VOLUME) & RDA5807M_VOLUME_MASK;

    if (volume == RDA5807M_VOLUME_MASK)
        return false;
    else {
        updateRegister(RDA5807M_REG_VOLUME, RDA5807M_VOLUME_MASK, volume + 1);
        return true;
    };
};

bool RDA5807M::volumeDown(bool alsoMute) {
    byte volume = getRegister(RDA5807M_REG_VOLUME) & RDA5807M_VOLUME_MASK;

    if (volume) {
        updateRegister(RDA5807M_REG_VOLUME, RDA5807M_VOLUME_MASK, volume - 1);
        return true;
    } else {
        if (alsoMute)
            //If we are to trust the datasheet, this is superfluous as a volume
            //of zero triggers mute & HiZ on its own.
            mute();
        return false;
    };
};

void RDA5807M::seekUp(bool wrap) {
    updateRegister(RDA5807M_REG_CONFIG,
                   (RDA5807M_FLG_SEEKUP | RDA5807M_FLG_SEEK |
                    RDA5807M_FLG_SKMODE), 
                   (RDA5807M_FLG_SEEKUP | RDA5807M_FLG_SEEK |
                    (wrap ? 0x00 : RDA5807M_FLG_SKMODE)));
};

void RDA5807M::seekDown(bool wrap) {
    updateRegister(RDA5807M_REG_CONFIG,
                   (RDA5807M_FLG_SEEKUP | RDA5807M_FLG_SEEK |
                    RDA5807M_FLG_SKMODE), 
                   (0x00 | RDA5807M_FLG_SEEK |
                    (wrap ? 0x00 : RDA5807M_FLG_SKMODE)));
};

void RDA5807M::mute(void) {
    updateRegister(RDA5807M_REG_CONFIG, RDA5807M_FLG_DMUTE, 0x00);
};

void RDA5807M::unMute(bool minVolume) {
    if (minVolume)
        updateRegister(RDA5807M_REG_VOLUME, RDA5807M_VOLUME_MASK, 0x1);
    updateRegister(RDA5807M_REG_CONFIG, RDA5807M_FLG_DMUTE, RDA5807M_FLG_DMUTE);
};

const byte RDA5807M_BandLimits[4][2] PROGMEM = {
    {87, 108},
    {76, 91},
    {76, 108},
    {65, 76}
};

const byte RDA5807M_ChannelSpacings[4] PROGMEM = { 100, 200, 50, 25 };

word RDA5807M::getFrequency(void) {
    word frequency = getRegister(RDA5807M_REG_STATUS) & RDA5807M_READCHAN_MASK;
    byte bandConfig = getRegister(RDA5807M_REG_TUNING) & (RDA5807M_BAND_MASK |
                                                          RDA5807M_SPACE_MASK);

    return (word)pgm_read_byte(&RDA5807M_BandLimits[
            (bandConfig & RDA5807M_BAND_MASK) >> 2][0]) * 100 + frequency * 
        (word)pgm_read_byte(&RDA5807M_ChannelSpacings[
            bandConfig & RDA5807M_SPACE_MASK]) / 10;
};

byte RDA5807M::getRSSI(void) {
    return (getRegister(RDA5807M_REG_RSSI) & RDA5807M_RSSI_MASK) >> RDA5807M_RSSI_SHIFT;
};
