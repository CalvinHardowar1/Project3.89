#include <iostream>
#include "Book.hpp"

#ifndef ARRAY_BAG_
#define ARRAY_BAG_
#include <vector>

template <class ItemType>
class ArrayBag
{
private:

protected:
	static const int DEFAULT_CAPACITY = 10;
	ItemType items[DEFAULT_CAPACITY];
	int item_count_;
	int getIndexOf(const ItemType& target) const;
public:
	ArrayBag();
	ArrayBag(int item_count, int items_arr[]);
	int getCurrentSize() const;
	bool isEmpty()const;
	bool add(const ItemType& new_entry);
	bool remove(const ItemType& an_entry);
	void clear();
	bool contains(const ItemType& an_entry)const;
	int getFrequencyOf(const ItemType& an_entry) const;
	ArrayBag<ItemType>& operator += (const ArrayBag<ItemType>& obj);
	ArrayBag<ItemType>& operator /= (const ArrayBag<ItemType>& obj);
};
#endif