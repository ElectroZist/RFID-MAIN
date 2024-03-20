
////**** PCB RFID UNIVERSAL UNO ****////

#include <EEPROM.h>
#include <rfid.h>


///// RFID /////
RFID rfid;  //create a variable type of RFID
uchar serNum[5]; // array to store your ID
int ser;
int a, b, c, d, e, g;
bool check_rfid = false;

int Out1 = A5;
int buzzer = A4;

int rfidCard1 = 470; //insert value of Tag1
int rfidCard2 = 421; //insert value of Tag2
int rfidCard3 = 496; //insert value of Tag3
int rfidCard4 = 548; //insert value of Tag4


void setup() {

  Serial.begin(115200);

  pinMode(Out1, OUTPUT);
  pinMode(buzzer, OUTPUT);

}

void loop() {

  a = checkRFID(0);
  b = checkRFID(1);
  c = checkRFID(2);
  d = checkRFID(3);

  if (a == rfidCard1 && b == rfidCard2  && c == rfidCard3  && d == rfidCard4 && (check_rfid == false))  {
    Serial.println("correct");
    digitalWrite(Out1, HIGH);
    check_rfid = true;
  } else if (a != rfidCard1 && b != rfidCard2  && c != rfidCard3 && d != rfidCard4 && (check_rfid == true)) {
    digitalWrite(Out1, LOW);
    Serial.println("No Combination");
    check_rfid = false;
  }



  delay(50);
}




int checkRFID(int i) {

  ser = 0;

  if (i == 0) {
    rfid.begin(2, 5, 6, 8, 3, 7);
  }
  if (i == 1) {
    rfid.begin(2, 5, 6, 9, 3, 7);
  }
  if (i == 2) {
    rfid.begin(2, 5, 6, 10, 3, 7);
  }
  if (i == 3) {
    rfid.begin(2, 5, 6, 11, 3, 7);
  }

  delay(150);
  rfid.init();

  uchar status;
  serNum[0] = 0;
  serNum[1] = 0;
  serNum[2] = 0;
  serNum[3] = 0;
  serNum[4] = 0;
  serNum[5] = 0;
  uchar str[MAX_LEN];
  // Search card, return card types
  status = rfid.request(PICC_REQIDL, str);
  if (status != MI_OK)
  {
    return;
  }

  // Show card type
  //rfid.showCardType(str);

  //Prevent conflict, return the 4 bytes Serial number of the card
  status = rfid.anticoll(str);
  if (status == MI_OK)
  {
    memcpy(serNum, str, 5);
  }

  delay(100);

  rfid.halt(); //command the card into sleep mode
  ser = serNum[1] + serNum[3] + serNum[4];
  Serial.print("Sensor No: "); Serial.print(i); Serial.print("  ");
  Serial.print("Card ID: "); Serial.println(ser);
  return ser;

}
