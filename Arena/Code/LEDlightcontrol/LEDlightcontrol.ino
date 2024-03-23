int bluePin = 3;
int greenPin = 7;
int redPin = 9;

void setup() {
  // put your setup code here, to run once:
  pinMode(bluePin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);

  analogWrite(bluePin, 255);
  analogWrite(redPin, 255);
  analogWrite(greenPin, 255);

}

void loop() {
  // put your main code here, to run repeatedly:
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    delay(3000);
    
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, HIGH);
    
    digitalWrite(bluePin, LOW);
    digitalWrite(greenPin, LOW);
    delay(3000);
    
    digitalWrite(bluePin, HIGH);
    digitalWrite(greenPin, HIGH);

}
