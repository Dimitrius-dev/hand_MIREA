int fingers[2];
uint8_t pinFingers[] = {//pins
  //FOR FINGERS: from thumb to pinky
  //RIGHT HAND:
  14,//A0
  15 //A1
  //LEFT HAND:
};

void setup() {
  Serial.begin(9600);
  for(int i = 0;i<2;i++){
    pinMode(pinFingers[i], INPUT);
  }
}

void loop() {
  /*
  Serial.print("s1 = ");
  Serial.print(analogRead(pinFingers[0]));
  Serial.print(" s2 = ");
  Serial.print(analogRead(pinFingers[1]));
  Serial.println("");
  */
  
  if(Serial.available()>0){
    char a = Serial.read();
    if(a == 'a'){

      Serial.print("s");//start
      for(int i = 0;i<2;i++){
        fingers[i] = analogRead(pinFingers[i]);
        Serial.print("b");//before
        Serial.print(fingers[i]);
        Serial.print("a");//after
      }
      Serial.print("e");//end
    }
  }
  
}
