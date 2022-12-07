const int buzzerPin = 12;
const int flamePin = 11;
int Flame = HIGH;
int redled = 5;
int greenled = 6;
#include <DHT.h>;
#define DHT11_PIN 2
#define DHTTYPE DHT11
DHT dht(DHT11_PIN, DHTTYPE);
int temp, hum;


void setup() 
{
  pinMode(buzzerPin, OUTPUT);
  pinMode(redled, OUTPUT);
  pinMode(greenled, OUTPUT);
  pinMode(flamePin, INPUT);
  Serial.begin(9600);
  dht.begin();
  
}

void loop() 
{
  temp = dht.readTemperature();
  hum = dht.readHumidity();
  Serial.println(temp);
  Serial.print("°F ");
  Serial.println(hum);
  Serial.print("% ");
  delay(1000);
  
       Flame = digitalRead(flamePin);
  if (Flame== LOW)
  {
    Serial.println("Fire detected");
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(redled, HIGH);
    digitalWrite(greenled, LOW);
    }
    else  {
      digitalWrite(buzzerPin, LOW);
    digitalWrite(greenled, HIGH);
    digitalWrite(redled, LOW);
    }
   }

  
  
  
