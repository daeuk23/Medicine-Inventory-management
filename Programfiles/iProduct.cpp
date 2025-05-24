#include "iProduct.h"
using namespace std;
namespace sdds {
	ostream& operator << (ostream& ostr, const iProduct& iproduct)
	{
		// display(ostr) working on "this" object, so same work with specific object
		return iproduct.display(ostr);
	}
	istream& operator >> (istream& istr, iProduct& iproduct)
	{
		return iproduct.read(istr);
	}
}