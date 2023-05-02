
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <BlynkSimpleEsp32.h>
#include "Adafruit_HTU21DF.h"

#define BLYNK_TEMPLATE_ID "TMPL6JvKokjjm"
#define BLYNK_TEMPLATE_NAME "MINI WEATHER STATION"
#define BLYNK_AUTH_TOKEN "iLkh0wUUdjs4Z4Hd0Q8avTICnW6YLA9s"

#define BLYNK_PRINT Serial

#define SEALEVELPRESSURE_HPA (1013.25)
#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels
#define OLED_RESET    -1  // Reset pin # (or -1 if sharing reset pin)
#define LIGHT_SENSOR_PIN 15 //LDR sensor pin
#define BUZZER 18
#define LED_WIFI 34
#define BUTTON 14

bool break_happened = false;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_BMP280 bmp;
Adafruit_HTU21DF htu = Adafruit_HTU21DF();

double calcLightIntensity(int AnVal, int Resistor){
  double Vout= AnVal*0.0048828125;
  int lux=((2500/Vout-500)/Resistor);
  return lux;
}

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "AndroidAP8156";  // type your wifi name
char pass[] = "87654321";  // type your wifi password
BlynkTimer timer;


void sendSensor()
{
    digitalWrite(LED_WIFI,HIGH);
    float temp = bmp.readTemperature();
    float pressure = bmp.readPressure()/100;
    float alt = bmp.readAltitude(1013.25);
    int analogVal = analogRead(LIGHT_SENSOR_PIN); //read values from D15
    int Resistance= 10; //I am using a 1k ohms resistor
    int luxval=calcLightIntensity(analogVal, Resistance );

  // You can send any value at any time.
  // Please don't send more that 10 values per second.
    if (Blynk.connected()){
      Blynk.virtualWrite(V0, temp);
      Blynk.virtualWrite(V1, pressure);
      Blynk.virtualWrite(V2, alt);
      Blynk.virtualWrite(V3, luxval);
      Serial.print("Temperature : ");
      Serial.print(temp);
      Serial.print("    Pressure : ");
      Serial.print(pressure);
      Serial.print("    Altitude : ");
      Serial.println(alt);
    }
    
    
}

void ring_buzzer(){

  bool button_pressed=digitalRead(BUTTON);
  //Serial.println(digitalRead(BUTTON),break_happened);
  //Ring the buzzer
  while (break_happened == false && button_pressed == HIGH) {
    bool button_pressed=digitalRead(BUTTON);
    if (button_pressed == LOW) {
      //Serial.println(digitalRead(BUTTON));
      delay(200);
      break_happened = true;
      digitalWrite(BUZZER,LOW);
      break;
    }
    digitalWrite(BUZZER,HIGH);
    delay(500);
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(BUZZER, OUTPUT);
  pinMode(LIGHT_SENSOR_PIN, INPUT);
  pinMode(LED_WIFI,OUTPUT);
  pinMode(BUTTON,INPUT);

  Blynk.begin(auth, ssid, pass);
  while (Blynk.connect() == false) {
    if(((millis()/1000) - timeout) > 10){   // issue msg if not connected to Blynk in more than 10 seconds
      break; 
    }
  }
  
  //dht.begin();
  Serial.println(F("BMP280 test"));

  Wire.begin();
 // initialize the SSD1306 OLED display with I2C address = 0x3D
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
 // clear the display buffer.
  display.clearDisplay();
  display.setTextSize(1);   // text size = 1
  display.setTextColor(WHITE, BLACK);  // set text color to white and black background
  display.setTextWrap(false);           // disable text wrap
  display.setCursor(5, 0);              // move cursor to position (0, 4) pixel
  display.print("Mini Weather Station");
  /***
  display.setCursor(123, 4);            // move cursor to position (123, 4) pixel
  display.println("S");  display.setCursor(123, display.getCursorY());
  display.println("T");  display.setCursor(123, display.getCursorY());
  display.println("A");  display.setCursor(123, display.getCursorY());
  display.println("T");  display.setCursor(123, display.getCursorY());
  display.println("I");  display.setCursor(123, display.getCursorY());
  display.println("O");  display.setCursor(123, display.getCursorY());
  display.println("N");
  display.display();        // update the display
  ***/

  unsigned status;
  status = bmp.begin(0x76);
  if (!status) {
     // connection error or device address wrong!
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    display.setCursor(34, 23);
    display.print("Connection");
    display.setCursor(49, 33);
    display.print("Error");
    display.display();        // update the display
    while (1) // stay here
      delay(1000);
  }
  if (!htu.begin()) {
    Serial.println("Couldn't find sensor!");
    while (1);
  }
  
  display.display(); 
  // update the display

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

  timer.setInterval(100L, sendSensor);

}

void loop() {
  timer.setInterval(100L, sendSensor);
  float temp_bmp280 = bmp.readTemperature();    // get temperature in degree Celsius
  float pres = bmp.readPressure()/100;       // get pressure in Pa
  float alti = bmp.readAltitude(SEALEVELPRESSURE_HPA);       // get altitude in meter
  int analogVal = analogRead(LIGHT_SENSOR_PIN); //read values from D15
  int Resistance= 1; //I am using a 1k ohms resistor
  int luxval=calcLightIntensity(analogVal, Resistance );
  float temp_htu21d = htu.readTemperature();
  float rel_hum = htu.readHumidity();
  
  delay(1000);  // wait a second
 // print data on the LCD
   // print temperature
  //display.clearDisplay();
  Serial.print("Temperature1 = ");
  Serial.print(temp_bmp280);
  Serial.println("*C");
  Serial.print("Temperature2 = ");
  Serial.print(temp_htu21d);
  Serial.println("*C");
  
  display.setCursor(0, 16);
  display.print("Temperature:");
  display.setCursor(75, 16);
  if (temp_bmp280 < 0)
    display.printf("-%02u.%02u C", (int)abs(temp_bmp280) % 100, (int)(abs(temp_bmp280) * 100) % 100 );
  else
    display.printf(" %02u.%02u C", (int)temp_bmp280 % 100, (int)(temp_bmp280 * 100) % 100 );
 // print degree symbols ( ° )
  display.drawRect(111, 16, 3, 3, WHITE);
  //delay(2000);
  if (temp_bmp280>27.15 || temp_bmp280<27){
    Serial.println(digitalRead(BUTTON));
    ring_buzzer();
  }
  else{
    bool break_happened = false;
  }

 //print pressure
  //display.clearDisplay();
  Serial.print("Pressure = ");
  Serial.print(pres);
  Serial.println("hPa");
  display.setCursor(0, 28);
  display.print("Pressure:");
  display.setCursor(60, 28);
  display.printf("%02u hPa", (int)(pres));
  //delay(2000);

  
  //print humidity
  //display.clearDisplay();
  Serial.print("Humidity = ");
  Serial.print(rel_hum);
  Serial.println("%");
  display.setCursor(0, 40);
  display.print("Humidity:");
  display.setCursor(60, 40);
  display.printf("%02u %s", (int)(rel_hum), "%");
  //delay(2000);

   //print Altitude
  //Serial.print("Approx. Altitude = ");
  //Serial.print(alti);
  //Serial.println("m");
  //display.setCursor(38, 56);
  //display.printf("%02u m", (int)(alti));
  
  //print lux
  //display.clearDisplay();
  Serial.print("Light Intensity:");
  Serial.print(luxval);
  Serial.println(" lux");
  display.setCursor(0, 52);
  display.print("Light Intensity:");
  display.setCursor(80, 52);
  display.printf("%02u lux", (int)(luxval));
  //delay(2000);

 // update the display
  display.display();
  delay(1000);  // wait a second
  Serial.println();

  Blynk.run();
  timer.run();
}
