#include "bs.h"
inline int toggle_bit(char c, int b)
{
    return c ^ (1 << b);
}
