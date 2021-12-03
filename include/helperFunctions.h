#pragma once 

// Comment next line if you want to disable debug printing
#define DEBUG

#ifdef DEBUG
#define DEBUG_PRINTLN(x)  Serial.println (x)
#define DEBUG_PRINT(x)  Serial.print (x)
#else
#define DEBUG_PRINTLN(x)
#define DEBUG_PRINT(x)
#endif

namespace helper
{
    // Returns the bit value of a specefic bit (at the position "pos") in a number (binaryValue)
    template <typename T>
    bool getBit(const T& binaryValue, int pos)
    {
        return (binaryValue >> pos) & 0x1;
    }   

    // Set the bit of the number "binaryValue" at position "pos" to "bit"
    template <typename T>
    T writeBit(const T& binaryValue, int pos, bool bit)
    {
        return (binaryValue) ^ ((-bit ^ binaryValue) & (1UL << pos));
    }

    struct rgb {
    int r;       // int between 0 and 255
    int g;       // int between 0 and 255
    int b;       // int between 0 and 255
    };

    struct hsv{
        int h;       // angle in degrees between 0 and 360
        int s;       // int between 0 and 100
        int v;       // int between 0 and 100
    };

} // namespace helper
