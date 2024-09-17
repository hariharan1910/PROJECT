#define Sober 150 
#define Drunk 400
#define MQ3 0
#define USE_ARDUINO_INTERRUPTS true    
#include <PulseSensorPlayground.h>  

const int PulseWire = 1;        
int Threshold = 550;     
PulseSensorPlayground pulseSensor;  // Creates an instance of the PulseSensorPlayground object called "pulseSensor"




int i1 = 2;
int i2 = 3;
int i3 = 4;
int i4 = 5 ;
int bpmled = 6;
int bpm = 7;
int alc = 9;
int buzzer = 10;



void motor(int mode){
  if(mode == 1){
    digitalWrite(i1, HIGH);
    digitalWrite(i3, HIGH);
    digitalWrite(i2,LOW);
    digitalWrite(i4, LOW);
  }else{
    digitalWrite(i1, LOW);
    digitalWrite(i3, LOW);
    digitalWrite(i2,LOW);
    digitalWrite(i4, LOW);
  }
}


int getbpm(){
    int myBPM = pulseSensor.getBeatsPerMinute();  
    if (pulseSensor.sawStartOfBeat()) {            
      Serial.println("♥  A HeartBeat Happened ! ");
      Serial.print("BPM: ");                        
      Serial.println(myBPM);                      
    }

    return myBPM;
}

int getalc(){
  int alc_val = analogRead(MQ3); 
  Serial.print("MQ3 Value: ");
  Serial.println(alc_val);

  return alc_val;
}


void setup() {
  // put your setup code here, to run once:
  pinMode(i1, OUTPUT);
  pinMode(i2, OUTPUT);
  pinMode(i3, OUTPUT);
  pinMode(i4, OUTPUT);

  pinMode(bpmled, OUTPUT);
  pinMode(bpm, OUTPUT);
  pinMode(alc, OUTPUT);
  pinMode(buzzer, OUTPUT);

  Serial.begin(115200);
  pulseSensor.analogInput(PulseWire);   
  pulseSensor.blinkOnPulse(bpmled);       //auto-magically blink Arduino's LED with heartbeat.
  pulseSensor.setThreshold(Threshold); 

  if (pulseSensor.begin()) {
    Serial.println("We created a pulseSensor Object !");  //This prints one time at Arduino power-up,  or on Arduino reset.  
  }


}

void loop() {

  int bp = getbpm();
  int al = getalc();

  if (bp > 100){
    digitalWrite(bpm, HIGH);
  }else{
    digitalWrite(bpm, LOW);
  }

  if (al > 600){
    digitalWrite(alc, HIGH);
  }else{
    digitalWrite(alc, LOW);
 }

 if (bp > 100 && al > 600){
    digitalWrite(buzzer, HIGH);
    motor(0);
 }else{
  digitalWrite(buzzer, LOW);
    motor(1);

 }

  delay(100);

}
