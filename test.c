#include "bs.h"
#include <assert.h>

int main()
{
    assert(7 == flip_bit(0b0101, 1));
    assert(0b0100 == flip_bit(0b0101, 0));
    assert(0b0111 == flip_bit(0b1111, 3));
    return 0;
}
