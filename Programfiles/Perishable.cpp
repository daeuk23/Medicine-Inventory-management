#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <fstream>
#include "Perishable.h"
#include "Utils.h"

using namespace std;
namespace sdds {
	Perishable::Perishable() : Item(),m_expiry()
	{
		m_handling = nullptr;
	}
	//for safety way
	/*Perishable::Perishable(const Perishable& perishable) : Item(perishable) {
		ut.alocpy(m_handling, perishable.m_handling);
		m_expiry = perishable.m_expiry;
	}*/
	Perishable::Perishable(const Perishable& perishable)
	{
		*this = perishable;
	}
	Perishable& Perishable::operator=(const Perishable& perishable)
	{
		if (this != &perishable)
		{
			Item::operator=(perishable);
			if (perishable.m_handling) {
				ut.alocpy(m_handling, perishable.m_handling);
			}
			m_expiry = perishable.m_expiry;
		}
		return*this;
	}
	Perishable::operator bool() const
	{
		return (m_sku >= 10000 && m_sku <= 39999) && m_state;
	}
	Perishable::~Perishable()
	{
			delete[] m_handling;
			m_handling = nullptr;
	}
	const Date& Perishable::expiry()const
	{
		return m_expiry;
	}
	int Perishable::readSku(istream& is)
	{
		m_sku = ut.getint(10000, 39999, "SKU: ");
		return m_sku;
	}
	ofstream& Perishable::save(ofstream& ofstr) const
	{
		if (*this)
		{
			Item::save(ofstr);
			ofstr << "\t";
			if (m_handling) {
				ofstr << m_handling;
			}
			ofstr << "\t";

			//query so couldnt change m_expiry directly
			Date tempArr = m_expiry;
			tempArr.formatted(false);
			ofstr << tempArr;
		}
		return ofstr;
	}
	ifstream& Perishable::load(ifstream& ifstr)
	{
		Item::load(ifstr);
		//for allocate, deallocate memory with alocpy
		char loadArr[1000];
		ifstr.getline(loadArr, 1000, '\t');
		ut.alocpy(m_handling, loadArr);
		m_expiry.read(ifstr);
		ifstr.ignore(1000, '\n');
		if (ifstr.fail())
		{
			m_state = "Input file stream read (perishable) failed!";
		}
		return ifstr;
	}
	ostream& Perishable::display(ostream& os) const
	{
		/* this is for bad state but calling base display function include printing it so no need here
	  	if (!m_state)
		{
			os << m_state;
		}*/
			if (Item::linear())
			{
				Item::display(os);
				if (m_handling != nullptr && m_handling[0] != '\0') 
				{
					os << "*";
				}
				else 
				{
					os << " ";
				}
				os << m_expiry;
			}
			else 
			{
				os << "Perishable ";
				Item::display(os);
				os << "Expiry date: ";
				os << m_expiry << endl;
				if (m_handling != nullptr && m_handling[0] != '\0') 
				{
					os << "Handling Instructions: ";
					os << m_handling << endl;
				}
			}
			return os;
	}
	istream& Perishable::read(istream& is)
	{
		Item::read(is);
	    delete[] m_handling;
		m_handling = nullptr;
		cout << "Expiry date (YYMMDD): ";
		is >> m_expiry;
		is.ignore(1000, '\n');
		cout << "Handling Instructions, ENTER to skip: ";
		//peek() => read the first next char
		if (is.peek() != '\n')
		{
			char handArr[1000]{};
			is.getline(handArr, 1000, '\n');
			m_handling = new char[strlen(handArr) + 1];
			ut.alocpy(m_handling, handArr);
		}
		if (is.fail())
		{
			m_state = "Perishable console date entry failed!";
		}
		return is;
	}
}
