
#include <Adafruit_LiquidCrystal.h>

// Tinkercad I2C LCD
Adafruit_LiquidCrystal lcd(0);

// PIR sensor pins
const int entrySensor = 5;
const int exitSensor = 6;

int peopleCount = 0;
int lastEntryState = LOW;
int lastExitState = LOW;

unsigned long lastEntryTime = 0;
unsigned long lastExitTime = 0;

const unsigned long cooldown = 2000;

void setup() {
  pinMode(entrySensor, INPUT);
  pinMode(exitSensor, INPUT);

  Serial.begin(9600);

  lcd.begin(16, 2);
  lcd.setBacklight(1);
  lcd.clear();

  updateDisplay();
}

void loop() {
  int entryState = digitalRead(entrySensor);
  int exitState = digitalRead(exitSensor);

  // Person detected at entry
  if (entryState == HIGH &&
      lastEntryState == LOW &&
      millis() - lastEntryTime >= cooldown) {
    peopleCount++;
    lastEntryTime = millis();
    updateDisplay();
  }

  // Person detected at exit
  if (exitState == HIGH &&
      lastExitState == LOW &&
      millis() - lastExitTime >= cooldown) {
    if (peopleCount > 0) {
      peopleCount--;
    }

    lastExitTime = millis();
    updateDisplay();
  }

  lastEntryState = entryState;
  lastExitState = exitState;

  delay(20);
}

void updateDisplay() {
  lcd.setCursor(0, 0);
  lcd.print("Room Occupancy  ");

  lcd.setCursor(0, 1);
  lcd.print("People: ");
  lcd.print(peopleCount);
  lcd.print("       ");

  Serial.print("People inside: ");
  Serial.println(peopleCount);
}
