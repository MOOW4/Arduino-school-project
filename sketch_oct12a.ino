#include <IRremote.h>
#include <Servo.h>

Servo myservo;
int pos;

const int receiverPin = 7;
const int servoPin = 9;
IRrecv receiver(receiverPin);
decode_results results;

const int LED1 = 11;
const int LED2 = 10;
bool isOpen = false;

void setup()
{
  myservo.attach(servoPin);
  receiver.enableIRIn();
  receiver.blink13(true); // LED on Arduino labaled as 'L' will signal IR controller signal being received
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  myservo.write(0);
}

void loop()
{
  if (receiver.decode(&results)) {
    switch(results.value){
      case 0xFF38C7: // button '5'
        digitalWrite(LED1, HIGH);
        break;
      case 0xFF18E7: // button '2'
        digitalWrite(LED2, HIGH);
        break;
      case 0xFF30CF: // button '1'
        if (isOpen == false){                // OPEN the door
          for (pos = 0; pos <= 180; pos++) { // goes from 0 degrees to 180 degrees
            myservo.write(pos);              // tell servo to go to position in variable 'pos'
            delay(15);                       // waits 15ms for the servo to reach the position
          }
          isOpen = true;
        } else {                                  // CLOSE the door
            for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
              myservo.write(pos);                 // tell servo to go to position in variable 'pos'
              delay(15);                          // waits 15ms for the servo to reach the position
            }
            isOpen = false; 
          }

        break;
    }
    receiver.resume();
  }
}