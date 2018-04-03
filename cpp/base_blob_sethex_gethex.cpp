#include <iostream>
#include <stdint.h>
#include <string.h>

// To compile:
// g++ -std=c++11 -Wall -g -O0 <file.cpp> -o <file>

/*******************************************************************************
 * uint8_t[] -> std::string
 * Convert array of uint8_t to std::string.
 */
std::string HexStr(const uint8_t *bytes, uint8_t len)
{
    static const char hexmap[16] = {'0', '1', '2', '3', '4', '5', '6', '7',
                                    '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

    std::string rv;
    for (int i = 0; i < len; i++)
    {
        uint8_t byte = bytes[i];

        char byte_lsb = hexmap[byte & 0xf];
        char byte_msb = hexmap[byte >> 4];

        rv.push_back(byte_msb);
        rv.push_back(byte_lsb);
    }

    return rv;
}

/*******************************************************************************
 * p_util_hexdigit
 */
const signed char p_util_hexdigit[256] =
{ -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    0,1,2,3,4,5,6,7,8,9,-1,-1,-1,-1,-1,-1,
    -1,0xa,0xb,0xc,0xd,0xe,0xf,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,0xa,0xb,0xc,0xd,0xe,0xf,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, };

/*******************************************************************************
 * HexDigit
 */
signed char HexDigit(char c)
{
    return p_util_hexdigit[(unsigned char)c];
}

/*******************************************************************************
 * class base_blob
 */
template <unsigned int BITS>
class base_blob
{
protected:
    static constexpr int WIDTH = BITS / 8;
    uint8_t data[WIDTH];

public:
    base_blob() {
        memset(data, 0, sizeof(data));
    }

    void SetHex(const char* psz);
    std::string GetHex() const;
};

/*******************************************************************************
 * base_blob::GetHex
 */
template <unsigned int BITS>
std::string base_blob<BITS>::GetHex() const
{
    return HexStr(data, WIDTH);
}

/*******************************************************************************
 * base_blob::SetHex
 * char[] -> uint8_t[]
 * Convert array of char to array of uint8_t.
 */
template <unsigned int BITS>
void base_blob<BITS>::SetHex(const char* psz)
{
    if (strlen(psz) == 0)
        return;

    memset(data, 0, sizeof(data));

    const char* pbegin = psz;
    psz += strlen(psz) - 1; // last char (before '\0')

    int i = 0;
    uint8_t nimble = 0; // index for uint8_t array

    while (pbegin <= psz && i < WIDTH) {
        nimble = (uint8_t)HexDigit(*pbegin++);
        data[i] = (nimble << 4);

        if (pbegin <= psz) {
            nimble = (uint8_t)HexDigit(*pbegin++);
            data[i] |= nimble;
            i++;
        }
    }
}

/*******************************************************************************
 * main
 */
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
