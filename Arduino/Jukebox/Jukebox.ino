#include <LiquidCrystal.h>
#define NUM_KEYS 5

LiquidCrystal  lcd(8, 9, 4, 5, 6, 7);

const int speakerPin = 11;               //the pin that buzzer is connected to
const int analog_pin = A0;
const int adc_key_val[5] ={30, 150, 360, 535, 760 };
const int select_song_btn = 2;
const int play_btn = 1;
const int stop_btn = 3;

int adc_key_in;
int key=-1;
int oldkey=-1;

bool song_stop_flag = true;

typedef enum {
  SELECT_A_SONG_MESSAGE,
  SELECT_A_SONG,
  SONG_PLAY,
  SONG_STOP
} StateTypeDef;

typedef enum {
  NONE,
  SONG1,
  SONG2
} SelectedSongTypeDef;

StateTypeDef state = SELECT_A_SONG_MESSAGE;
SelectedSongTypeDef song = NONE;

unsigned long blinkTime = 0;
bool show = true;

void setup()
{
  // ADCSRA =  bit (ADIE) | bit (ADIF);
  pinMode(speakerPin, OUTPUT);    //set the output pin for the speaker
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("Happy Jukebox!");
  delay(2000);
}

void loop()
{
  adc_key_in = analogRead(analog_pin);
  key = get_key(adc_key_in);

  if (key != oldkey) {

    delay(50);
    adc_key_in = analogRead(analog_pin);
    key = get_key(adc_key_in);

    if (key != oldkey) {			

      oldkey = key;

      //DOWN
      if (key == play_btn) {
        state = SELECT_A_SONG;
        if (song == NONE) {
          song = SONG1;
        } else if (song == SONG1) {
          song = SONG2;
        } else {
          song = SONG1;
        }
      }

      //UP
      if (key == select_song_btn) {
        state = SONG_PLAY;
      }

      //LEFT
      if (key == stop_btn) {
        state = SONG_STOP;
      }
    }
  }

  switch(state) {
    case SONG_PLAY:
      song_stop_flag = false;

      if (song == SONG1) {
        playHappyBirthday();
      } else if (song == SONG2) {
        playTwinkleTwinkleLittleStar();
      }
      
      break;
    case SELECT_A_SONG_MESSAGE:
      lcd.setCursor(0, 1);

      if (millis() > blinkTime + 1000) {
        if (show == true) {
          lcd.print("Select a song UP");
          show = false;
        } else {
          lcd.print("                ");
          show = true;
        }
        blinkTime = millis();
      } 
      
      break;
    case SELECT_A_SONG:
      switch(song) {
        case SONG1:
          lcd.setCursor(0, 1);
          lcd.print("Happy Birthday  ");
          break;
        case SONG2:
          lcd.setCursor(0, 1);
          lcd.print("Little Star     ");
          break;
        case NONE:
          break;
      }
      break;
    case SONG_STOP:
      song_stop_flag = true;
      state = SELECT_A_SONG_MESSAGE;
      song = NONE;
      break;
  }
 
}

void playHappyBirthday(void)
{
  play('g', 2);       //ha
  play('g', 1);       //ppy
  play('a', 4);       //birth
  play('g', 4);       //day
  play('C', 4);       //to
  play('b', 4);       //you

  play(' ', 2);       //pause for 2 beats

  play('g', 2);       //ha
  play('g', 1);       //ppy
  play('a', 4);       //birth
  play('g', 4);       //day
  play('D', 4);       //to
  play('C', 4);       //you

  play(' ', 2);       //pause for 2 beats

  play('g', 2);       //ha
  play('g', 1);       //ppy
  play('G', 4);       //birth
  play('E', 4);       //day
  play('C', 4);       //dear
  play('b', 4);       //your
  play('a', 6);       //name

  play(' ', 2);       //pause for 2 beats

  play('F', 2);       //ha
  play('F', 1);       //ppy
  play('E', 4);       //birth
  play('C', 4);       //day
  play('D', 4);       //to
  play('C', 6);       //you
  play(' ', 3);
}

void playTwinkleTwinkleLittleStar()
{
  play('C', 1);   //262 1
  play(' ', 0.1); //0   0.1
  play('C', 1);   //262 1
  play(' ', 0.1); //0   0.1
  play('G', 1);   //392 1
  play(' ', 0.1); //0   0.1
  play('G', 1);   //392 1
  play(' ', 0.1); //0   0.1

  play('A', 1);   //440 1
  play(' ', 0.1); //0   0.1
  play('A', 1);   //440 1
  play(' ', 0.1); //0   0.1

  play('G', 3);   //392 2
  play(' ', 0.1); //0   0.1

  play('F', 1);   //349 1
  play(' ', 0.1); //0   0.1
  play('F', 1);   //349 1
  play(' ', 0.1); //0   0.1
  play('E', 1);   //329 1
  play(' ', 0.1); //0   0.1
  play('E', 1);   //329 1
  play(' ', 0.1); //0   0.1
  play('D', 1);   //294 1
  play(' ', 0.1); //0   0.1
  play('D', 1);   //294 1
  play(' ', 0.1); //0   0.1
  play('C', 2);   //262 2
  play(' ', 3);
}

void play( char note, float beats)
{
  adc_key_in = analogRead(analog_pin);
  key = get_key(adc_key_in);

  if (!song_stop_flag && key != stop_btn) {
    int numNotes = 14;  // number of notes in our note and frequency array (there are 15 values, but arrays start at 0)

    //Note: these notes are C major (there are no sharps or flats)

    //this array is used to look up the notes
    char notes[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C', 'D', 'E', 'F', 'G', 'A', 'B', ' '};
    //this array matches frequencies with each letter (e.g. the 4th note is 'f', the 4th frequency is 175)
    int frequencies[] = {131, 147, 165, 175, 196, 220, 247, 262, 294, 330, 349, 392, 440, 494, 0};

    int currentFrequency = 0;    //the frequency that we find when we look up a frequency in the arrays
    int beatLength = 180;   //the length of one beat (changing this will speed up or slow down the tempo of the song)

    //look up the frequency that corresponds to the note
    for (int i = 0; i < numNotes; i++)  // check each value in notes from 0 to 14
    {
      if (notes[i] == note)             // does the letter passed to the play function match the letter in the array?
      {
        currentFrequency = frequencies[i];   // Yes! Set the current frequency to match that note
      }
    }

    //play the frequency that matched our letter for the number of beats passed to the play function
    tone(speakerPin, currentFrequency, beats * beatLength);
    delay(beats * beatLength);  //wait for the length of the tone so that it has time to play
    delay(50);                  //a little delay between the notes makes the song sound more natural
  }
  

}

/* CHART OF FREQUENCIES FOR NOTES IN C MAJOR
  Note      Frequency (Hz)
  c        131
  d        147
  e        165
  f        175
  g        196
  a        220
  b        247
  C        262
  D        294
  E        330
  F        349
  G        392
  A        440
  B        494
*/

int get_key(unsigned int input){
  int k;
  for (k = 0; k < NUM_KEYS; k++){
    if (input < adc_key_val[k]){
      return k;
    }
  }
  if (k >= NUM_KEYS)
    k = -1;
  return k;
}
