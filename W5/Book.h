/*/////////////////////////////////////////////////////////////////////////
Full Name  : Hanbi Gong
Student ID#: 111932224
Email      : hgong12@myseneca.ca
Section    : OOP 345

I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. 
This submitted piece of work has not been shared with any other student or 3rd party content provider.

/////////////////////////////////////////////////////////////////////////*/

#ifndef SENECA_BOOK_H
#define SENECA_BOOK_H

#include <iostream>
#include <string>

namespace seneca {

	class Book {
	private:
		// 자료형을 이럻게 사용한 이유? 
		// 1. query functino에 나온 반환값 자료형을 기반으로 정의함
		// m_title, m_country, m_year, m_price
		// 2. 나머지는 상식적으로 생각
		// 예를 들어 작가의 이름은 string(문자), decription은 항상 string(문자)
		std::string m_author; // 작가의 이름 저장
		std::string m_title; // 책 제목 저장
		std::string m_country; // 출판 나라 저장
		size_t m_year; // 출판 년도 저장
		double m_price; // 책 가격 저장
		std::string m_desc; // 책 소개글 저장
		std::string remove_trim(std::string input); // 공백을 제거해주는 함수
	public:
		// 기본 생성자, 멤버 변수를 초기화 해야함
		Book(); 
		// m_title(Book클래스의 멤버 변수)을 반환해주는 함수. 앞의 const는 반환하는 m_title을 const string 자료형으로 반환해준다는 의미
		// 뒤의 const는 해당 함수 내부에서 멤버 변수의 값을 변경 및 수정하면 안된다는 의미
		const std::string& title() const;
		// m_country(Book클래스의 멤버 변수)를 반환하는 함수
		const std::string& country() const;
		// m_year(Book클래스의 멤버 변수)를 반환하는 함수
		const size_t& year() const;
		// m_price(Book클래스의 멤버 변수)를 반환하는 함수
		// 왜 여기에는 const가 안붙여져 있나? 나중에 이 함수를 가지고 m_price값을 업데이트 할 것임
		double& price();
		// m_price(Book클래스의 멤버 변수)를 p(함수 인자)로 설정하는 함수
		void setPrice(const double p);
		// strBook으로부터 값을 추출해서 Book클래스의 멤버 변수에 저장하는 구조채 
		Book(const std::string& strBook);
		// functor(함수 객체)
		template <typename T>
		void fixSpelling(T& spellChecker) {
			spellChecker(m_desc);
		}
		// book객체의 내용을 출력하는 함수. 출력형식은 프로젝트 description에 나와있음
		// friend? 다른 클래스의 private 멤버 변수, 멤버 함수에 접근할 수 있게 됨
		// 이 경우 Book클래스(const Book& book)의 private 멤버변수에 접근할 수 있음
		friend std::ostream& operator<<(std::ostream& os, const Book& book);
	};
}
#endif