/*/////////////////////////////////////////////////////////////////////////
Full Name  : Hanbi Gong
Student ID#: 111932224
Email      : hgong12@myseneca.ca
Section    : OOP 345

I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. 
This submitted piece of work has not been shared with any other student or 3rd party content provider.

/////////////////////////////////////////////////////////////////////////*/


#ifndef SENECA_MOVIE_H
#define SENECA_MOVIE_H

#include "SpellChecker.h"
#include <iostream>

namespace seneca {
	class Movie {
	private:
		std::string m_title;
		int m_year;
		std::string m_desc;
		std::string remove_trim(std::string input);
	public:
		Movie();
		const std::string& title() const;
		Movie(const std::string& strMovie);
		// 이게 functor: 함수 객체
		template <typename T>
		void fixSpelling(T& spellChecker) {
			spellChecker(m_title);
			spellChecker(m_desc);
		}
		friend std::ostream& operator<<(std::ostream& os, const Movie& movie);
	};

}
#endif