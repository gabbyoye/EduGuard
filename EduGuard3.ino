/*
 * 
* Reset      9              
* SPI SS     10               
* SPI MOSI   11              
* SPI MISO   12               
* SPI SCK    13              
*
 */
#include <Adafruit_NeoPixel.h>
#include <SPI.h>
#include <MFRC522.h>

#define PIN            6
#define NUMPIXELS      16
#define LOCK           7
#define SS_PIN 10
#define RST_PIN 9

long stRFID = 0;
long stSerial = 0;
boolean flagRFID = false;
boolean flagSerial = false;
boolean buzzerTime = false;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  pixels.begin(); // This initializes the NeoPixel library.
  pinMode(LOCK,OUTPUT);
  digitalWrite(LOCK, HIGH);
  for (int i = NUMPIXELS; i >= 0; i--) {
       pixels.setPixelColor(i, pixels.Color(0 , 0, 10)); // Moderately bright green color.
        // This sends the updated pixel color to the hardware.
  }
      pixels.show();
}

void loop(){
  long curTime = millis();
  //serial section
  if(Serial.available() > 0){
    int ascii = Serial.read();
    if(ascii == 32){
      for (int i = NUMPIXELS; i >= 0; i--) {
        pixels.setPixelColor(i, pixels.Color(10 , 0, 0)); // Moderately bright green color.
        // This sends the updated pixel color to the hardware.
      }
      pixels.show();
      stSerial = curTime+30000;
      flagSerial = true;
    }
  }
  //rfid section
  if (mfrc522.PICC_IsNewCardPresent()&& mfrc522.PICC_ReadCardSerial()){
    Serial.print("UID tag :");
    String content= "";
    byte letter;
    for (byte i = 0; i < mfrc522.uid.size; i++){
      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(mfrc522.uid.uidByte[i], HEX);
      content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
      content.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    Serial.println();
    content.toUpperCase();
    if(content.substring(1) == "84 3C 71 8B"){
      for (int i = NUMPIXELS; i >= /*NUMPIXELS/2*/0; i--) {
        pixels.setPixelColor(i, pixels.Color(0 , 75, 0)); // Moderately bright green color.
        pixels.show(); // This sends the updated pixel color to the hardware. 
      }
      /*for(int i = (NUMPIXELS/2)-1; i >=0; i--){
        pixels.setPixelColor(i, pixels.Color(100 , 0, 0)); // Moderately bright green color.
        pixels.show();
      }*/
      
      digitalWrite(LOCK, LOW);
      stRFID = curTime + 2000;
      flagRFID = true;
    }
  }
  //Time check section
  if(flagRFID && curTime > stRFID){
    digitalWrite(LOCK, HIGH);
    Serial.println("Meh");
    flagRFID = false;
    for (int i = NUMPIXELS; i >= 0; i--) {
      int r = 0;
      int b = 10;
      if(flagSerial){
        r =10;
        b=0;
      }
      pixels.setPixelColor(i, pixels.Color(r , 0, b)); // Moderately bright green color.
         // This sends the updated pixel color to the hardware.
    }
    pixels.show();
  }
  if(flagSerial && curTime > stSerial){
    for (int i = NUMPIXELS; i >= 0; i--) {
      pixels.setPixelColor(i, pixels.Color(0 , 0, 10)); // Moderately bright green color.
         // This sends the updated pixel color to the hardware.
    }
    pixels.show();
    Serial.println("UGH");
    flagSerial = false;
  }
  int spassed = (curTime - stSerial)/1000;
  if (flagSerial) {
    if (spassed % 3 == 0 && !buzzerTime){
      tone(5,440);
      buzzerTime = true;
    }else if(spassed % 3 != 0 && buzzerTime) {
      noTone(5);
      buzzerTime = false;
    }
  } else {
    noTone(5);
  }
  /*if(flagSerial && curTime > stRFID){
    for (int i = NUMPIXELS; i >= 0; i--) {
      pixels.setPixelColor(i, pixels.Color(100 , 0, 0)); // Moderately bright green color.
         // This sends the updated pixel color to the hardware.
    }
    pixels.show();
  }
  */
}

