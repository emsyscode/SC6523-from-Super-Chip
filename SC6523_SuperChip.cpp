/*Begining of Auto generated code by Atmel studio */
#define VFD_in 7  // This is the pin number 7 on Arduino UNO
#define VFD_clk 8 // This is the pin number 8 on Arduino UNO
#define VFD_stb 9 // This is the pin number 9 on Arduino UNO
//ATT: On the Uno and other ATMEGA based boards, unsigned ints 
//(unsigned integers) are the same as ints in that they store a 2 byte value.
//Long variables are extended size variables for number storage, and store
// 32 bits (4 bytes), from -2,147,483,648 to 2,147,483,647.
//*************************************************/
void setup() {
  pinMode(VFD_clk, OUTPUT);
  pinMode(VFD_in, OUTPUT);
  pinMode(VFD_stb, OUTPUT);
  
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  digitalWrite(VFD_stb, LOW);
  digitalWrite(13, LOW);
  delay(500);
  digitalWrite(13, HIGH);
  delay(500);
  digitalWrite(13, LOW);
  delay(500);
  digitalWrite(13, HIGH);
  delay(500);
}
/***************************************************************/
void send_char(unsigned char a)
{
 unsigned char transmit = 15; //define our transmit pin
 unsigned char data = 170; //value to transmit, binary 10101010
 unsigned char mask = 1; //our bitmask
  data=a;
  //
  digitalWrite(VFD_stb, LOW); // When strobe is low, all output is enable. If high, all output will be set to low.
  delayMicroseconds(5);
  digitalWrite(VFD_clk,LOW);// need invert the signal to allow 8 bits is is low only send 7 bits
  delayMicroseconds(5);
  for (mask = 00000001; mask>0; mask <<= 1) { //iterate through bit mask
  digitalWrite(VFD_clk,LOW);// need invert the signal to allow 8 bits is is low only send 7 bits
  delayMicroseconds(5);
    if (data & mask){ // if bitwise AND resolves to true
      digitalWrite(VFD_in, HIGH);
      //Serial.print(1);
    }
    else{ //if bitwise and resolves to false
      digitalWrite(VFD_in, LOW);
      //Serial.print(0);
    }
    digitalWrite(VFD_clk,HIGH);// need invert the signal to allow 8 bits is is low only send 7 bits
    delayMicroseconds(5);
    //
    digitalWrite(VFD_stb, HIGH); // When strobe is low, all output is enable. If high, all output will be set to low.
  delayMicroseconds(5);
  }
}
/***************************************************************/
void send_char_without(unsigned char a)
{
 unsigned char transmit = 15; //define our transmit pin
 unsigned char data = 170; //value to transmit, binary 10101010
 unsigned char mask = 1; //our bitmask
  data=a;
  for (mask = 00000001; mask>0; mask <<= 1) { //iterate through bit mask
  digitalWrite(VFD_clk, LOW);
  delayMicroseconds(5);
    if (data & mask){ // if bitwise AND resolves to true
      digitalWrite(VFD_in, HIGH);
      //Serial.print(1);
    }
    else{ //if bitwise and resolves to false
      digitalWrite(VFD_in, LOW);
      //Serial.print(0);
    }
    digitalWrite(VFD_clk,HIGH);// need invert the signal to allow 8 bits is is low only send 7 bits
    delayMicroseconds(5);
  }
}
/***************************************************************/
void send_char_8bit_stb(unsigned char a)
{
 unsigned char transmit = 15; //define our transmit pin
 unsigned char data = 170; //value to transmit, binary 10101010
 unsigned char mask = 1; //our bitmask
 int i = -1;
  data=a;
  //
  for (mask = 00000001; mask>0; mask <<= 1) { //iterate through bit mask
   i++;
   digitalWrite(VFD_clk, LOW);
  delayMicroseconds(5);
    if (data & mask){ // if bitwise AND resolves to true
      digitalWrite(VFD_in, HIGH);
      //Serial.print(1);
    }
    else{ //if bitwise and resolves to false
      digitalWrite(VFD_in, LOW);
      //Serial.print(0);
    }
    digitalWrite(VFD_clk,HIGH);// need invert the signal to allow 8 bits is is low only send 7 bits
    delayMicroseconds(1);
    if (i==7){
    //Serial.println(i); // Only to debug
    digitalWrite(VFD_stb, HIGH);
    delayMicroseconds(2);
    }
     
  }
}
/***************************************************************/
void patternVFD(){
//send total of 156 bits, the 4 last bits belongs to DR, SC, BU, X;
digitalWrite(VFD_stb, LOW); //
delayMicroseconds(2);
send_char_8bit_stb(0B01000001); // firts 8 bits is address, every fixed as (0B010000001), see if clk finish LOW or HIGH Very important!
//
send_char_without(0B01010011);  send_char_without(0B10110100); //  1:8    -9:16// First 14 segments display(Note: skip the 6 & 9)Belongs Second 
send_char_without(0B00000111);  send_char_without(0B11111001); // 17:24  -25:32// Second 14 segments display(Note: skip 25 & 26) Belongs Third 
send_char_without(0B00000010);  send_char_without(0B10101110); // 33:40  -41:48// Third 14 segments display(Note:Skip 40 & 44 the 41,42 & 43) Belongs first 7seg display 
send_char_without(0B00100111);  send_char_without(0B11100110); // 49:56  -57:64  
send_char_without(0B11110001);  send_char_without(0B10011111); // 65:72  -73:80// skip 78    
send_char_without(0B01110011);  send_char_without(0B10111101); // 81:88  -89:96// skip 85
send_char_without(0B11001100);  send_char_without(0B11110110); // 97:104-105:112
send_char_without(0B11101101);  send_char_without(0B00000000); //113:120-121:128
send_char_without(0B00000000);  send_char_without(0B00000000); //129:136-137:144
send_char_without(0B00000000);  send_char_without(0B00000000); //145:152-153:160 // 0B0000xxxx see the bits DR, SC, BU, X(This bits switch on/off and sleep...
delayMicroseconds(2);
digitalWrite(VFD_stb, LOW); // 
delayMicroseconds(2);
}
/***************************************************************/
void allOn(){
//send total of 156 bits, the 4 last bits belongs to DR, SC, BU, X;
digitalWrite(VFD_stb, LOW); //
delayMicroseconds(2);
send_char_8bit_stb(0B01000001); // firts 8 bits is address, every fixed as (0B010000001), see if clk finish LOW or HIGH Very important!
//
send_char_without(0B11111111);  send_char_without(0B11111111);  // Block 0, bit 0:F
send_char_without(0B11111111);  send_char_without(0B11111111);  // Block 1, bit 0:F
send_char_without(0B11111111);  send_char_without(0B11111111);  // Block 2, bit 0:F
send_char_without(0B11111111);  send_char_without(0B11111111);  // Block 3, bit 0:F
send_char_without(0B11111111);  send_char_without(0B11111111);  // Block 4, bit 0:F
send_char_without(0B11111111);  send_char_without(0B11111111);  // Block 5, bit 0:F
send_char_without(0B11111111);  send_char_without(0B11111111);  // Block 6, bit 0:F
send_char_without(0B11111111);  send_char_without(0B11111111);  // Block 7, bit 0:F
send_char_without(0B11111111);  send_char_without(0B11111111);  // Block 8, bit 0:F
send_char_without(0B11111111);  send_char_without(0B00001111);  // Block 9, bit 0:F   //Last four bits is bits of control
delayMicroseconds(2);
digitalWrite(VFD_stb, LOW); // 
delayMicroseconds(2);
}
/***************************************************************/
void allOff(){
//send total of 156 bits, the 4 last bits belongs to DR, SC, BU, X;
digitalWrite(VFD_stb, LOW); //
delayMicroseconds(2);
send_char_8bit_stb(0B01000001); // firts 8 bits is address, every fixed as (0B010000001), see if clk finish LOW or HIGH Very important!
//
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 0, bit 0:F
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 1, bit 0:F
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 2, bit 0:F
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 3, bit 0:F
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 4, bit 0:F
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 5, bit 0:F
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 6, bit 0:F
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 7, bit 0:F
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 8, bit 0:F
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 9, bit 0:F   //Last four bits is bits of control(0bCCCCssss) C= control, s=segments
delayMicroseconds(2);
digitalWrite(VFD_stb, LOW); // 
}
/***************************************************************/
void symbols1(){
//send total of 156 bits, the 4 last bits belongs to DR, SC, BU, X;
digitalWrite(VFD_stb, LOW); //
delayMicroseconds(2);
send_char_8bit_stb(0B01000001); // firts 8 bits is address, every fixed as (0B010000001), see if clk finish LOW or HIGH Very important!
//
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 0, bit 0:F
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 1, bit 0:F
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 2, bit 0:F
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 3, bit 0:F
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 4, bit 0:F
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 5, bit 0:F
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 6, bit 0:F
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 7, bit 0:F
send_char_without(0B01000000);  send_char_without(0B00000000);  // Block 8, bit 0:F
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 9, bit 0:F   //Last four bits is bits of control(0bCCCCssss) C= control, s=segments
delayMicroseconds(2);
digitalWrite(VFD_stb, LOW); // 
}
void symbols2(){
//send total of 156 bits, the 4 last bits belongs to DR, SC, BU, X;
digitalWrite(VFD_stb, LOW); //
delayMicroseconds(2);
send_char_8bit_stb(0B01000001); // firts 8 bits is address, every fixed as (0B010000001), see if clk finish LOW or HIGH Very important!
//
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 0, bit 0:F
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 1, bit 0:F
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 2, bit 0:F
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 3, bit 0:F
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 4, bit 0:F
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 5, bit 0:F
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 6, bit 0:F
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 7, bit 0:F
send_char_without(0B01100000);  send_char_without(0B00000000);  // Block 8, bit 0:F
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 9, bit 0:F   //Last four bits is bits of control(0bCCCCssss) C= control, s=segments
delayMicroseconds(2);
digitalWrite(VFD_stb, LOW); // 
}
void symbols3(){
//send total of 156 bits, the 4 last bits belongs to DR, SC, BU, X;
digitalWrite(VFD_stb, LOW); //
delayMicroseconds(2);
send_char_8bit_stb(0B01000001); // firts 8 bits is address, every fixed as (0B010000001), see if clk finish LOW or HIGH Very important!
//
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 0, bit 0:F
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 1, bit 0:F
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 2, bit 0:F
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 3, bit 0:F
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 4, bit 0:F
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 5, bit 0:F
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 6, bit 0:F
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 7, bit 0:F
send_char_without(0B01110000);  send_char_without(0B00000000);  // Block 8, bit 0:F
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 9, bit 0:F   //Last four bits is bits of control(0bCCCCssss) C= control, s=segments
delayMicroseconds(2);
digitalWrite(VFD_stb, LOW); // 
}
void symbols4(){
//send total of 156 bits, the 4 last bits belongs to DR, SC, BU, X;
digitalWrite(VFD_stb, LOW); //
delayMicroseconds(2);
send_char_8bit_stb(0B01000001); // firts 8 bits is address, every fixed as (0B010000001), see if clk finish LOW or HIGH Very important!
//
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 0, bit 0:F
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 1, bit 0:F
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 2, bit 0:F
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 3, bit 0:F
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 4, bit 0:F
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 5, bit 0:F
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 6, bit 0:F
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 7, bit 0:F
send_char_without(0B01111000);  send_char_without(0B00000000);  // Block 8, bit 0:F
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 9, bit 0:F   //Last four bits is bits of control(0bCCCCssss) C= control, s=segments
delayMicroseconds(2);
digitalWrite(VFD_stb, LOW); // 
}
void symbols5(){
//send total of 156 bits, the 4 last bits belongs to DR, SC, BU, X;
digitalWrite(VFD_stb, LOW); //
delayMicroseconds(2);
send_char_8bit_stb(0B01000001); // firts 8 bits is address, every fixed as (0B010000001), see if clk finish LOW or HIGH Very important!
//
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 0, bit 0:F
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 1, bit 0:F
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 2, bit 0:F
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 3, bit 0:F
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 4, bit 0:F
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 5, bit 0:F
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 6, bit 0:F
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 7, bit 0:F
send_char_without(0B01111100);  send_char_without(0B00000000);  // Block 8, bit 0:F
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 9, bit 0:F   //Last four bits is bits of control(0bCCCCssss) C= control, s=segments
delayMicroseconds(2);
digitalWrite(VFD_stb, LOW); // 
}
void symbols6(){
//send total of 156 bits, the 4 last bits belongs to DR, SC, BU, X;
digitalWrite(VFD_stb, LOW); //
delayMicroseconds(2);
send_char_8bit_stb(0B01000001); // firts 8 bits is address, every fixed as (0B010000001), see if clk finish LOW or HIGH Very important!
//
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 0, bit 0:F
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 1, bit 0:F
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 2, bit 0:F
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 3, bit 0:F
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 4, bit 0:F
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 5, bit 0:F
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 6, bit 0:F
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 7, bit 0:F
send_char_without(0B01111110);  send_char_without(0B00000000);  // Block 8, bit 0:F
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 9, bit 0:F   //Last four bits is bits of control(0bCCCCssss) C= control, s=segments
delayMicroseconds(2);
digitalWrite(VFD_stb, LOW); // 
}
/***************************************************************/
void symbols_sample(void){
  // This code replace the symbols6! I've write it to show how is possible simplify the code
  // The range of bits is 20*16 total send, because I only change the byte 16(symbols zone)
  // I'm controle with a IF and send it case is 16 byte.
  //send total of 156 bits, the 4 last bits belongs to DR, SC, BU, X;
digitalWrite(VFD_stb, LOW); //
delayMicroseconds(2);
send_char_8bit_stb(0B01000001); // firts 8 bits is address, every fixed as (0B010000001), see if clk finish LOW or HIGH Very important!
//
  for (int v=0; v<21; v++){
    send_char_without(0x00);
    if (v==17){  // important if put "=" only, run here every time, don't make confusion with precedence signals!!!
      send_char_without(0b01111110);
      //Serial.println(0x7E, BIN); // Only to debut
    }
    //Serial.println(v, DEC); // Only to debug
  }
  delayMicroseconds(2);
digitalWrite(VFD_stb, LOW); // 
}
/*****************************************************************/
void hiFolks(void){
//send total of 156 bits, the 4 last bits belongs to DR, SC, BU, X;
digitalWrite(VFD_stb, LOW); //
delayMicroseconds(2);
send_char_8bit_stb(0B01000001); // firts 8 bits is address, every fixed as (0B010000001), see if clk finish LOW or HIGH Very important!
send_char_without(0B00100110);  send_char_without(0B01101000);  // Block 0, bit 0:F
send_char_without(0B00000011);  send_char_without(0B00000000);  // Block 1, bit 0:F
send_char_without(0B00000000);  send_char_without(0B11000000);  // Block 2, bit 0:F
send_char_without(0B00010100);  send_char_without(0B01100001);  // Block 3, bit 0:F
send_char_without(0B00001100);  send_char_without(0B00110110);  // Block 4, bit 0:F
send_char_without(0B00000010);  send_char_without(0B10011000);  // Block 5, bit 0:F
send_char_without(0B00011000);  send_char_without(0B11000100);  // Block 6, bit 0:F
send_char_without(0B10010001);  send_char_without(0B00000000);  // Block 7, bit 0:F
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 8, bit 0:F
send_char_without(0B00000000);  send_char_without(0B00000000);  // Block 9, bit 0:F   //Last four bits is bits of control(0bCCCCssss) C= control, s=segments
delayMicroseconds(2);
digitalWrite(VFD_stb, LOW); // 
}
/*****************************************************************/
void loop() {
      for (int i=0; i< 4; i++){
        allOn();
        delay(500);
        allOff();
        delay(500);
      }
    symbols1();
  delay(300);
   symbols2();
  delay(300);
   symbols3();
  delay(300);
   symbols4();
  delay(300);
   symbols5();
  delay(300);
  // symbols6();
  //delay(300);
  symbols_sample();  // this replace the function "symbols6" as a example of how is possible simplify code.
  delay(300);
  hiFolks();
  delay(3000);
}
