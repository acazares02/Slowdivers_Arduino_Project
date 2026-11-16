const int NUM_PADS = 1;


//copper tape pins defined
const int tapePins[NUM_PADS]  = {2, 3, 4, 5};


// servo signal pins defined
const int servoPins[NUM_PADS] = {9, 10, 11, 6};






const int REST_ANGLE   = 0;   // where the servo sits normally
const int ACTIVE_ANGLE = 90;  // where it goes when its pad is bridged


//!!may need to fix angles to align better w whats needed for project, may need to write 4 separate lines. check back w this!! 
//—---------------------------------------------------------------------------
Servo servos[NUM_PADS];


int lastState[NUM_PADS];      // each pad state change to trigger next
//—---------------------------------------------------------------------------


void setup() {
 Serial.begin(9600);




 for (int i = 0; i < NUM_PADS; i++) {
   // INPUT_PULLUP: high normally, low w gnd.
 
   pinMode(tapePins[i], INPUT_PULLUP);


   servos[i].attach(servoPins[i]);
   servos[i].write(REST_ANGLE);


   lastState[i] = HIGH;      // starts no bridge
 }


 Serial.println("trigged!");
}
//—---------------------------------------------------------------------------


void loop() {
 for (int i = 0; i < NUM_PADS; i++) {
   int currentState = digitalRead(tapePins[i]);


   // state change detection
   if (currentState != lastState[i]) {


     if (currentState == LOW) {
       // pad was bridged
       Serial.print("Pad ");
       Serial.print(i + 1);
       Serial.println(" bridged -> servo moves");
       servos[i].write(ACTIVE_ANGLE);
     } else {
       // bridge was removed
       Serial.print("Pad ");
       Serial.print(i + 1);
       Serial.println(" released -> servo returns");
       servos[i].write(REST_ANGLE);
     }
   }


   lastState[i] = currentState;
 }


 delay(10); 
}
