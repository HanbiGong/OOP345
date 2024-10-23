/*/////////////////////////////////////////////////////////////////////////
Full Name  : Hanbi Gong
Student ID#: 111932224
Email      : hgong12@myseneca.ca
Section    : OOP 345

I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. 
This submitted piece of work has not been shared with any other student or 3rd party content provider.

/////////////////////////////////////////////////////////////////////////*/


#include <iostream>
#include <fstream>
#include <iomanip>
#include "SpellChecker.h"

namespace seneca {

	std::string SpellChecker::remove_trim(std::string input)
	{
		size_t first = input.find_first_not_of(' ');
		size_t end = input.find_last_not_of(' ');
		if (first == std::string::npos) {
			return "";
		}
		return input.substr(first, end - first + 1);
	}
	SpellChecker::SpellChecker() {
		for (size_t i = 0; i < 6; i++) {
			m_missCnt[i] = 0;
			m_badWords[i] = "";
			m_goodWords[i] = "";
		}
	}
	SpellChecker::SpellChecker(const char* filename)
	{
		// 멤버변수 초기화
		for (size_t i = 0; i < 6; i++) {
			m_missCnt[i] = 0;
			m_badWords[i] = "";
			m_goodWords[i] = "";
		}
		std::ifstream file(filename);
		if (!file)
		{
			throw "Bad file name!";
		}
		std::string strWord;

		// Read from the file, and load and store data
		file.clear();
		for (size_t i = 0; i < 6; i++) {
			if (file) {
				std::getline(file, strWord);
				size_t start_pos = strWord.find(" ");

				m_badWords[i] = remove_trim(strWord.substr(0, start_pos));

				start_pos += 1;
				size_t end_pos = strWord.find('\n', start_pos);

				m_goodWords[i] = remove_trim(strWord.substr(start_pos, end_pos - start_pos));
			}
		}
		file.close();
	}
	void SpellChecker::operator()(std::string& text)
	{
		// 몇번이나 수정되었는지 저장해야 함
		// find로 해당 문자가 다른 위치에 있으면 replace함
		// descprition이 들어갈 것. 그리고 bad word랑 매칭되는 것 있으면 ?
		for (size_t i = 0; i < 6; i++) {
			while (text.find(m_badWords[i]) != std::string::npos) {
				size_t pos = text.find(m_badWords[i]);
				text.replace(pos, m_badWords[i].size(), m_goodWords[i]);
				m_missCnt[i]+=1;
			}
		}
	}
	void SpellChecker::showStatistics(std::ostream& out) const
	{
		std::cout << "Spellchecker Statistics" << std::endl;
		for (size_t i = 0; i < 6; i++) {
			out << std::setw(15) << std::right << m_badWords[i];
			out << ": ";
			out << m_missCnt[i] << " replacements" << std::endl;
			
		}

	}
}