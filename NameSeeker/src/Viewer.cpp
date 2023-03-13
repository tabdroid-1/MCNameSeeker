#include <iostream>

#include "Viewer.h"

using namespace std;

size_t curl_callback(void *ptr, size_t size, size_t nmemb, std::string* data);
void Cleanup(CURL *curl, curl_slist *headers);

// string Viewer::Call(const char* link) {

    
//     CURL* curl = curl_easy_init();
//     CURLcode res;

//     string response_string;

//     // struct curl_slist *headers = NULL; //linked-list string structure
// 	// if (!curl)
// 	// {
// 	// 	cout << "ERROR : Curl initialization\n" << endl;
// 	// 	Cleanup(curl, headers);
// 	// 	return NULL;
// 	// }


//     curl_easy_setopt(curl, CURLOPT_URL, link);
//     curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_callback); // pass our call back function to handle received data
// 	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string); // pass the variable to hold the received data

//     res = curl_easy_perform(curl);


//     std::cout << res << std::endl;
//     /* Check for errors */
//     if (res == CURLE_OK) {
//         char *ct;

//         res = curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &ct);
        

//         if ((CURLE_OK == res) && ct == NULL) {

//             return NULL;
//         }
//     }



//     if(res != CURLE_OK) {
//         cout << stderr << "curl_easy_perform() failed: \n" << curl_easy_strerror(res) << endl;
//     }
//     /* always cleanup */
//     curl_easy_cleanup(curl);

//     curl_global_cleanup();



//     return response_string;
// }
string Viewer::Call(const char* url)
{
	curl_global_init(CURL_GLOBAL_ALL); // sets the program environment
	CURL *curl = curl_easy_init(); // initialize curl
	std::string response_string;
	struct curl_slist *headers = NULL; //linked-list string structure
	if (!curl)
	{
		cout << "ERROR : Curl initialization\n" << endl;
		Cleanup(curl, headers);
		return NULL;
	}

	headers = curl_slist_append(headers, "User-Agent: libcurl-agent/1.0");
	headers = curl_slist_append(headers, "Content-Type: application/json");
	headers = curl_slist_append(headers, "Cache-Control: no-cache");

	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

	//ignore ssl verification if you don't have the certificate or don't want secure communication
	// you don't need these two lines if you are dealing with HTTP url
	// curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
	// curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

	curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L); //maximum time allowed for operation to finish, its in seconds
	curl_easy_setopt(curl, CURLOPT_URL, url); // pass the url
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_callback); // pass our call back function to handle received data
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string); // pass the variable to hold the received data


	CURLcode status = curl_easy_perform(curl); // execute request
	if (status != 0)
	{
		cout << "Error: Request failed on URL : " << url << endl;
		cout << "Error Code: " << status << " Error Detail : " << curl_easy_strerror(status) << endl;
		Cleanup(curl, headers);
		return NULL;
	}

	// do the clean up
	curl_easy_cleanup(curl);
	curl_slist_free_all(headers);
	curl_global_cleanup();

	return response_string;
}

size_t curl_callback(void *ptr, size_t size, size_t nmemb, std::string* data) {
	data->append((char*)ptr, size * nmemb);
	return size * nmemb;
}

void Cleanup(CURL *curl, curl_slist *headers)
{
	if (curl)
		curl_easy_cleanup(curl);
	if (headers)
		curl_slist_free_all(headers);
	curl_global_cleanup();
}
