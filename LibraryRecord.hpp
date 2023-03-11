#include"ArrayBag.cpp"
#include "Book.hpp"
#include<vector>
class LibraryRecord :public ArrayBag<Book>
{
private:
	std::vector<Book> checkedout;
	std::vector<int> no_checkout;
public:
	LibraryRecord();
	bool checkIn(Book& in_book);
	bool checkOut(Book& out_book);
	int getCheckOutHistory(Book& book);
	void display();
	int findIndex(const Book& book);
	void displayTitles();
	bool duplicateStock();
	bool removeStock(Book& book);
	bool equivalentRecords(LibraryRecord& record);
	LibraryRecord& operator += (const LibraryRecord& obj);
	LibraryRecord& operator /= (const LibraryRecord& obj);
};