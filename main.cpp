
#include <Arduino.h>
#define LED1 10
#define LED2 9
#define LED3 8
#define LED4 7
#define STATUS_LED_RED 6
#define STATUS_LED_GREEN 5
#define STATUS_LED_BLUE 4    
#define START_BUTTON 2
#define STOP_BUTTON 3

unsigned long longPressDuration = 2000; // Duration for long press(2s)
unsigned long pressStartTime = 0; // initializing variable that stores when the Button was pressed
unsigned long lastBlinkTime = 0; 
unsigned long lastActionTime = 0;
unsigned long blinkInterval = 500; 
unsigned long ledChangeInterval = 3000; 

int blinkState = LOW;  // Current LED starting state
int currentLed = LED1; // Current LED while charging
bool isCharging = false; 
int step = 0;


int buttonDebounce(char pin){
   const int DEBOUNCE_DELAY = 50;
  static int buttonState, lastButtonState;
  static long lastDebounceTime; 
  int out = 0;
  int reading = digitalRead(pin);
  if(reading != lastButtonState) lastDebounceTime = millis();

  if((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
    if (reading != buttonState) {
      buttonState = reading;
      // ACTIVE LOWso !buttonState
      if(!buttonState) {
        out = 1;
      }
    }
  }
  lastButtonState = reading;
  return out;
}

void SetLedState(char led1, char led2, char led3, char led4) {
    digitalWrite(LED1, led1);
    digitalWrite(LED2, led2);
    digitalWrite(LED3, led3);
    digitalWrite(LED4, led4);
}

void SetRGBLedState(char red, char green, char blue) {
    digitalWrite(STATUS_LED_RED, red);
    digitalWrite(STATUS_LED_GREEN, green);
    digitalWrite(STATUS_LED_BLUE, blue);
}
void updateLedState() {
    // Cycling LEDs on or off based on current step
    if (step == 0) {
        digitalWrite(LED1, blinkState);
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, LOW);
        digitalWrite(LED4, LOW);
    } else if (step == 1) {
        digitalWrite(LED1, HIGH);  
        digitalWrite(LED2, blinkState);
        digitalWrite(LED3, LOW);
        digitalWrite(LED4, LOW);
    } else if (step == 2) {
        digitalWrite(LED1, HIGH);  
        digitalWrite(LED2, HIGH);  
        digitalWrite(LED3, blinkState);
        digitalWrite(LED4, LOW);
    } else if (step == 3) {
        digitalWrite(LED1, HIGH);  
        digitalWrite(LED2, HIGH);  
        digitalWrite(LED3, HIGH);  
        digitalWrite(LED4, blinkState);
    }
}

void END_CHARGE(){
    Serial.println("Charging ended.");
    for(int i = 0; i < 4; i++) {
        SetLedState(HIGH, HIGH, HIGH, HIGH);
        delay(500);
        SetLedState(LOW, LOW, LOW, LOW);
        delay(500);
    }
    SetRGBLedState(LOW, HIGH, LOW); 
    isCharging = false; 
}
void START_CHARGE() {
    if (!isCharging) {  
        if (buttonDebounce(START_BUTTON)==1) {  
            Serial.println("Charging started.");
            SetRGBLedState(HIGH, LOW, LOW);  //Red indicates charging has started 
            isCharging = true;  
            step = 0;  // Starting from LED1
            currentLed = LED1;
            lastActionTime = millis();  // Set time for first action
        }
    }
}

void CHARGING_PROCESS() {
    unsigned long currentTime = millis();

    // Verifying if it's time to change LED(after 3s)
    if (currentTime - lastActionTime >= ledChangeInterval) {
        lastActionTime = currentTime;  // Updating time for next action
        step++;  
        if (step > 3) {  
            END_CHARGE();  
            return;
        }
    }

    // Blink for current LED
    if (currentTime - lastBlinkTime >= blinkInterval) {
        blinkState = !blinkState;  // Change led state(HIGH, LOW)
        lastBlinkTime = currentTime;
        updateLedState();  // Updating LED by step
    }
}

void FORCED_CHARGE_STOP(){
    int stopButtonState = digitalRead(STOP_BUTTON);

    if (stopButtonState == LOW) { // STOP BUTTON is pressed
        if (pressStartTime == 0) {
            pressStartTime = millis();  // Register the current time when STOP button was pressed
        }

        // Verifying if the button was pressed long enough
        if ((millis() - pressStartTime) >= longPressDuration) {
            Serial.println("Long press detected. Stopping charge...");
            END_CHARGE();  
        }
    } else {  // (button not pressed)
        pressStartTime = 0; 
    }
}

void setup() {
    Serial.begin(28800);
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
    pinMode(LED4, OUTPUT);
    pinMode(STATUS_LED_RED, OUTPUT);
    pinMode(STATUS_LED_GREEN, OUTPUT);
    pinMode(STATUS_LED_BLUE, OUTPUT);
    pinMode(START_BUTTON, INPUT_PULLUP);
    pinMode(STOP_BUTTON, INPUT_PULLUP);
    SetRGBLedState(LOW, HIGH, LOW);  // INITIAL STATE (GREEN, CHARGING STATION FREE)
    Serial.println("Program is running");
}

void loop() {
    START_CHARGE();         
    FORCED_CHARGE_STOP();   
    if(isCharging) {
        CHARGING_PROCESS();
    }
}