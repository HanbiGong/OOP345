// Name: Hanbi Gong
// Seneca Student ID: 111932224
// Seneca email: hgong12@myseneca.ca
// Date of completion: Aug 2nd, 2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SENECA_WORKSTATION_H
#define SENECA_WORKSTATION_H

#include <iostream>
#include <deque>

#include "Station.h"
#include "CustomerOrder.h"

namespace seneca {
	extern std::deque<seneca::CustomerOrder> g_pending;
	extern std::deque<seneca::CustomerOrder> g_completed;
	extern std::deque<seneca::CustomerOrder> g_incomplete;

	class Workstation: public Station{
	private:
		std::deque<seneca::CustomerOrder> m_orders; // Entering the back and exiting the front
		Workstation* m_pNextStation;
	public:
		Workstation(const std::string& str); // string�� station Ŭ������ �ѱ�
		
		void fill(std::ostream& os);
		bool attemptToMoveOrder();
		void setNextStation(Workstation* station);
		Workstation* getNextStation() const;
		void display(std::ostream& os) const;
		Workstation& operator+=(CustomerOrder&& newOrder);

		// the object cannot be copied or moved. 
		Workstation(const Workstation& other) = delete;
		Workstation& operator=(const Workstation& other) = delete;
		Workstation(Workstation&& other) noexcept = delete;
		Workstation& operator=(Workstation&& other) noexcept = delete;

	};
}

#endif