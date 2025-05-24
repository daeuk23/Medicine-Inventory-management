#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include <string.h>
#include "Utils.h"
using namespace std;
namespace sdds {
    Utils ut;
    void Utils::testMode(bool testmode) {
        m_testMode = testmode;
    }
    void Utils::getSystemDate(int* year, int* mon, int* day) {
        if (m_testMode) {
            if (day) *day = sdds_testDay;
            if (mon) *mon = sdds_testMon;
            if (year) *year = sdds_testYear;
        }
        else {
            time_t t = std::time(NULL);
            tm lt = *localtime(&t);
            if (day) *day = lt.tm_mday;
            if (mon) *mon = lt.tm_mon + 1;
            if (year) *year = lt.tm_year + 1900;
        }
    }
    int Utils::daysOfMon(int month, int year)const {
        int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
        int mon = (month >= 1 && month <= 12 ? month : 13) - 1;
        return days[mon] + int((mon == 1) * ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
    }
    void Utils::alocpy(char*& destination, const char* source)
    {
        if (destination != nullptr)
        {
            delete[] destination;
            destination = nullptr;
        }
        if (source)
        {
            destination = new char[strlen(source) + 1];
            strcpy(destination, source);
        }
    }
    int Utils::getint(const char* prompt)
    {
        int intV = 0;
        bool valid = false;
        if (prompt)
        {
            cout << prompt;
        }
        while (!valid)
        {
            cin >> intV;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid Integer, retry: ";
            }
            else
            {
                if (cin.get() != '\n') 
                {
                    cin.ignore(10000, '\n');
                }
                valid = true;
            }
        }
        return intV;
    }
    int Utils::getint(int min, int max, const char* prompt, const char* errMes)
    {
        int intV = 0;
        bool valid = false;

        while (!valid)
        {
            intV = getint(prompt);
            if (intV < min || intV > max) {
                if (errMes) {
                    cout << errMes << ", retry: ";
                }
                else {
                    cout << "Value out of range [" << min << "<=val<=" << max << "]: ";
                    prompt = nullptr;
                }
            }
            else {
                valid = true;
            }
        }
        return intV;
    }
    double Utils::getdouble(const char* prompt)
    {
        double doubleV = 0;
        bool valid = false;
        if (prompt)
        {
            cout << prompt;
        }
        while (!valid)
        {
            cin >> doubleV;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid number, retry: ";
            }
            else
            {
                valid = true;
            }
        }
        return doubleV;
    }
    double Utils::getdouble(double min, double max, const char* prompt, const char* errMes)
    {
        double doubleV = 0;
        bool valid = false;

        while (!valid)
        {
            doubleV = getdouble(prompt);
            if (doubleV < min || doubleV > max) {
                if (errMes) {
                    cout << errMes << ", retry: ";
                }
                else {
                    cout.precision(2);
                    cout.setf(ios::fixed);
                    cout << "Value out of range [" << min << "<=val<=" << max << "]: ";
                    prompt = nullptr;
                }
            }
            else {
                valid = true;
            }
        }
        return doubleV;
    }
}

