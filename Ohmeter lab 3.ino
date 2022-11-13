#include <LiquidCrystal.h>//includes lcd library
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // sets lcd pin outs to arduino outputs
const int pbPin = 7;// declares the value of 7 to be used for the pushbutton pin
const float Max_Ohms = 10000.00; // declares the value of 10000 to be used for cacluating ohms, stores max resistance value of potentiometer
const int readerpin = A0;//declares value A0 to be used for the potentiometer
const float Mult = (5.00/1023.00);//declares the float variable used to convert bits to volts 
const float Ohms_Mult = (10000.00/1023.00);//declares the float variable used to convert bits to ohms
bool pbValue; //declares the t/f variable used to save the value of the pushbutton
bool Stopper =0;//declares the t/f variable used to set if the button was pressed
int Ohms_Volts_Bits= 0;//declares the integer variable used to count how many times the button was pressed
float Volts ;//declares the float variable used to save the value of volts
int Bits ;//declares the integer variable used to save the value of bits
float Ohms ;//declares the float variable used to save the value of ohms


byte Ohm[] = {//an array of bytes, called Ohm
  B00000,
  B01110,
  B10001,
  B10001,
  B10001,
  B01010,
  B11011,
  B00000
};




void setup()//happens once
{ 
 Serial.begin(9600);//initializes serial moniter
 lcd.begin(16,2);//initializes serial lcd with 16 cols & 2 rows
 pinMode(pbPin, INPUT_PULLUP);// initializes button pin as an input connected to a pull up resistor
 lcd.createChar(0, Ohm);//turn the array of bytfes into a character that can be displayed on the lcd, assigned to 0.
}

void loop()//loops following
{
  analogWrite(6, 100);//send Vo of lcd connected to pin 6 100/225 bits of 5 volts (sets the brightness of lcd)
  Bits = analogRead(readerpin);//saves value of A0 to bits
  pbValue = digitalRead(pbPin);// saves value of button to pb value
   Volts = Mult * Bits;
  Ohms = (5000/(5-Volts))-1000;
    if(pbValue==0 && Stopper == 0){// if button is pressed and stopper value is 0, is activated once when the button is pressed(aka not continuously)
    lcd.clear();   //clears lcd screen
    Stopper = 1;//sets stopper true
    Ohms_Volts_Bits = ++Ohms_Volts_Bits;// adds 1 to Ohms_Volts_Bits
    }
    if(pbValue==1) { //if button is not pressed (activated continuously)
      Stopper = 0; // sets stoper false
    }

     if(Ohms_Volts_Bits == 0) //if Ohms_Volts_Bits value is 0 then (button pressed 0 times)
    {
      lcd.setCursor(0,0); //sets the position of the leading character of following lcd print
    lcd.print("Bits = ");// prints to lcd
    lcd.print(Bits);  // prints to lcd the value of Bits
    }

    if (Ohms_Volts_Bits == 1)//if Ohms_Volts_Bits value is 1 then (button pressed once)
    {
    lcd.setCursor(0,0);//sets the position of the leading character of following lcd print
    lcd.print("Voltage =");// prints to lcd
    lcd.print(Volts); // prints to lcd the value of Volts
    }

     if (Ohms_Volts_Bits == 2)//if Ohms_Volts_Bits value is 1 then (button pressed twice)
    {
    lcd.setCursor(0,0);//sets the position of the leading character of following lcd print
    lcd.print("Ohms =");// prints to lcd
    lcd.print(Ohms); // prints to lcd the value of Ohms
    lcd.write(byte(0));//prints ohm charaacter to lcd
    }

  if(Ohms_Volts_Bits == 3){//if Ohms_Volts_Bits value is 1 then (button pressed thrice)
    Ohms_Volts_Bits = 0; // reset buttoncounter to 0
  }
}
