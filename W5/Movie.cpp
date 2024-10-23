/*/////////////////////////////////////////////////////////////////////////
Full Name  : Hanbi Gong
Student ID#: 111932224
Email      : hgong12@myseneca.ca
Section    : OOP 345

I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. 
This submitted piece of work has not been shared with any other student or 3rd party content provider.

/////////////////////////////////////////////////////////////////////////*/


#include "Movie.h"
#include <iomanip>

namespace seneca {
	std::string Movie::remove_trim(std::string input)
	{
		size_t first = input.find_first_not_of(' ');
		size_t end = input.find_last_not_of(' ');
		if (first == std::string::npos) {
			return "";
		}
		return input.substr(first, end - first + 1);
	}

	Movie::Movie()
	{
		m_title = "";
		m_year = 0;
		m_desc = "";
	}
	const std::string& Movie::title() const
	{
		return m_title;
	}
	Movie::Movie(const std::string& strMovie)
	{
		size_t start_pos = strMovie.find(",");

		m_title = remove_trim(strMovie.substr(0, start_pos));
		start_pos += 1;
		size_t end_pos = strMovie.find(',', start_pos);

		if (remove_trim(strMovie.substr(start_pos, end_pos - start_pos)) != "") {
			m_year = std::stoi(remove_trim(strMovie.substr(start_pos, end_pos - start_pos)));
		}
		start_pos = end_pos+1;
		end_pos = strMovie.find('\n', start_pos);

		m_desc = remove_trim(strMovie.substr(start_pos, end_pos - start_pos));
	}

	std::ostream& operator<<(std::ostream& os, const Movie& movie)
	{
		os << std::right << std::setw(40) << movie.m_title << " | "
			<< std::right << std::setw(4) << movie.m_year << " | "
			<< movie.m_desc;
		os << std::endl;
		return os;
	}
}