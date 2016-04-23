/* Arduino RDA5807M Library
 * See the README file for author and licensing information. In case it's
 * missing from your distribution, use the one here as the authoritative
 * version: https://github.com/csdexter/RDA5807M/blob/master/README
 *
 * This library is for interfacing with a RDA Microelectronics RDA5807M
 * single-chip FM broadcast radio receiver.
 * See the example sketches to learn how to use the library in your code.
 *
 * This is the main include file for the library.
 */

#ifndef _RDA5807M_H_INCLUDED
#define _RDA5807M_H_INCLUDED

#if defined(ARDUINO) && ARDUINO >= 100
# include <Arduino.h>
#else
# include <WProgram.h>
#endif

//Register file origins for sequential mode
#define RDA5807M_FIRST_REGISTER_WRITE 0x02
#define RDA5807M_FIRST_REGISTER_READ 0x0A
#define RDA5807M_LAST_REGISTER 0x3A

//Register addresses
#define RDA5807M_REG_CHIPID 0x00
#define RDA5807M_REG_CONFIG 0x02
#define RDA5807M_REG_TUNING 0x03
#define RDA5807M_REG_GPIO 0x04
#define RDA5807M_REG_VOLUME 0x05
#define RDA5807M_REG_I2S 0x06
#define RDA5807M_REG_BLEND 0x07
#define RDA5807M_REG_FREQ 0x08
#define RDA5807M_REG_STATUS 0x0A
#define RDA5807M_REG_RSSI 0x0B
#define RDA5807M_REG_RDSA 0x0C
#define RDA5807M_REG_RDSB 0x0D
#define RDA5807M_REG_RDSC 0x0E
#define RDA5807M_REG_RDSD 0x0F
#define RDA5800_REG_LNA 0x10
#define RDA5807M_REG_SEEK 0x20

//Status bits (from the chip)
#define RDA5807M_STATUS_RDSR 0x8000
#define RDA5807M_STATUS_STC 0x4000
#define RDA5807M_STATUS_SF 0x2000
#define RDA5807M_STATUS_RDSS 0x1000
#define RDA5807M_STATUS_BLKE 0x0800
#define RDA5807M_STATUS_ST 0x0400
#define RDA5800_STATUS_ST 0x0100

//Flag bits (to the chip)
#define RDA5807M_FLG_DHIZ 0x8000
#define RDA5807M_FLG_DMUTE 0x4000
#define RDA5807M_FLG_MONO 0x2000
#define RDA5807M_FLG_BASS 0x1000
#define RDA5807M_FLG_RCLKNOCAL 0x0800
#define RDA5807M_FLG_RCLKDIRECT 0x0400
#define RDA5807M_FLG_SEEKUP 0x0200
#define RDA5807M_FLG_SEEK 0x0100
#define RDA5807M_FLG_SKMODE word(0x0080)
#define RDA5807M_FLG_RDS word(0x0008)
#define RDA5807M_FLG_NEW word(0x0004)
#define RDA5807M_FLG_RESET word(0x0002)
#define RDA5807M_FLG_ENABLE word(0x0001)
#define RDA5807M_FLG_DIRECT word(0x0020)
#define RDA5807M_FLG_TUNE word(0x0010)
#define RDA5807M_FLG_DE 0x0800
#define RDA5807M_FLG_SOFTMUTE 0x0200
#define RDA5807M_FLG_AFCD 0x0100
#define RDA5807P_FLG_INTMODE 0x8000
#define RDA5807M_FLG_EASTBAND65M 0x0200
#define RDA5807M_FLG_SOFTBLEND word(0x0002)
#define RDA5807M_FLG_FREQMODE word(0x0001)
#define RDA5807M_FLG_FMTRUE 0x0100
#define RDA5807M_FLG_FMREADY word(0x0080)
#define RDA5807M_FLG_BLOCKE word(0x0010)
#define RDA5807P_FLG_STCIEN 0x4000
#define RDA5807P_FLG_I2S word(0x0040)
#define RDA5807P_FLG_I2SSLAVE 0x1000
#define RDA5807P_FLG_SWLR 0x0800
#define RDA5807P_FLG_SCLKINVERT_I 0x0400
#define RDA5807P_FLG_SIGNED 0x0200
#define RDA5807P_FLG_WSINVERT_I 0x0100
#define RDA5807P_FLG_WSINVERT_O word(0x0008)
#define RDA5807P_FLG_SCLKINVERT_O word(0x0004)
#define RDA5807P_FLG_DELAY_L word(0x0002)
#define RDA5807P_FLG_DELAY_R word(0x0001)
#define RDA5800_FLG_SPACE_200K word(0x0001)
#define RDA5800_FLG_SPACE_50K word(0x0004)
#define RDA5800_FLG_BAND_JAPAN word(0x0002)

//Masks and constants for configuration parameters
//NOTE: the entire family, including the RDA5800, all report the same ChipID.
#define RDA5807M_CHIPID 0x58
#define RDA5807M_CLKMODE_MASK word(0x0070)
#define RDA5807M_CLKMODE_32K (0x0 << 4)
#define RDA5807M_CLKMODE_12M (0x1 << 4)
#define RDA5807M_CLKMODE_13M (0x2 << 4)
#define RDA5807M_CLKMODE_19M (0x3 << 4)
#define RDA5807M_CLKMODE_24M (0x5 << 4)
#define RDA5807M_CLKMODE_26M (0x6 << 4)
#define RDA5807M_CLKMODE_38M (0x7 << 4)
#define RDA5807M_CHAN_MASK 0xFFC0
#define RDA5807M_CHAN_SHIFT 6
#define RDA5807M_BAND_MASK word(0x000C)
#define RDA5807M_BAND_WEST (0x0 << 2)
#define RDA5807M_BAND_JAPAN (0x1 << 2)
#define RDA5807M_BAND_WORLD (0x2 << 2)
#define RDA5807M_BAND_EAST (0x3 << 2)
#define RDA5807M_SPACE_MASK word(0x0003)
#define RDA5807M_SPACE_100K 0x0
#define RDA5807M_SPACE_200K 0x1
#define RDA5807M_SPACE_50K 0x2
#define RDA5807M_SPACE_25K 0x3
#define RDA5807M_SEEKTH_MASK 0x7F00
#define RDA5807M_SEEKTH_SHIFT 8
#define RDA5807M_VOLUME_MASK word(0x000F)
#define RDA5807M_VOLUME_SHIFT 0
#define RDA5807M_OPENMODE_MASK word(0x6000)
#define RDA5807M_OPENMODE_WRITE (0x3 << 13)
#define RDA5807M_SOFTBLENDTH_MASK 0x7C00
#define RDA5807M_SOFTBLENDTH_SHIFT 10
#define RDA5807M_SEEKTHOLD_MASK word(0x00FC)
#define RDA5807M_SEEKTHOLD_SHIFT 2
#define RDA5807M_SEEKMODE_MASK 0x7000
#define RDA5807M_SEEKMODE_OLD (0x1 << 12)
#define RDA5807M_READCHAN_MASK 0x03FF
#define RDA5807M_READCHAN_SHIFT 0
#define RDA5807M_RSSI_MASK 0xFE00
#define RDA5807M_RSSI_SHIFT 9
#define RDA5807M_BLERA_MASK word(0x000C)
#define RDA5807M_BLERA_0 (0x0 << 2)
#define RDA5807M_BLERA_12 (0x1 << 2)
#define RDA5807M_BLERA_35 (0x2 << 2)
#define RDA5807M_BLERA_U (RDA5807M_BLERA_12 | RDA5807M_BLERA_35)
#define RDA5807M_BLERB_MASK word(0x0003)
#define RDA5807M_BLERB_0 0x0
#define RDA5807M_BLERB_12 0x1
#define RDA5807M_BLERB_35 0x2
#define RDA5807M_BLERB_U (RDA5807M_BLERB_12 | RDA5807M_BLERB_35)
#define RDA5807P_GPIO3_MASK word(0x0030)
#define RDA5807P_GPIO3_HIZ (0x0 << 4)
#define RDA5807P_GPIO3_ST (0x1 << 4)
#define RDA5807P_GPIO3_L (0x2 << 4)
#define RDA5807P_GPIO3_H (0x3 << 4)
#define RDA5807P_GPIO2_MASK word(0x000C)
#define RDA5807P_GPIO2_HIZ (0x0 << 2)
#define RDA5807P_GPIO2_INT (0x1 << 2)
#define RDA5807P_GPIO2_L (0x2 << 2)
#define RDA5807P_GPIO2_H (0x3 << 2)
#define RDA5807P_GPIO1_MASK word(0x0003)
#define RDA5807P_GPIO1_HIZ 0x0
#define RDA5807P_GPIO1_L 0x2
#define RDA5807P_GPIO1_H 0x3
#define RDA5807P_LNAP_MASK word(0x00C0)
#define RDA5807P_LNAP_NONE (0x0 << 6)
#define RDA5807P_LNAP_N (0x1 << 6)
#define RDA5807P_LNAP_P (0x2 << 6)
#define RDA5807P_LNAP_BOTH (0x3 << 6)
#define RDA5807P_LNAI_MASK word(0x0030)
#define RDA5807P_LNAI_1_8M (0x0 << 4)
#define RDA5807P_LNAI_2_1M (0x1 << 4)
#define RDA5807P_LNAI_2_5M (0x2 << 4)
#define RDA5807P_LNAI_3_0M (0x3 << 4)
#define RDA5807P_I2SRATE_MASK word(0x00F0)
#define RDA5807P_I2SRATE_8K (0x0 << 4)
#define RDA5807P_I2SRATE_11_025K (0x1 << 4)
#define RDA5807P_I2SRATE_12K (0x2 << 4)
#define RDA5807P_I2SRATE_16K (0x3 << 4)
#define RDA5807P_I2SRATE_22_05K (0x4 << 4)
#define RDA5807P_I2SRATE_24K (0x5 << 4)
#define RDA5807P_I2SRATE_32K (0x6 << 4)
#define RDA5807P_I2SRATE_44_1K (0x7 << 4)
#define RDA5807P_I2SRATE_48K (0x8 << 4)
#define RDA5800_VOLUMEDSP_MASK word(0x00F0)
#define RDA5800_VOLUMEDSP_SHIFT 4
#define RDA5800_LNAP_MASK 0x6000
#define RDA5800_LNAP_N (0x1 << 13)
#define RDA5800_LNAP_P (0x2 << 13)
#define RDA5800_LNAP_BOTH (0x3 << 13)

//DO NOT USE (begin) -----------------------------------------------------------
//
//One day, avr-gcc will take its role seriously and allow a way to enforce
//struct packing order, because it's a very common idiom in the embedded world
//and because the standard allows the implementation to define it.
//Until then, the beautiful structs below are nothing but an exercise in C
//calligraphy.
typedef struct __attribute__ ((__packed__)) {
    uint8_t disableHiZ:1;
    uint8_t disableMute:1;
    uint8_t mono:1;
    uint8_t bass:1;
    uint8_t rClkNotAlways:1;
    uint8_t rClkInput:1;
    uint8_t seekUp:1;
    uint8_t seek:1;
    uint8_t seekMode:1;
    uint8_t clkMode:3;
    uint8_t rds:1;
    uint8_t newDemodulation:1;
    uint8_t softReset:1;
    uint8_t enable:1;
    union {
        uint16_t channel:10;
        struct {
            uint8_t channel5800;
            uint8_t reserved5800_1:2;
        };
    };
    uint8_t direct:1;
    uint8_t tune:1;
    union {
        struct {
            uint8_t band:2;
            uint8_t space:2;
        };
        struct {
            uint8_t reserved5800_2:1;
            uint8_t space50kHz:1;
            uint8_t band5800:1;
            uint8_t space5800:1;
        };
    };
    uint8_t reserved1:1;
    uint8_t stcInterruptEnable:1;
    uint8_t reserved2:2;
    uint8_t deEmphasis:1;
    uint8_t reserved3:1;
    uint8_t softMute:1;
    uint8_t afcDisable:1;
    uint8_t reserved4:1;
    uint8_t i2s:1;
    uint8_t gpio3:2;
    uint8_t gpio2:2;
    uint8_t gpio1:2;
    uint8_t interruptMode:1;
    uint8_t seekThreshold:7;
    union {
      struct {
          uint8_t lnaPort:2;
          uint8_t lnaCurrent:2;
      };
      uint8_t volumeDSP:4;
    };
    uint8_t volume:4;
    uint8_t reserved5:1;
    uint8_t openMode:2;
    uint8_t i2sMode:1;
    uint8_t wsIsRight:1;
    uint8_t invertSclkInput:1;
    uint8_t signedData:1;
    uint8_t invertWsInput:1;
    uint8_t i2sSampleRate:4;
    uint8_t invertWsOutput:1;
    uint8_t invertSclkOutput:1;
    uint8_t delayLeft:1;
    uint8_t delayRight:1;
    uint8_t reserved6:1;
    uint8_t softBlendThreshold:5;
    uint8_t bandLimit65M:1;
    uint8_t reserved7:1;
    uint8_t seekThresholdOld:6;
    uint8_t softBlend:1;
    uint8_t frequencyMode:1;
    uint16_t frequencyDirect;
} TRDA5807MRegisterFileWrite;

typedef struct __attribute__ ((__packed__)) {
    uint8_t rdsReady:1;
    uint8_t seekTuneComplete:1;
    uint8_t seekFail:1;
    uint8_t rdsSynchronized:1;
    uint8_t blockEFound:1;
    uint8_t stereo:1;
    union {
        uint16_t readChannel:10;
        struct {
            uint8_t reserved5800_3:1;
            uint8_t stereo5800:1;
            uint8_t readChannel5800;
        };
    };
    uint8_t rssi:7;
    uint8_t isStation:1;
    uint8_t ready:1;
    uint8_t reserved:2;
    uint8_t blockE:1;
    uint8_t blerA:2;
    uint8_t blerB:2;
    uint16_t rdsA;
    uint16_t rdsB;
    uint16_t rdsC;
    uint16_t rdsD;
} TRDA5807MRegisterFileRead;
//DO NOT USE (end)--------------------------------------------------------------

extern const word RDA5807M_BandLowerLimits[];
extern const byte RDA5807M_ChannelSpacings[];

class RDA5807M
{
    public:
        /*
        * Description:
        *   This is the constructor, it initializes internal data structures.
        */
        RDA5807M(void) {};

        /*
        * Description:
        *   This is the destructor, it delegates to end().
        */
        ~RDA5807M() { end(); };

        /*
        * Description:
        *   Mutes and disables the chip.
        */
        void end(void);

        /*
        * Description:
        *   Initializes the RDA5807M, starts the radio and configures band
        *   limits.
        * Parameters:
        *   band - The desired band limits, one of the RDA5807M_BAND_* 
        *          constants.
        */
        void begin(byte band);

        /*
        * Description:
        *   Getter and setter for single random access to registers.
        * Parameters:
        *   reg   - register to get or set, one of the RDA5807M_REG_* constants.
        *   value - value to set the given register to.
        * Returns:
        *   current value of given register.
        */
        void setRegister(byte reg, word value);
        word getRegister(byte reg);

        /*
        * Description:
        *   Read-before-write setter for single random access to registers.
        * Parameters:
        *   reg   - register to update, one of the RDA5807M_REG_* constants.
        *   mask  - mask of the bits that are to be updated.
        *   value - value to set the given register and bits to.
        */
        void updateRegister(byte reg, word mask, word value) {
            setRegister(reg, getRegister(reg) & ~mask | value);
        };

        /*
        * Description:
        *   Getter and setter for bulk sequential access to registers. Gets
        *   always start at RDA5807M_FIRST_REGISTER_READ while sets always
        *   start at RDA5807M_FIRST_REGISTER_WRITE. The RDA5807M register file
        *   has exactly RDA5807M_LAST_REGISTER word-sized entries.
        * Parameters:
        *   count - how many sequential registers to get/set.
        *   regs  - will be filled with the values of the got registers or will
        *           be the source of the values for the set registers.
        */
        void setRegisterBulk(byte count, const word regs[]);
        void getRegisterBulk(byte count, word regs[]);

//DO NOT USE (begin) -----------------------------------------------------------
        /*
        * Description:
        *   Overloaded versions of the above, for use with the memory mapped
        *   register file structs. This is needed because Arduino and RDS5807M
        *   differ in endianness and so to maintain the correspondence between
        *   struct fields and the actual values transferred, you need to process
        *   the memory mapped struct byte-wise.
        */
        void setRegisterBulk(const TRDA5807MRegisterFileWrite *regs);
        void getRegisterBulk(TRDA5807MRegisterFileRead *regs);
//DO NOT USE (end) -------------------------------------------------------------

        /*
        * Description:
        *   Increase the volume by 1. If the maximum volume has been
        *   reached, no further increase will take place and returns false;
        *   otherwise true.
        */
        bool volumeUp(void);

        /*
        * Description:
        *   Decrease the volume by 1. If the minimum volume has been
        *   reached, no further decrease will take place and returns false;
        *   otherwise true.
        * Parameters:
        *   alsoMute - mute the output when reaching minimum volume, in
        *              addition to returning false
        */
        bool volumeDown(bool alsoMute = false);

        /*
        * Description:
        *   Commands the radio to seek up to the next valid channel.
        * Parameters:
        *   wrap - set to true to allow the seek to wrap around the current
        *          band.
        */
        void seekUp(bool wrap = true);

        /*
        * Description:
        *   Commands the radio to seek down to the next valid channel.
        * Parameters:
        *   wrap - set to true to allow the seek to wrap around the current
        *          band.
        */
        void seekDown(bool wrap = true);

        /*
        * Description:
        *   Mutes the audio output.
        */
        void mute(void);

        /*
        * Description:
        *   Unmutes the audio output.
        * Parameters:
        *   minVolume - set the volume to minimum value before unmuting if true,
        *               otherwise leave it untouched causing the chip to blast
        *               audio out at whatever the previous volume level was.
        */
        void unMute(bool minVolume = false);

        /*
        * Description:
        *   Gets the frequency the chip is currently tuned to.
        * Returns:
        *   frequency in 10kHz units.
        */
        word getFrequency(void);

        /*
        * Description:
        *   Retrieves the Received Signal Strength Indication measurement for
        *   the currently tuned station.
        */
        byte getRSSI(void);
};

#endif
