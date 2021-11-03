#pragma once 

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
} // namespace helper
