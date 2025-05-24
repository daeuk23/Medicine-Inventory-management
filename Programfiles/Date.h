#ifndef SDDS_DATE_H
#define SDDS_DATE_H
#include <iostream>
#include "Status.h"

namespace sdds {
	const int MAXIMUM_YEAR = 2030;
	class Date {
	private:
		int m_year;
		int m_month;
		int m_day;
		Status m_st;
		bool m_flag;//format

		bool validate();
		int uniqueDate();
	public:
		Date();
		Date(int year, int month, int day);

		bool operator==(Date& date);
		bool operator!=(Date& date);
		bool operator<(Date& date);
		bool operator>(Date& date);
		bool operator<=(Date& date);
		bool operator>=(Date& date);

		const Status& state();
		Date& formatted(bool format);
		operator bool() const;

		std::ostream& write(std::ostream& os)const; 
		std::istream& read(std::istream& is);		
	};
	std::ostream& operator<<(std::ostream& os, const Date& date);
	std::istream& operator>>(std::istream& is, Date& date);


}

#endif

