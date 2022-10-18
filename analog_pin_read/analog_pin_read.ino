void setup() {
  Serial.begin(9600);
  analogReference(DEFAULT);

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);

  Serial.println("A0 A1  A2  A3"); //15 tussen min en max
}

void loop() {
  Serial.print(analogRead(A0));
  Serial.print("\t");
  Serial.print(analogRead(A1));
  Serial.print("\t");
  Serial.print(analogRead(A2));
  Serial.print("\t");
  Serial.println(analogRead(A3));

  delay(50);
}//
/*

*/
