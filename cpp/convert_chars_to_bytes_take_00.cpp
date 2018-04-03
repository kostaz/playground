#include <iostream>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

// uint8_t[] -> std::string
// Convert array of uint8_t to std::string.
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

signed char HexDigit(char c)
{
    return p_util_hexdigit[(unsigned char)c];
}

// char[] -> uint8_t[]
// Convert array of char to array of uint8_t.
void SetHex(const char* psz, uint8_t* data, uint8_t data_len)
{
    if (data_len == 0 || strlen(psz) == 0)
        return;

    memset(data, 0, data_len * sizeof(uint8_t));

    const char* pbegin = psz;
    psz += strlen(psz) - 1; // last char (before '\0')

    int i = 0;
    uint8_t nimble = 0; // index for uint8_t array

    while (pbegin <= psz && i < data_len) {
        nimble = (uint8_t)HexDigit(*pbegin++);
        data[i] = (nimble << 4);

        if (pbegin <= psz) {
            nimble = (uint8_t)HexDigit(*pbegin++);
            data[i] |= nimble;
            i++;
        }
    }
}

void test_char_to_uint8_array_conversion(const char* psz,
                                         uint8_t* data, uint8_t len)
{
    SetHex(psz, data, len);
    std::string s = HexStr(data, len);

    printf("0x%s\n", s.c_str());
    std::cout << "0x" << std::hex << s << std::endl;
}

int main()
{
#define WIDTH 8
    uint8_t data[WIDTH];
    std::string s;

    s = "a0b1c2d312345678";
    test_char_to_uint8_array_conversion(s.c_str(), data, WIDTH);

    return 0;
}
