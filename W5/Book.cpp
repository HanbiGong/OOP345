/*/////////////////////////////////////////////////////////////////////////
Full Name  : Hanbi Gong
Student ID#: 111932224
Email      : hgong12@myseneca.ca
Section    : OOP 345

I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. 
This submitted piece of work has not been shared with any other student or 3rd party content provider.

/////////////////////////////////////////////////////////////////////////*/

#include "Book.h"
#include <iostream>
#include <iomanip>

namespace seneca {
	std::string Book::remove_trim(std::string input)
	{
		size_t first = input.find_first_not_of(' ');
		size_t end = input.find_last_not_of(' ');
		if (first == std::string::npos) {
			return "";
		}
		return input.substr(first, end - first + 1);
	}
	Book::Book()
	{
		m_author = "";
		m_title = "";
		m_country = "";
		m_year = 0;
		m_price = 0.0;
		m_desc = "";
	}
	const std::string& Book::title() const
	{
		return m_title;
	}
	const std::string& Book::country() const
	{
		return m_country;
	}
	const size_t& Book::year() const
	{
		return m_year;
	}
	double& Book::price()
	{
		return m_price;
	}
	void Book::setPrice(const double p)
	{
		m_price = p;
	}
	Book::Book(const std::string& strBook): m_author(""), m_title(""), m_country(""), m_year(0), m_price(0.0), m_desc("")
	{
		size_t start_pos = strBook.find(",");

		m_author = remove_trim(strBook.substr(0, start_pos));
		start_pos += 1;
		size_t end_pos = strBook.find(',', start_pos);

		m_title = remove_trim(strBook.substr(start_pos, end_pos - start_pos));
		start_pos = end_pos + 1;
		end_pos = strBook.find(',', start_pos);

		m_country = remove_trim(strBook.substr(start_pos, end_pos - start_pos));
		start_pos = end_pos + 1;
		end_pos = strBook.find(',', start_pos);

		if (remove_trim(strBook.substr(start_pos, end_pos - start_pos)) != "") {
			m_price = std::stod(remove_trim(strBook.substr(start_pos, end_pos - start_pos)));
		}
		start_pos = end_pos + 1;
		end_pos = strBook.find(',', start_pos);


		if (remove_trim(strBook.substr(start_pos, end_pos - start_pos)) != "") {
			m_year = std::stoi(remove_trim(strBook.substr(start_pos, end_pos - start_pos)));
		}
		start_pos = end_pos + 1;
		end_pos = strBook.find('\n', start_pos);

		m_desc = remove_trim(strBook.substr(start_pos, end_pos - start_pos));

	}
	std::ostream& operator<<(std::ostream& os, const Book& book)
	{
		os << std::right << std::setw(20) << book.m_author << " | "
			<< std::right << std::setw(22) << book.m_title << " | "
			<< std::right << std::setw(5) << book.m_country << " | "
			<< std::left << std::setw(4) << book.m_year << " | "
			<< std::right << std::setw(6) << std::fixed << std::setprecision(2) << book.m_price << " | "
			<< book.m_desc;
		os << std::endl;
		return os;
	}
}