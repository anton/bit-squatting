#include "bs.h"
#include <assert.h>

int main()
{
    assert(7 == flip_bit(0b00000101, 1));
    return 0;
}
