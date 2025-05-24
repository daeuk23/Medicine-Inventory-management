#ifndef SDDS_MENU_H
#define SDDS_MENU_H

namespace sdds {
    const int MAXIMUMOPT = 15;

    class Menu {
        char* m_menuCont;
        unsigned int m_optNum;
    public:
        Menu();
        Menu(const char* menuCont);
        Menu(unsigned int numOption ,const char* menuCont);
        ~Menu();
        
        // cannot be copied or assigned to other menu
        Menu(const Menu& menu) = delete;
        Menu& operator=(const Menu& menu) = delete;

        unsigned int run() const;
    };
}

#endif // !SDDS_MENU_H