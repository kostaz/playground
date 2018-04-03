#include <iostream>
#include <stdint.h>

#include "uint256.h"

// To build and run:
// $ meson build
// $ cd build
// $ ninja
// $ ./bitcoind

int main()
{
    // 2-byte array (16 bits, 2 characters)
    base_blob<16> bb16;
    bb16.SetHex("abcd");
    std::cout << bb16.GetHex() << std::endl;

    // 4-byte array (32 bits, 8 characters)
    base_blob<32> bb32;
    bb32.SetHex("abcd1234");
    std::cout << bb32.GetHex() << std::endl;

    // 20-byte array (160 bits, 40 characters)
    base_blob<160> bb160;
    bb160.SetHex("1234567890abcdefa0b1c2d3e4f50987654321eb");
    std::cout << bb160.GetHex() << std::endl;

    // 32-byte array (256 bits, 64 characters)
    base_blob<256> bb256;
    bb256.SetHex("1234567890abcdefa0b1c2d3e4f50987654321eb1234567890abcdefa0b1c2d3");
    std::cout << bb256.GetHex() << std::endl;
}
