#include "Reservation.h"
#include <string>
#include <iomanip>
#include <iostream>

namespace seneca {
	std::string Reservation::remove_trim(std::string input)
	{
		size_t first = input.find_first_not_of(' '); 
		size_t end = input.find_last_not_of(' ');
		if (first == std::string::npos) {
			return "";
		}
		return input.substr(first, end - first + 1);
	}
	Reservation::Reservation() {
		m_reservationId = "";
		m_name = "";
		m_email = "";
		m_numPeople = 0;
		m_day = 1;
		m_hour = 1;
	}
	Reservation::Reservation(const std::string& res) : m_reservationId(""), m_name(""), m_email(""), m_numPeople(0), m_day(1), m_hour(1) {
		size_t start_pos = res.find(":");
		m_reservationId = remove_trim(res.substr(0, start_pos));

		start_pos += 1;
		size_t end_pos = res.find(',', start_pos);

		m_name = remove_trim(res.substr(start_pos, end_pos - start_pos));
		start_pos = end_pos + 1;
		end_pos = res.find(',', start_pos);

		m_email = remove_trim(res.substr(start_pos, end_pos - start_pos));
		start_pos = end_pos + 1;
		end_pos = res.find(',', start_pos);

		if (remove_trim(res.substr(start_pos, end_pos - start_pos)) != "") {
			m_numPeople = std::stoi(remove_trim(res.substr(start_pos, end_pos - start_pos)));
		}
		start_pos = end_pos + 1;
		end_pos = res.find(',', start_pos);


		if (remove_trim(res.substr(start_pos, end_pos - start_pos)) != "") {
			m_day = std::stoi(remove_trim(res.substr(start_pos, end_pos - start_pos)));
		}
		start_pos = end_pos + 1;
		end_pos = res.find(',', start_pos);

		if (remove_trim(res.substr(start_pos, end_pos - start_pos)) != "") {
			m_hour = std::stoi(remove_trim(res.substr(start_pos, end_pos - start_pos)));
		}
		start_pos = end_pos + 1;
		end_pos = res.find(',', start_pos);
	}

	void Reservation::update(int day, int time) {
		// Assume the parameters are correct and don't require validation.
		m_day = day;
		m_hour = time;
	}

	std::ostream& operator<<(std::ostream& os, const Reservation& rs) {

		std::string tag = "";
		if (rs.m_hour >= 6 && rs.m_hour <= 9) {
			tag = "Breakfast";
		}
		else if (rs.m_hour >= 11 && rs.m_hour <= 15) {
			tag = "Lunch";
		}
		else if (rs.m_hour >= 17 && rs.m_hour <= 21) {
			tag = "Dinner";
		}
		else {
			tag = "Drinks";
		}

		// Reservation ID: NAME  <email>    Breakfast on day DAY @ HOUR:00 for #PARTY_SIZE people.
		os << "Reservation " << std::setw(10) << std::right << rs.m_reservationId << ": "
			<< std::setw(20) << std::right << rs.m_name << "  "
			<< std::setw(20) << std::left << ("<" + rs.m_email + ">") << "    "
			<< (tag + " on day ")
			<< rs.m_day << " @ " << rs.m_hour << ":00 for "
			<< rs.m_numPeople << " " << (rs.m_numPeople == 1 ? "person" : "people") << "." << std::endl;

		return os;

	}

}
