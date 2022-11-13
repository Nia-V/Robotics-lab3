#include <LiquidCrystal.h>// include lcd library
#include <DHT.h>// include dht library
#include <DHT_U.h>// include dht driver
#include "NewPing.h"// Include NewPing Library
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);// sets lcd pin outs to arduino outputs
#define DHTPIN A0     // DHT-11 Output Pin connection
#define DHTTYPE DHT11   // DHT Type is DHT 11
#define TRIGGER_PIN  10 //trigger is connected to pin 10
#define ECHO_PIN     9//echo is connected to pin 13
#define MAX_DISTANCE 400// max range of sensor
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); //initailizing newping sensor named sonar
DHT dht(DHTPIN, DHTTYPE); // Initialize DHT sensor for normal 16mhz Arduino
float hum;  //Stores humidity value
float temp; //Stores temperature value
float duration; // Stores HC-SR04 pulse duration value
float distance; // Stores calculated distance in cm
float soundsp;  // Stores calculated speed of sound in M/S
float soundcm;  // Stores calculated speed of sound in cm/ms
int iterations = 5;//
int left = 7; //saves left pb pin
int right = 8;//saves rigth pb pin
bool leftval;//saves left pb value
bool rightval;//saves right pb value
bool stopper = 0; //declares the t/f variable used to set if the button was pressed
int counter = 2; //declares the int variable used to save how many times a button was pressed
void setup() {//happens once
Serial.begin(9600);
  lcd.begin(16, 2);//initializes serial lcd with 16 cols & 2 rows
pinMode(left, INPUT_PULLUP);// initializes button pin as an input connected to a pull up resistor
pinMode(right, INPUT_PULLUP);// initializes button pin as an input connected to a pull up resistor
}

void loop() {//loops following
analogWrite(6, 100);//send Vo of lcd connected to pin 6 100/225 bits of 5 volts (sets the brightness of lcd)
 leftval = digitalRead(left);// saves input of left button to left val
rightval = digitalRead(right);// saves input of right button to right val
            //DHT11
hum = dht.readHumidity();  // Get Humidity value
temp= dht.readTemperature();  // Get Temperature value

            //ULTRASONIC
soundsp = 331.4 + (0.606 * temp) + (0.0124 * hum); // Calculate the Speed of Sound in M/S
soundcm = soundsp / 10000;// Convert to cm/ms
duration = sonar.ping_median(iterations);
distance = (duration / 2) * soundcm;// Calculate the distance


lcd.setCursor(0,0);//sets the position of the leading character of following lcd print
if (leftval == 0) {//if left button is pressed 
  stopper= 0;// stopper is = 0
  lcd.clear();// clear lcd
}
if (rightval == 0) {//right buttom is pressed
  stopper= 1;// stopper is 1
  lcd.clear();// clear lcd
}
if (stopper== 0){//if stopper is equal to 0 then...
      
        lcd.print("Hum:");// prints to lcd
        lcd.print(hum); // prints to lcd the value of hum
        lcd.print("%"); // prints to lcd
        lcd.setCursor(0,1);//sets the position of the leading character of following lcd print
        lcd.print("Temp: ");// prints to lcd
        lcd.print(temp);// prints to lcd the value of temp
        lcd.print(" C"); // prints to lcd
    }


else if (stopper == 1){//if stopper value is one
      if (distance < 400 || distance > 2) {//and if distance is less than 400 or greater than 2 then..,
       lcd.print(distance);// prints to lcd the value of distance
       lcd.print(" cm");// prints to lcd
       }
        
         else if (distance >= 400 || distance <= 2) {//or and if distance is greater than 400 or less than or eaqual to 2 then
           lcd.print("Out of range");// prints to lcd
        }
}

}