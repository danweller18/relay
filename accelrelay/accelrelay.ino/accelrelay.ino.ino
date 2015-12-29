//accelerometer with relay
//based on (330 mV/G × (1023 ADC units) / 3.3 V) = 102.3 (ADC units)/G

//set vars
#define RELAY 2
#define ACCEL 3
const int xpin = A0;
const int ypin = A1;
const int zpin = A2;
int sampleDelay = 500;
int relayStatus = 0;

void setup() {
  // initialize the serial communications:
  Serial.begin(9600);

  //Make sure the analog-to-digital converter from the AREF pin
  analogReference(EXTERNAL);

  //set pins
  pinMode(xpin, INPUT);
  pinMode(ypin, INPUT);
  pinMode(zpin, INPUT);
  //set relay + accelerometer pins
  pinMode(RELAY, OUTPUT);
  pinMode(ACCEL, OUTPUT);
  //set state- relay+accel
  digitalWrite(ACCEL, HIGH); 
  digitalWrite(RELAY, LOW);
}

void loop() {
  //read status of relay
  relayStatus = digitalRead(RELAY); 
  if (relayStatus == LOW) {
    //declare scoped variables
    
    //zero_G is the reading we expect from the sensor when it detects
    //no acceleration.  Subtract this value from the sensor reading to
    //get a shifted sensor reading.
    float zero_G = 512.0; 
    
    //scale is the number of units we expect the sensor reading to
    //change when the acceleration along an axis changes by 1G.
    //Divide the shifted sensor reading by scale to get acceleration in Gs.
    float scale = 102.3;
  
    //variables round 1 to compare
    float xbase = analogRead(xpin);
    delay(1); 
    float ybase = analogRead(ypin);
    delay(1); 
    float zbase = analogRead(zpin);
  
    //convert to g
    xbase = (xbase - zero_G)/scale;
    ybase = (ybase - zero_G)/scale;
    zbase = (zbase - zero_G)/scale;
  
    //print round one
    Serial.print("xbase: ");
    Serial.print(xbase);
    Serial.print("\t");
    Serial.print("ybase: ");
    Serial.print(ybase);
    Serial.print("\t");
    Serial.print("zbase: ");
    Serial.print(zbase);
    Serial.print("\n");
    
    // delay before next reading:
    delay(sampleDelay);
    
    //read changing values
    float x2 = analogRead(xpin);
    delay(1); 
    float y2 = analogRead(ypin);
    delay(1); 
    float z2 = analogRead(zpin);

    //convert to g
    float x2axis = (x2 - zero_G)/scale;
    float y2axis = (y2 - zero_G)/scale;
    float z2axis = (z2 - zero_G)/scale;

    //round 2
    Serial.print("x2base: ");
    Serial.print(x2axis);
    Serial.print("\t");
    Serial.print("y2base: ");
    Serial.print(y2axis);
    Serial.print("\t");
    Serial.print("z2base: ");
    Serial.print(z2axis);
    Serial.print("\n");
  
    //set abs contstant values
    float absc = fabs(0.00);
    Serial.print("absc: ");
    Serial.print(absc);
    Serial.print("\n");
    
    //set abs X values
    float absx2 = fabs(x2axis);
    Serial.print("absx2: ");
    Serial.print(absx2);
    Serial.print("\t");
    float absxb = fabs(xbase);
    Serial.print("absxb: ");
    Serial.print(absxb);
    Serial.print("\n");
  
    //set abs Y values
    float absy2 = fabs(y2axis);
    Serial.print("absy2: ");
    Serial.print(absy2);
    Serial.print("\t");
    float absyb = fabs(ybase);
    Serial.print("absyb: ");
    Serial.print(absyb);
    Serial.print("\n");
  
    //set abs Z values
    float absz2 = fabs(z2axis);
    Serial.print("absz2: ");
    Serial.print(absz2);
    Serial.print("\t");
    float abszb = fabs(zbase);
    Serial.print("abszb: ");
    Serial.print(abszb);
    Serial.print("\n\n");
  
    //if they stop moving- stop
    if ((absx2 - absxb) == absc && (absy2 - absyb) == absc && (absz2 - abszb) == absc) {
      //turn relay off
      digitalWrite(RELAY, HIGH);
      Serial.print("\noff\n");
    }
    
    // delay before next reading:
    delay(sampleDelay); 
  }
}
