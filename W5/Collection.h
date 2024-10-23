/*/////////////////////////////////////////////////////////////////////////
Full Name  : Hanbi Gong
Student ID#: 111932224
Email      : hgong12@myseneca.ca
Section    : OOP 345

I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. 
This submitted piece of work has not been shared with any other student or 3rd party content provider.

/////////////////////////////////////////////////////////////////////////*/


#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H

#include "Book.h"
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <functional>

// 템플릿 클래스이기 때문에(template<typename T>를 사용하는 클래스) 클래스의 멤버 함수들의 구현은 header파일에 해야함
// 왜? 템플릿 클래스는 원래 그렇게 사용해야 함 
namespace seneca {
	/*typename T
	T = int
	T smallest -> int smallest*/
	template <typename T>
	class Collection {
	private:
		// resize it when a new item is added.
		std::string m_name;
		T* m_items; // 동적으로 (배열의 크기가) 할당되는 T타입의 배열, 새로운 아이템이 추가될 때마다 사이즈가 변경됨
		size_t m_size; // 배열의 크기를 저장하는 변수, 자료형 size_t를 사용하는 이유는 원래 배열의 인덱스, 사이즈를 저장하는 변수의 자료형은 size_t를 쓰는게 좋음
		// "void를 반환하고 두개의 인자를 받는" 함수에 대한 포인터. 포인터 이름은 m_observer
		// 관찰자 함수, 말 그대로 이벤트를 관찰하는 함수
		// Collection클래스의 멤버 변수인 m_item 배열에 아이템(데이터)가 추가되면, Collection 클래스는 이 포인터에 저장된 함수를 호출할 것임!
		// 여기서 이벤트란? Collection클래스의 멤버 변수인 m_item에 데이터가 추가되는 것 -> 이 이벤트는 어떻게 우리가 설정할까? 79번째 줄
		// 일반적인 변수랑 비슷하다고 생각하면 됨. int number에 숫자를 저장하는 것처럼 m_observer에는 함수를 저장(등록)하는 거라고 생각하면 됨
		// 예) Collection<Book> c, Book b 일 때(T를 Book으로 설정)
		// 이 포인터에 "1234"를 출력하는 함수인 void A(c, b)를 저장함 
		// Collection클래스의 멤버 변수인 m_item 배열에 아이템(데이터)가 추가될때마다(event), 
		// Collection 클래스는 "1234"를 출력할 것임
		void (*m_observer)(const Collection<T>&, const T&); 
		
		public:
		// this class doesn't support any copy operations
		// 기본 생성자: m_name은 함수의 인자로 들어온 name으로 초기화 해주고, 나머지는 가본으로 초기화 해줌
		Collection(const std::string& name) {
			m_name = name;
			m_items = nullptr; // 포인터이기 때문에 nullptr로 초기화
			m_size = 0; // 처음의 배열에는 아무것도 저장하지 않은 상태임으로 배열의 크기는 0이라서 0으로 초기화
			m_observer = nullptr; // 포인터이기 때문에 nullptr로 초기화
		};
		// 동적으로 할당될 m_items에 대해서 할당 해제
		// 함수에 대한 포인터(m_observer)는 메모리를 동적으로 할당하지 않기 때문에 메모리 할당 해제를 하지 않음
		~Collection() {
			delete[] m_items;
			m_items = nullptr;
		}
		const std::string& name() const {
			return m_name;
		};
		size_t size() const {
			return m_size;
		};
		// 관찰자 함수를 등록하는 함수.(m_observer)에 함수를 저장(등록)
		void setObserver(void (*observer)(const Collection<T>&, const T&)) {
			m_observer = observer;
		};
		Collection<T>& operator+=(const T& item) {
			// adds a copy of item to the collection, 
			// only if the collection doesn't contain an item with the same title. 
			// If item is already in the collection, this function does nothing. 
			for (size_t i = 0; i < m_size; i++) {
				//	ASSUMPTION : type T has a member function called title() that returns the title of the item(std::string).
				if (m_items[i].title() == item.title()) {
					return *this;
				}
			}
			// If the item is not yet in the collection, this function:
			//	resizes the array of items to accommodate the new item
			//	if an observer has been registered, this operator calls the observer function passing the current object(*this) and the new item as arguments.
			// 기존 항목을 복사하고 새 항목을 추가하기 위해 배열 크기 증가
			T* newItems = new T[m_size + 1];
			for (size_t i = 0; i < m_size; ++i) {
				newItems[i] = m_items[i];
			}
			newItems[m_size] = item;

			// 기존 배열 삭제 및 새 배열 할당
			delete[] m_items;
			m_items = newItems;
			++m_size;

			// 관찰자 함수가 설정되어 있다면 호출
			if (m_observer) {
				m_observer(*this, item);
			}

			return *this;
		};
		// m_items[idx]에 있는 값을 반환
		// 만약 idx가 현재 배열의 크기(m_size)를 넘어서면 error를 throw.
		T& operator[](size_t idx) const {
			if (idx >= m_size) {
				std::ostringstream oss;
				oss << "Bad index [" +std::to_string(idx)+"]. Collection has [" +std::to_string(m_size)+ "] items.";
				// 이 에러는 const char이 아니고 exception객체이다.
				// 따라서 여기에서 에러가 발생하면 exception객체를 throw하고  
				// w5_p2.cpp파일의 200번째 줄인 catch가 이 에러를 잡을 것이다. 
				// 실행 흐름?w5_p2.cpp파일의 200번째 줄 확인하기!
				// try구문 내에서 에러가 발생 -> 여기 102번째 줄의 throw 구문을 걍 던짐 -> 그걸 catch가 받아서 처리
				throw std::out_of_range(oss.str());
			}
			return m_items[idx];
		};
		// m_items 배열에 title을 가지는 T가 있으면 해당 아이템의 주소값을 반환
		T* operator[](const std::string& title) const {
			for (size_t i = 0; i < m_size; i++) {
				if (m_items[i].title() == title) {
					return &m_items[i];
				}
			}
			return nullptr;
		};
		// 삽입 연산자 오버로드
		template <typename U>
		friend std::ostream& operator<<(std::ostream& os, const Collection<U>& collection);

	};
	template <typename T>
	std::ostream& operator<<(std::ostream& os, const Collection<T>& collection) {
		for (size_t i = 0; i < collection.m_size; ++i) {
			os << collection.m_items[i];
		}
		return os;
	}

}
#endif