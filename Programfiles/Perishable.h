#ifndef SDDS_PERISHABLE_H	
#define SDDS_PERISHABLE_H
#include "Item.h"
#include "Date.h"
using namespace std;
namespace sdds {
	class Perishable : public Item {
		Date m_expiry{};
		char* m_handling{};
	public:
		Perishable();
		~Perishable();
		Perishable(const Perishable& perishable);
		Perishable& operator=(const Perishable& perishable);
		operator bool() const;
		const Date& expiry()const;
		int readSku(istream& is);
		ofstream& save(ofstream& ofstr) const;
		ifstream& load(ifstream& ifstr);
		ostream& display(ostream& os) const;
		istream& read(istream& is);
	};
}
#endif // !SDDS_PERISHABLE_H