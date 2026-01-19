const int sensorPin = 2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(sensorPin, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  int state = digitalRead(sensorPin);

  if(state == HIGH){
  Serial.println("NOTHING DETECTED"); //NOTHING IN THE WAY
  }

  if(state == LOW){
  Serial.println("OBJECT DETECTED"); //SOMETHING IN THE WAY
  }
//test
}
