#include <iostream>

#include "Checker.h"

using namespace std;


bool Checker::Call(const char* link) {

    CURL* curl = curl_easy_init();
    CURLcode res;

    curl_easy_setopt(curl, CURLOPT_URL, link);

    res = curl_easy_perform(curl);


    /* Check for errors */
    if (res == CURLE_OK) {
        char *ct;

        res = curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &ct);
        
        if ((CURLE_OK == res) && ct == NULL) {

            return true;
        }
    }

    if(res != CURLE_OK) {
        cout << stderr << "curl_easy_perform() failed: \n" << curl_easy_strerror(res) << endl;
    }
    /* always cleanup */
    curl_easy_cleanup(curl);

    curl_global_cleanup();


    return false;
}