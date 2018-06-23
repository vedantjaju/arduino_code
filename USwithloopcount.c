//loop counter
int loopCount = 0;
int loopCountA =0, loopCountB = 0;
int obsLoopA,obsLoopB;
#define repeat 40

//entry and exit
int net;

//ultrasonic 1 & 2

#define echoPinA 2
#define trigPinA 3
#define echoPinB 4
#define trigPinB 5 
int maxD = 35;
int duA, duB;
int disA,disB;
int trigA = 0, trigB=0;


//smoke
#define smokePin 1
int smoke;
int smokeThres = 400;

//vibration
#define vibraPin 9

//temperature
#define tempPin 0
float temp;

void setup() 
{
  //Serial Communication
  Serial.begin(9600);
  
  //ultrasonic 1 & 2
  pinMode(12, OUTPUT);
  digitalWrite(12,HIGH);
  pinMode(trigPinA, OUTPUT);
  pinMode(echoPinA, INPUT);
  pinMode(trigPinB, OUTPUT);
  pinMode(echoPinB, INPUT);

  //vibration 
  pinMode(vibraPin, INPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  digitalWrite(11,HIGH);
  digitalWrite(10,LOW);

  //temperature
  pinMode(tempPin, INPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  digitalWrite(7,HIGH);
  digitalWrite(6,LOW);

  //smoke
  pinMode(smokePin, INPUT);
  pinMode(8, OUTPUT);
  digitalWrite(8,HIGH);
}

void loop()
{

    trigA = 0, trigB =0;    //trig is never used here

    digitalWrite(trigPinA, LOW);    //US-A is on
    delayMicroseconds(2); 
    digitalWrite(trigPinA, HIGH);
    delayMicroseconds(10); 
    digitalWrite(trigPinA, LOW);
    duA = pulseIn(echoPinA, HIGH);
    disA = duA/58.2;
    Serial.print(disA);   //print distance
    Serial.print(" ");
    
    if(disA <= maxD-5)
    {
      trigA = 1;
      obsLoopA = loopCountA;
    }
    Serial.print(loopCountA);
    Serial.print(" ");
    loopCountA++;

    
    digitalWrite(trigPinB, LOW); 
    delayMicroseconds(2); 
    digitalWrite(trigPinB, HIGH);
    delayMicroseconds(10); 
    digitalWrite(trigPinB, LOW);
    duB = pulseIn(echoPinB, HIGH);
    disB = duB/58.2;
    Serial.print(disB);
    Serial.print(" ");
    
    if(disB < maxD - 5)
    {
      trigB = 1;
      obsLoopB = loopCountB;
    }
    Serial.print(loopCountB);
    Serial.print(" ");
    loopCountB++;


    if(obsLoopA < obsLoopB && obsLoopA!=0)
    {
      Serial.print("en ");
      net++
      obsLoopB = obsLoopA = 0;
    }
    
    else if(obsLoopB < obsLoopA && obsLoopB!= 0)
    {
      Serial.print("ex ");
      net--;
      obsLoopB = obsLoopA = 0;
    }
    
    delay(200);   //insert an appropriate delay betn 2 cycles
    Serial.println(" ");  
}


//limit on loopcount missing
//
