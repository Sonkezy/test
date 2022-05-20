#pragma once

#include <iostream>
#include <string>
#include <vector>

void pw_rand(
        std::vector<std::string>& passwords,
        std::string options,
        int pw_number,
        int pw_length,
        std::string removed);
void pw_output(std::vector<std::string>& passwords, std::string options);
void pw_rm(std::string& used, std::string removed);
void pw_check_options(std::string &password,std::string options);
