#pragma once


#include <curl/curl.h>
#include <curl/options.h>

class Viewer {

public:

    Viewer();
    ~Viewer();

    static std::string Call(const char* link);
};