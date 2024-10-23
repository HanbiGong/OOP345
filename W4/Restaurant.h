#ifndef SENECA_RESTAURANT_H
#define SENECA_RESTAURANT_H

#include "Reservation.h"
#include <iostream>

namespace seneca {
	class Restaurant {
	private:
		Reservation** m_rsv{ nullptr }; // Reservation pointer를 담는 배열
		size_t m_size;
		static int CALL_CNT; // 함수의 호출횟수를 저장함
	public:
		// 기본 생성자
		Restaurant();
		Restaurant(const Reservation* reservations[], size_t cnt);

		// 할당 생성자
		Restaurant& operator=(const Restaurant&);
		Restaurant(const Restaurant&);

		// 이동 생성자
		Restaurant(Restaurant&& other) noexcept;
		Restaurant& operator=(Restaurant&& other) noexcept;

		// 소멸자
		~Restaurant();

		size_t size() const;
		friend std::ostream& operator<<(std::ostream& os, const Restaurant& rs);
	};
}
#endif