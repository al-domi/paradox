int var = 11;
int sendOut [9] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; // pin that is updated
bool xTrue = true;

void setup() {
  Serial.begin(9600);

  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
}

void loop() {
  for (int i = 3; i < 12; i++) {
    int x = digitalRead(i);
    
    if (x == 0) {
      if (sendOut[i-3] == 0) {
        if (xTrue == true) {
          sendOut[i-3] = 1;
          xTrue = false;
        } else {
          sendOut[i-3] = 2;
          xTrue = true;
        }
      }
    }
  }

  int array[9] = {sendOut[0], sendOut[1], sendOut[2], sendOut[3], sendOut[4], sendOut[5], sendOut[6], sendOut[7], sendOut[8]};
  int total = 0;

  for(int i = 8; i >= 0; --i) {
    int exponent = pow(3, (8 - i));
    if (exponent % 2 == 0) {
      exponent = exponent + 1;
    }
    int add = array[i] * exponent;
    
    //Serial.println(exponent);
    total = total + add;

  }
  
  Serial.println(total);

  delay(500);
}
