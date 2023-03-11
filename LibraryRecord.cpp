#include "LibraryRecord.hpp"

#include <iostream>
#include "LibraryRecord.hpp"

LibraryRecord::LibraryRecord()
{
}
/** @param:   A reference to a Book object to be checked in
    @return:  returns true if a book was successfully added to items_, false otherwise
    @post:    adds book to items_.
 **/
bool LibraryRecord::checkIn(Book& in_book)
{
	if (add(in_book))
	{
		return true;
	}
	else
		return false;
}
/** @param:   A reference to a Book object to be checked out   
    @return:  returns true if a book was successfully removed from items_, false otherwise
    @post:    removes the book from the LibraryRecord and if remove was successful, it adds the book to the vector of checked-out books.
 **/
bool LibraryRecord::checkOut(Book& out_book)
{
	int i = findIndex(out_book);

	if (i >= 0)
	{
		no_checkout[i]++;
		return true;
	}
	else
	{
		checkedout.push_back(out_book);
		no_checkout.push_back(1);
		return true;
	}

	return false;

}
/**
  @param:   A reference to a Book object
  @return:  The number of times (int) the referenced Book has been checked out
*/
int LibraryRecord::getCheckOutHistory(Book& book)
{
	int i = findIndex(book);
	if (i == -1)
		return 0;
	else
		return no_checkout[i];
}
/**
    @post:    Outputs the names of the Books in the LibraryRecord and the number of times each Book has been cheked out

      For each Book in the LibraryRecord you will output:
             "[title_] is written by [author_]. Page Count: [page_count_]. [It is / It is not] available digitally.\n
             It has been checked out [_] times.\n"
  **/
void LibraryRecord::display()
{
	Book obj;
	
	for (int i = 0; i < checkedout.size(); i++)
	{
		obj = checkedout[i];
		obj.display();
		std::cout << "It has been checkedout " << no_checkout[i] << " times." << std::endl;
	}
}

int LibraryRecord::findIndex(const Book& book)
{
	for (int i = 0; i < checkedout.size(); i++)
	{
		if (checkedout[i] == book)
		{
			return i;
		}
	}
	return -1;
}
/**
  @post:    Prints the title of each Book in the LibraryRecord
  Example:
  "title1, title2, title3, title4!\n" Note the commas and exclamation mark.
*/
void LibraryRecord::displayTitles()
{
	Book temp;
	for (int i = 0; i < item_count_; i++)
	{
		temp = items[i];
		temp.displayTitlesOfBooks();
		
		if (i < item_count_ - 1)
		{
			std::cout << ", ";
		}
		else {
			std::cout << "!";
		}
	}
}
/**
  @return:    Returns true if the LibraryRecord was successfully duplicated, false otherwise (there is nothing to duplicate or duplicating would exceed DEFAULT_CAPACITY).
  @post:      Duplicates all the items in the LibraryRecord
  Example: we originally have [book1, book2] and after duplication we have [book1, book2, book1, book2]
*/
bool LibraryRecord::duplicateStock()
{
	LibraryRecord newRecord;
	if (item_count_ > 10 || item_count_ < 0)
	{
		return false;
	}

	for (int i = 0; i < checkedout.size(); i++)
	{
		newRecord.checkedout.push_back(checkedout[i]);
	}

	newRecord.item_count_ = item_count_;
	for (int i = 0; i < item_count_; i++)
	{
		newRecord.add(items[i]);
	}

	return true;
}
/**
  @param:   A reference to a book
  @return: True if at least one copy of the referenced book was removed from items_, false otherwise 
  @post: remove all occurrences of the referenced book
*/
bool LibraryRecord::removeStock(Book& book)
{
	int freq = getFrequencyOf(book);
	int count = 0;
	for (int i = 0; i < freq; i++)
	{
		bool flag = remove(book);
		if (flag)
		{
			count++;
		}
	}

	if (count >= 1)
		return true;
	else
		return false;
}
/**
  @param:   A reference to another LibraryRecord
  @return:  Returns true if the 2 library records have the same contents (including the same number of duplicates for each book), regardless of their order. For example, if the current holdings of the LibraryRecord are [book1, book2, book3]
  and those of the referenced LibraryRecord are [book3, book1, book2], it will return true.

  However, [book1, book2, book2, book3] is not equivalent to [book1, book2, book3, book3], because it contains two copies of book2 and only one copy of book3
*/
bool LibraryRecord::equivalentRecords(LibraryRecord& record)
{
	if (item_count_ != record.item_count_)
	{
		return false;
	}
	Book temp;
	int f1, f2;
	for (int i = 0; i < item_count_; i++)
	{
		temp = items[i];
		f1 = getFrequencyOf(temp);
		f2 = record.getFrequencyOf(temp);
		if (f1 != f2)
		{
			return false;
		}
	}
	return true;
}
/**
    @param:   A reference to another LibraryRecord object
    @post:    Combines the contents from both LibraryRecord objects, including duplicates.
    Example: [book1, book2, book3] += [book1, book4] will produce [book1, book2, book3, book1, book4]

    IMPORTANT: We are carrying over the number of times a book has been checked out. For example, if we have LibraryRecord1 += LibraryRecord2 and
    book4 is in LibraryRecord2 and has been checked out 2 times, then it should still be checked out 2 times in LibraryRecord1 after the += operation
    Hint: use getCheckOutHistory and the checkout history vector
*/
LibraryRecord& LibraryRecord::operator += (const LibraryRecord& obj)
{
	int s = item_count_ + obj.item_count_;

	for (int i = 0; i < obj.checkedout.size(); i++)
	{
		int index = this->findIndex(obj.checkedout[i]);
		if (index == -1)
		{
			this->checkedout.push_back(obj.checkedout[i]);
			this->no_checkout.push_back(obj.no_checkout[i]);
		}
		else {
			int ind = no_checkout[index] += obj.no_checkout[i];
			this->no_checkout[index] = ind;
		}
	}

	item_count_ = s;
	
	for (int i = 0; i < obj.item_count_; i++)
	{
		add(obj.items[i]);
	}
	return *this;
}
/** @param:   A reference to another LibraryRecord object
    @post:    Combines the contents from both LibraryRecord objects, EXCLUDING duplicates.
    Example: [book1, book2, book3] /= [book1, book4] will produce [book1, book2, book3, book4]

    IMPORTANT: We are carrying over the number of times a book has been checked out. For example, if we have LibraryRecord1 /= LibraryRecord2 and
    book4 is in LibraryRecord2 and has been checked out 2 times, then it should still be checked out 2 times in LibraryRecord1 after the /= operation
    Hint: use getCheckOutHistory and the checkout history vector
*/
LibraryRecord& LibraryRecord::operator/=(const LibraryRecord& obj)
{
	int s = item_count_ + obj.item_count_;
	
	for (int i = 0; i < checkedout.size(); i++)
	{
		int index = this->findIndex(obj.checkedout[i]);
		if (this->findIndex(obj.checkedout[i]) == -1)
		{
			this->checkedout.push_back(obj.checkedout[i]);
			this->no_checkout.push_back(obj.no_checkout[i]);
		}
		else {
			this->no_checkout[index] += obj.no_checkout[i];
		}
	}

	item_count_ = s;

	for (int i = 0; i < obj.item_count_; i++)
	{
		if (this->contains(items[i]) == false)
		{
			this->add(obj.items[i]);
		}
	}
	return *this;
}