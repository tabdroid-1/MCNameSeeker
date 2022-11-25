#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <chrono>
#include <thread>
#include <unordered_map>

#include "rcg/Checker.h"


using namespace std;
using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
using std::chrono::system_clock;

static string RandomName(int ch);

int main()
{
    srand(time(NULL));
    int ch = 3;
    int delayIndex;
    std::unordered_map<int, std::chrono::milliseconds> delays;

    delays[0] = 100ms;
    delays[1] = 500ms;
    delays[2] = 1000ms;


    cout << "How long name should be? (minimum 3) >> ";
    cin >> ch;

    if (ch < 3) {
        cout << "ERROR: invalid amount" << endl;
        return -1;
    }


    cout << "How long delay between each call should be? (Recomended: 1000ms) 0: 100ms 1: 500ms 2: 1000ms >> ";
    cin >> delayIndex;

    if (delayIndex >= 3 || delayIndex <= -1) {
        cout << "ERROR: invalid amount" << endl;
        return -1;
    }

    while (true) {

        string name = RandomName(ch);
        string api = "https://api.mojang.com/users/profiles/minecraft/";
        string sLink = api + name;
        const char* cLink = sLink.c_str(); 

        //for save
        vector<string> lines;

        if (Checker::Call(cLink)) {

            // inform user wich name is available
            cout << name << " available" << endl;

            // temp variable to save names to vector
            string fileLine;
            ifstream readFile("names.txt");
            

            if (readFile.is_open())
            {
                //read lines and push into vector
                while (getline(readFile, fileLine))
                {

                    lines.push_back(fileLine);
                    
                }
            }

            // add available name
            lines.push_back(name);

            ofstream save("names.txt", ofstream::trunc);

            //iterate vector and add lines
            for (int i = 0; i < lines.size(); i++) {
                
                save << lines[i] << endl;
            }

            //close file
            save.close();
        }

        cout << endl;

        // Wait 1 second until next call to prevent spam
        sleep_for(1s);

    }

    return 0;
}

static string RandomName(int ch)
{

    const int ch_MAX = 37;

    char alpha[ch_MAX] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g',
                        'h', 'i', 'j', 'k', 'l', 'm', 'n',
                        'o', 'p', 'q', 'r', 's', 't', 'u',
                        'v', 'w', 'x', 'y', 'z', '_', '1',
                        '2', '3', '4', '5', '6', '7', '8',
                        '9', '0' };

    string result;

    for (int i = 0; i < ch; i++){
        result = result + alpha[rand() % ch_MAX];
    }
        
    return result;
}