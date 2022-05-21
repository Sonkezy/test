#include <lib/pwgen.h>
#include <lib/sha1.h>
#include <stdlib.h>
#include <time.h>

const std::string pw_digits = "0123456789";
const std::string pw_uppers = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const std::string pw_lowers = "abcdefghijklmnopqrstuvwxyz";
const std::string pw_symbols = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";
const int term_width = 80;

void pw_rand(
        std::vector<std::string>& passwords,
        std::string options,
        int pw_number,
        int pw_length,
        std::string removed,
        std::string sha_input)
{
    bool sha = false;
    std::string used = pw_lowers;
    for (int i = 0; i < 5; i++) {
        used += pw_lowers;
    }
    if (find_option(options, 'c')) {
        used += pw_uppers;
    }
    if (find_option(options, 'n')) {
        used += pw_digits;
    }
    if (find_option(options, 'y')) {
        used += pw_symbols;
    }
    if (find_option(options, 'H')) {
        std::string sha_key = sha_gen(sha_input);
        used = sha_key;
        sha = true;
    }
    if (find_option(options, 'r')) {
        pw_rm(used, removed);
    }
    srand(time(NULL));
    for (int i = 0; i < pw_number; i++) {
        std::string password;
        for (int j = 0; j < pw_length; j++) {
            int rand_value = rand() % used.length();
            password.push_back(used[rand_value]);
        }
        if (!sha) {
            pw_check_options(password, options);
        }

        passwords.push_back(password);
    }
}

void pw_output(std::vector<std::string>& passwords, std::string options)
{
    std::size_t found;
    bool columns = false;
    found = options.find("C");
    if (found != std::string::npos) {
        columns = true;
    }
    int count = 0;
    for (int i = 0; i < (int)passwords.size(); i++) {
        printf("%s ", passwords[i].c_str());
        count += (passwords[i].length() + 1);
        if (count >= (term_width - (int)passwords[i].length()) && columns) {
            printf("\n");
            count = 0;
        }
    }
    printf("\n");
}

void pw_rm(std::string& used, std::string removed)
{
    for (int i = 0; i < (int)removed.length(); i++) {
        std::size_t found = used.find(removed[i]);
        while (found != std::string::npos) {
            used.erase(found, 1);
            found = used.find(removed[i]);
        }
    }
}

void pw_check_options(std::string& password, std::string options)
{
    int rand_value_1;
    int rand_value_2;
    bool success = true;
    bool capitalize = find_option(options, 'c');
    bool numerals = find_option(options, 'n');
    bool symbols = find_option(options, 'y');
    if (capitalize) {
        capitalize = false;
        for (int i = 0; i < (int)pw_uppers.length(); i++) {
            bool found_uppers = find_option(password, pw_uppers[i]);
            if (found_uppers) {
                capitalize = true;
            }
        }
        if (!capitalize) {
            success = false;
            rand_value_1 = rand() % password.length();
            rand_value_2 = rand() % pw_uppers.length();
            password[rand_value_1] = pw_uppers[rand_value_2];
        }
    }
    if (numerals) {
        numerals = false;
        for (int i = 0; i < (int)pw_digits.length(); i++) {
            bool found_digits = find_option(password, pw_digits[i]);
            if (found_digits) {
                numerals = true;
            }
        }
        if (!numerals) {
            success = false;
            rand_value_1 = rand() % password.length();
            rand_value_2 = rand() % pw_digits.length();
            password[rand_value_1] = pw_digits[rand_value_2];
        }
    }
    if (symbols) {
        symbols = false;
        for (int i = 0; i < (int)pw_symbols.length(); i++) {
            bool found_symbols = find_option(password, pw_symbols[i]);
            if (found_symbols) {
                symbols = true;
            }
        }
        if (!symbols) {
            success = false;
            rand_value_1 = rand() % password.length();
            rand_value_2 = rand() % pw_symbols.length();
            password[rand_value_1] = pw_symbols[rand_value_2];
        }
    }
    if (!success) {
        pw_check_options(password, options);
    }
}

int parser_int(char* c)
{
    int number = 0;
    for (int i = 0; i < ((int)strlen(c)); i++) {
        int n = c[i] - 48;
        int pow = 1;
        for (int j = 1; j < ((int)strlen(c) - i); j++) {
            pow = pow * 10;
        }
        number += (n * pow);
    }
    return number;
}

void options_update(std::string& options, char option, bool action)
{
    if (action == 1) {
        bool already = false;
        for (int i = 0; i < (int)options.length(); i++) {
            if (options[i] == option) {
                already = true;
                break;
            }
        }
        if (!already) {
            options.push_back(option);
        }
    } else {
        for (int i = 0; i < (int)options.length(); i++) {
            if (options[i] == option) {
                options.erase(i, 1);
            }
        }
    }
}

bool find_option(std::string options, char option)
{
    std::size_t found = options.find(option);
    if (found != std::string::npos) {
        return true;
    } else {
        return false;
    }
}
