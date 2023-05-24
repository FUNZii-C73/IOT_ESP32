#define RAIN_PIN 5 //  rain sensor

#define D5 21 //  D5 pin as 21 SDA
#define D6 22 //  D6 pin as 22 SCL

#define DHT_PIN 4 //  DHT sensor
#define DHT_TYPE DHT11 

#include <RTClib.h>

#include <DHT.h> 
#include <Wire.h>
  

DHT dht(DHT_PIN, DHT_TYPE); 
RTC_DS1307 rtc;

void setup() {
  Serial.begin(9600);
  pinMode(forward,OUTPUT);
  pinMode(reverse,OUTPUT);
  pinMode(MOTOR,OUTPUT);
  pinMode(RAIN_PIN, INPUT_PULLUP);  
  
  if (! rtc.begin()) { 
    Serial.println("Couldn't find RTC");
    while (1);
  }

  DateTime now = rtc.now(); // get the current date and time from the RTC module
  if (now.year() <= 2000) { // check if the RTC module has lost power
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // set the RTC to the date and time when the sketch was compiled
    Serial.println("RTC lost power, setting to compiled time");
  }
}


void rainsensor()
{
 int rainState = digitalRead(RAIN_PIN);

  if (rainState == LOW) {
    Serial.println("Rain detected!");
  } else {
    Serial.println("No rain detected.");
  }
  
  delay(1000);
}

void rtcClock()
{
   DateTime now = rtc.now(); // get the current date and time
  Serial.print(now.year(), DEC); // print year
  Serial.print('/');
  printDigits(now.month()); // print month
  Serial.print('/');
  printDigits(now.day()); // print day
  Serial.print(' ');
  printDigits(now.hour()); // print hour
  Serial.print(':');
  printDigits(now.minute()); // print minute
  Serial.print(':');
  printDigits(now.second()); // print second
  Serial.println(); // print newline
  delay(1000); // wait for 1 second
}

void printDigits(int digits) {
  if (digits < 10) {
    Serial.print('0'); // add a leading zero if necessary
  }
  Serial.print(digits);
}

void tempsensor()
{
   float temperature = dht.readTemperature(); // read temperature from DHT sensor
  float humidity = dht.readHumidity(); // read humidity from DHT sensor
  
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
  
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
  
  delay(2000); 
}




void loop() {

 rainsensor();
 rtcClock();
 tempsensor();
 RoofMotor();
}
