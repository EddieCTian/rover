#include <Arduino.h>
#include <Wire.h>

#define slave_address 1

#if slave_address == 1
    #define total_no_of_sensors 2
#elif slave_address == 2
    #define total_no_of_sensors 2
#elif slave_address == 3
    #define total_no_of_sensors 2
#endif

const int outputA_pins[3] = {4, 9, 11};
const int outputB_pins[3] = {5, 10, 12};
int Sensor_values[total_no_of_sensors] = { 0 };
int aStates[total_no_of_sensors] = { 0 };
int bStates[total_no_of_sensors] = { 0 };
int bLastStates[total_no_of_sensors] = { 0 };
int aLastStates[total_no_of_sensors] = { 0 };
byte Sensor_value_bytes[2] = { 7 };

int currentSensor = 0;
// encoder 1: 0
// encoder 2: 1
// encoder 3: 2

void receiveEvent(int numBytes);
void requestEvent();

void setup() {
    Wire.begin(slave_address);
    Wire.onReceive(receiveEvent);
    Wire.onRequest(requestEvent);
    Serial.begin(115200);

    // Setting all pinModes and Sensor states
    for (int i = 0; i < total_no_of_sensors; i++) {
        pinMode(outputA_pins[i], INPUT);
        pinMode(outputB_pins[i], INPUT);
        aLastStates[i] = digitalRead(outputA_pins[i]);
        bLastStates[i] = digitalRead(outputB_pins[i]);
    }
}

void loop() {
    
    // Go through n number of sensors and update them all
    for (int i = 0; i < total_no_of_sensors; i++) {
        aStates[i] = digitalRead(outputA_pins[i]);  // Reads the "current" state of the outputA[i]
        bStates[i] = digitalRead(outputB_pins[i]);
        if(aStates[i] != aLastStates[i]){
            if(aStates[i]) {
                bStates[i] ? Sensor_values[i]-- : Sensor_values[i]++;
            } else {
                bStates[i] ? Sensor_values[i]++ : Sensor_values[i]--;
            }
        }

        if(bLastStates[i] != bStates[i]){
            if(bStates[i]) {
                aStates[i] ? Sensor_values[i]++ : Sensor_values[i]--;
                
            } else {
                aStates[i] ? Sensor_values[i]-- : Sensor_values[i]++;
            }
        }
        bLastStates[i] = bStates[i];
        aLastStates[i] = aStates[i];
    }
    Serial.println(Sensor_values[0]);
    //delay(); // might not be needed maybe
}

void receiveEvent(int numBytes) {
    // Set currentSensor so the desired sensor is reported
    currentSensor = Wire.read();
    Serial.println(currentSensor);
}

void requestEvent() {
    // Report back the value of the sensor requested
    Sensor_value_bytes[0] = ((Sensor_values[0]) >> 8) & (0xFF);
    Sensor_value_bytes[1] = (Sensor_values[0]) & (0xFF);
    Wire.write(Sensor_value_bytes, 2);
}