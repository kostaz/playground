/**
 * Utilities for converting data from/to strings.
 */
#ifndef BITCOIN_UTILSTRENCODINGS_H
#define BITCOIN_UTILSTRENCODINGS_H

#include <stdint.h>
#include <string>

signed char HexDigit(char c);

std::string HexStr(const uint8_t *bytes, uint8_t len);

#endif // BITCOIN_UTILSTRENCODINGS_H
