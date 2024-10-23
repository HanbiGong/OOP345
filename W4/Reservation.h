#ifndef SENECA_RESERVATION_H
#define SENECA_RESERVATION_H

#include <string>
namespace seneca {
	class Reservation {
	private:
		std::string m_reservationId;
		std::string m_name;
		std::string m_email;
		unsigned int m_numPeople;
		unsigned int m_day; 
		unsigned int m_hour;
		std::string remove_trim(std::string input);
	public:
		// default constructor
		Reservation();
		// other constructor
		Reservation(const std::string& res);
		void update(int day, int time);
		// friend insertion operator
		friend std::ostream& operator<<(std::ostream& os, const Reservation& rs);
	};
}
#endif