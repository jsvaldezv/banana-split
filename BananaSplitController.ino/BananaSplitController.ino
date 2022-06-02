/*
  Made by Gustavo Silveira, 2019.
    http://www.musiconerd.com
    http://www.youtube.com/musiconerd
    http://facebook.com/musiconerdmusiconerd
    http://instagram.com/musiconerd/
    http://www.gustavosilveira.net
    gustavosilveira@musiconerd.com
    
  Modified by Flavio Everardo 2021.
    flavio.everardo@tec.mx
    
  - This Sketch reads the Arduino's digital and analog ports and send midi notes and midi control change
*/

/////////////////////////////////////////////
// "DEBUG" if you just want to debug the code in the serial monitor

#define PRODUCTIVE 1 //* put here the uC you are using, like in the lines above followed by "1", like "ATMEGA328 1", "DEBUG 1", etc.

/////////////////////////////////////////////
// LIBRARIES
// -- Defines the MIDI library -- //
#include <MIDI.h> // by Francois Best. Install this library first
MIDI_CREATE_DEFAULT_INSTANCE();

/////////////////////////////////////////////
// BUTTONS
const int N_BUTTONS = 12; //*  total numbers of buttons. 12 by default
const int BUTTON_ARDUINO_PIN[N_BUTTONS] = {2,3,4,5,6,7,8,9,10,11,12,13}; //* pins of each button connected straight to the Arduino

int buttonCState[N_BUTTONS] = {};        // stores the button current value
int buttonPState[N_BUTTONS] = {};        // stores the button previous value

#define pin13 1 //* uncomment if you are using pin 13 (pin with led), or comment the line if not using
byte pin13index = 0; //* put the index of the pin 13 of the buttonPin[] array if you are using, if not, comment

// debounce
unsigned long lastDebounceTime[N_BUTTONS] = {0};  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    //* the debounce time; increase if the output flickers

//OCTAVE UP AND DOWN
 
/////////////////////////////////////////////
// POTENTIOMETERS
const int N_POTS = 6; //* total numbers of pots (slide & rotary)
const int POT_ARDUINO_PIN[N_POTS] = {A0, A1, A2, A3, A4, A5}; //* pins of each pot connected straight to the Arduino

int potCState[N_POTS] = {0}; // Current state of the pot, modulation wheel
int potPState[N_POTS] = {0}; // Previous state of the pot
int potVar = 0; // Difference between the current and previous state of the pot

int midiCState[N_POTS] = {0}; // Current state of the midi value
int midiPState[N_POTS] = {0}; // Previous state of the midi value

const int TIMEOUT = 300; //* Amount of time the potentiometer will be read after it exceeds the varThreshold
const int varThreshold = 10; //* Threshold for the potentiometer signal variation
boolean potMoving = true; // If the potentiometer is moving
unsigned long PTime[N_POTS] = {0}; // Previously stored time
unsigned long timer[N_POTS] = {0}; // Stores the time that has elapsed since the timer was reset

///////////////////////////////////////////// Checar**
// MAKEY
const int N_PUSHES = 4; //*  total numbers of buttons. 12 by default
const int PUSH_MAKEY[N_PUSHES] = {16,17,18,19}; //* pins of each button connected straight to the Arduino

int makeyCState[N_PUSHES] = {};        // stores the button current value
int makeyPState[N_PUSHES] = {};        // stores the button previous value

/////////////////////////////////////////////
// MIDI
byte midiCh = 1; //* MIDI channel to be used
byte note = 36; //* Lowest note to be used
byte cc = 1; //* Lowest MIDI CC to be used

/////////////////////////////////////////////
// SETUP
void setup() 
{
  // Baud Rate
  // 31250 for MIDI class compliant | 115200 for Hairless MIDI
  Serial.begin(115200); //*

  #ifdef DEBUG
    Serial.println("Debug mode");
    Serial.println();
  #endif

  // Buttons
  // Initialize buttons with pull up resistors
  for (int i = 0; i < N_BUTTONS; i++) 
  {
    pinMode(BUTTON_ARDUINO_PIN[i], INPUT_PULLUP);
  }

  #ifdef pin13 // inicializa o pino 13 como uma entrada
    pinMode(BUTTON_ARDUINO_PIN[pin13index], INPUT);
  #endif

  for (int i = 0; i < N_PUSHES; i++)
  {
    pinMode(PUSH_MAKEY[i], INPUT);
  }
}

/////////////////////////////////////////////
// LOOP
void loop() 
{
  buttons();
  potentiometers();
  makey();
}

void makey()
{
  for (int i = 0; i < N_PUSHES; i++)
  {
    //Serial.println("Push " + String(PUSH_MAKEY[i]) + ":" + digitalRead(PUSH_MAKEY[i]));
    makeyCState[i] = digitalRead(PUSH_MAKEY[i]);

    if(makeyCState[i] != makeyPState[i])
    {
      //Serial.println("Push " + String(PUSH_MAKEY[i]) + ":" + digitalRead(PUSH_MAKEY[i]));
      
      if (makeyCState[i] == LOW)
        MIDI.sendControlChange(cc + i, 127, midiCh);
      else
        MIDI.sendControlChange(cc + i, 0, midiCh);
        
      makeyPState[i] = makeyCState[i];
    }
  }
}

/////////////////////////////////////////////
// BUTTONS
void buttons() 
{
  for (int i = 0; i < N_BUTTONS; i++) 
  { 
    buttonCState[i] = digitalRead(BUTTON_ARDUINO_PIN[i]);  // read pins from arduino
    
    #ifdef pin13
      if (i == pin13index) 
      {
        buttonCState[i] = !buttonCState[i]; // inverts the pin 13 because it has a pull down resistor instead of a pull up
      }
    #endif
    
    if ((millis() - lastDebounceTime[i]) > debounceDelay) 
    {
      if (buttonPState[i] != buttonCState[i]) 
      {
        lastDebounceTime[i] = millis();

        if (buttonCState[i] == LOW) // Sends the MIDI note ON
        {        
          #ifdef PRODUCTIVE //Productive Mode
            MIDI.sendNoteOn(note + i, random(100,127), midiCh); // note, random velocity, channel            
          #elif DEBUG
            Serial.print(i);
            Serial.println(": button on");
          #endif
        }
        else 
        {
          // Sends the MIDI note OFF accordingly to the chosen board
          #ifdef PRODUCTIVE //Productive Mode
            MIDI.sendNoteOn(note + i, 0, midiCh); // note, velocity, channel                    
          #elif DEBUG
            Serial.print(i);
            Serial.println(": button off");
          #endif
        }
        
        buttonPState[i] = buttonCState[i];
      }
    }
  }
}

/////////////////////////////////////////////
// POTENTIOMETERS
void potentiometers() 
{
  for (int i = 0; i < N_POTS; i++) // Loops through all the potentiometers
  { 
    potCState[i] = analogRead(POT_ARDUINO_PIN[i]); // reads the pins from arduino
    midiCState[i] = map(potCState[i], 0, 1023, 0, 127); // Maps the reading of the potCState to a value usable in midi
    potVar = abs(potCState[i] - potPState[i]); // Calculates the absolute value between the difference between the current and previous state of the pot

    if (potVar > varThreshold) // Opens the gate if the potentiometer variation is greater than the threshold
    { 
      PTime[i] = millis(); // Stores the previous time
    }

    timer[i] = millis() - PTime[i]; // Resets the timer 11000 - 11000 = 0ms

    if (timer[i] < TIMEOUT) // If the timer is less than the maximum allowed time it means that the potentiometer is still moving
    { 
      potMoving = true;
    }
    else 
    {
      potMoving = false;
    }

    if (potMoving == true) 
    { 
      // If the potentiometer is still moving, send the change control
      if (midiPState[i] != midiCState[i]) 
      {
        // Sends the MIDI CC accordingly to the chosen board
        #ifdef PRODUCTIVE //Productive Mode
          MIDI.sendControlChange(cc + i, midiCState[i], midiCh); // cc number, cc value, midi channel
        #elif DEBUG
          Serial.print("Pot: ");
          Serial.print(i);
          Serial.print(" ");
          Serial.println(midiCState[i]);
        #endif

        potPState[i] = potCState[i]; // Stores the current reading of the potentiometer to compare with the next
        midiPState[i] = midiCState[i];
      }
    }
  }
}
