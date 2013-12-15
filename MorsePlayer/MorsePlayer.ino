/*
 *  ARDUINO MORSE CODE PLAYER
 *  BY SAM 'Figglewatts' GIBSON
 *
 *  All these definitions below define the letters encoded as bytes.
 *  The first 5 bits represent the letter itself (a 0 is a dot and a 1 is a dash).
 *  For example, 00111 would be ..---, which if you cut out the trailing dots
 *  is a letter O.
 *  The final 3 bits represent the length of the letter. The value for this can
 *  be found by simply converting it to decimal, e.g. 011 would be a length of 3,
 *  100 would be 4 etc.
 *  So, the letter O would be 00111011, because it's 3 dots or dashes long.
 */

#define    letterA    B00001010
#define    letterB    B01000100
#define    letterC    B01010100
#define    letterD    B00100011
#define    letterE    B00000001
#define    letterF    B00010100
#define    letterG    B00110011
#define    letterH    B00000100
#define    letterI    B00000010
#define    letterJ    B00111100
#define    letterK    B00101011
#define    letterL    B00100100
#define    letterM    B00011010
#define    letterN    B00010010
#define    letterO    B00111011
#define    letterP    B00110100
#define    letterQ    B01101100
#define    letterR    B00010011
#define    letterS    B00000011
#define    letterT    B00001001
#define    letterU    B00001011
#define    letterV    B00001100
#define    letterW    B00011011
#define    letterX    B01001100
#define    letterY    B01011100
#define    letterZ    B01100100

// the following are a series of arrays of letters encoded as bytes
// these are what the system will actually decode and play
byte the[] = { letterT, letterH, letterE };
byte quick[] = { letterQ, letterU, letterI, letterC, letterK };
byte brown[] = { letterB, letterR, letterO, letterW, letterN };
byte fox[] = { letterF, letterO, letterX };
byte jumps[] = { letterJ, letterU, letterM, letterP, letterS };
byte over[] = { letterO, letterV, letterE, letterR };
byte lazy[] = { letterL, letterA, letterZ, letterY };
byte dog[] = { letterD, letterO, letterG };

byte bitMask = B00000001; // this is a bitmask used for reading the bit on the far right
byte sizeMask = B00000111; // this is a bitmask used for reading the 3 bits on the left, to determine the letter size

short timeUnit = 50; // the time unit (in milliseconds)

void setup() {
  pinMode(3, OUTPUT); // set pin 3 (the speaker/piezo) to OUTPUT
}

void loop() {
  playMorse(the, 3);
  playMorse(quick, 5);
  playMorse(brown, 5);
  playMorse(fox, 3);
  playMorse(jumps, 5);
  playMorse(over, 4);
  playMorse(the, 3);
  playMorse(lazy, 4);
  playMorse(dog, 3);
}

// the playMorse function does exactly that
// it plays the array of letters with length specified
void playMorse(byte message[], int length) {
  // for each letter (byte) in the array
  for (int iterator = 0; iterator < length; iterator++)
  {
    byte morseLetter = message[iterator]; // make a temporary copy
    
    int letterSize = morseLetter & sizeMask; // apply the size bitmask to determine the letter size
    morseLetter = morseLetter >> 3; // shift the byte 3 bits to the right since we don't need the rightmost 3 bits anymore
    
    boolean morseTones[letterSize]; // make an array of booleans to store what is a dot and what is a dash
    
    // for each dot or dash in the letter
    for (int iterator = 0; iterator < letterSize; iterator++)
    {
      morseTones[letterSize - iterator] = morseLetter & bitMask; // read the rightmost bit using the bitmask, and put it into the boolean array as a boolean
      morseLetter = morseLetter >> 1; // shift the bits right by one so we can read the next bit
    }
    
    // for each boolean in the boolean array
    for (int iterator = 1; iterator <= sizeof(morseTones); iterator++)
    {
      // if it was a 1 in the byte
      if (morseTones[iterator] == true) {
        tone(3, 900, timeUnit*3); // we have a dah (dash, or 1), so play it
      }
      else {
        // it was a 0 in the byte
        tone(3, 900, timeUnit); // we have a dit (dot, or 0), so play it
      }
      delay(timeUnit*7); // wait for space between letter (supposed to be equal to 3 time units, but changed for hearability)
    }
    delay(timeUnit*14); // wait for space between word (supposed to be equal to 7 time units, but changed for hearability)
  }
}
