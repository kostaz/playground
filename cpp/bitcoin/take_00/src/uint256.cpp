#include <string.h>

#include "uint256.h"
#include "utilstrencodings.h"

template <unsigned int BITS>
std::string base_blob<BITS>::GetHex() const
{
    return HexStr(data, WIDTH);
}

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

template std::string base_blob<16>::GetHex() const;
template void base_blob<16>::SetHex(const char* psz);

template std::string base_blob<32>::GetHex() const;
template void base_blob<32>::SetHex(const char* psz);

template std::string base_blob<160>::GetHex() const;
template void base_blob<160>::SetHex(const char* psz);

template std::string base_blob<256>::GetHex() const;
template void base_blob<256>::SetHex(const char* psz);
