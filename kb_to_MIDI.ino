#include <Keypad.h>

const int channel = 1; // MIDI channel
const byte ROWS = 10;
const byte COLS = 9;

// 10x9 matrix keyboard
char keys[ROWS][COLS] = {
  {0,1,2,3,4,5,6,7,8},
  {9,10,11,12,13,14,15,16,17},
  {18,19,20,21,22,23,24,25,26},
  {27,28,39,30,31,32,33,34,35},
  {36,37,38,39,40,41,42,43,44},
  {45,46,47,48,49,50,51,52,53},
  {54,55,56,57,58,59,60,61,62},
  {63,64,65,66,67,68,69,70,71},
  {72,73,74,75,76,77,78,79,80},
  {81,82,83,84,85,86,87,88,89}
};

// Pin #'s used on Teensy++ 2.0 using Arduino pin numbering
byte rowPins[ROWS] = {0,1,2,3,4,5,7,8,9,10};
byte colPins[COLS] = {26,25,24,23,22,21,20,19,18};

// init keypad
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
  kpd.setDebounceTime(5); // in milliseconds
}

unsigned long loopCount = 0;
unsigned long startTime = millis();

void loop() {

  loopCount++;
  if ( (millis()-startTime)>1000 ) {
    startTime = millis();
    loopCount = 0;
  }

  if ( kpd.getKeys() ) {
    for(int i=0; i<LIST_MAX; i++) {
      if (kpd.key[i].stateChanged) {
        uint8_t keytmp = kpd.key[i].kchar;
        switch (kpd.key[i].kstate) {
          case PRESSED:
            // note sent = keytmp value (0-89) & 99 = max velocity)
            usbMIDI.sendNoteOn(keytmp, 99, channel);
            break;
          case HOLD:
            break;
          case RELEASED:
            usbMIDI.sendNoteOff(keytmp, 0, channel);
            break;
          case IDLE:
            break;
        }
      }
    }
  }
} // end: loop()
