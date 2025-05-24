#include <iostream>
#include <ctime>
#include <string.h>
#include "Status.h"
#include "Utils.h"

using namespace std;
namespace sdds {

    Status::Status(const char* description){
        ut.alocpy(m_description, description);
        m_stCode = 0;
    }

    Status::Status(const Status& status) {
        *this = status;
    }

    Status::~Status(){
        clear();
    }

    Status& Status::clear() {
        if (m_description != nullptr) {
            delete[] m_description;
        }
        m_description = nullptr;
        return *this;
    }

    Status& Status::operator=(const char* description) {
        // also prevent memory leak
        ut.alocpy(m_description, description);
        return*this;
    }

    Status& Status::operator=(int stCode)
    {
        m_stCode = stCode;
        return*this;
    }

    Status& Status::operator=(const Status& status) {
        if (this != &status)
        {
            ut.alocpy(m_description, status.m_description);
            m_stCode = status.m_stCode;
        }
        return*this;
    }

    Status::operator int() const {
        return m_stCode;
    }

    Status::operator const char* () const {
        return m_description;
    }

    Status::operator bool() const {
        // true if no desc *
        return m_description == nullptr;
    }

    std::ostream& operator<<(std::ostream& result, const Status& status)
    {
        if (!status) {
            if ((int)status != 0) {
                result << "ERR#" << (int)status << ": ";
            }
        }
        result << (const char*)status;
        return result;
    }
}