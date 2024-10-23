#include "Restaurant.h"
#include <iostream>

namespace seneca {
	int Restaurant::CALL_CNT = 0; // 정적 멤버 변수 초기화

	Restaurant::Restaurant()
	{
		m_rsv = nullptr;
		m_size = 0;
	}
	
	Restaurant::Restaurant(const Reservation* reservations[], size_t cnt):m_rsv(nullptr), m_size(0)
	{
		if (cnt > 0) {
			m_size = cnt;
			// Reservation* reservations[](statically) == Reservation** m_rsv(dynamically)
			m_rsv = new Reservation * [cnt];
			for (size_t i = 0; i < cnt; ++i) {
				m_rsv[i] = new Reservation(*reservations[i]);
			}
		}
	}

	Restaurant& Restaurant::operator=(const Restaurant& rs)
	{
		if (this == &rs) {
			return *this;
		}
		for (size_t i = 0; i < m_size; i++) {
			delete m_rsv[i];
		}
		delete[] m_rsv;

		// 새로운 메모리 할당 및 복사
		m_size = rs.m_size;
		m_rsv = new Reservation* [m_size];
		for (size_t i = 0; i < m_size; ++i) {
			m_rsv[i] = new Reservation(*rs.m_rsv[i]);
		}
		return *this;
	}

	Restaurant::Restaurant(const Restaurant& rs) :m_rsv(nullptr), m_size(0)
	{
		*this = rs;
	}

	Restaurant::Restaurant(Restaurant&& other) noexcept :m_rsv(other.m_rsv), m_size(other.m_size)
	{
		other.m_rsv = nullptr;
		other.m_size = 0;
	}

	Restaurant& Restaurant::operator=(Restaurant&& other) noexcept
	{
		if (this != &other) {
			// 기존 메모리 해제
			for (size_t i = 0; i < m_size; ++i) {
				delete m_rsv[i];
			}
			delete[] m_rsv;

			// 이동된 자원 가져오기
			m_rsv = other.m_rsv;
			m_size = other.m_size;

			// 원본 객체 초기화
			other.m_rsv = nullptr;
			other.m_size = 0;
		}
		return *this;
	}

	Restaurant::~Restaurant()
	{
		for (size_t i = 0; i < m_size; ++i) {
			delete m_rsv[i];
		}
		delete[] m_rsv;
		m_size = 0;
	}

	size_t Restaurant::size() const
	{
		return m_size;
	}

	std::ostream& operator<<(std::ostream& os, const Restaurant& rs)
	{
		os << "--------------------------" << std::endl;
		os << "Fancy Restaurant (" << ++Restaurant::CALL_CNT << ")" << std::endl;
		os << "--------------------------" << std::endl;
		if (rs.size() == 0 || rs.m_rsv == nullptr) {
			os << "This restaurant is empty!" << std::endl;
		}
		else {
			for (size_t i = 0; i < rs.size(); i++) {
				os << *(rs.m_rsv[i]);
			}
		}
		os << "--------------------------" << std::endl;
		return os;
	}

}