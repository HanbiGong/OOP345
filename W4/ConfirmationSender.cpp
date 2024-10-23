#include "ConfirmationSender.h"
#include <iostream>
#include<string>
#include <algorithm>

namespace seneca {
	ConfirmationSender::ConfirmationSender()
	{
		m_rsv = nullptr;
		m_size = 0;
	}
	ConfirmationSender& ConfirmationSender::operator=(const ConfirmationSender& other)
	{
		if (this == &other || !&other) {
			return *this;
		}
		delete[] m_rsv;  // 기존 메모리 해제
		m_size = other.m_size;
		if (m_size > 0) {
			m_rsv = new const seneca::Reservation * [m_size];
			for (size_t i = 0; i < m_size; ++i) {
				m_rsv[i] = other.m_rsv[i];
			}
		}
		else {
			m_rsv = nullptr;
		}
		return *this;
	}
	ConfirmationSender::ConfirmationSender(const ConfirmationSender& other) :m_rsv(nullptr), m_size(0)
	{
		*this = other;

	}
	ConfirmationSender::ConfirmationSender(ConfirmationSender&& other) noexcept :m_rsv(other.m_rsv), m_size(other.m_size)
	{
		other.m_rsv = nullptr;
		other.m_size = 0;
	}
	ConfirmationSender& ConfirmationSender::operator=(ConfirmationSender&& other) noexcept
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
	ConfirmationSender::~ConfirmationSender()
	{
		delete[] m_rsv;
		m_rsv = nullptr;
		m_size = 0;
	}
	ConfirmationSender& ConfirmationSender::operator+=(const Reservation& res)
	{
		if (std::find(m_rsv, m_rsv + m_size, &res) == m_rsv + m_size) {
			// 배열 크기 조정 및 주소 추가
			const Reservation** new_rsv = new const Reservation * [m_size + 1];
			for (size_t i = 0; i < m_size; ++i) {
				new_rsv[i] = m_rsv[i];
			}
			new_rsv[m_size] = &res;
			delete[] m_rsv;
			m_rsv = new_rsv;
			++m_size;
		}
		return *this;
	}
	ConfirmationSender& ConfirmationSender::operator-=(const Reservation& res)
	{
		const Reservation** pos = std::find(m_rsv, m_rsv + m_size, &res);
		if (pos != m_rsv + m_size) {
			size_t index = pos - m_rsv;
			for (size_t i = index; i < m_size - 1; ++i) {
				m_rsv[i] = m_rsv[i + 1];
			}
			--m_size;
			const Reservation** new_rsv = new const Reservation*[m_size];
			for (size_t i = 0; i < m_size; ++i) {
				new_rsv[i] = m_rsv[i];
			}
			delete[] m_rsv;
			m_rsv = new_rsv;
		}
		return *this;
	}
	size_t ConfirmationSender::size() const
	{
		return m_size;
	}
	std::ostream& operator<<(std::ostream& os, const ConfirmationSender& res)
	{
		os << "--------------------------" << std::endl;
		os << "Confirmations to Send"  << std::endl;
		os << "--------------------------" << std::endl;
		if (res.size() == 0 || res.m_rsv == nullptr) {
			os << "There are no confirmations to send!" << std::endl;
		}
		else {
			for (size_t i = 0; i < res.size(); i++) {
				os << *(res.m_rsv[i]);
			}
		}
		os << "--------------------------" << std::endl;
		return os;
	}
}