#ifndef Xbee3-Arduino_h
#define Xbee3-Arduino_h

#include "Arduino.h"

class AtCmds
{
    public:
        void broadcastAT(char par1, char par2, char value);
        void apiToAddr(char par1, char par2, char value, byte msb, byte lsb);
        void apiToAddr(char par1, char par2, byte msb, byte lsb, byte lenHigh, byte lenLow);
        void apiToAddr64(char par1, char par2, long ms32, long ls32, byte lenHigh, byte lenLow);
        void apiToAddr64(char par1, char par2, long ms32, long ls32, byte lenHigh, byte lenLow, char value);
        void discovery();
        void transmitCoordinator(short len, char payload[]);
};



#endif