#ifndef SENECA_FOODORDER_H
#define SENECA_FOODORDER_H
#include<iostream>

extern double g_taxrate;
extern double g_dailydiscount;

namespace seneca {
	
	class FoodOrder {
		private:
			char* customer_name;
			char* order_description;
			double price;
			bool special;
		public:
			FoodOrder();
			~FoodOrder();
			void read(std::istream& in);
			void display();
			// copy constructor & assignment
			FoodOrder(const FoodOrder& other);
			FoodOrder& operator=(const FoodOrder& other);
//class 내에 포인터형을 변수로 가지고 있을 경우, 무조건 구현해줘야 하는것: 소멸자, copy constructor, copy assignment **3개 무조건 꼭 구현** 메모리 누수 방지
	};
}
#endif // !FOODORDER
