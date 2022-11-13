#include <LiquidCrystal.h>//includes lcd library
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);// sets lcd pin outs to arduino outputs
const int pbPin = 7;;// declares the value of 7 to be used for the pushbutton pin
int potsPin = A0;//declares value A0 to be used for the potentiometer
bool pbValue; //declares the t/f variable used to save the value of the pushbutton
bool Stopper = 0;//declares the t/f variable used to set if the button was pressed
int Volts_Bits= 0;//declares the integer variable used to count how many times the button was pressed
const float Mult = (5.00/1023.00);//declares the float variable used to convert bits to volts 
float Volts ;//declares the float variable used to save the value of volts
int Bits ;//declares the integer variable used to save the value of bits
void setup()//happens once
{ 
Serial.begin(9600);//initializes serial moniter
lcd.begin(16,2);//initializes serial lcd with 16 cols & 2 rows
pinMode(pbPin, INPUT_PULLUP);// initializes button pin as an input connected to a pull up resistor

}

void loop(){//loops following

  analogWrite(6, 100);//send Vo of lcd connected to pin 6 100/225 bits of 5 volts (sets the brightness of lcd)
  Bits = analogRead(potsPin);//saves bits* 5/1023 to volts
  Volts = Mult * Bits;//saves bits* 5/1023 to volts
  pbValue = digitalRead(pbPin);// saves value of button to pb value

    if(pbValue==0 && Stopper == 0){// if button is pressed and stopper value is 0, is activated once when the button is pressed(aka not continuously)
    
    lcd.clear();    //clears lcd screen
    Stopper = 1;//sets stopper true
    Volts_Bits = ++Volts_Bits;// adds 1 to Ohms_Volts_Bits
    }
    if(pbValue==1) { //if button is not pressed (activated continuously)
      Stopper = 0;// sets stoper false
    }

    
    if(Volts_Bits == 0)//if Ohms_Volts_Bits value is 0 then (button pressed 0 times)
    {
      lcd.setCursor(0,0);//sets the position of the leading character of following lcd print
    lcd.print("Bits = ");// prints to lcd
    lcd.print(Bits);  // prints to lcd the value of Bits
    }

    if (Volts_Bits == 1)//if Ohms_Volts_Bits value is 1 then (button pressed once)
    {
    lcd.setCursor(0,0);//sets the position of the leading character of following lcd print
    lcd.print("Voltage =");// prints to lcd
    lcd.print(Volts);  // prints to lcd the value of Ohms
    }

    if(Volts_Bits == 2){//if Ohms_Volts_Bits value is 1 then (button pressed twice)
      Volts_Bits = 0;// reset buttoncounter to 0
    }
}
