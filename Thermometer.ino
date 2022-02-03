/* THERMOMETER */
#include <LiquidCrystal.h>
int tempPin = 0;
int dataPin = 4;       // DS [S1] on 74HC595
int latchPin = 5;      // ST_CP [RCK] on 74HC595
int clockPin = 6;      // SH_CP [SCK] on 74HC595
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

/* LEDS */
byte leds = 0;
int tDelay = 100;

void setup() {
  lcd.begin(16, 2);
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
}

void loop() {
  /* THERMOMETER */
  int tempReading = analogRead(tempPin);

  double tempK = log(10000.0 * ((1024.0 / tempReading - 1)));
  tempK = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * tempK * tempK )) * tempK );
  float tempC = tempK - 273.15;            // Convert Kelvin to Celcius
  float tempF = (tempC * 9.0)/ 5.0 + 32.0; // Convert Celcius to Fahrenheit
  
  // Display Temperature in C.
  lcd.setCursor(0, 0);
  lcd.print("Temp         C  ");
  lcd.setCursor(6, 0);
  lcd.print(tempC);
  
  // Display Temperature in F.
  lcd.setCursor(0, 1);
  lcd.print("Temp         F  ");
  lcd.setCursor(6, 1);
  lcd.print(tempF);
  delay(500);

  /* LEDS */
  if (tempC < 15.0) {
      leds = 3;
  } else if (tempC > 15.0 && tempC < 20.0) {
      leds = 12;
  } else if (tempC > 20.0 && tempC < 25.0) {
      leds = 48;
  } else {
      leds = 192;
  }

  updateShiftRegister();
}

// Used for updating LEDs.
void updateShiftRegister() {
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, LSBFIRST, leds);
   digitalWrite(latchPin, HIGH);
}
