/*/////////////////////////////////////////////////////////////////////////
Full Name  : Hanbi Gong
Student ID#: 111932224
Email      : hgong12@myseneca.ca
Section    : OOP 345

I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. 
This submitted piece of work has not been shared with any other student or 3rd party content provider.

/////////////////////////////////////////////////////////////////////////*/


#include "Bakery.h"

namespace seneca {
	
	// Custom private members
	std::string Bakery::remove_trim(std::string input)
	{
		size_t first = input.find_first_not_of(' ');
		size_t end = input.find_last_not_of(' ');
		if (first == std::string::npos) {
			return "";
		}
		return input.substr(first, end - first + 1);
	}

	// To read and save from a file one by one using a recursive function instead of a for loop.
	void Bakery::recursiveFile(std::ifstream& file) {
		std::string str = "";
		std::string sub_str = "";

		BakedType b;
		std::string desc;
		int life;
		int amount; 
		double price;

		if (std::getline(file, str)) {
			size_t start_pos = 0;

			sub_str = remove_trim(str.substr(start_pos, 8));
			if (sub_str == "Bread") {
				b = BakedType::BREAD;
			}
			else {
				b = BakedType::PASTERY;
			}
			start_pos += 8;

			sub_str = remove_trim(str.substr(start_pos, 20));
			desc = sub_str;
			start_pos += 20;

			sub_str = remove_trim(str.substr(start_pos, 14));
			life = std::stoi(sub_str);
			start_pos += 14;

			sub_str = remove_trim(str.substr(start_pos, 8));
			amount = std::stoi(sub_str);
			start_pos += 8;

			sub_str = remove_trim(str.substr(start_pos, 6));
			price = std::stod(sub_str);

			total_price += price;
			total_stock += amount;
			
			m_bakedGoods.push_back(BakedGood{ b, desc, life, amount, price });
			recursiveFile(file);
		}
	}

	Bakery::Bakery(const std::string& fileName)
	{
		// If the file name is "tree", throw an exception.
		// Each line in the file represents one BakedGood.
		// Each line is not split by a delimiter but has a fixed size for each field.
		// bakeType: 8, bakedDescription: 20, shelfLife: 14, stockAmount: 8, price: 6
		// Blank spaces should be removed.
		std::ifstream file(fileName);

		if (!file.is_open()) { // If there is an error reading the file, return.
			throw "";
			return;
		}
		total_price =0.0;
		total_stock=0;

		recursiveFile(file);

		file.close();
	}

	void Bakery::showGoods(std::ostream& os) const
	{
		std::for_each(m_bakedGoods.begin(), m_bakedGoods.end(),
			[&os](const BakedGood& good) { os << good << std::endl; });
		os << "Total Stock: " << total_stock << std::endl;
		os << "Total Price: " << std::fixed << std::setprecision(2) << total_price << std::endl;
	}

	void Bakery::sortBakery(const std::string& type)
	{
		// Sort in ascending order. 
		// Use a lambda expression to set the sorting criteria.
		std::sort(m_bakedGoods.begin(), m_bakedGoods.end(), [type](const BakedGood& a, const BakedGood& b) {
			if (type == "Description") {
				return a.bakedDescription < b.bakedDescription;
			}
			else if (type == "Shelf") {
				return a.shelfLife < b.shelfLife;

			}
			else if (type == "Stock") {
				return a.stockAmount < b.stockAmount;
			}
			else if (type == "Price") {
				return a.price < b.price;
			}
			else {
				std::cerr << "Invalid sort field: " << type << std::endl;
				return false; // Set to return false by default.
			}}
		);
	}

	std::vector<BakedGood> Bakery::combine(const Bakery& bakery)
	{
		size_t newSize = m_bakedGoods.size() + bakery.m_bakedGoods.size();
		std::vector<BakedGood> merged(newSize);
		sortBakery("Price");
		std::merge(m_bakedGoods.begin(), m_bakedGoods.end(), bakery.m_bakedGoods.begin(), bakery.m_bakedGoods.end(), merged.begin(), [](const BakedGood& a, const BakedGood& b) {
			return a.price < b.price; });
		return merged;
	}

	bool Bakery::inStock(std::string description, BakedType type) const
	{
		auto it = std::find_if(m_bakedGoods.begin(), m_bakedGoods.end(),
			[&](const BakedGood& bg) {
				return bg.bakedDescription == description && bg.bakeType == type && bg.stockAmount > 0;
			});

		return it != m_bakedGoods.end();
	}

	std::list<BakedGood> Bakery::outOfStock(BakedType type) const
	{
		std::list<BakedGood> result;

		// Use std::copy_if with a lambda function
		std::copy_if(m_bakedGoods.begin(), m_bakedGoods.end(), std::back_inserter(result),
			[&](const BakedGood& bg) {
				return bg.bakeType == type && bg.stockAmount == 0;
			});

		return result;
	}
	
	// Free helper
	std::ostream& operator<<(std::ostream& out, const BakedGood& b)
	{
		std::string typeStr = (b.bakeType == BakedType::BREAD) ? "Bread" : "Pastry";
		out << "* " << std::setw(10) << std::left << typeStr
			<< " * " << std::setw(20) << std::left << b.bakedDescription
			<< " * " <<std::setw(5) << std::left << b.shelfLife
			<< " * "<< std::setw(5) << std::left << b.stockAmount
			<< " * " << std::setw(8) << std::right << std::fixed << std::setprecision(2) << b.price
			<< " * ";
		return out;
	}
}
