
//#include <Arduino.h>
#include <Wire.h>
#include "SSD1306Wire.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//#include "SSD1306Brzo.h"
//#include "SH1106Brzo.h"

#define OLED_RESET LED_BUILTIN
Adafruit_SSD1306 display(OLED_RESET);

int iLOG = 1;

//int pSDA = 0;
//int pSCL = 2;
int pCLK = 2; //4
int pSDATA = 0; //5

//SSD1306Wire  display(0x3c, 0, 2);

uint8_t pINTBUT1 = 14;
uint8_t pINTBUT2 = 12;
uint8_t pINTBUT3 = 13;
uint8_t pSUM = 15;

char* explain[] = {" Druecke den Button", " Druecke den Button", " Druecke den Button", "    wo Farbe und", " wo Position stimmt,", "  wo Farbe stimmt,", "  Position stimmt.", "  aber Farbe nicht.", " aber Position nicht"};


int IntButton = 0;
int WaitButton = 0;
int Level=0;
int Lives=5;
char* Modus[]= {"undefined", "Esy", "But", "Col"};
int intModus=0;
unsigned long last_interrupt_time = 0;


//Declarations

void serTOpar (int data) {
  //convert int into array
  int myByte[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  for (int i=0; i<9; i++) {
    if (data == i+1){
      myByte[i]=1;
    }
  }
  //reset array
  digitalWrite(pSDATA, LOW);
  digitalWrite(pCLK, LOW);
  for (int i=0; i<9; i++){
    digitalWrite(pCLK, HIGH);
    //delay(1);
    digitalWrite(pCLK, LOW);
    //delay(1);
  }
  //output values
  for (int i=7; i>=0; i--){
    digitalWrite(pSDATA, myByte[i]);
    //delay(1);
    digitalWrite(pCLK, HIGH);
    //delay(1);
    digitalWrite(pCLK, LOW);
    //delay(1);
  }
  digitalWrite(pSDATA, myByte[8]);
}
void testdrawline() {
  for (int16_t i=0; i<display.width(); i+=4) {
    display.drawLine(0, 0, i, display.height()-1, WHITE);
    display.display();
    delay(1);
  }
  for (int16_t i=0; i<display.height(); i+=4) {
    display.drawLine(0, 0, display.width()-1, i, WHITE);
    display.display();
    delay(1);
  }
  delay(250);

  display.clearDisplay();
  for (int16_t i=0; i<display.width(); i+=4) {
    display.drawLine(0, display.height()-1, i, 0, WHITE);
    display.display();
    delay(1);
  }
  for (int16_t i=display.height()-1; i>=0; i-=4) {
    display.drawLine(0, display.height()-1, display.width()-1, i, WHITE);
    display.display();
    delay(1);
  }
  delay(250);

  display.clearDisplay();
  for (int16_t i=display.width()-1; i>=0; i-=4) {
    display.drawLine(display.width()-1, display.height()-1, i, 0, WHITE);
    display.display();
    delay(1);
  }
  for (int16_t i=display.height()-1; i>=0; i-=4) {
    display.drawLine(display.width()-1, display.height()-1, 0, i, WHITE);
    display.display();
    delay(1);
  }
  delay(250);

  display.clearDisplay();
  for (int16_t i=0; i<display.height(); i+=4) {
    display.drawLine(display.width()-1, 0, 0, i, WHITE);
    display.display();
    delay(1);
  }
  for (int16_t i=0; i<display.width(); i+=4) {
    display.drawLine(display.width()-1, 0, i, display.height()-1, WHITE);
    display.display();
    delay(1);
  }
  delay(250);
}
void displayTest(){
  // draw many lines
  //testdrawline();
  display.setTextSize(1);
  display.setCursor(0,0);
  display.clearDisplay();
  display.setTextColor(BLACK, WHITE);
  display.println("123456789x123456789x123456789x123456789x");
  display.display();
  delay(5000);
  display.setTextSize(2);
  display.clearDisplay();
  display.println("123456789x123456789x123456789x123456789x");
  display.display();
  delay(5000);
  display.setTextSize(3);
  display.clearDisplay();
  display.println("12345");
  display.display();
  delay(5000);

}

void printStatus()
{
  Serial.print(millis());
  Serial.print("Level: ");
  Serial.print(Level);
  Serial.print(" Modus: ");
  Serial.print(Modus[intModus]);
  Serial.print(" Lives: ");
  Serial.println(Lives);
  display.setTextSize(2);
  display.setCursor(0,0);
  display.clearDisplay();
  display.setTextColor(BLACK, WHITE);
  display.print(" Lvl: ");
  display.setTextColor(WHITE);
  display.print(" ");
  display.println(Level);
  display.setTextColor(BLACK, WHITE);
  display.print(" Mode:");
  display.setTextColor(WHITE);
  display.print(" ");
  display.println(String(Modus[intModus]));
  display.setTextColor(BLACK, WHITE);
  display.print(" Live:");
  display.setTextColor(WHITE);
  display.print(" ");
  display.println(Lives);
  display.display();
}

void printExplain(int game)
{
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.clearDisplay();
  for (int i=0; i<3; i++)
  {
    display.println(explain[(i*3)+game-1]);
  }
  display.display();
  IntButton=0;
  while(IntButton==0)
  {
    delay(50);
  }
  IntButton=0;
}

void setSum(int dur)
{
  digitalWrite(pSUM,HIGH);
  delay(dur);
  digitalWrite(pSUM,LOW);
}

void IntCallback1()
{
  if (millis() - last_interrupt_time > 200)
 {
   IntButton = IntButton + 1;
   Serial.print(millis());
   Serial.println("Button 1 pressed");
   Serial.print(millis());
   Serial.print("IntButton value = ");
   Serial.println(IntButton);
 }
 last_interrupt_time = millis();
}

void IntCallback2()
{
  if (millis() - last_interrupt_time > 200)
 {
   IntButton = IntButton + 2;
   Serial.print(millis());
   Serial.println("Button 2 pressed");
   Serial.print(millis());
   Serial.print("IntButton value = ");
   Serial.println(IntButton);
 }
 last_interrupt_time = millis();
}

void IntCallback3()
{
  if (millis() - last_interrupt_time > 200)
 {
   IntButton = IntButton + 3;
   Serial.print(millis());
   Serial.println("Button 3 pressed");
   Serial.print(millis());
   Serial.print("IntButton value = ");
   Serial.println(IntButton);
 }
 last_interrupt_time = millis();
}

int getRandomNumber(int startNum, int endNum) {
  randomSeed(ESP.getCycleCount());
  return random(startNum, endNum+1);
}

void gameSimple(int idelay, int rounds, int decrease)
{
  printExplain(1);
  Serial.print(millis());
  Serial.println("Einfaches Spiel: Drueck den Knopf wo Position und Farbe stimmt!");
  for (int i=0; i<rounds; i++)
  {
    Level++;
    printStatus();
    int del = idelay - (i * decrease); //delay berechnen
    IntButton = 0;
    WaitButton = getRandomNumber(1, 3);
    Serial.print(millis());
    Serial.print("Waiting for: ");
    Serial.println(WaitButton);
    serTOpar(((WaitButton - 1)*3)+(WaitButton));
    //setColor(WaitButton);
    //setLED(WaitButton);
    delay(del);
    serTOpar(0);
    delay(500);
    if (IntButton != WaitButton)
    {
      Lives--;
      Serial.print(millis());
      Serial.print("Verbleibende Leben: ");
      Serial.println(Lives);
      Level--;
      setSum(1000); //Ton ausgeben
      if (Lives == 0)
      {
        break;
      }
    }
    else{
      Serial.print(millis());
      Serial.println("################### Round won ###################");
    }
  }
}

void gameButton(int idelay, int rounds, int decrease) //Correct Button but wrong color
{
  printExplain(2);
  Serial.println("Button Spiel: Drueck den Knopf wo die Position stimmt. Die Farbe kann falsch sein!");
  for (int i=0; i<rounds; i++)
  {
    Level++;
    printStatus();
    Serial.print("Current Level: "); //display Level
    Serial.println(Level);
    int del = idelay - (i * decrease); //delay berechnen
    IntButton = 0;
    WaitButton = getRandomNumber(1, 3);
    serTOpar(((WaitButton - 1)*3)+(getRandomNumber(1, 3)));
    //setColor(getRandomNumber(1, 3));
    //setLED(WaitButton);
    delay(del);
    serTOpar(0);
    delay(500);
    if (IntButton != WaitButton)
    {
      Lives--;
      Serial.print("Verbleibende Leben: ");
      Serial.println(Lives);
      Level--;
      setSum(1000); //Ton ausgeben
      if (Lives == 0)
      {
        break;
      }
    }
  }
}

void gameColor(int idelay, int rounds, int decrease) //correct color but wrong button
{
  printExplain(3);
  Serial.println("Button Spiel: Drueck den Knopf wo die Farbe stimmt. Die Position kann falsch sein!");
  for (int i=0; i<rounds; i++)
  {
    Level++;
    printStatus();
    Serial.print("Current Level: "); //display Level
    Serial.println(Level);
    int del = idelay - (i * decrease); //delay berechnen
    IntButton = 0;
    WaitButton = getRandomNumber(1, 3);
    serTOpar(((getRandomNumber(1, 3) - 1)*3)+(WaitButton));
    //setColor(WaitButton);
    //setLED(getRandomNumber(1, 3));
    delay(del);
    serTOpar(0);
    delay(500);
    if (IntButton != WaitButton)
    {
      Lives--;
      Serial.print("Verbleibende Leben: ");
      Serial.println(Lives);
      Level--;
      setSum(1000); //Ton ausgeben
      if (Lives == 0)
      {
        break;
      }
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(2000); //debug
  pinMode(pINTBUT1,INPUT);
  pinMode(pINTBUT2,INPUT);
  pinMode(pINTBUT3,INPUT);
  pinMode(pSUM,OUTPUT);
  pinMode(pCLK,OUTPUT);
  pinMode(pSDATA,OUTPUT);
  digitalWrite(pSUM,LOW);
  serTOpar(0);
  //setColor(0);
  //setLED(0);

  attachInterrupt(digitalPinToInterrupt(pINTBUT1), IntCallback1, FALLING);
  attachInterrupt(digitalPinToInterrupt(pINTBUT2), IntCallback2, FALLING);
  attachInterrupt(digitalPinToInterrupt(pINTBUT3), IntCallback3, FALLING);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  // init done

  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(2000);

  // Clear the buffer.
  display.clearDisplay();

}

void loop() {

  //displayTest();
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(0,0);
  display.clearDisplay();
  display.println("Willkommen");
  display.println(" zu einer");
  display.println(" Version");
  display.println("   von:");
  display.display();
  delay(3000);
  display.setCursor(0,0);
  display.clearDisplay();
  display.println("  Schlag");
  display.println("   den");
  display.println(" Maulwurf");
  display.display();
  delay(3000);
  display.setCursor(0,0);
  display.clearDisplay();
  display.println("  Bitte");
  display.println("  Knopf");
  display.println(" druecken");
  display.display();
  Serial.print(millis());
  Serial.println("Press any Button to start...");
  IntButton=0;
  while(IntButton == 0)
  {
    delay(50);
  }
  for (int i=0; i<3; i++) //Startsignal
  {
    delay(500);
    setSum(1000);
  }
  IntButton=0;

  for (int i=0; i<1000; i++)
  {
    switch (i%3)
    {
      case 0:
        intModus=1;
        gameSimple(2000-(i*100), 10, 100);
        break;
      case 1:
        intModus=2;
        gameButton(2000-(i*100), 10, 100);
        break;
      case 2:
        intModus=3;
        gameColor(2000-(i*100), 10, 100);
        break;
    }
    if (Lives == 0)
    {
      break;
    }
  }

  //Game over
  display.setTextSize(2);
  display.setCursor(0,0);
  display.clearDisplay();
  display.println("Game over!");
  display.println(" ");
  display.print("Level: ");
  display.println(Level-1);
  display.setTextSize(1);
  display.println("");
  display.println("Druecken fuer Start!");
  display.display();
  Serial.print(millis());
  Serial.println("Game Over!!!");
  for (int i=0; i<3; i++) //3 Töne ausgeben
  {
    delay(500);
    setSum(1000);
  }
  IntButton=0;
  while (IntButton==0)
  {
    delay(50);
  }
  serTOpar(0);
  //setColor(0);
  //setLED(0);
  Lives = 5;
  Level=0;
  IntButton = 0;
}
