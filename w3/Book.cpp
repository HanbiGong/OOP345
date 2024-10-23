#include "Book.h"

#include <iostream>
#include <string>
#include <iomanip>

namespace seneca {

    // Default constructor
    Book::Book() : m_title(""), m_numChapters(0), m_numPages(0) {}

    // Parameterized constructor
    Book::Book(const std::string& title, unsigned nChapters, unsigned nPages)
        : m_title(title), m_numChapters(nChapters), m_numPages(nPages) {
    }

    // Copy constructor
    Book::Book(const Book& other)
        : m_title(""), m_numChapters(0), m_numPages(0) {
        *this = other;
    }

    // Copy assignment operator
    Book& Book::operator=(const Book& other) {
        if (this != &other) {
            m_title = other.m_title;
            m_numChapters = other.m_numChapters;
            m_numPages = other.m_numPages;
        }
        return *this;
    }

    // Move constructor
    Book::Book(Book&& other) noexcept
        : m_title(std::move(other.m_title)), m_numChapters(other.m_numChapters), m_numPages(other.m_numPages) {
        other.m_numChapters = 0;
        other.m_numPages = 0;
    }

    // Move assignment operator
    Book& Book::operator=(Book&& other) noexcept {
        if (this != &other) {
            m_title = std::move(other.m_title);
            m_numChapters = other.m_numChapters;
            m_numPages = other.m_numPages;

            other.m_numChapters = 0;
            other.m_numPages = 0;
        }
        return *this;
    }

    // Print function
    std::ostream& Book::print(std::ostream& os) const {
        // Book이 valid 할때만 정보를 출력한다.
        if (!m_title.empty() && m_numChapters > 0 && m_numPages > 0) {
            std::string titleInfo = m_title + "," + std::to_string(m_numChapters) + "," + std::to_string(m_numPages);
            double avgPagesPerChapter = static_cast<double>(m_numPages) / m_numChapters;
            os << std::right << std::setw(56) << titleInfo
                << " | "
                << std::left << std::setw(15) << ("(" + std::to_string(avgPagesPerChapter) + ")");
        }
        else {
            os << "| Invalid book data";
        }
        return os;
    }

    bool Book::operator>(const Book& other) const
    {
        double avgPagesPerChapter = static_cast<double>(m_numPages) / m_numChapters;
        double other_avgPagesPerChapter = static_cast<double>(other.m_numPages) / other.m_numChapters;
        if (avgPagesPerChapter > other_avgPagesPerChapter) {
            return true;
        }
        return false;
    }

    bool Book::operator<(const Book& other) const
    {
        double avgPagesPerChapter = static_cast<double>(m_numPages) / m_numChapters;
        double other_avgPagesPerChapter = static_cast<double>(other.m_numPages) / other.m_numChapters;
        if (avgPagesPerChapter < other_avgPagesPerChapter) {
            return true;
        }
        return false;
    }

    // Overloaded operator<< for printing
    std::ostream& operator<<(std::ostream& os, const Book& bk) {
        return bk.print(os);
    }

}
