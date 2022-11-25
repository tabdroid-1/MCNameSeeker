#pragma once


#include "../../dependecies/include/curl/curl.h"
#include "../../dependecies/include/curl/options.h"

class Checker {

public:

    Checker();
    ~Checker();

    static bool Call(const char* link);
};