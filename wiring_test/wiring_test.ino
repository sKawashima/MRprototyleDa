void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(4, INPUT);
  pinMode(7, INPUT);
}

void loop() {
//  Serial.print(digitalRead(2));
//  Serial.print(", ");
//  Serial.print(digitalRead(4));
//  Serial.print(", ");
//  Serial.print(digitalRead(7));
//  Serial.print(", ");
//  Serial.print(analogRead(0));
//  Serial.print(", ");
//  Serial.print(analogRead(1));
//  Serial.print(", ");
//  Serial.print(analogRead(2));
//  Serial.print(", ");
  Serial.print(analogRead(3));
//  Serial.print(", ");
//  Serial.print(analogRead(4));
  Serial.print("\n");
}
