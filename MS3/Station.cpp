// Name: Hanbi Gong
// Seneca Student ID: 111932224
// Seneca email: hgong12@myseneca.ca
// Date of completion: Aug 2nd, 2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Station.h"

namespace seneca {
	
	int Station::m_widthField = 0;
	int Station::id_generator = 0;
	
	Station::Station(const std::string str):m_id(0), m_name(""), m_desc(""), m_serialNumber(0), m_number(0)
	{
		Utilities util;
		size_t next_pos = 0;
		bool more = true;

		m_id = ++id_generator;

		m_name = util.extractToken(str, next_pos, more);
		m_serialNumber = std::stoul(util.extractToken(str, next_pos, more));
		m_number = std::stoul(util.extractToken(str, next_pos, more));

		if (int(util.getFieldWidth()) > m_widthField) {
			m_widthField = int(util.getFieldWidth());
		}

		m_desc = util.extractToken(str, next_pos, more);
	}
	const std::string& Station::getItemName() const
	{
		return m_name;
	}
	size_t Station::getNextSerialNumber()
	{
		return m_serialNumber++;
	}
	size_t Station::getQuantity() const
	{
		return m_number;
	}
	void Station::updateQuantity()
	{
		if (m_number > 0) {
			m_number--;
		}
	}
	void Station::display(std::ostream& os, bool full) const
	{
		os << std::setw(3)<<std::right << std::setfill('0') << m_id << " | ";
		os << std::setw(m_widthField) << std::setfill(' ') << std::left << m_name << " | ";
		os << std::setw(6) << std::setfill('0') << std::right << m_serialNumber << " | ";

		if (full) {
			os << std::setw(4) << std::setfill(' ') << m_number << " | ";
			os << m_desc;
		}

		os << std::endl;
	}
}
