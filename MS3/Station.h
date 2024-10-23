// Name: Hanbi Gong
// Seneca Student ID: 111932224
// Seneca email: hgong12@myseneca.ca
// Date of completion: Aug 2nd, 2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

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