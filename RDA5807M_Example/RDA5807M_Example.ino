/*
* RDA5807M Example Sketch
*
* This example sketch illustrates how to use some of the basic commands in the
* RDA5807M Library. The sketch will start the RDA5807M in West-FM mode
* (87-108MHz) and then wait for user commands via the serial port.
* More information on the RDA5807M chip can be found in the datasheet.
*
* HARDWARE SETUP:
* This sketch assumes you are using the RRD-102 (V2.0) breakout board.
*
* The board should be connected to a 3.3V Arduino's I2C interface.
* Alternatively, a 5V Arduino can be used if a proper I2C level translator is
* used (see the README for an example).
* You will need an audio amplifier as the RDA5807M is too weak to directly drive
* a pair of headphones. Immediate candidates would be a pair of active
* (multimedia) speakers that you're probably already using with your computer.
* You will also need a proper antenna connected to breakout board. Luckily
* for you, this is a very forgiving chip when it comes to "proper" antennas,
* so for FM only you will be able to get away with just a 2ft (60cm) length of
* wire connected to the FM antenna pad on the shield. Decent results can
* probably be obtained using a 6" breadboard jumper wire too.
*
* USING THE SKETCH:
* Once you've connected the RRD-102 to your Arduino board (and antenna(s), as
* appropriate), connect the Arduino to your computer, select the corresponding
* board and COM port from the Tools menu and upload the sketch. After the sketch
* has been updated, open the serial terminal using a 9600 baud speed. The sketch
* accepts single character commands (just enter the character and press 'send').
* Here is a list of the acceptable commands:
*   v/V     - decrease/increase the volume
*   s/S     - seek down/up with band wrap-around
*   m/M     - mute/unmute audio output
*   f       - display currently tuned frequency
*   q       - display RSSI for currently tuned station
*   t       - display decoded status register
*   ?       - display this list
*
*/

//Due to a bug in Arduino, this needs to be included here too/first
#include <Wire.h>

//Add the RDA5807M Library to the sketch.
#include <RDA5807M.h>

//Create an instance of the RDA5807M named radio
RDA5807M radio;
//Other variables we will use below
char command;
word status, frequency;

void setup()
{
  //Create a serial connection
  Serial.begin(9600);

  //Initialize the radio to the West-FM band. (see RDA5807M_BAND_* constants).
  //The mode will set the proper receiver bandwidth.
  radio.begin(RDA5807M_BAND_WEST);
}

void loop()
{
  //Wait until a character comes in on the Serial port.
  if(Serial.available()){
    //Decide what to do based on the character received.
    command = Serial.read();
    switch(command){
      case 'v':
        if(radio.volumeDown()) Serial.println(F("Volume decreased"));
        else Serial.println(F("ERROR: already at minimum volume"));
        Serial.flush();
        break;
      case 'V':
        if(radio.volumeUp()) Serial.println(F("Volume increased"));
        else Serial.println(F("ERROR: already at maximum volume"));
        Serial.flush();
        break;
      case 's':
        Serial.println(F("Seeking down with band wrap-around"));
        Serial.flush();
        radio.seekDown();
        break;
      case 'S':
        Serial.println(F("Seeking up with band wrap-around"));
        Serial.flush();
        radio.seekUp();
        break;
      case 'm':
        radio.mute();
        Serial.println(F("Audio muted"));
        Serial.flush();
        break;
      case 'M':
        radio.unMute();
        Serial.println(F("Audio unmuted"));
        Serial.flush();
        break;
      case 'f':
        frequency = radio.getFrequency();
        Serial.print(F("Currently tuned to "));
        Serial.print(frequency / 100);
        Serial.print(".");
        Serial.print(frequency % 100);
        Serial.println(F("MHz FM"));
        Serial.flush();
        break;
      case 'q': 
        Serial.print(F("RSSI = "));
        Serial.print(radio.getRSSI());
        Serial.println("dBuV");
        Serial.flush();
        break;
      case 't':
        status = radio.getRegister(RDA5807M_REG_STATUS);
        Serial.println(F("Status register {"));
        if(status & RDA5807M_STATUS_RDSR)
            Serial.println(F("* RDS Group Ready"));
        if(status & RDA5807M_STATUS_STC)
            Serial.println(F("* Seek/Tune Complete"));
        if(status & RDA5807M_STATUS_SF)
            Serial.println(F("* Seek Failed"));
        if(status & RDA5807M_STATUS_RDSS)
            Serial.println(F("* RDS Decoder Synchronized"));
        if(status & RDA5807M_STATUS_BLKE)
            Serial.println(F("* RDS Block E Found"));
        if(status & RDA5807M_STATUS_ST)
            Serial.println(F("* Stereo Reception"));
        Serial.println("}");
        Serial.flush();
        break;
      case '?':
        Serial.println(F("Available commands:"));
        Serial.println(F("* v/V     - decrease/increase the volume"));
        Serial.println(F("* s/S     - seek down/up with band wrap-around"));
        Serial.println(F("* m/M     - mute/unmute audio output"));
        Serial.println(F("* f       - display currently tuned frequency"));
        Serial.println(F("* q       - display RSSI for current station"));
        Serial.println(F("* t       - display decoded status register"));
        Serial.println(F("* ?       - display this list"));
        Serial.flush();
        break;
    }
  }
}
