#ifndef SENECA_BOOK_H
#define SENECA_BOOK_H

#include <iostream>
#include <string>

namespace seneca {
	class Book
	{
		std::string m_title{};
		unsigned m_numChapters{};
		unsigned m_numPages{};
	public:
		Book();
		Book(const std::string& title, unsigned nChapters, unsigned nPages);
		Book(const Book& other);
		Book& operator=(const Book& other);
		Book(Book&& other) noexcept;
		Book& operator=(Book&& other) noexcept;
		std::ostream& print(std::ostream& os) const;
		// For part2 -- 비교 연산자 재정의 필요
		bool operator> (const Book& other) const;
		bool operator< (const Book& other) const;

	};
	std::ostream& operator<<(std::ostream& os, const Book& bk);
}

#endif
