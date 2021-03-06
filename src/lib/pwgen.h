#pragma once

#include <cstring>
#include <iostream>
#include <string>
#include <vector>

void pw_rand(
        std::vector<std::string>& passwords,
        std::string options,
        int pw_number,
        int pw_length,
        std::string removed,
        std::string sha_input);
void pw_output(std::vector<std::string>& passwords, std::string options);
void pw_rm(std::string& used, std::string removed);
void pw_check_options(std::string& password, std::string options);
int parser_int(char* c);
void options_update(std::string& options, char option, bool action);
bool find_option(std::string options, char option);
