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

byte the[] = { letterT, letterH, letterE };
byte quick[] = { letterQ, letterU, letterI, letterC, letterK };
byte brown[] = { letterB, letterR, letterO, letterW, letterN };
byte fox[] = { letterF, letterO, letterX };
byte jumps[] = { letterJ, letterU, letterM, letterP, letterS };
byte over[] = { letterO, letterV, letterE, letterR };
byte lazy[] = { letterL, letterA, letterZ, letterY };
byte dog[] = { letterD, letterO, letterG };

byte bitMask = B00000001;
byte sizeMask = B00000111;

short timeUnit = 50; // the time unit (in milliseconds)

void setup() {
  // put your setup code here, to run once:
  pinMode(3, OUTPUT);
  
  Serial.begin(9600);
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
  Serial.println("END END END");
  Serial.println("END END END");
  Serial.println("END END END");
  Serial.println("END END END");
  Serial.println("END END END");
}

void playMorse(byte message[], int length) {
  for (int iterator = 0; iterator < length; iterator++)
  {
    byte morseLetter = message[iterator];
    
    int letterSize = morseLetter & sizeMask;
    morseLetter = morseLetter >> 3;
    
    boolean morseTones[letterSize];
    
    for (int iterator = 0; iterator < letterSize; iterator++)
    {
      morseTones[letterSize - iterator] = morseLetter & bitMask;
      morseLetter = morseLetter >> 1;
      //Serial.print(morseTones[letterSize - i]);
    }
    
    for (int iterator = 1; iterator <= sizeof(morseTones); iterator++)
    {
      if (morseTones[iterator] == true) {
        tone(3, 900, timeUnit*3); // dah
        Serial.print("-");
      }
      else {
        tone(3, 900, timeUnit); // dit
        Serial.print(".");
      }
      delay(timeUnit*7); // space between letter
    }
    delay(timeUnit*14); // space between word
    Serial.println();
  }
}
