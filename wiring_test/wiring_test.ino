void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(4, INPUT);
}

void loop() {
  Serial.print(digitalRead(2));
  Serial.print(", ");
  Serial.println(digitalRead(4));
}
