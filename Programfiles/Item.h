#ifndef SDDS_ITEM_H
#define SDDS_ITEM_H
#include "iProduct.h"
#include "Status.h"

using namespace std;
namespace sdds {
	class Item : public iProduct {
		char* m_description{};
		bool m_linear{};
		double m_price{};
		int m_qty{};
		int m_qtyNeeded{};
	protected:
		Status m_state{};
		int m_sku{};
		bool linear() const;
	public:
		Item();
		~Item();
		Item(const Item& item);
		Item& operator=(const Item& item);
		virtual int qtyNeeded() const;
		virtual int qty() const;
		virtual operator double() const;
		virtual operator bool() const;
		virtual int operator -=(int qty);
		virtual int operator +=(int qty);
		virtual void linear(bool linear);
		void clear();
		virtual bool operator==(int sku) const;
		virtual bool operator ==(const char* description) const;
		virtual ofstream& save(ofstream& ofstr) const;
		virtual ifstream& load(ifstream& ifstr);
		virtual ostream& display(ostream& os) const;
		virtual int readSku(istream& is);
		virtual istream& read(istream& is);
	};
}
#endif