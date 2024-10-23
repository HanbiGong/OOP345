#include "Utilities.h"

namespace seneca {
    char Utilities::m_delimiter = ' ';
	void Utilities::setFieldWidth(size_t newWidth)
	{
		m_widthField = newWidth;
	}
	size_t Utilities::getFieldWidth() const
	{
		return m_widthField;
	}
	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
	{
        if (next_pos >= str.length()) {
            more = false;
            return "";
        }

        size_t pos = str.find(m_delimiter, next_pos);

        // Check for delimiter at next_pos
        if (pos == next_pos) {
            more = false;
            throw std::runtime_error("Delimiter found at the next position.");
        }

        std::string token;

        if (pos == std::string::npos) {
            token = str.substr(next_pos);
            next_pos = str.length();
            more = false;
        }
        else {
            token = str.substr(next_pos, pos - next_pos);
            next_pos = pos + 1;
            more = true;
        }

        // Trim spaces from beginning and end
        token.erase(token.begin(), std::find_if(token.begin(), token.end(), [](unsigned char ch) { return !std::isspace(ch); }));
        token.erase(std::find_if(token.rbegin(), token.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(), token.end());

        // Check for empty token after trimming
        if (token.empty()) {
            more = false;
            throw std::runtime_error("Empty token found");
        }

        // Update m_widthField if necessary
        if (token.length() > m_widthField) {
            m_widthField = token.length();
        }

        return token;
	}
	void Utilities::setDelimiter(char newDelimiter)
	{
		m_delimiter = newDelimiter;
	}
	char Utilities::getDelimiter()
	{
		return m_delimiter;
	}
}