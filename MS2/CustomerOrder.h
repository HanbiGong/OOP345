#ifndef SENECA_CUSTOMERORDER_H
#define SENECA_CUSTOMERORDER_H

#include "Utilities.h"
#include "Station.h"

#include <iostream>

namespace seneca {
	struct Item
	{
		std::string m_itemName;
		size_t m_serialNumber{ 0 };
		bool m_isFilled{ false };

		Item(const std::string& src) : m_itemName(src) {};
	};

	class CustomerOrder{
	private:
		std::string m_name;
		std::string m_product;
		size_t m_cntItem;
		Item** m_lstItem;
	public:
		static size_t m_widthField;
		CustomerOrder();
		CustomerOrder(const std::string& str);
		// The copy constructor should throw an exception
		CustomerOrder(const CustomerOrder& cst);
		// Copy operator= should be deleted
		CustomerOrder& operator=(const CustomerOrder& cst) = delete;
		// Move
		CustomerOrder(CustomerOrder&& other) noexcept;
		CustomerOrder& operator=(CustomerOrder&& other) noexcept;

		~CustomerOrder();
		bool isOrderFilled() const;
		bool isItemFilled(const std::string& itemName) const;
		void fillItem(Station& station, std::ostream& os);
		void display(std::ostream& os) const;
	};
}

#endif