



#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7, 8);

const int POTPIN = 1;
const int MAXPOT = 800; 

const int SPEAKERPIN = 9; // buzzer

const int RANDSEEDPIN = 0; 

const int MAXSTEPDURATION = 300; 
const int MINSTEPDURATION = 150; 

byte desene[6][8] = {
  // 1: masina sus
  { B00000,
    B01110,
    B11111,
    B01010,
    B00000,
    B00000,
    B00000,
    B00000}
  // 2: masina jos
  ,{B00000,
    B00000,
    B00000,
    B00000,
    B01110,
    B11111,
    B01010,
    B00000}
  // 3: obstacol sus 
  ,{B00000,
    B11110,
    B11111,
    B01010,
    B00000,
    B00000,
    B00000,
    B00000}
  // 4: obstacol jos
  ,{B00000,
    B00000,
    B00000,
    B00000,
    B11110,
    B11111,
    B01010,
    B00000}
  // 5: accident sus
  ,{B10101,
    B01110,
    B01110,
    B10101,
    B00000,
    B00000,
    B00000,
    B00000}
  // 6: accident jos
  ,{B00000,
    B00000,
    B00000,
    B10101,
    B01110,
    B01110,
    B10101,
    B00000}
};

const int NCARPOSITIONS = 4;

const char BLANK=32;
char car2glyphs[NCARPOSITIONS][2] = {
  {1,BLANK},{2,BLANK},{BLANK,1},{BLANK,2}
};
char truck2glyphs[NCARPOSITIONS][2] = {
  {3,BLANK},{4,BLANK},{BLANK,3},{BLANK,4}
};
char crash2glyphs[NCARPOSITIONS][2] = {
  {5,BLANK},{6,BLANK},{BLANK,5},{BLANK,6}
};

const int ROADLEN = 15; // latimea LCD fara masina (16 - 1)
int road[ROADLEN]; // pozitia celorlalte masini
char road_buff[2+ROADLEN];
int road_index;
int car_pos;

const int MAXROADPOS = 3*NCARPOSITIONS;
int step_duration;

int crash; 
unsigned int crashtime; 
const int CRASHSOUNDDURATION = 250;

const char *INTRO1="Trafic intens";
const char *INTRO2="Condu prudent!";
const int INTRODELAY = 2000;

void setup()
{
  crash = crashtime = road_index = 0;
  step_duration = MAXSTEPDURATION;
  road_buff[1+ROADLEN] = '\0'; 
  randomSeed(analogRead(RANDSEEDPIN));
  for (int i=0; i<6; i++) {
    lcd.createChar(i+1,desene[i]);
  }
  for (int i=0; i<ROADLEN; i++) {
    road[i]=-1;
  }
  pinMode(SPEAKERPIN,OUTPUT);
  analogWrite(SPEAKERPIN,0); 
  lcd.begin(16,2);
  getSteeringWheel();
  drawRoad();
  lcd.setCursor(1,0);
  lcd.print(INTRO1);
  lcd.setCursor(1,1);
  lcd.print(INTRO2);
  delay(INTRODELAY);
}

void loop() {
  unsigned long now = millis()-INTRODELAY;
  if (!crash) {
    getSteeringWheel();
    crash = (car_pos==road[road_index]);
  }
  if (crash) {
    if (!crashtime) {
      crashtime=now;
      drawRoad();
      lcd.setCursor(2,0);
      lcd.print("Ati condus");
      lcd.setCursor(2,1);
      lcd.print(now/1000);
      lcd.print(" secunde.");
    }
    if ((now-crashtime)<CRASHSOUNDDURATION) {
      analogWrite(SPEAKERPIN,random(255)); 
    } 
    else {
      analogWrite(SPEAKERPIN,0);  
    }
    delay(10);
  } 
  else {

    int prev_pos = road[(road_index-1)%ROADLEN];
    int this_pos = random(MAXROADPOS);
    while (abs(this_pos-prev_pos)<2) { 
      this_pos = random(MAXROADPOS);
    }
    road[road_index] = this_pos;
    road_index = (road_index+1)%ROADLEN;
    drawRoad();
    delay(step_duration);
    if (step_duration>MINSTEPDURATION) {
      step_duration--; // marim viteza daca jocul continua
    }
  }
}
void getSteeringWheel() {
  car_pos = map(analogRead(POTPIN),0,1024,0,NCARPOSITIONS);
}

void drawRoad() {
  for (int i=0; i<2; i++) {
    if (crash) {
      road_buff[0]=crash2glyphs[car_pos][i];
    } 
    else {
      road_buff[0]=car2glyphs[car_pos][i];
    }
    for (int j=0; j<ROADLEN; j++) {
      int pos = road[(j+road_index)%ROADLEN];
      road_buff[j+1] = pos>=0 && pos<NCARPOSITIONS ? truck2glyphs[pos][i] : BLANK;
    }
    lcd.setCursor(0,i);
    lcd.print(road_buff);
  }
}
