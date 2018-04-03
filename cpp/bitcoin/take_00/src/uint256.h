#include <string>
#include <stdint.h>
#include <string.h>

/** Template base class for fixed-sized opaque blobs. */
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
