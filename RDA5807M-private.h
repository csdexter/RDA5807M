/* Arduino RDA5807M Library
 * See the README file for author and licensing information. In case it's
 * missing from your distribution, use the one here as the authoritative
 * version: https://github.com/csdexter/RDA5807M/blob/master/README
 *
 * This library is for interfacing with a RDA Microelectronics RDA5807M
 * single-chip FM broadcast radio receiver.
 * See the example sketches to learn how to use the library in your code.
 *
 * This file contains definitions that are only used by the RDA5807M class and
 * shouldn't be needed by most users.
 */

#ifndef _RDA5807M_PRIVATE_H_INCLUDED
#define _RDA5807M_PRIVATE_H_INCLUDED

//Define RDA5807M I2C Addresses
#define RDA5807M_I2C_ADDR_SEQRDA (0x20 >> 1)
#define RDA5807M_I2C_ADDR_RANDOM (0x22 >> 1)
#define RDA5807M_I2C_ADDR_SEQTEA (0xC0 >> 1)

#endif