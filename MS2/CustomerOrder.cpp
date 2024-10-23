#include "CustomerOrder.h"

namespace seneca {
	size_t CustomerOrder::m_widthField = 0;

	CustomerOrder::CustomerOrder()
	{
		m_name = "";
		m_product = "";
		m_cntItem = 0;
		m_lstItem = nullptr;
	}

	CustomerOrder::CustomerOrder(const std::string& str)
	{
		m_name = "";
		m_product = "";
		m_cntItem = 0;
		m_lstItem = nullptr;

		Utilities util;
		size_t next_pos = 0;
		bool more = true;

		m_name = util.extractToken(str, next_pos, more);
		m_product = util.extractToken(str, next_pos, more);
		size_t next_pos_tmp = next_pos;
		bool more_tmp = more;
		// Item들 갯수 세기
		std::string tmp = "";
		while (more_tmp) {
			util.extractToken(str, next_pos_tmp, more_tmp);
			++m_cntItem;
		}
		// Item 실제로 만들기
		m_lstItem = new Item * [m_cntItem];
		for (size_t i = 0; i < m_cntItem; i++) {
			m_lstItem[i] = new Item(util.extractToken(str, next_pos, more));
		}

		if (util.getFieldWidth() > m_widthField) {
			m_widthField = util.getFieldWidth();
		}
	}

	CustomerOrder::CustomerOrder(const CustomerOrder& cst)
	{
		throw "";
	}

	CustomerOrder::CustomerOrder(CustomerOrder&& other) noexcept : m_name(std::move(other.m_name)), m_product(std::move(other.m_product)),
		m_cntItem(other.m_cntItem), m_lstItem(other.m_lstItem) {
		other.m_cntItem = 0;
		other.m_lstItem = nullptr;
	}

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& other) noexcept
	{
		if (this != &other) {
			// 기존 리소스 해제
			for (size_t i = 0; i < m_cntItem; ++i) {
				delete m_lstItem[i];
			}
			delete[] m_lstItem;

			// 이동
			m_name = std::move(other.m_name);
			m_product = std::move(other.m_product);
			m_cntItem = other.m_cntItem;
			m_lstItem = other.m_lstItem;

			// 원래 객체 초기화
			other.m_cntItem = 0;
			other.m_lstItem = nullptr;
		}
		return *this;
	}

	CustomerOrder::~CustomerOrder()
	{
		for (size_t i = 0; i < m_cntItem; ++i) {
			delete m_lstItem[i]; // 각 Item 객체 해제
		}
		delete[] m_lstItem;
	}

	bool CustomerOrder::isOrderFilled() const
	{
		for (size_t i = 0; i < m_cntItem; i++) {
			if (!m_lstItem[i]->m_isFilled) {
				return false;
			}
		}
		return true;
	}

	bool CustomerOrder::isItemFilled(const std::string& itemName) const
	{
		for (size_t i = 0; i < m_cntItem; i++) {
			if ((m_lstItem[i]->m_itemName) == itemName && !(m_lstItem[i]->m_isFilled)) {
				return false;
			}
		}
		return true;
	}

	void CustomerOrder::fillItem(Station& station, std::ostream& os)
	{
		if (m_lstItem && m_cntItem>0) {
			for (size_t i = 0; i < m_cntItem; ++i) {
				if (m_lstItem[i]->m_itemName == station.getItemName()) {
					if (!m_lstItem[i]->m_isFilled) {
						if (station.getQuantity() > 0) {
							m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
							m_lstItem[i]->m_isFilled = true;
							station.updateQuantity();
							os << "    Filled " << m_name << ", " << m_product
								<< " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
						}
						else {
							os << "    Unable to fill " << m_name << ", " << m_product
								<< " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
						}
					}
					return; // Item handled, exit the function
				}
			}
		}

	}

	void CustomerOrder::display(std::ostream& os) const
	{
		os << m_name << " - " << m_product << std::endl;
		for (size_t i = 0; i < m_cntItem; ++i) {
			os << "["
				<< std::setw(6) << std::setfill('0') << m_lstItem[i]->m_serialNumber
				<< "] " << std::setw(m_widthField) << std::left << std::setfill(' ') << m_lstItem[i]->m_itemName
				<< " - " << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << std::endl;
		}
	}
}