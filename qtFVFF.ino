#include "Wire.h"
#include "LiquidCrystal_I2C.h"
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

char data;
void setup() {
    // Réglage du port numérique associé à la LED : mode sortie = OUTPUT
Serial.begin(9600);
pinMode(2, OUTPUT); // LED VERTE
pinMode(4, OUTPUT); // LED ROUGE
lcd.init();                      // initialize the lcd 
  lcd.backlight();

}
void loop() { 
  //partie LED
  if(Serial.available()){
    data=Serial.read();
    if(data=='1'){
      digitalWrite(2, HIGH);
      delay(1000);
      digitalWrite(4,LOW);
      Serial.write('1');
    }
    else if (data=='0'){
      digitalWrite(2,LOW);
      delay(1000);
      digitalWrite(4,HIGH);
      Serial.write('0');
    }
  }
  //partie LCD
 if (Serial.available()) {
    delay(100);
    // clear the screen
    lcd.clear();
    while (Serial.available() > 0) {
      // display each character to the LCD
      lcd.write(Serial.read());
    }
  }
}
