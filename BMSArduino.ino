#include <Arduino.h>
#include <ArduinoJson.h>

// Define LED and toggle switch pins for each room (up to Room 10)
const int Room1LED = 2;
const int Room2LED = 3;
const int Room3LED = 4;
const int Room4LED = 5;
const int Room5LED = 6;
const int Room6LED = 7;
const int Room7LED = 8;
const int Room8LED = 9;
const int Room9LED = 10;
const int Room10LED = 11;

const int Room1Toggle = 22;
const int Room2Toggle = 23;
const int Room3Toggle = 24;
const int Room4Toggle = 25;
const int Room5Toggle = 26;
const int Room6Toggle = 27;
const int Room7Toggle = 28;
const int Room8Toggle = 29;
const int Room9Toggle = 30;
const int Room10Toggle = 31;

// Define a pin for the master toggle switch
const int MasterToggle = 32;

// Variables to store LED states
int Room1LEDState = LOW;
int Room2LEDState = LOW;
int Room3LEDState = LOW;
int Room4LEDState = LOW;
int Room5LEDState = LOW;
int Room6LEDState = LOW;
int Room7LEDState = LOW;
int Room8LEDState = LOW;
int Room9LEDState = LOW;
int Room10LEDState = LOW;

// Variables to store previous toggle switch states
int Room1SwitchStatePrev = HIGH;
int Room2SwitchStatePrev = HIGH;
int Room3SwitchStatePrev = HIGH;
int Room4SwitchStatePrev = HIGH;
int Room5SwitchStatePrev = HIGH;
int Room6SwitchStatePrev = HIGH;
int Room7SwitchStatePrev = HIGH;
int Room8SwitchStatePrev = HIGH;
int Room9SwitchStatePrev = HIGH;
int Room10SwitchStatePrev = HIGH;
int MasterSwitchStatePrev = HIGH;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);

  // Set LED pins as outputs
  pinMode(Room1LED, OUTPUT);
  pinMode(Room2LED, OUTPUT);
  pinMode(Room3LED, OUTPUT);
  pinMode(Room4LED, OUTPUT);
  pinMode(Room5LED, OUTPUT);
  pinMode(Room6LED, OUTPUT);
  pinMode(Room7LED, OUTPUT);
  pinMode(Room8LED, OUTPUT);
  pinMode(Room9LED, OUTPUT);
  pinMode(Room10LED, OUTPUT);

  // Set toggle switch pins as inputs with internal pull-ups
  pinMode(Room1Toggle, INPUT_PULLUP);
  pinMode(Room2Toggle, INPUT_PULLUP);
  pinMode(Room3Toggle, INPUT_PULLUP);
  pinMode(Room4Toggle, INPUT_PULLUP);
  pinMode(Room5Toggle, INPUT_PULLUP);
  pinMode(Room6Toggle, INPUT_PULLUP);
  pinMode(Room7Toggle, INPUT_PULLUP);
  pinMode(Room8Toggle, INPUT_PULLUP);
  pinMode(Room9Toggle, INPUT_PULLUP);
  pinMode(Room10Toggle, INPUT_PULLUP);

  // Set master toggle switch pin as input with internal pull-up
  pinMode(MasterToggle, INPUT_PULLUP);
}

void loop() {
  // Handle commands from NodeMCU
  if (Serial1.available() > 0) {
    String command = Serial1.readStringUntil('\n');
    command.trim();
    
    if (command == "get") {
      sendJSONResponse(); // Send JSON response when "get" command received
    } else if (command == "all on") {
      setAllLEDs(HIGH); // Turn all LEDs on
    } else if (command == "all off") {
      setAllLEDs(LOW); // Turn all LEDs off
    } else {
      handleSerialCommand(command); // Handle other commands
    }
  }

  // Update LEDs based on toggle switch state changes
  updateLED(Room1Toggle, Room1SwitchStatePrev, Room1LED, Room1LEDState);
  updateLED(Room2Toggle, Room2SwitchStatePrev, Room2LED, Room2LEDState);
  updateLED(Room3Toggle, Room3SwitchStatePrev, Room3LED, Room3LEDState);
  updateLED(Room4Toggle, Room4SwitchStatePrev, Room4LED, Room4LEDState);
  updateLED(Room5Toggle, Room5SwitchStatePrev, Room5LED, Room5LEDState);
  updateLED(Room6Toggle, Room6SwitchStatePrev, Room6LED, Room6LEDState);
  updateLED(Room7Toggle, Room7SwitchStatePrev, Room7LED, Room7LEDState);
  updateLED(Room8Toggle, Room8SwitchStatePrev, Room8LED, Room8LEDState);
  updateLED(Room9Toggle, Room9SwitchStatePrev, Room9LED, Room9LEDState);
  updateLED(Room10Toggle, Room10SwitchStatePrev, Room10LED, Room10LEDState);

  // Update all LEDs based on master toggle switch state
  updateMasterLEDs(MasterToggle, MasterSwitchStatePrev);
}

// Function to handle commands from NodeMCU
void handleSerialCommand(String command) {
  int roomNumber = command.substring(4, command.indexOf(' ')).toInt();

  // Extract action and convert to lowercase
  String action = command.substring(command.indexOf(' ') + 1);
  action.toLowerCase();

  Serial.println(roomNumber);
  Serial.println(action);

  if (roomNumber >= 1 && roomNumber <= 10) {
    int ledPin = getLEDPin(roomNumber);
    int& ledState = getLEDState(roomNumber);
    
    if (action == "on") {
      ledState = HIGH;
    } else if (action == "off") {
      ledState = LOW;
    }
    
    digitalWrite(ledPin, ledState);
  }
}

// Function to get the LED pin for a given room number
int getLEDPin(int roomNumber) {
  switch (roomNumber) {
    case 1: return Room1LED;
    case 2: return Room2LED;
    case 3: return Room3LED;
    case 4: return Room4LED;
    case 5: return Room5LED;
    case 6: return Room6LED;
    case 7: return Room7LED;
    case 8: return Room8LED;
    case 9: return Room9LED;
    case 10: return Room10LED;
    default: return -1; // Invalid room number
  }
}

// Function to get the LED state for a given room number
int& getLEDState(int roomNumber) {
  switch (roomNumber) {
    case 1: return Room1LEDState;
    case 2: return Room2LEDState;
    case 3: return Room3LEDState;
    case 4: return Room4LEDState;
    case 5: return Room5LEDState;
    case 6: return Room6LEDState;
    case 7: return Room7LEDState;
    case 8: return Room8LEDState;
    case 9: return Room9LEDState;
    case 10: return Room10LEDState;
    default: return Room1LEDState; // Default to Room1LEDState for invalid room number
  }
}

// Function to update LED state based on toggle switch state change
void updateLED(int togglePin, int& prevSwitchState, int ledPin, int& ledState) {
  int switchState = digitalRead(togglePin);
  if (switchState == LOW && prevSwitchState == HIGH) {
    ledState = HIGH;
    digitalWrite(ledPin, ledState);
    delay(50); // Debounce delay
  }
  if (switchState == HIGH && prevSwitchState == LOW){
    ledState = LOW;
    digitalWrite(ledPin, ledState);
    delay(50); // Debounce delay
  }
  
  prevSwitchState = switchState;
}

// Function to update all LED states based on master toggle switch state change
void updateMasterLEDs(int togglePin, int& prevSwitchState) {
  int switchState = digitalRead(togglePin);
  if (switchState == LOW && prevSwitchState == HIGH) {
    int newState = !Room1LEDState; // Toggle the state of all LEDs
    setAllLEDs(newState);
    delay(50); // Debounce delay
  }
  
  prevSwitchState = switchState;
}

// Function to set the state of all LEDs
void setAllLEDs(int state) {
  Room1LEDState = state;
  Room2LEDState = state;
  Room3LEDState = state;
  Room4LEDState = state;
  Room5LEDState = state;
  Room6LEDState = state;
  Room7LEDState = state;
  Room8LEDState = state;
  Room9LEDState = state;
  Room10LEDState = state;
  
  digitalWrite(Room1LED, Room1LEDState);
  digitalWrite(Room2LED, Room2LEDState);
  digitalWrite(Room3LED, Room3LEDState);
  digitalWrite(Room4LED, Room4LEDState);
  digitalWrite(Room5LED, Room5LEDState);
  digitalWrite(Room6LED, Room6LEDState);
  digitalWrite(Room7LED, Room7LEDState);
  digitalWrite(Room8LED, Room8LEDState);
  digitalWrite(Room9LED, Room9LEDState);
  digitalWrite(Room10LED, Room10LEDState);
}

// Function to send JSON response
void sendJSONResponse() {
  StaticJsonDocument<512> jsonDocument;
  
  jsonDocument["room1"] = Room1LEDState;
  jsonDocument["room2"] = Room2LEDState;
  jsonDocument["room3"] = Room3LEDState;
  jsonDocument["room4"] = Room4LEDState;
  jsonDocument["room5"] = Room5LEDState;
  jsonDocument["room6"] = Room6LEDState;
  jsonDocument["room7"] = Room7LEDState;
  jsonDocument["room8"] = Room8LEDState;
  jsonDocument["room9"] = Room9LEDState;
  jsonDocument["room10"] = Room10LEDState;

  serializeJson(jsonDocument, Serial1);
  Serial1.println();
}
