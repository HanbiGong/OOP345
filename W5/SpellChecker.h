/*/////////////////////////////////////////////////////////////////////////
Full Name  : Hanbi Gong
Student ID#: 111932224
Email      : hgong12@myseneca.ca
Section    : OOP 345

I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. 
This submitted piece of work has not been shared with any other student or 3rd party content provider.

/////////////////////////////////////////////////////////////////////////*/


#ifndef SENECA_SPELLCHECKER_H
#define SENECA_SPELLCHECKER_H

#include <iostream>
#include "Book.h"

namespace seneca {
	class SpellChecker {
	private:
		std::string m_badWords[6];
		std::string m_goodWords[6];
		std::string remove_trim(std::string input);
		size_t m_missCnt[6];
	public:
		SpellChecker();
		SpellChecker(const char* filename);
		void operator()(std::string& text);
		void showStatistics(std::ostream& out) const;
	};
}
#endif