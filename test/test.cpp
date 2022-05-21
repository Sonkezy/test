#include "../src/lib/pwgen.h"

#include "../src/lib/sha1.h"

#include "../thirdparty/ctest.h"

CTEST(parser, char_to_int)
{
    char number [3] = {'7','3','2'};
    int real = parser_int(number);
    ASSERT_EQUAL(732, real);
}
