#include <iostream>
#include <ctime>
#include <iomanip>
#include "Date.h"
#include "Utils.h"

using namespace std;
namespace sdds {

    bool Date::validate() {
        bool result = false;
        int crYear, crMonth, crDay;
        ut.getSystemDate(&crYear, &crMonth, &crDay);
        m_st.clear();

        if (!result && (m_year < crYear || m_year > MAXIMUM_YEAR)) {
            m_st = "Invalid year in date";
            m_st = 1;
        }
        else if (!result && (m_month < 1 || m_month > 12)) {
            m_st = "Invalid month in date";
            m_st = 2;
        }
        else if (!result && (m_day < 1 || m_day > ut.daysOfMon(m_month, m_year))) {
            m_st = "Invalid day in date";
            m_st = 3;
        }
        else {
            result = true;
        }
        return result;
    }

    int Date::uniqueDate(){
        return m_year * 372 + m_month * 31 + m_day;
    }

    Date::Date() {
        m_flag = true;
        ut.getSystemDate(&m_year, &m_month, &m_day);
        m_st.clear();
    }

    Date::Date(int year, int month, int day) {
        m_flag = true;
        m_year = year;
        m_month = month;
        m_day = day;
    }

    bool Date::operator==(Date& date) {
        return uniqueDate() == date.uniqueDate();
    }

    bool Date::operator!=(Date& date) {
        return uniqueDate() != date.uniqueDate();
    }

    bool Date::operator<(Date& date) {
        return uniqueDate() < date.uniqueDate();
    }

    bool Date::operator>(Date& date) {
        return uniqueDate() > date.uniqueDate();
    }

    bool Date::operator<=(Date& date) {
        return uniqueDate() <= date.uniqueDate();
    }

    bool Date::operator>=(Date& date) {
        return uniqueDate() >= date.uniqueDate();
    }

    const Status& Date::state() {
        return m_st;
    }


    Date& Date::formatted(bool format) {
        m_flag = format;
        return *this;
    }

    Date::operator bool() const {
        return m_st;
    }

    ostream& Date::write(ostream& os) const{
        if (m_flag)
        {
            os << m_year << "/" << setw(2) << setfill('0') << m_month << "/" << setw(2) << setfill('0')  << m_day;
        }
        else
        {
            os << m_year % 100 << setw(2) << setfill('0') << m_month << setw(2) << setfill('0') << m_day;
        }
        return os;
    }

    istream& Date::read(istream& ist)
    {
        int val;
        ist >> val;
        m_st.clear();

        if (ist.fail()) {
            ist.setstate(ios::badbit);
            m_st = "Invalid date value";
        }
        else {
            m_day = val % 100;
            m_month = (val / 100) % 100;
            m_year = val / 10000;
            if (m_year == 0) {
                m_year = 2023;
            }
            else {
                m_year += 2000;
            }
            if (!validate()) {
                ist.setstate(ios::badbit);
            }
        }
        return ist;
    }

    ostream& operator<<(ostream& os, const Date& date)
    {
        date.write(os);
        return os;
    }
    istream& operator>>(istream& is, Date& date)
    {
        date.read(is);
        return is;
    }
}