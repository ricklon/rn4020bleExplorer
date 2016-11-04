/*
  chipKIT BLE shield Simlpe serial and echo

*/

#define WAKE_SW 8
//#define WAKE_HW 11
//#define CMD_MLPD 12
#define MAX_INPUT 200
#define SERIAL_BRD Serial
#define SERIAL_BLE Serial1

bool ble = false;

String inputString = "";
char incomingByte = 0;
String commandString = "";
char cmdByte = 0;

void setup() {
  //wake_sw
  pinMode( WAKE_SW, OUTPUT);
  digitalWrite( WAKE_SW, HIGH);
  /*
  //wake_hw
  pinMode(WAKE_HW, OUTPUT);
  digitalWrite(WAKE_HW, HIGH);
  //cmd_mldp
  pinMode(CMD_MLPD, OUTPUT);
  digitalWrite(CMD_MLPD, HIGH);
*/

  delay(800);

  SERIAL_BRD.begin(115200);
  SERIAL_BLE.begin(115200);


  while (1)
  {
    if (SERIAL_BRD.available() > 0)
    {
      char cc = SERIAL_BRD.read();
      if (cc == 'h' || cc == '?' || cc == '\n' || cc == '\r') {
        SERIAL_BRD.println("Press 's' to start.");
        SERIAL_BRD.println("Sample Commands:");
        SERIAL_BRD.println("'D Dump'");
        SERIAL_BRD.println("'SN,<string> set device name'");
        SERIAL_BRD.println("'LS List Server Services'");
        SERIAL_BRD.println("'LC List Client Services'");
        SERIAL_BRD.println("'M Last Signal Strength'");
        SERIAL_BRD.println("'R,1 Reboot'");
        SERIAL_BRD.println("'1-9 Profile'");
        SERIAL_BRD.println("'V Version'");
        SERIAL_BRD.println("'H Help'");
      }
      if (cc == 's') {
        break;
      }
      if (cc == '1') {
        SERIAL_BLE.print("+\n");
        delay(500);
        SERIAL_BLE.print("SF,1\n");
        delay(500);
        SERIAL_BLE.print("SS,30000000\n");
        delay(500);
        SERIAL_BLE.print("SR,32000800\n");
        delay(500);
        SERIAL_BLE.print("SN,HEYBUDDY\n");
        delay(500);
        SERIAL_BLE.print("SB,4\n");
        delay(500);
        SERIAL_BLE.print("R,1\n");
        delay(2000);
        break;
      }
      if (cc == '2') {
        SERIAL_BLE.print("+\n");
        delay(500);
        SERIAL_BLE.print("SF,1\n");
        delay(500);
        SERIAL_BLE.print("SS,30000000\n");
        delay(500);
        SERIAL_BLE.print("SR,32000800\n");
        delay(500);
        SERIAL_BLE.print("SN,HEYBUDDY\n");
        delay(500);
        SERIAL_BLE.print("SB,4\n");
        delay(500);
        SERIAL_BLE.print("R,1\n");
        delay(2000);
        break;
      }
      if (cc == '3') {
        enableBLE();
        delay(110);
        SERIAL_BLE.print("$$$"); //get command prompt
        delay(110);
      
        SERIAL_BRD.println("SF,1\r"); //factory reset
        SERIAL_BLE.print("SF,1\r"); //factory reset
        delay(1000);

        SERIAL_BLE.print("$$$"); //get command prompt
        delay(500);

        SERIAL_BRD.println("SS,C0\r");
        SERIAL_BLE.print("SS,C0\r");
        delay(500);
       
        SERIAL_BRD.println("S-,BLEBlaster\r"); //set bluetooth name
        SERIAL_BLE.print("S-,BLEBlaster\r"); //set bluetooth name
        delay(500);

        SERIAL_BRD.println("SR,00A0\r"); //A0 0x2000 + 0x8000
        SERIAL_BLE.print("SR,00A0\r"); //A0 0x2000 + 0x8000
        delay(500);
      
        SERIAL_BRD.println("R,1\r");
        SERIAL_BLE.print("R,1\r");
        delay(500);
        break;
      }
    }
  }
  SERIAL_BRD.println("start");
}

void loop() {
  if (SERIAL_BRD.available() > 0) {
    cmdByte = SERIAL_BRD.read();
    commandString += String(cmdByte);

    if (cmdByte == '\n' || cmdByte == '\r')
    {
      SERIAL_BRD.print("cmd: ");
      SERIAL_BRD.println(commandString);
      SERIAL_BLE.print(commandString);
      commandString = "";
    }
  }
  //read from ble device blocking or non blocking
  if (SERIAL_BLE.available() > 0)
  {

    incomingByte = SERIAL_BLE.read();
    inputString += String(incomingByte);

    if (incomingByte == '\n' || incomingByte == '\r')
    {
      //SERIAL_BRD.print("resp: ");
      SERIAL_BRD.print(inputString);
      inputString = "";
    }
  }

}

void enableBLE() {
  digitalWrite(WAKE_SW, LOW);
  //SERIAL_BLE.begin(115200);
  ble = true;
}
