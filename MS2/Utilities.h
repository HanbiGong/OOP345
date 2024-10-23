#ifndef SENECA_UTILITIES_H
#define SENECA_UTILITIES_H

#include <string>
#include <iostream>
#include <stdexcept>
#include <algorithm>

namespace seneca
{
	class Utilities{
	private:
		size_t m_widthField = 1;
	public:
		static char m_delimiter; // 모든 객체가 하나의 값을 공유해야함으로 static을 사용함
		void setFieldWidth(size_t newWidth);
		size_t getFieldWidth() const;
		std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
		static void setDelimiter(char newDelimiter);
		static char getDelimiter();
	};
}

#endif
