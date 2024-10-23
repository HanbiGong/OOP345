#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstring>
#include<sstream>
#include "FoodOrder.h"

double g_taxrate =0;
double g_dailydiscount=0;
namespace seneca {
    // Constructor
	FoodOrder::FoodOrder()
	{
		customer_name = nullptr;
		order_description = nullptr;
		price = 0;
		special = false;
	}

	FoodOrder::~FoodOrder()
	{
		delete[] customer_name;
		customer_name = nullptr;
		delete[] order_description;
		order_description = nullptr;
	}

	void FoodOrder::read(std::istream& in) {
		if (in.good()) {
			std::string s;
			// if getline works properly
			if (std::getline(in, s)) {
				std::istringstream iss(s); // 문자열을 입력스트림처럼 다룰 수 있게 하는 함수 --> 문자열에서 데이터를 읽어오기
				std::string token;

				// customer name
				if (std::getline(iss, token, ',')) { // iss(문자열)에서 ,을 기준으로 끊어 읽어서 string자료형 변수인 token에 저장함
					if (customer_name!=nullptr) {
						delete[] customer_name;
						delete[] order_description;
					}
					customer_name = new char[token.size() + 1];
					strcpy(customer_name, token.c_str());

					// order description
					if (std::getline(iss, token, ',')) {
						order_description = new char[token.size() + 1];
						strcpy(order_description, token.c_str());
					}

					// price
					if (std::getline(iss, token, ',')) {
						price = std::stod(token);
					}

					// special
					if (std::getline(iss, token)) {
						if (token == "Y") {
							special = true;
						}
						else {
							special = false;
						}
					}
				}
			}
			else {
				if (customer_name != nullptr) {
					delete[] customer_name;
				}
				customer_name = nullptr;
			}
		}
	}

	void FoodOrder::display() {
		static int counter = 0; // 함수가 호출될때마다 증가하는 값
		counter++;
		// 1. print counter
		std::cout << std::left << std::setw(2) << counter<<". ";
		if (customer_name) {
			// 2. print Name
			std::cout << std::left << std::setw(10) << customer_name;

			std::cout << "|";
			// 3. print Order Description
			std::cout << std::left << std::setw(25) << order_description;
			std::cout << "|";
			// 4. print price w/tax
			std::cout << std::left << std::setw(12) << std::fixed << std::setprecision(2) << price + (price * g_taxrate);
			std::cout << "|";
			// 5. print special price
			if (special) {
				std::cout << std::right << std::setw(13) << price + (price * g_taxrate) - g_dailydiscount;
			}
		}
		else {
			std::cout << "No Order";
		}
		std::cout << std::endl;


		
	}
	FoodOrder::FoodOrder(const FoodOrder& other) : price(other.price), special(other.special)
	{
		if (other.customer_name) {
			customer_name = new char[strlen(other.customer_name) + 1];
			strcpy(customer_name, other.customer_name);

			order_description = new char[strlen(other.order_description) + 1];
			strcpy(order_description, other.order_description);
		}
		else {
			customer_name = nullptr;
			order_description = nullptr;
		}
		
	}

	FoodOrder& FoodOrder::operator =(const FoodOrder& other){
		if (this != &other && other.customer_name) {
			// 기존의 메모리 해제
			delete[] customer_name;
			delete[] order_description;

			// 새로운 메모리 할당 및 복사
			customer_name = new char[strlen(other.customer_name) + 1];
			strcpy(customer_name, other.customer_name);

			order_description = new char[strlen(other.order_description) + 1];
			strcpy(order_description, other.order_description);

			price = other.price;
			special = other.special;
		}
		return *this;
	}
}