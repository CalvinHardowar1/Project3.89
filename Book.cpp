#include <iostream>
#include "Book.hpp"

Book::Book(std::string title, std::string author, int page_count, bool is_digital) : title_{ title }, author_{ author }, page_count_{ page_count }, is_digital_{ is_digital }{}


std::string Book::getTitle() const
{
    return title_;
}

std::string Book::getAuthor() const
{
    return author_;
}

int Book::getPageCount() const
{
    return page_count_;
}

bool Book::isDigital() const
{
    return is_digital_;
}

void Book::setTitle(const std::string& title)
{
    title_ = title;
}

void Book::setAuthor(const std::string& author)
{
    author_ = author;
}

void Book::setPageCount(const int& page_count)
{
    if (page_count > 0)
    {
        page_count_ = page_count;
    }
}

void Book::setDigital()
{
    is_digital_ = true;
}
/**
  @post     : displays Book data in the form:
  "[title_] is written by [author_]. Page Count: [page_count_]. [It is / It is not] available digitally.\n"     
*/
void Book::display()
{
    std::string is_or_not;
    if (is_digital_ == true)
    {
        is_or_not = "It is ";
    }
    else
    {
        is_or_not = "It is not ";
    }
    std::cout << title_ << " is written by " << author_ <<". Page Count: " << page_count_ << ". " << is_or_not << "available digitally. \n";
}

/**
  @param     : A reference to the right hand side of the == operator.
  @return     : Returns true if the right hand side book is the identical, false otherwise.

  Note: ALL attributes must be equal for two books to be deemed equal.

  Example: In order for book1 to be == to book 2 we must have:
  - The same title
  - The same author
  - The same page count
  - They must either be both digital or both not
/*/

bool Book::operator==(const Book& obj) const
{
    if (title_ == obj.title_ && author_ == obj.author_ && page_count_ == obj.page_count_ && is_digital_ == obj.is_digital_)
    {
        return true;
    }
    else
        return false;
}

/**
  @param     : A reference to the right hand side of the != operator.
  @return     : Returns true if the right hand side book is NOT identical (!=), false otherwise.

  Note: ALL attributes must be equal for two books to be deemed equal.
/*/

bool Book::operator!=(const Book& obj) const
{
    if (title_ != obj.title_ || author_ != obj.author_ || page_count_ != obj.page_count_ || is_digital_ != obj.is_digital_)
    {
        return true;
    }
    else
        return false;
}


void Book::displayTitlesOfBooks()
{
    std::cout << this->getTitle();
}