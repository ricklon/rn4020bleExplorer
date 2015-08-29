/*
  chipKIT BLE shield Simlpe serial and echo

*/

#define WAKE_SW 10
#define WAKE_HW 11
#define CMD_MLPD 12
#define MAX_INPUT 200


String inputString = "";
char incomingByte = 0;
String commandString = "";
char cmdByte = 0;

void setup() {
  //wake_sw
  pinMode( WAKE_SW, OUTPUT);
  digitalWrite( WAKE_SW, HIGH);
  //wake_hw
  pinMode(WAKE_HW, OUTPUT);
  digitalWrite(WAKE_HW, HIGH);
  //cmd_mldp
  pinMode(CMD_MLPD, OUTPUT);
  digitalWrite(CMD_MLPD, HIGH);

  delay(800);

  Serial.begin(115200);
  Serial0.begin(115200);


  while (1)
  {
    if (Serial.available() > 0)
    {
      char cc = Serial.read();
      if (cc == 'h' || cc == '?' || cc == '\n' || cc == '\r') {
        Serial.println("Press 's' to start.");
        Serial.println("Sample Commands:");
        Serial.println("'D Dump'");
        Serial.println("'SN,<string> set device name'");
        Serial.println("'LS List Server Services'");
        Serial.println("'LC List Client Services'");
        Serial.println("'M Last Signal Strength'");
        Serial.println("'R,1 Reboot'");
        Serial.println("'1-9 Profile'");
        Serial.println("'V Version'");
        Serial.println("'H Help'");
      }
      if (cc == 's') {
        break;
      }
      if (cc == '1') {
        Serial0.print("+\n");
        delay(500);
        Serial0.print("SF,1\n");
        delay(500);
        Serial0.print("SS,30000000\n");
        delay(500);
        Serial0.print("SR,32000800\n");
        delay(500);
        Serial0.print("SN,HEYBUDDY\n");
        delay(500);
        Serial0.print("SB,4\n");
        delay(500);
        Serial0.print("R,1\n");
        delay(2000);
        break;
      }
      if (cc == '2') {
        Serial0.print("+\n");
        delay(500);
        Serial0.print("SF,1\n");
        delay(500);
        Serial0.print("SS,30000000\n");
        delay(500);
        Serial0.print("SR,32000800\n");
        delay(500);
        Serial0.print("SN,HEYBUDDY\n");
        delay(500);
        Serial0.print("SB,4\n");
        delay(500);
        Serial0.print("R,1\n");
        delay(2000);
        break;
      }
      if (cc == '2') {
        /*cmd: SS,C0000000
        cmd: A
        cmd: R,1
        cmd: D
        cmd: A
        cmd: A
        cmd: LS
        cmd: SHR,0018
        cmd: SHW,0018,64
        cmd: WC,0019,0100. //response?
        cmd: SHW,0018,32
        cmd: SUW,2A19,24
        cmd: |c
        cmd: lc //END
        //checkout command SE security mode
        */

      }
    }
  }
  Serial.println("start");



}

void loop() {
  if (Serial.available() > 0) {
    cmdByte = Serial.read();
    commandString += String(cmdByte);

    if (cmdByte == '\n' || cmdByte == '\r')
    {
      Serial.print("cmd: ");
      Serial.println(commandString);
      Serial0.print(commandString);
      commandString = "";
    }
  }
  //read from ble device blocking or non blocking
  if (Serial0.available() > 0)
  {

    incomingByte = Serial0.read();
    inputString += String(incomingByte);

    if (incomingByte == '\n' || incomingByte == '\r')
    {
      //Serial.print("resp: ");
      Serial.print(inputString);
      inputString = "";
    }
  }

}
