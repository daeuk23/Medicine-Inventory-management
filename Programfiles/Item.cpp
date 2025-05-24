#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "Item.h"
#include "Utils.h"
using namespace std;
namespace sdds {
    bool Item::linear() const
    {
        return m_linear;
    }
    Item::Item() : iProduct() {
        m_price = m_qty = m_qtyNeeded = m_sku = 0;
        m_description = nullptr;
        m_linear = false;
        m_state.clear();
    }
    Item::~Item()
    {
        clear();
    }
    Item::Item(const Item& item) : iProduct()
    {
        *this = item;
    }
    Item& Item::operator=(const Item& item)
    {
        if (this != &item)
        {
            m_price = item.m_price;
            m_qty = item.m_qty;
            m_qtyNeeded = item.m_qtyNeeded;
            if (item.m_description) {
                ut.alocpy(m_description, item.m_description);
            }
            m_linear = item.m_linear;
            m_state = item.m_state;
            m_sku = item.m_sku;
        }
        return* this;
    }
    int Item::qtyNeeded() const
    {
        return m_qtyNeeded;
    }
    int Item::qty() const
    {
        return m_qty;
    }
    Item::operator double() const
    {
        return m_price;
    }
    Item::operator bool() const
    {
        return m_state;
    }
    int Item::operator -=(int qty)
    {
        return m_qty -= qty;
    }
    int Item::operator +=(int qty)
    {
        // add to m_qty and return that value
        return m_qty += qty;
    }
    void Item::linear(bool linear)
    {
        m_linear = linear;
    }
    void Item::clear()
    {
        if (m_description != nullptr)
        {
            delete[] m_description;
            m_description = nullptr;
        }
        m_state.clear();
    }
    bool Item::operator==(int sku) const
    {
        return m_sku == sku;
    }
    bool Item::operator ==(const char* description) const
    {
        return (m_description && description && strstr(m_description, description));
    }
    ofstream& Item::save(ofstream& ofstr) const
    {
        if (m_state)
        {
            ofstr << m_sku << '\t' << m_description << '\t' << m_qty << '\t' << m_qtyNeeded << '\t' << fixed << setprecision(2) << m_price;
        }
        return ofstr;
    }
    ifstream& Item::load(ifstream& ifstr)
    {
        char file[1000]{};

        ifstr >> m_sku;
        ifstr.clear();
        ifstr.ignore(1000, '\t');
        ifstr.getline(file, 1000, '\t');
        ut.alocpy(m_description, file);
        ifstr >> m_qty;
        ifstr >> m_qtyNeeded;
        ifstr >> m_price;
        ifstr.get();

        if (ifstr.fail()) {
            m_state = "Input file stream read failed!";
        }
        return ifstr;
    }
    ostream& Item::display(ostream& os) const
    {
        if (!m_state)
        {
            os << m_state;
        }
        else
        {
            if(m_linear)
            { 
                char resultDesc[36]{};
                strncpy(resultDesc, m_description, 35);
                resultDesc[35] = '\0';
                os << left << setw(5) << m_sku << " | " << setw(35) << left << setfill(' ') << resultDesc << " | ";
                os << right << setw(4) << setfill(' ') << m_qty << " | " << right << setw(4) << setfill(' ') << m_qtyNeeded << " | ";
                os << right << setw(7) << setfill(' ') << fixed << setprecision(2) << m_price << " |";
            }
            else
            {
                os << "AMA Item:" << std::endl
                    << m_sku << ": " << m_description << endl
                    << "Quantity Needed: " << m_qtyNeeded << endl
                    << "Quantity Available: " << m_qty << endl
                    << "Unit Price: $" << fixed << setprecision(2) << m_price << endl
                    << "Needed Purchase Fund: $" << m_price * (m_qtyNeeded - m_qty) << endl;
            }
        }
        return os;
    }
    int Item::readSku(istream& is)
    {
        m_sku = ut.getint(40000, 99999, "SKU: ");
        return m_sku;
    }
    istream& Item::read(istream& is)
    {
        char tempArr[1000]{};
        cout << "AMA Item:" << endl;
        cout << "SKU: " << m_sku << endl;
        cout << "Description: ";
        is.getline(tempArr, 1000, '\n');
        ut.alocpy(m_description, tempArr);
        m_qtyNeeded = ut.getint(1, 9999, "Quantity Needed: ");
        m_qty = ut.getint(0, m_qtyNeeded, "Quantity On Hand: ");
        m_price = ut.getdouble(0.0, 9999.0, "Unit Price: $");
        m_state.clear();
        if (is.fail())
        {
            m_state = "Console entry failed!";
        }
        else
        {
            //to good state
            m_state.clear();
        }
        return is;
    }

}