#include <lib/pwgen.h>

void help_message();
void error_input();

const int term_width = 80;
const int term_length = 20;

int main(int argc, char** argv)
{
    std::vector<std::string> passwords;
    int pw_length = 8;      // Standart length of passwords
    bool if_pw_len = false; // If length of passwords has input
    int pw_number = ((term_width - 1) / (pw_length + 1))
            * term_length;  // Standart numbers of passwords
    bool if_pw_num = false; // If number of passwords has input
    std::string removed;
    int numb_of_removed = 0;
    std::string sha_input;
    int numb_of_sha_input = 0;
    std::string options = "cnC";
    bool help = false;

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            for (int j = 1; j < (int)strlen(argv[i]); j++) {
                switch (argv[i][j]) {
                case 'c':
                    options_update(options, 'c', 1);
                    break;
                case 'A':
                    options_update(options, 'c', 0);
                    break;
                case 'n':
                    options_update(options, 'n', 1);
                    break;
                case '0':
                    options_update(options, 'n', 0);
                    break;
                case 'y':
                    options_update(options, 'y', 1);
                    break;
                case 'r':
                    options_update(options, 'r', 1);
                    if (argc - i > 1 || (int)strlen(argv[i]) <= 2) {
                        removed = argv[i + 1];
                    } else {
                        error_input();
                    }
                    numb_of_removed = i + 1;
                    j += (int)strlen(argv[i]);
                    break;
                case 'h':
                    help = true;
                    break;
                case 'H':
                    options_update(options, 'H', 1);
                    if (argc - i > 1 || (int)strlen(argv[i]) <= 2) {
                        sha_input = argv[i + 1];
                    } else {
                        error_input();
                    }
                    numb_of_sha_input = i + 1;
                    j += (int)strlen(argv[i]);
                    break;
                case 'C':
                    options_update(options, 'C', 1);
                    pw_number = ((term_width - 1) / (pw_length + 1))
                            * term_length;
                    break;
                case '1':
                    options_update(options, 'C', 0);
                    pw_number = 1;
                    break;
                default:
                    help = true;
                    break;
                }
            }
        }
    }
    if (help == true) {
        help_message();
    }

    for (int i = 1; i < argc; i++) {
        bool if_number = true;
        if (i == numb_of_sha_input || i == numb_of_removed) {
            if (i < argc - 1) {
                i++;
            } else {
                break;
            }
        }
        for (int j = 1; j < (int)strlen(argv[i]); j++) {
            if (argv[i][j] < '0' || argv[i][j] > '9') {
                if_number = false;
            }
        }
        if (if_number && if_pw_num && if_pw_len) {
            error_input();
        }
        if (if_number && if_pw_len && (!if_pw_num)) {
            pw_number = parser_int(argv[i]);
            // printf("%d\n", pw_number);
            if_pw_num = true;
        }
        if (if_number && (!if_pw_len)) {
            pw_length = parser_int(argv[i]);
            // printf("%d\n", pw_length);
            if_pw_len = true;
        }
    }
    // std::cout << options << std::endl;
    pw_rand(passwords, options, pw_number, pw_length, removed, sha_input);
    pw_output(passwords, options);
    return 0;
}

void help_message()
{
    fputs("Usage: pwgen [ OPTIONS ] [ pw_length ] [ num_pw ]\n\n", stderr);
    fputs("Options supported by pwgen:\n", stderr);
    fputs("  -c\n", stderr);
    fputs("\tInclude at least one capital letter in the password\n", stderr);
    fputs("  -A\n", stderr);
    fputs("\tDon't include capital letters in the password\n", stderr);
    fputs("  -n\n", stderr);
    fputs("\tInclude at least one number in the password\n", stderr);
    fputs("  -0\n", stderr);
    fputs("\tDon't include numbers in the password\n", stderr);
    fputs("  -y\n", stderr);
    fputs("\tInclude at least one special symbol in the password\n", stderr);
    fputs("  -r <chars> \n", stderr);
    fputs("\tRemove characters from the set of characters to "
          "generate passwords\n",
          stderr);
    fputs("  -h\n", stderr);
    fputs("\tPrint a help message\n", stderr);
    fputs("  -H <chars>\n", stderr);
    fputs("\tUse sha1 hash of given word as a (not so) random generator\n",
          stderr);
    fputs("  -C\n\tPrint the generated passwords in columns\n", stderr);
    fputs("  -1\n\tDon't print the generated passwords in columns\n", stderr);
    exit(1);
}

void error_input()
{
    printf("Invalid input\n");
    help_message();
}

