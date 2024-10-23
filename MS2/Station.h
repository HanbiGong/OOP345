#ifndef SENECA_STATION_H
#define SENECA_STATION_H

#include "Utilities.h"
#include<string>
#include<iomanip>

namespace seneca
{
	class Station{
	private:
		int m_id;
		std::string m_name;
		std::string m_desc;
		unsigned int m_serialNumber;
		unsigned int m_number;
	public:
		static int m_widthField;
		static int id_generator;
		Station(std::string str);
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
	};
}

#endif