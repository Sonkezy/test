#include "../src/lib/pwgen.h"

#include "../src/lib/sha1.h"

#include "../thirdparty/ctest.h"

CTEST(parser, char_to_int)
{
    char number[3] = {'7', '3', '2'};
    int real = parser_int(number);
    int exp = 732;
    ASSERT_EQUAL(exp, real);
}

CTEST(parser, upper_to_lower)
{
    std::string upper = {'A', 'B', 'C'};
    std::string real = parser_to_lower(upper);
    std::string exp = {'a', 'b', 'c'};
    for (int i = 0; i < 3; i++) {
        ASSERT_EQUAL((int)exp[i], (int)real[i]);
    }
}

CTEST(sha1, generate)
{
    std::string input = "string";
    std::string real = sha_gen(input);
    std::string exp = "ecb252044b5ea0f679ee78ec1a12904739e2904d";
    for (int i = 0; i < (int)real.length(); i++) {
        ASSERT_EQUAL((int)exp[i], (int)real[i]);
    }
}

CTEST(options, update)
{
    char add_option = 'A';
    char erase_option = 'X';
    std::string real = "XYZ";
    std::string exp = "YZA";
    options_update(real, add_option, 1);
    options_update(real, erase_option, 0);
    for (int i = 0; i < (int)real.length(); i++) {
        ASSERT_EQUAL((int)exp[i], (int)real[i]);
    }
}

CTEST(options, find)
{
    char option_1 = 'A';
    char option_2 = 'H';
    std::string options = "ABCDEFG";
    bool real_1 = find_option(options,option_1);
    bool real_2 = find_option(options,option_2);
    ASSERT_TRUE(real_1);
    ASSERT_FALSE(real_2);
}

CTEST(Password_generate, check_options)
{
    std::string password = "ABCabc123";
    std::string options = "y";
    int exp_length = (int)password.length();
    pw_check_options(password, options);
    int real_length = (int)password.length();
    ASSERT_EQUAL(exp_length, real_length);
}

CTEST(Password_generate, remove)
{
    std::string real = "ABCabc123";
    std::string removed = "abc";
    std::string exp = "ABC123";
    pw_rm(real, removed);
    for (int i = 0; i < (int)real.length(); i++) {
        ASSERT_EQUAL((int)exp[i], (int)real[i]);
    }
}

CTEST(Password_generate, generate)
{
    std::vector<std::string> passwords;
    std::string options = "yr";
    std::string removed = "abc";
    std::string sha_input = "abc";
    int pw_length = 8;
    int pw_number = 20;
    pw_rand(passwords, options, pw_number, pw_length, removed, sha_input);
    int real_number = passwords.size();
    int exp_number = 20;
    int real_length = passwords[rand()%real_number].length();
    int exp_length = 8;
    ASSERT_EQUAL(exp_number, real_number);
    ASSERT_EQUAL(exp_length, real_length);
}
