#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Menu.h"
#include "Utils.h"

namespace sdds {
    Menu::Menu() {
        m_menuCont = nullptr;
        m_optNum = 0;
    }


	Menu::Menu(const char* menuContent) {
		if (menuContent) {
			m_menuCont = new char[strlen(menuContent) + 1];
			strcpy(m_menuCont, menuContent);
		}
		else {
			m_menuCont = nullptr;
		}
		m_optNum = 0;
	}

	Menu::Menu(unsigned int numOption, const char* menuCont)
	{
		if (numOption <= MAXIMUMOPT && menuCont) {
			m_optNum = numOption;
			m_menuCont = new char[strlen(menuCont) + 1];
			strcpy(m_menuCont, menuCont);
		}
		else {
			m_optNum = 0;
			m_menuCont = nullptr;
		}
	}

	Menu::~Menu()
	{
		if (m_menuCont != nullptr) {
			delete[] m_menuCont;
		}
	}

	unsigned int Menu::run() const {
		if (m_optNum == 0) {
			std::cout << "Invalid Menu!" << std::endl;
			return 0;
		}

		std::cout << m_menuCont << "0- Exit" << std::endl;
		// auto generate range out message
		return ut.getint(0, m_optNum, "> ");
	}
}