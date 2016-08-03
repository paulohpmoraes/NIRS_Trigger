// NIRx Trigger Interface
// Sends trigger signals to NIRx NIRScout 1624 parallel port
//   through USB ports

// NIRx NIRScout 1624 specifications
// Minimum pulse duration: at least 10 ms.
// Maximum pulse duration: no restriction.
// Minimum inteval between triggers: 100 ms.

int pins[4] = {2, 3, 4, 5};
int buttons[2] = {6, 7};
int bits[16][4] = { {HIGH, HIGH, HIGH, HIGH},
                    { LOW, HIGH, HIGH, HIGH},
                    {HIGH,  LOW, HIGH, HIGH},
                    { LOW,  LOW, HIGH, HIGH},
                    {HIGH, HIGH,  LOW, HIGH},
                    { LOW, HIGH,  LOW, HIGH},
                    {HIGH,  LOW,  LOW, HIGH},
                    { LOW,  LOW,  LOW, HIGH},
                    {HIGH, HIGH, HIGH,  LOW},
                    { LOW, HIGH, HIGH,  LOW},
                    {HIGH,  LOW, HIGH,  LOW},
                    { LOW,  LOW, HIGH,  LOW},
                    {HIGH, HIGH,  LOW,  LOW},
                    { LOW, HIGH,  LOW,  LOW},
                    {HIGH,  LOW,  LOW,  LOW},
                    { LOW,  LOW,  LOW,  LOW} };
                    
#define PULSE 15   // Trigger duration (ms)
#define WAIT 110   // Interval between triggers (ms)

int trig;

void trigger(int t) {
  int i;
  digitalWrite(LED_BUILTIN, LOW);
  for (i = 0; i < 4; i++) {
    digitalWrite(pins[i],bits[t][i]);
  }
  delay(PULSE);
  for (i = 0; i < 4; i++) {
    digitalWrite(pins[i],bits[0][i]);
  }
  delay(WAIT);
  digitalWrite(LED_BUILTIN, HIGH);
}

void setup() {
  int i;
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  for (i = 0; i < 4; i++) {
    pinMode(pins[i], OUTPUT);
  }
  for (i = 0; i < 2; i++) {
    pinMode(buttons[i], INPUT_PULLUP);
  }
  trigger(0);
  Serial.begin(9600, SERIAL_8N1);  // opens serial port at 9600 8n1
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
  if(Serial.available() == 1) {
    trig = int(Serial.read());
    if((trig > 48) && (trig < 58)) { // '1' to '9'
       trigger(trig - 48); 
    }
    if((trig > 64) && (trig < 71)) { // 'A' to 'F'
       trigger(trig - 55);
    }
  }
  if(digitalRead(buttons[0]) == LOW) {
    trigger(1);
  }
  if(digitalRead(buttons[1]) == LOW) {
    trigger(2);
  }
}
