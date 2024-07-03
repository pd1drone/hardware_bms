#include <Arduino.h>
#include <ArduinoJson.h>

// Define LED and toggle switch pins for each room
const int Room1LED = A0;
const int Room2LED = A1;
const int Room3LED = A2;
const int Room4LED = A3;
const int Room5LED = A4;
const int Room6LED = A5;
const int Room7LED = A6;
const int Room8LED = A7;
const int Room9LED = A8;
const int Room10LED = A9;
const int Room11LED = A10;
const int Room12LED = A11;
const int Room13LED = A12;
const int Room14LED = A13;
const int Room15LED = A14;
const int Room16LED = A15;
const int Room17LED = 2;
const int Room18LED = 3;
const int Room19LED = 4;
const int Room20LED = 5;
const int Room21LED = 6;
const int Room22LED = 7;
const int Room23LED = 8;
const int Room24LED = 9;
const int Room25LED = 10;
const int Room26LED = 11;
const int Room27LED = 12;
const int Room28LED = 13;
const int Room29LED = 14;
const int Room30LED = 15;

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
const int Room11Toggle = 32;
const int Room12Toggle = 33;
const int Room13Toggle = 34;
const int Room14Toggle = 35;
const int Room15Toggle = 36;
const int Room16Toggle = 37;
const int Room17Toggle = 38;
const int Room18Toggle = 39;
const int Room19Toggle = 40;
const int Room20Toggle = 41;
const int Room21Toggle = 42;
const int Room22Toggle = 43;
const int Room23Toggle = 44;
const int Room24Toggle = 45;
const int Room25Toggle = 46;
const int Room26Toggle = 47;
const int Room27Toggle = 48;
const int Room28Toggle = 49;
const int Room29Toggle = 50;
const int Room30Toggle = 51;

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
int Room11LEDState = LOW;
int Room12LEDState = LOW;
int Room13LEDState = LOW;
int Room14LEDState = LOW;
int Room15LEDState = LOW;
int Room16LEDState = LOW;
int Room17LEDState = LOW;
int Room18LEDState = LOW;
int Room19LEDState = LOW;
int Room20LEDState = LOW;
int Room21LEDState = LOW;
int Room22LEDState = LOW;
int Room23LEDState = LOW;
int Room24LEDState = LOW;
int Room25LEDState = LOW;
int Room26LEDState = LOW;
int Room27LEDState = LOW;
int Room28LEDState = LOW;
int Room29LEDState = LOW;
int Room30LEDState = LOW;

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
int Room11SwitchStatePrev = HIGH;
int Room12SwitchStatePrev = HIGH;
int Room13SwitchStatePrev = HIGH;
int Room14SwitchStatePrev = HIGH;
int Room15SwitchStatePrev = HIGH;
int Room16SwitchStatePrev = HIGH;
int Room17SwitchStatePrev = HIGH;
int Room18SwitchStatePrev = HIGH;
int Room19SwitchStatePrev = HIGH;
int Room20SwitchStatePrev = HIGH;
int Room21SwitchStatePrev = HIGH;
int Room22SwitchStatePrev = HIGH;
int Room23SwitchStatePrev = HIGH;
int Room24SwitchStatePrev = HIGH;
int Room25SwitchStatePrev = HIGH;
int Room26SwitchStatePrev = HIGH;
int Room27SwitchStatePrev = HIGH;
int Room28SwitchStatePrev = HIGH;
int Room29SwitchStatePrev = HIGH;
int Room30SwitchStatePrev = HIGH;

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
  pinMode(Room11LED, OUTPUT);
  pinMode(Room12LED, OUTPUT);
  pinMode(Room13LED, OUTPUT);
  pinMode(Room14LED, OUTPUT);
  pinMode(Room15LED, OUTPUT);
  pinMode(Room16LED, OUTPUT);
  pinMode(Room17LED, OUTPUT);
  pinMode(Room18LED, OUTPUT);
  pinMode(Room19LED, OUTPUT);
  pinMode(Room20LED, OUTPUT);
  pinMode(Room21LED, OUTPUT);
  pinMode(Room22LED, OUTPUT);
  pinMode(Room23LED, OUTPUT);
  pinMode(Room24LED, OUTPUT);
  pinMode(Room25LED, OUTPUT);
  pinMode(Room26LED, OUTPUT);
  pinMode(Room27LED, OUTPUT);
  pinMode(Room28LED, OUTPUT);
  pinMode(Room29LED, OUTPUT);
  pinMode(Room30LED, OUTPUT);

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
  pinMode(Room11Toggle, INPUT_PULLUP);
  pinMode(Room12Toggle, INPUT_PULLUP);
  pinMode(Room13Toggle, INPUT_PULLUP);
  pinMode(Room14Toggle, INPUT_PULLUP);
  pinMode(Room15Toggle, INPUT_PULLUP);
  pinMode(Room16Toggle, INPUT_PULLUP);
  pinMode(Room17Toggle, INPUT_PULLUP);
  pinMode(Room18Toggle, INPUT_PULLUP);
  pinMode(Room19Toggle, INPUT_PULLUP);
  pinMode(Room20Toggle, INPUT_PULLUP);
  pinMode(Room21Toggle, INPUT_PULLUP);
  pinMode(Room22Toggle, INPUT_PULLUP);
  pinMode(Room23Toggle, INPUT_PULLUP);
  pinMode(Room24Toggle, INPUT_PULLUP);
  pinMode(Room25Toggle, INPUT_PULLUP);
  pinMode(Room26Toggle, INPUT_PULLUP);
  pinMode(Room27Toggle, INPUT_PULLUP);
  pinMode(Room28Toggle, INPUT_PULLUP);
  pinMode(Room29Toggle, INPUT_PULLUP);
  pinMode(Room30Toggle, INPUT_PULLUP);
}

void loop() {
  // Handle commands from NodeMCU
  if (Serial1.available() > 0) {
    String command = Serial1.readStringUntil('\n');
    command.trim();
    
    if (command == "get") {
      sendJSONResponse(); // Send JSON response when "get" command received
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
  updateLED(Room11Toggle, Room11SwitchStatePrev, Room11LED, Room11LEDState);
  updateLED(Room12Toggle, Room12SwitchStatePrev, Room12LED, Room12LEDState);
  updateLED(Room13Toggle, Room13SwitchStatePrev, Room13LED, Room13LEDState);
  updateLED(Room14Toggle, Room14SwitchStatePrev, Room14LED, Room14LEDState);
  updateLED(Room15Toggle, Room15SwitchStatePrev, Room15LED, Room15LEDState);
  updateLED(Room16Toggle, Room16SwitchStatePrev, Room16LED, Room16LEDState);
  updateLED(Room17Toggle, Room17SwitchStatePrev, Room17LED, Room17LEDState);
  updateLED(Room18Toggle, Room18SwitchStatePrev, Room18LED, Room18LEDState);
  updateLED(Room19Toggle, Room19SwitchStatePrev, Room19LED, Room19LEDState);
  updateLED(Room20Toggle, Room20SwitchStatePrev, Room20LED, Room20LEDState);
  updateLED(Room21Toggle, Room21SwitchStatePrev, Room21LED, Room21LEDState);
  updateLED(Room22Toggle, Room22SwitchStatePrev, Room22LED, Room22LEDState);
  updateLED(Room23Toggle, Room23SwitchStatePrev, Room23LED, Room23LEDState);
  updateLED(Room24Toggle, Room24SwitchStatePrev, Room24LED, Room24LEDState);
  updateLED(Room25Toggle, Room25SwitchStatePrev, Room25LED, Room25LEDState);
  updateLED(Room26Toggle, Room26SwitchStatePrev, Room26LED, Room26LEDState);
  updateLED(Room27Toggle, Room27SwitchStatePrev, Room27LED, Room27LEDState);
  updateLED(Room28Toggle, Room28SwitchStatePrev, Room28LED, Room28LEDState);
  updateLED(Room29Toggle, Room29SwitchStatePrev, Room29LED, Room29LEDState);
  updateLED(Room30Toggle, Room30SwitchStatePrev, Room30LED, Room30LEDState);
}

// Function to handle commands from NodeMCU
void handleSerialCommand(String command) {
  int roomNumber = command.substring(4, command.indexOf(' ')).toInt();

  // Extract action and convert to lowercase
  String action = command.substring(command.indexOf(' ') + 1);
  action.toLowerCase();

  Serial.println(roomNumber);
  Serial.println(action);

  if (roomNumber >= 1 && roomNumber <= 30) {
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
    case 11: return Room11LED;
    case 12: return Room12LED;
    case 13: return Room13LED;
    case 14: return Room14LED;
    case 15: return Room15LED;
    case 16: return Room16LED;
    case 17: return Room17LED;
    case 18: return Room18LED;
    case 19: return Room19LED;
    case 20: return Room20LED;
    case 21: return Room21LED;
    case 22: return Room22LED;
    case 23: return Room23LED;
    case 24: return Room24LED;
    case 25: return Room25LED;
    case 26: return Room26LED;
    case 27: return Room27LED;
    case 28: return Room28LED;
    case 29: return Room29LED;
    case 30: return Room30LED;
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
    case 11: return Room11LEDState;
    case 12: return Room12LEDState;
    case 13: return Room13LEDState;
    case 14: return Room14LEDState;
    case 15: return Room15LEDState;
    case 16: return Room16LEDState;
    case 17: return Room17LEDState;
    case 18: return Room18LEDState;
    case 19: return Room19LEDState;
    case 20: return Room20LEDState;
    case 21: return Room21LEDState;
    case 22: return Room22LEDState;
    case 23: return Room23LEDState;
    case 24: return Room24LEDState;
    case 25: return Room25LEDState;
    case 26: return Room26LEDState;
    case 27: return Room27LEDState;
    case 28: return Room28LEDState;
    case 29: return Room29LEDState;
    case 30: return Room30LEDState;
    default: return Room1LEDState; // Default to Room1LEDState for invalid room number
  }
}

// Function to update LED state based on toggle switch state change
void updateLED(int togglePin, int& prevSwitchState, int ledPin, int& ledState) {
  int switchState = digitalRead(togglePin);
  if (togglePin == 51){
    Serial.println(switchState);
  }
  if (switchState == LOW && prevSwitchState == HIGH) {
    ledState = 1;
    digitalWrite(ledPin, ledState);
    delay(50); // Debounce delay
  }
  if (switchState == HIGH && prevSwitchState == LOW){
    ledState = 0;
    digitalWrite(ledPin, ledState);
    delay(50); // Debounce delay
  }
  
  prevSwitchState = switchState;
}

// Function to send JSON response
void sendJSONResponse() {
  StaticJsonDocument<1024> jsonDocument;
  
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
  jsonDocument["room11"] = Room11LEDState;
  jsonDocument["room12"] = Room12LEDState;
  jsonDocument["room13"] = Room13LEDState;
  jsonDocument["room14"] = Room14LEDState;
  jsonDocument["room15"] = Room15LEDState;
  jsonDocument["room16"] = Room16LEDState;
  jsonDocument["room17"] = Room17LEDState;
  jsonDocument["room18"] = Room18LEDState;
  jsonDocument["room19"] = Room19LEDState;
  jsonDocument["room20"] = Room20LEDState;
  jsonDocument["room21"] = Room21LEDState;
  jsonDocument["room22"] = Room22LEDState;
  jsonDocument["room23"] = Room23LEDState;
  jsonDocument["room24"] = Room24LEDState;
  jsonDocument["room25"] = Room25LEDState;
  jsonDocument["room26"] = Room26LEDState;
  jsonDocument["room27"] = Room27LEDState;
  jsonDocument["room28"] = Room28LEDState;
  jsonDocument["room29"] = Room29LEDState;
  jsonDocument["room30"] = Room30LEDState;
  
  String jsonResponse;
  serializeJson(jsonDocument, jsonResponse);
  
  Serial.println(jsonResponse);
  Serial1.println(jsonResponse);
}

