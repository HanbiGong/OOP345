#ifndef SENECA_CONFIRMATIONSENDER_H
#define SENECA_CONFIRMATIONSENDER_H

#include "Reservation.h"
#include <iostream>

namespace seneca {
	class ConfirmationSender {
	private:
		// Reservation pointer를 담는 배열
		// 가리키는 객체를 수정할 수 없음 
		const seneca::Reservation** m_rsv{ nullptr }; 
		size_t m_size;
	public:
		// 기본 생성자
		ConfirmationSender();

		// 할당 생성자
		ConfirmationSender& operator=(const ConfirmationSender&);
		ConfirmationSender(const ConfirmationSender&);

		// 이동 생성자
		ConfirmationSender(ConfirmationSender&& other) noexcept;
		ConfirmationSender& operator=(ConfirmationSender&& other) noexcept;
		
		// 소멸자
		~ConfirmationSender();

		ConfirmationSender& operator+=(const Reservation& res);
		ConfirmationSender& operator-=(const Reservation& res);
		friend std::ostream& operator<<(std::ostream& os, const ConfirmationSender& res);
		// Retuern size of array m_rsv
		size_t size() const;
	};
}
#endif