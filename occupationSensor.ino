const int A = 2;
const int B = 3;
int count = 0;
int state;
unsigned long startTime; 
unsigned long elapsedTime;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A, INPUT_PULLUP);
  pinMode(B, INPUT_PULLUP);
  state = 0;

}

// 0 = nothing happened, 1 = A broke first, 2 = B broke first
void loop() {

  int Astate = digitalRead(A);
  int Bstate = digitalRead(B);
  elapsedTime = millis() - startTime;

  if(state == 0){ //initial state
    if(Astate == LOW){
      startTime = millis();
      state = 1;
      Serial.println("A BEAM BROKEN");
    }

    else if(Bstate == LOW){
      startTime = millis();
      state = 2;
      Serial.println("B BEAM BROKEN");     
    }
  }

  else if(state == 1){ //for entering
    if(elapsedTime <= 800 && Bstate == LOW){
      count++;
      state = 0;
      Serial.print("Occupancy Count = ");
      Serial.println(count);
    }
    else if(Astate == HIGH && Bstate == HIGH){ //both beams clear
      state = 0;
    } 
  }

  else if(state == 2){ //for exiting
    if(elapsedTime <= 800 && Astate == LOW){
      if(count>0) count--;
      state = 0;
      Serial.print("Occupancy Count = ");
      Serial.println(count);
    }
    else if(Astate == HIGH && Bstate == HIGH){ //both beams clear
      state = 0;
    } 
  }  


}
