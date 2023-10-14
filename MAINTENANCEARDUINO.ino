#define TRIG_PIN 4  // Define the pins for HC-SR04 sensor
#define ECHO_PIN 5
#define MOTOR_ENA 6                 // Enable pin for motor driver
#define MOTOR_IN1 9                 // Motor driver input pin 1
#define MOTOR_IN2 10                // Motor driver input pin 2
#define REED_SWITCH_PIN_DOOR 8      // Reed switch pin for door closed
#define REED_SWITCH_PIN_CONTACT 11  // Reed switch pin for contact detection
#define pinbitch 13                 //testwr

//Relays
const int MAIN_DOOR_VALVE = A0;  // Relay 1 connected to analog pin A0
const int TRAP_DOOR_VALVE = A1;  // Relay 2 connected to analog pin A1
const int COMP1_VALVE = A2;      // Relay  3 connected to analog pin A2
const int COMP2_VALVE = A3;      // Relay 4 connected to analog pin A3


bool isMotorRunning = false;

void setup() {
  // Set the baud rate for both the hardware and software serial ports
  Serial.begin(9600);    // Serial monitor for debugging

  // Define pin modes
  pinMode(TRIG_PIN, OUTPUT);  //Ultrasonic pins
  pinMode(ECHO_PIN, INPUT);

  pinMode(MAIN_DOOR_VALVE, OUTPUT);
  pinMode(TRAP_DOOR_VALVE, OUTPUT);
  pinMode(COMP1_VALVE, OUTPUT);
  pinMode(COMP2_VALVE, OUTPUT);


  pinMode(MOTOR_ENA, OUTPUT);
  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);
  pinMode(REED_SWITCH_PIN_DOOR, INPUT);     // Enable internal pull-up resistor for the door reed switch
  pinMode(REED_SWITCH_PIN_CONTACT, INPUT);  // Enable internal pull-up resistor for the contact reed switch

  pinMode(pinbitch, INPUT);  //tEEST

  digitalWrite(MAIN_DOOR_VALVE, HIGH);
  digitalWrite(TRAP_DOOR_VALVE, HIGH);
  digitalWrite(COMP1_VALVE, HIGH);
  digitalWrite(COMP2_VALVE, HIGH);
}


void loop() {
  if (Serial.available()) {
    char command = Serial.read(); // read the command from the serial monitor
    
    if (command == '1') { // if the command is '1'
      digitalWrite(A0, HIGH); // set A0 pin to a high state
      Serial.println("A0 pin set to HIGH"); // send a confirmation message back to the serial monitor
    }
    else if (command == '0') { // if the command is '0'
      digitalWrite(A0, LOW); // set A0 pin to a low state
      Serial.println("A0 pin set to LOW"); // send a confirmation message back to the serial monitor
    }
    else if (command == '2') { // if the command is '0'
       while (!isContactDetected()) {
              startMotorBackward();

              // Keep running the motor backward until contact is detected
            }
            stopMotor();
    }
      
    else {
      Serial.println("Invalid command"); // send an error message if the command is invalid
    }
  }
}

void startMotorBackward() {
  digitalWrite(MOTOR_ENA, HIGH);  // Enable the motor driver
  delay(200);
  digitalWrite(MOTOR_IN1, LOW);   // Motor input 1 LOW
  digitalWrite(MOTOR_IN2, HIGH);  // Motor input 2 HIGH
  isMotorRunning = true;
}
bool isContactDetected() {
  return digitalRead(REED_SWITCH_PIN_CONTACT) == HIGH;
}

void stopMotor() {
  digitalWrite(MOTOR_ENA, LOW);  // Disable the motor driver
  delay(200);
  digitalWrite(MOTOR_IN1, LOW);  // Motor input 1 LOW
  digitalWrite(MOTOR_IN2, LOW);  // Motor input 2 LOW
  isMotorRunning = false;
}