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
bool RoomLEDStates[10] = {false, false, false, false, false, false, false, false, false, false};

// Variables to store previous toggle switch states
int MasterSwitchStatePrev = HIGH;
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
  // Request and handle commands from NodeMCU
  if (Serial1.available() > 0) {
    String responseFromNodeMCU = Serial1.readStringUntil('\n');
    responseFromNodeMCU.trim();
    Serial.println(responseFromNodeMCU);
    // Process the received JSON
    processJSONResponse(responseFromNodeMCU);
  }

  // Update the state of each room based on the toggle switch
  updateLED(Room1Toggle, Room1SwitchStatePrev, "Room1");
  updateLED(Room2Toggle, Room2SwitchStatePrev, "Room2");
  updateLED(Room3Toggle, Room3SwitchStatePrev, "Room3");
  updateLED(Room4Toggle, Room4SwitchStatePrev, "Room4");
  updateLED(Room5Toggle, Room5SwitchStatePrev, "Room5");
  updateLED(Room6Toggle, Room6SwitchStatePrev, "Room6");
  updateLED(Room7Toggle, Room7SwitchStatePrev, "Room7");
  updateLED(Room8Toggle, Room8SwitchStatePrev, "Room8");
  updateLED(Room9Toggle, Room9SwitchStatePrev, "Room9");
  updateLED(Room10Toggle, Room10SwitchStatePrev, "Room10");

  // Update the state of the master toggle switch
  updateMasterLEDs(MasterToggle, MasterSwitchStatePrev);
  
  Serial.println("umabot dito!");
  delay(50);
}

// Function to process received JSON and control LEDs
void processJSONResponse(String jsonString) {
  StaticJsonBuffer<512> jsonBuffer;
  JsonObject& jsonDocument = jsonBuffer.parseObject(jsonString);

  // Check if the JSON parsing was successful
  if (!jsonDocument.success()) {
    Serial.println("Failed to parse JSON");
    return;
  }

  // Control each room's LED based on the received JSON
  for (int i = 0; i < 10; i++) {
    String roomKey = "Room" + String(i + 1);

    // Check if the key exists in the JSON object
    if (jsonDocument.containsKey(roomKey)) {
      bool roomState = jsonDocument[roomKey];

      // Map room number to corresponding LED pin
      int ledPin;
      switch (i) {
        case 0: ledPin = Room1LED; break;
        case 1: ledPin = Room2LED; break;
        case 2: ledPin = Room3LED; break;
        case 3: ledPin = Room4LED; break;
        case 4: ledPin = Room5LED; break;
        case 5: ledPin = Room6LED; break;
        case 6: ledPin = Room7LED; break;
        case 7: ledPin = Room8LED; break;
        case 8: ledPin = Room9LED; break;
        case 9: ledPin = Room10LED; break;
      }

      // Control the LED based on the state
      RoomLEDStates[i] = roomState;
      digitalWrite(ledPin, roomState ? HIGH : LOW); // LOW turns the LED on, HIGH turns it off
    }
  }
}

// Function to update LED state based on toggle switch state change
void updateLED(int togglePin, int& prevSwitchState, const String roomName) {
  int switchState = digitalRead(togglePin);
  // Check if switch state has changed
  if (switchState == LOW && prevSwitchState == HIGH) {
    // Switch turned ON
  Serial.println(switchState);
  Serial.println(prevSwitchState);
    Serial.println(roomName + " ON");
    Serial1.println(roomName + " ON"); // Send ON message to NodeMCU
  } else if (switchState == HIGH && prevSwitchState == LOW) {
    // Switch turned OFF
  Serial.println(switchState);
  Serial.println(prevSwitchState);
    Serial.println(roomName + " OFF");
    Serial1.println(roomName + " OFF"); // Send OFF message to NodeMCU
  }

  // Update previous switch state
  prevSwitchState = switchState;
}

// Function to update all LED states based on master toggle switch state change
void updateMasterLEDs(int togglePin, int& prevSwitchState) {
  int switchState = digitalRead(togglePin);
  // Update all LEDs if master switch is toggled
  if (switchState == LOW && prevSwitchState == HIGH) {
    
  Serial.println(switchState);
  Serial.println(prevSwitchState);
    Serial.println("all on");
    Serial1.println("all on"); // Send "all on" message to NodeMCU
  } else if (switchState == HIGH && prevSwitchState == LOW) {
    
  Serial.println(switchState);
  Serial.println(prevSwitchState);
    Serial.println("all off");
    Serial1.println("all off"); // Send "all off" message to NodeMCU
  }

  // Update previous switch state
  prevSwitchState = switchState;
}
