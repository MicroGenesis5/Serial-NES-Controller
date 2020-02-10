// Arduino Mega part of Serial NES Controller project: https://www.microgenesis5.com/_txt/nes.html

String InBytes;

void setup() {

  Serial.begin(9600); // USB
  Serial1.begin(9600);

}

void loop() {

  // check serial port
  while (Serial1.available()) {
    delay(1);
    if (Serial1.available() > 0) {
      char c = Serial1.read();
      Serial.print(c);
      if (isControl(c)) {
        break;
      }
    }
  }

  if (Serial.available() > 0) {
    InBytes = Serial.readStringUntil('\n');
    Serial1.print(InBytes);
    Serial.write("command sent");
  }  


}
