// Name: Hanbi Gong
// Seneca Student ID: 111932224
// Seneca email: hgong12@myseneca.ca
// Date of completion: Aug 2nd, 2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Workstation.h"


namespace seneca {

	std::deque<seneca::CustomerOrder> g_pending;
	std::deque<seneca::CustomerOrder> g_completed;
	std::deque<seneca::CustomerOrder> g_incomplete;

	Workstation::Workstation(const std::string& str):Station(str)
	{
		m_pNextStation = nullptr;
	}
	void Workstation::fill(std::ostream& os)
	{
		// m_orders�� �ֹ��� ����� 
		if (!m_orders.empty()) {
			m_orders.front().fillItem(*this, os);
		}
		
	}
	bool Workstation::attemptToMoveOrder()
	{
		if (m_orders.empty())
		{
			return false;
		}

		if (m_orders.front().isItemFilled(getItemName()) || getQuantity() < 1) {
			if (m_pNextStation != nullptr) { // ���� WorkStation���� �Ѿ
				*m_pNextStation += std::move(m_orders.front()); // ���� �ֹ��� ���� workstation�� m_order�� �ű�
				m_orders.pop_front();
			}
			else { // ���� ���� Station�� ���ٸ� �ش� �ֹ��� station�� ������ ���� �°��̴ϱ�
				if (m_orders.front().isOrderFilled()) { // �ֹ��� �� ó���Ǿ�����
					g_completed.push_back(std::move(m_orders.front())); // �ֹ��� �տ� �ִ� ���� ������ g_completed ť�� �ֱ�
					m_orders.pop_front();
				}
				else { // �ֹ��� ó������ ���� ���� �ִٸ� 
					g_incomplete.push_back(std::move(m_orders.front()));
					m_orders.pop_front();
				}
			}
		}
		return true;
	}
	void Workstation::setNextStation(Workstation* station)
	{
		m_pNextStation = station;
	}
	Workstation* Workstation::getNextStation() const
	{
		return m_pNextStation;
	}
	void Workstation::display(std::ostream& os) const
	{
		os << getItemName() << " --> ";
		if (m_pNextStation) {
			os << m_pNextStation->getItemName();
		}
		else {
			os << "End of Line";
		}
		os << '\n';
		//// need to delete
		//std::cout << "=== Station name: "<< getItemName() << "========== = Orders====" << m_orders.size() << "======== = " << std::endl;
		//
		//for (auto& order : m_orders) {
		//	order.display(std::cout);
		//}
	}
	Workstation& Workstation::operator+=(CustomerOrder&& newOrder)
	{
		m_orders.push_back(std::move(newOrder));
		return *this;
	}
}