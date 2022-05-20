#pragma once

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

unsigned circular_shift(int bits, unsigned word);
std::string parser_to_lower(std::string sha_key);
std::string sha_gen(std::string mess);
