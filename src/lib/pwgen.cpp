#include <lib/pwgen.h>
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
        std::string removed)
{
    std::string used = pw_lowers;
    used += pw_lowers;
    std::size_t found;
    found = options.find("c");
    if (found != std::string::npos) {
        used += pw_uppers;
    }
    found = options.find("n");
    if (found != std::string::npos) {
        used += pw_digits;
    }
    found = options.find("y");
    if (found != std::string::npos) {
        used += pw_symbols;
    }
    used += pw_lowers;
    used += pw_lowers;
    used += pw_lowers;
    found = options.find("r");
    if (found != std::string::npos) {
        pw_rm(used, removed);
    }
    srand(time(NULL));
    for (int i = 0; i < pw_number; i++) {
        std::string password;
        for (int j = 0; j < pw_length; j++) {
            int rand_value = rand() % used.length();
            password.push_back(used[rand_value]);
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
