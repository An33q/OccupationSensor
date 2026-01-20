const int A = 2;
const int B = 3;
int count = 0;
int state;
unsigned long startTime; 
unsigned long elapsedTime;
unsigned long timeout;
int Astate, Bstate;
int prevAstate = HIGH;
int prevBstate = HIGH;


// 0 = idle
// 1 = A first (entering)
// 2 = B first (exiting)
// 3 = wait-for-clear (lockout)

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A, INPUT_PULLUP);
  pinMode(B, INPUT_PULLUP);
  state = 0;

}


void loop() {

  Astate = digitalRead(A);
  Bstate = digitalRead(B);
  elapsedTime = millis() - startTime;

//--------------IDLE---------------
  if(state == 0){ //initial state
    if(Astate == LOW && prevAstate == HIGH){
      state = 1;
      startTime = millis();
      //Serial.println("A BEAM BROKEN FIRST");
    }

    else if(Bstate == LOW && prevBstate == HIGH){
      state = 2;
      startTime = millis();
      //Serial.println("B BEAM BROKEN FIRST");     
    }
  }

//-------------ENTERING----------------
  else if(state == 1){ //for entering
    if(elapsedTime <= 800 && Bstate == LOW && prevBstate == HIGH){
      count++;
      Serial.print("Occupancy Count = ");
      Serial.println(count);
      timeout = millis();
      state = 3;
    }
    else if(elapsedTime > 800){//} || (Astate == HIGH && Bstate == HIGH)){ //both beams clear
      state = 0;
    } 
  }


//--------------EXITING-------------------
  else if(state == 2){ //for exiting
    if(elapsedTime <= 800 && Astate == LOW && prevAstate == HIGH){
      if(count>0) count--;
      Serial.print("Occupancy Count = ");
      Serial.println(count);
      timeout = millis();
      state = 3;
    }
    else if(elapsedTime > 800){// || (Astate == HIGH && Bstate == HIGH)){ //both beams clear
      state = 0;
    } 
  }
  
  else if (state == 3) {   // WAIT FOR CLEAR
    if (Astate == HIGH && Bstate == HIGH && ((millis() - timeout) >= 500)) {
      state = 0;
      startTime = millis(); //reset timing
    }
  }

  prevAstate = Astate;
  prevBstate = Bstate;

}
