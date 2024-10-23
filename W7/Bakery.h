/*/////////////////////////////////////////////////////////////////////////
Full Name  : Hanbi Gong
Student ID#: 111932224
Email      : hgong12@myseneca.ca
Section    : OOP 345

I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. 
This submitted piece of work has not been shared with any other student or 3rd party content provider.

/////////////////////////////////////////////////////////////////////////*/


#ifndef SENECA_BAKERY_H
#define SENECA_BAKERY_H

#include <algorithm>
#include <string>
#include <vector>
#include <list>
#include <fstream>
#include <iomanip>
#include <iostream>

namespace seneca
{
	enum class BakedType {
		BREAD, PASTERY
	};
	struct  BakedGood
	{
		BakedType bakeType;
		std::string bakedDescription;
		int shelfLife;
		int stockAmount;
		double price;
	};
	class Bakery {
	private:
		// p2
		double total_price;
		int total_stock;

		std::vector<BakedGood> m_bakedGoods;
		std::string remove_trim(std::string input);
		void recursiveFile(std::ifstream& file);

	public:
		Bakery(const std::string& fileName);
		// p2
		void showGoods(std::ostream& os) const;
		void sortBakery(const std::string& type);
		std::vector<BakedGood> combine(const Bakery& bakery);
		bool inStock(std::string description, BakedType type) const;
		std::list<BakedGood> outOfStock(BakedType type) const;

	};
	// Free Helpers: ����� ���� �Լ�
	std::ostream& operator<<(std::ostream& out, const BakedGood& b);
}

#endif
