#include <DHT.h>// include dht library
#include <DHT_U.h>// include dht driver
#include <LiquidCrystal.h>// include lcd library
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);// sets lcd pin outs to arduino outputs
#define DHTPIN A0     // DHT-11 Output Pin connection
#define DHTTYPE DHT11   // DHT Type is DHT 11
DHT dht(DHTPIN, DHTTYPE); // Initialize DHT sensor for normal 16mhz Arduino 


float hum;  //Stores humidity value
float temp; //Stores temperature value
void setup() //done once
{ 
 dht.begin(); // start dht sensor
 Serial.begin(9600); // initialize serial monitor
 lcd.begin(16,2); //initailize  lcd with 16 cols & 2 rows
}

void loop()//loops following
{
  analogWrite(6, 100); //send Vo of lcd connected to pin 6 100/225 bits of 5 volts (sets the brightness of lcd)
  delay(2000);  // Delay so sensor can stabalize
   
    hum = dht.readHumidity();  // Get Humidity value
    temp= dht.readTemperature();  // Get Temperature value
    
    // Print temperature and humidity values to serial monitor
    lcd.setCursor(0,0);//sets the position of the leading character of following lcd print
    lcd.print("Humidity: ");// prints to lcd
    lcd.print(hum);// prints to lcd the value of hum
    lcd.print("%"); // prints to lcd
    lcd.setCursor(0,1);//sets the position of the leading character of following lcd print
    lcd.print("Temp: ");// prints to lcd
    lcd.print(temp);// prints to lcd the value of temp
    lcd.print(" C"); // prints to lcd
}
