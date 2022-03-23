#include "Arduino.h"
#include "Xbee3-Arduino.h"

void AtCmds::broadcastAT(char par1, char par2, char value)
{
  Serial.write(0x7E);         //start byte
  Serial.write((byte)0x0);    //length msb
  Serial.write(0x10);         //length lsb
  Serial.write(0x17);         //command
  Serial.write((byte)0x01);   //idk
  Serial.write((byte)0x00);   //add64 start
  Serial.write((byte)0x00);
  Serial.write((byte)0x00);
  Serial.write((byte)0x00);
  Serial.write((byte)0x00);
  Serial.write((byte)0x00);
  Serial.write(0xFF);
  Serial.write(0xFF);         //add64 end : 000000000000FFFF= broadcast, zeros= to coordinator, F's= unknown 64-bit address
  Serial.write(0xFF);         //add16 msb
  Serial.write(0xFE);         //add16 lsb: 0000= to coordinator, FFFE=unknown 16-bit address, FFFF= broadcast (I think)
  Serial.write(0x02);
  Serial.write(par1);         //parameters you would like to query/ change
  Serial.write(par2);
  Serial.write(value);        //the value you want to assign to these paramters 
  long check=0x17 + 0x01 + 0xFF + 0xFF + 0xFF + 0xFE + 0x02 + par1 + par2 + value;
  Serial.write(0xFF-(check&0xFF));
}

void AtCmds::apiToAddr(char par1, char par2, char value, byte msb, byte lsb)
{
  Serial.write(0x7E);         //start byte
  Serial.write((byte)0x0);    //length msb
  Serial.write(0x10);         //length lsb
  Serial.write(0x17);         //command
  Serial.write((byte)0x01);   //idk
  
  Serial.write(0xFF);   //add64 start
  Serial.write(0xFF);   //set to FF...FF to use 16 bit addressing
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.write(0xFF);
  //add64 end : 000000000000FFFF= broadcast, zeros= to coordinator, F's= unknown 64-bit address
  Serial.write(msb);         //add16 msb
  Serial.write(lsb);         //add16 lsb: 0000= to coordinator, FFFE=unknown 16-bit address, FFFF= broadcast (I think)
  Serial.write(0x02);         //options, set to 0x02 to apply changes
  Serial.write(par1);         //parameters you would like to query/ change
  Serial.write(par2);
  Serial.write(value);        //the value you want to assign to these paramters 
  long check=0x17 + 0x01 + msb + lsb + 0x02 + par1 + par2 + 2040 + value;
  Serial.write(0xFF-(check&0xFF));
}

void AtCmds::apiToAddr(char par1, char par2, byte msb, byte lsb, byte lenHigh, byte lenLow)
{
  Serial.write(0x7E);         //start byte
  Serial.write(lenHigh);    //length msb
  Serial.write(lenLow);         //length lsb
  Serial.write(0x17);         //command
  Serial.write((byte)0x01);  
  
  Serial.write(0xFF);   //add64 start
  Serial.write(0xFF);   //set to FF...FF to use 16 bit addressing
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.write(0xFF);
  //add64 end : 000000000000FFFF= broadcast, zeros= to coordinator, F's= unknown 64-bit address
  Serial.write(msb);         //add16 msb
  Serial.write(lsb);         //add16 lsb: 0000= to coordinator, FFFE=unknown 16-bit address, FFFF= broadcast (I think)
  Serial.write(0x02);         //options, set to 0x02 to apply changes
  Serial.write(par1);         //parameters you would like to query/ change
  Serial.write(par2);
  long check=0x17 + 0x01 + msb + lsb + 0x02 + par1 + par2 + 2040;
  Serial.write(0xFF-(check&0xFF));
}

void AtCmds::apiToAddr64(char par1, char par2, long ms32, long ls32, byte lenHigh, byte lenLow)
{
  byte m1 = (ms32 >> 24)& 0xFF;
  byte m2 = (ms32 >> 16)& 0xFF;
  byte m3 = (ms32 >> 8)& 0xFF;
  byte m4 = (ms32)& 0xFF;
  
  byte l1 = (ls32 >> 24)& 0xFF;
  byte l2 = (ls32 >> 16)& 0xFF;
  byte l3 = (ls32 >> 8)& 0xFF;
  byte l4 = (ls32)& 0xFF;
  long check=0x17 + 0x01 + m1+m2+m3+m4+l1+l2+l3+l4 + 0x02 + par1 + par2 + 0xFF + 0xFE;
  Serial.write(0x7E);         //start byte
  Serial.write(lenHigh);    //length msb
  Serial.write(lenLow);         //length lsb
  Serial.write(0x17);         //command
  Serial.write(0x01);  
  
  Serial.write(m1);   //add64 start
  Serial.write(m2);   //set to FF...FF to use 16 bit addressing
  Serial.write(m3);
  Serial.write(m4);
  Serial.write(l1);
  Serial.write(l2);
  Serial.write(l3);
  Serial.write(l4);
  
  //add64 end : 000000000000FFFF= broadcast, zeros= to coordinator, F's= unknown 64-bit address
  Serial.write(0xFF);         //add16 msb
  Serial.write(0xFE);         //add16 lsb: 0000= to coordinator, FFFE=unknown 16-bit address, FFFF= broadcast (I think)
  Serial.write(0x02);         //options, set to 0x02 to apply changes
  Serial.write(par1);         //parameters you would like to query/ change
  Serial.write(par2);
  
  Serial.write(0xFF-(check&0xFF));
}

void AtCmds::apiToAddr64(char par1, char par2, long ms32, long ls32, byte lenHigh, byte lenLow, char value)
{
  byte m1 = (ms32 >> 24)& 0xFF;
  byte m2 = (ms32 >> 16)& 0xFF;
  byte m3 = (ms32 >> 8)& 0xFF;
  byte m4 = (ms32)& 0xFF;
  
  byte l1 = (ls32 >> 24)& 0xFF;
  byte l2 = (ls32 >> 16)& 0xFF;
  byte l3 = (ls32 >> 8)& 0xFF;
  byte l4 = (ls32)& 0xFF;
  long check=0x17 + 0x01 + m1+m2+m3+m4+l1+l2+l3+l4 + 0x02 + par1 + par2 + 0xFF + 0xFE + value;
  Serial.write(0x7E);         //start byte
  Serial.write(lenHigh);    //length msb
  Serial.write(lenLow);         //length lsb
  Serial.write(0x17);         //command
  Serial.write(0x01);  
  
  Serial.write(m1);   //add64 start
  Serial.write(m2);   //set to FF...FF to use 16 bit addressing
  Serial.write(m3);
  Serial.write(m4);
  Serial.write(l1);
  Serial.write(l2);
  Serial.write(l3);
  Serial.write(l4);
  
  //add64 end : 000000000000FFFF= broadcast, zeros= to coordinator, F's= unknown 64-bit address
  Serial.write(0xFF);         //add16 msb
  Serial.write(0xFE);         //add16 lsb: 0000= to coordinator, FFFE=unknown 16-bit address, FFFF= broadcast (I think)
  Serial.write(0x02);         //options, set to 0x02 to apply changes
  Serial.write(par1);         //parameters you would like to query/ change
  Serial.write(par2);
  Serial.write(value);
  
  Serial.write(0xFF-(check&0xFF));
  Serial.println("sending packet with checksum");
  Serial.println(0xFF-(check&0xFF));
}

void AtCmds::discovery()
{
  Serial.write(0x7E);         
  Serial.write((byte)0x0);    
  Serial.write(0x04);         
  Serial.write(0x08); 
  Serial.write(0x01); 
  Serial.write(0x6E);
  Serial.write(0x64);
  Serial.write(0x24);
}

void AtCmds::transmitCoordinator(short len, char payload[]) //needs overloaded version that takes a string
{
  long check=0;
  byte lenhigh = (len>>8) & 0xFF;
  byte lenlow = len & 0xFF;
  check+=0x10;
  check+=0xFF;
  check+=0xFE;
  Serial.write(0x7E);               //start byte
  Serial.write(lenhigh);            //length msb
  Serial.write(lenlow);             //length lsb
  Serial.write(0x10);               //command
  Serial.write((byte)0x00);         //frame id, set to zero to request no response
  Serial.write((byte)0x00);         //add64 start
  Serial.write((byte)0x00);
  Serial.write((byte)0x00);
  Serial.write((byte)0x00);
  Serial.write((byte)0x00);
  Serial.write((byte)0x00);
  Serial.write((byte)0x00);
  Serial.write((byte)0x00);         //add64 end : 000000000000FFFF= broadcast, zeros= to coordinator, F's= unknown 64-bit address
  Serial.write((byte)0xFF);         //add16 msb
  Serial.write((byte)0xFE);         //add16 lsb: 0000= to coordinator, FFFE=unknown 16-bit address, FFFF= broadcast (I think)
  Serial.write((byte)0x00);         //number of hops, when set to zero it defaults to maximum amount
  Serial.write((byte)0x00);         //options
  //payload goes here
  int payloadlen = strlen(payload);
  for(int i=0;i<payloadlen;i++){
    Serial.write((byte)payload[i]);
    check+=payload[i];
  }
  check = 0xFF-(check&0xFF);
  Serial.write(check);
}
