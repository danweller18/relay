#define RELAY 2
#define LED 3

void setup() {
  pinMode(RELAY, OUTPUT);
  pinMode(LED, OUTPUT);
  
  digitalWrite(LED, HIGH); 
  digitalWrite(RELAY, LOW);
  delay(2000);
}

void loop() {
  digitalWrite(RELAY, LOW);
  delay(1000);
  digitalWrite(RELAY, HIGH); 
  delay(1000);
}
