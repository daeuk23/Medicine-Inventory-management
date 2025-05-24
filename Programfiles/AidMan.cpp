#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <fstream>
#include "AidMan.h"
#include "Utils.h"
#include "Date.h"
#include <iomanip>

using namespace std;
namespace sdds {
	unsigned int AidMan::menu() const
	{
		cout << "Aid Management System" << endl;
		cout << "Date: " << Date() << endl;
		if (m_fileName) {
			cout << "Data file: " << m_fileName << endl;
		}
		else {
			cout << "Data file: No file" << endl;
		}
		return m_mainMenu.run();
	}

	void AidMan::save()
	{
		if (m_fileName)
		{
			ofstream ofstr(m_fileName);
			for (int i = 0; i < m_noOfiProduct; i++) {
				m_iProduct[i]->save(ofstr);
				ofstr << endl;
			}
			ofstr.close();
		}
	}

	void AidMan::deallocate()
	{
		for (int i = 0; i < m_noOfiProduct; i++)
		{
			delete m_iProduct[i];
		}
		if (m_fileName != nullptr)
		{
			delete[] m_fileName;
			m_fileName = nullptr;
		}
		m_noOfiProduct = 0;
	}

		bool AidMan::load()
	{
		char tmpFname[1000]{};
		bool isLoad = false;

		save();
		// m_noOfiProduct initialized to 0
		deallocate();
		cout << "Enter file name: ";
		cin.getline(tmpFname, 1000, '\n');
		ut.alocpy(m_fileName, tmpFname);
		ifstream ifstr(m_fileName);

		if (!ifstr.is_open())
		{
			cout << "Failed to open " << m_fileName << " for reading!" << endl;
			cout << "Would you like to create a new data file?" << endl;
			cout << "1- Yes!" << endl;
			cout << "0- Exit" << endl;
			cout << "> ";
			int select = ut.getint(0, 1);
			cout << endl;

			if (select == 1)
			{
				ofstream emptyFile(m_fileName);
				if (emptyFile.is_open())
				{
					emptyFile.close();
				}
			}
			return false;
		}
		else
		{
			while (!ifstr.eof()) {
				char firstC = ifstr.peek();
				
				//to skip empty lane
				if (firstC == '\n' || firstC == '\t'|| firstC == ' ') {
					ifstr.ignore(1000, '\n');
					firstC = ifstr.peek();
				}

				//first num of sku
				if (firstC >= '1' && firstC <= '3') {
					m_iProduct[m_noOfiProduct] = new Perishable;
					isLoad = true;
				}
				//first num of sku
				else if (firstC >= '4' && firstC <= '9') {
					m_iProduct[m_noOfiProduct] = new Item;
					isLoad = true;
				}

				//case if invalid value(sku): ex) alphabet, num..
				else {
					isLoad = false;
					ifstr.setstate(ios::failbit);
				}
				
				//repeat till no invalid value or eof
				if (isLoad) {
					// loading object to ifstr
					m_iProduct[m_noOfiProduct]->load(ifstr);
					m_noOfiProduct++;
				}
			}
			cout << m_noOfiProduct << " records loaded!\n\n";
			ifstr.close();
			return true;
		}
	}

	int AidMan::list(const char* sub_desc)
	{
		int matchNum = 0;
		if (m_noOfiProduct != 0) {
			cout << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << endl;
			cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
			for (int i = 0; i < m_noOfiProduct; i++) {
				if (sub_desc == nullptr) {
					//print as linear form
					m_iProduct[i]->linear(true);
					cout << setw(4) << setfill(' ') << i + 1 << " | ";
					cout << *m_iProduct[i] << endl;
					matchNum++;
				}
				else {
					if (*m_iProduct[i] == sub_desc) {
						m_iProduct[i]->linear(true);
						cout << setw(4) << setfill(' ') << i + 1 << " | ";
						cout << *m_iProduct[i] << endl;
						matchNum++;
					}
				}
			}
			cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
		}
		else {
			cout << "The list is empty!" << endl;
		}

		return matchNum;
	}

	int AidMan::search(int sku) const
	{
		int returnIdx = -1;
		for (int i = 0; i < m_noOfiProduct; i++)
		{
			// by calling == operator at iProduct
			if (*m_iProduct[i] == sku){
				returnIdx = i;
			}
		}
		return returnIdx;
	}

	void AidMan::remove(int index)
	{
		delete m_iProduct[index];

		//shift func -> from this index
		for (int i = index; i < m_noOfiProduct; i++)
		{
			m_iProduct[i] = m_iProduct[i + 1];
		}
		m_iProduct[m_noOfiProduct] = nullptr;
		m_noOfiProduct--;
		
	}

	void AidMan::swap(iProduct*& a, iProduct*& b)
	{
		iProduct* temp = a;
		a = b;
		b = temp;
	}

	void AidMan::bubbleSort()
	{
		for (int i = 0; i < m_noOfiProduct; i++) {
			for (int j = 0; j < m_noOfiProduct - 1; j++) 
			{
				if (m_iProduct[j]->qtyNeeded() - m_iProduct[j]->qty() < m_iProduct[j + 1]->qtyNeeded() - m_iProduct[j + 1]->qty()) 
				{
					swap(m_iProduct[j], m_iProduct[j + 1]);
				}
			}
		}
		cout << "Sort completed!" << endl << endl;
	}

	void AidMan::shipItem()
	{
		ofstream ofstr("shippingOrder.txt");
		Date curDate;
		int num = 0;

		ofstr << "Shipping Order, Date: " << curDate << endl;
		ofstr << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << endl;
		ofstr << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
		for (int i = 0; i < m_noOfiProduct; i++)
		{
			if (m_iProduct[i]->qty() == m_iProduct[i]->qtyNeeded())
			{
				m_iProduct[i]->linear(true);
				// num+1 = row num
				ofstr << right << setw(4) << setfill(' ') << num + 1 << " | ";
				// iproduct.display(ostr) so ofstr << *m_iProduct[i] << endl;
				m_iProduct[i]->display(ofstr);
				ofstr << endl;
				remove(i);
				num++;
			}
		}
		ofstr << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;

		cout << "Shipping Order for " << num << " times saved!" << endl << endl;
		ofstr.close();
	}

	AidMan::AidMan() :m_mainMenu(8, "---------------------------------\n1- List Items\n2- Add Item\n3- Remove Item\n4- Update Quantity\n5- Sort\n6- Ship Items\n7- New/Open Aid Database\n---------------------------------\n")
	{
		m_fileName = nullptr;
	}

	AidMan::AidMan(const char* fileName) : m_mainMenu(8, "---------------------------------\n1- List Items\n2- Add Item\n3- Remove Item\n4- Update Quantity\n5- Sort\n6- Ship Items\n7- New/Open Aid Database\n---------------------------------\n")
	{
		if (fileName) {
			m_fileName = new char[strlen(fileName) + 1];
			strcpy(m_fileName, fileName);
		}
		else {
			m_fileName = nullptr;
		}
	}

	AidMan::~AidMan()
	{
		deallocate();
	}

	void AidMan::run()
	{
		char tempArr[1000]{};
		int numItems = 0;
		unsigned int option;
		do {
			option = menu();
			if (option != 0 && m_fileName == nullptr && option != 7) {
				option = 7;
			}
			switch (option)
			{
			case 1:
				cout << "\n****List Items****\n";
				numItems = list(nullptr);
				if (numItems > 0)
				{
					cout << "Enter row number to display details or <ENTER> to continue:" << endl;
					cout << "> ";
					// case user press enter: go back
					if (cin.peek() == '\n')
					{
						cout << endl;
					}
					else 
					{
						int rowNum = ut.getint(0, numItems);
						m_iProduct[rowNum - 1]->linear(false);
						cout << *m_iProduct[rowNum - 1] << endl << endl;
					}
				}
				break;

			case 2:
				cout << "\n****Add Item****\n";
				if (m_noOfiProduct >= sdds_max_num_items)
				{
					cout << "Database full!";
				}
				else {
					cout << "1- Perishable" << endl;
					cout << "2- Non-Perishable" << endl;
					cout << "-----------------" << endl;
					cout << "0- Exit" << endl;
					cout << "> ";
					int cs2Select = ut.getint(0, 2);
					bool check = false;

					switch (cs2Select)
					{
					case 0:
						cout << "Aborted" << endl;
						break;
					case 1:
						m_iProduct[m_noOfiProduct] = new Perishable;
						check = true;
						break;
					case 2:
						m_iProduct[m_noOfiProduct] = new Item;
						check = true;
						break;
					}
					if (check)
					{
						//automatically ask inserting and save to insertSku *m_iProduct[m_noOfiProduct] save adress here
						int insertSku = m_iProduct[m_noOfiProduct]->readSku(cin);
						if (search(insertSku) != -1)
						{
							cout << "Sku: " << insertSku << " is already in the system, try updating quantity instead.\n" << endl;
							delete m_iProduct[m_noOfiProduct];
						}
						else
						{
							//read all elements in Item object, make sure that it's good state
							m_iProduct[m_noOfiProduct]->read(cin);
							cout  << endl;
						    m_noOfiProduct++;

						}
					}
				}
				break;

			case 3:
				cout << "\n****Remove Item****\n";
				cout << "Item description: ";
				cin.getline(tempArr, 1000, '\n');
				numItems = list(tempArr);
				//any matches founded
				if (numItems != 0)
				{
					int tmpSku = ut.getint(10000, 99999, "Enter SKU: ");
					int matchIdx = search(tmpSku);
					//case no matches
					if (matchIdx == -1)
					{
						cout << "SKU not found!";
					}
					else
					{
						cout << "Following item will be removed: " << endl;

						//display with no linear form
						m_iProduct[matchIdx]->linear(false);
						m_iProduct[matchIdx]->display(cout);

						cout << endl << "Are you sure?" << endl;
						cout << "1- Yes!" << endl;
						cout << "0- Exit" << endl;
						cout << "> ";
						int cs3Select = ut.getint(0, 1);

						if (cs3Select == 0)
						{
							cout << "Aborted!" << endl;
						}
						else if (cs3Select == 1)
						{
							remove(matchIdx);
							cout << "Item removed!" << endl;
						}
					}
					cout << endl;
				}
				break;

			case 4:
				cout << "\n****Update Quantity****\n";

				cout << "Item description: ";
				cin.getline(tempArr, 1000, '\n');
				numItems = list(tempArr);
				// if any item matches
				if (numItems != 0)
				{
					int tmpSku = ut.getint(10000, 99999, "Enter SKU: ");
					int matchIdx = search(tmpSku);
					//case no matches
					if (matchIdx == -1)
					{
						cout << "SKU not found!";
					}
					else
					{
						cout << "1- Add" << endl;
						cout << "2- Reduce" << endl;
						cout << "0- Exit" << endl;
						cout << "> ";

						int cs4Select = ut.getint(0, 2);

						// case quit
						if (cs4Select == 0) 
						{
							cout << "Aborted!" << endl;
						}

						else if (cs4Select == 1)
						{
							if (m_iProduct[matchIdx]->qty() == m_iProduct[matchIdx]->qtyNeeded())
							{
								cout << "Quantity Needed already fulfilled!" << endl;
							}
							else
							{
								cout << "Quantity to add: ";
								int addQty = ut.getint(1, m_iProduct[matchIdx]->qtyNeeded() - m_iProduct[matchIdx]->qty());
								// same meaning with : m_iProduct[matchIdx]->operator +=(addQty);
								*m_iProduct[matchIdx] += addQty;
								cout << addQty << " items added!" << endl;
							}
						}

						//case choose 2
						else
						{
							if (m_iProduct[matchIdx]->qty() == 0)
							{
								cout << "Quantity on hand is zero!" << endl;
							}
							else
							{
								cout << "Quantity to reduce: ";
								int reduceQty = ut.getint(1, m_iProduct[matchIdx]->qty());
								// same meaning with: m_iProduct[matchIdx]->operator -=(reduceQty);
								*m_iProduct[matchIdx] -= reduceQty;
								cout << reduceQty << " items removed!" << endl;
							}
						}
					}

				}
				else
				{
					cout << "No matches found" << endl;
				}
				cout << endl;
				break;

			case 5:
				cout << "\n****Sort****\n";
				bubbleSort();
				break;

			case 6:
			    cout << "\n****Ship Items****\n";
				shipItem();
				break;

			case 7:
				cout << "\n****New/Open Aid Database****\n";
				load();
				break;

		     //case1
			default:
				cout << "Exiting Program!" << endl;
				// save changes before exit
				save();
				break;
			}

		} while (option != 0);
	}
}