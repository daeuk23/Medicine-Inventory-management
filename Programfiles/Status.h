#ifndef SDDS_STATUS_H
#define SDDS_STATUS_H
#include <iostream>
namespace sdds {
	class Status {
		char* m_description = nullptr;
		int m_stCode;

	public:
		Status(const char* description = nullptr);
		Status(const Status& status);
		~Status();

		Status& clear();
		Status& operator=(const char* description);
		Status& operator=(int stCode);
		Status& operator=(const Status& status);

		operator int() const;
		operator const char* () const;
		operator bool() const;
	};
	std::ostream& operator<<(std::ostream & result, const Status& status);
}


#endif 