#pragma once
#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H

#include <iostream>
#include "Book.h"

namespace seneca {
	/*typename T
	T = int
	T smallest -> int smallest*/
	template <typename T, unsigned int C>
	class Collection {
	private:
		// manages a statically-allocated array of elements of any data type
		T m_items[C]; 
		unsigned int m_size;

		// Smallest item across all instances
		static T m_smallestItem;
		// Largest item across all instances
		static T m_largestItem;  

	protected:
		void setSmallestItem(const T& smallest);
		void setLargestItem(const T& largest);
		// part2
		T& operator[](unsigned int index);
		void incrSize();
	public:
		// default constructor
		Collection();
		static T getSmallestItem();
		static T getLargestItem();

		unsigned int size() const;
		unsigned int capacity() const;
		virtual bool operator+=(const T& other);
		std::ostream& print(std::ostream& os) const;

	};

	template <typename T, unsigned int C>
	T Collection<T, C>::m_smallestItem = 9999;

	template <typename T, unsigned int C>
	T Collection<T, C>::m_largestItem = -9999;

	// default constructor
	template <typename T, unsigned int C>
	Collection<T, C>::Collection() : m_size{ 0 } {}

	template <typename T, unsigned int C>
	void Collection<T, C>::setSmallestItem(const T& smallest) {
		if (smallest < m_smallestItem) {
			m_smallestItem = smallest;
		}
	}

	template <typename T, unsigned int C>
	void Collection<T, C>::setLargestItem(const T& largest)
	{
		if (largest > m_largestItem) {
			m_largestItem = largest;
		}
	}

	template<typename T, unsigned int C>
	T Collection<T, C>::getSmallestItem()
	{
		return m_smallestItem;
	}

	template <typename T, unsigned int C>
	T Collection<T, C>::getLargestItem() {
		return m_largestItem;
	}

	template <typename T, unsigned int C>
	unsigned int  Collection<T, C>::size() const {
		return m_size;
	}

	template <typename T, unsigned int C>
	unsigned int  Collection<T, C>::capacity() const {
		return C;
	}

	template <typename T, unsigned int C>
	bool Collection<T, C>::operator+=(const T& other) {
		if (size() > capacity()) {
			return false;
		}

		setSmallestItem(other);
		setLargestItem(other);

		m_items[size()] = other;
		m_size += 1;
		return true;
	}

	template <typename T, unsigned int C>
	std::ostream& Collection<T, C>::print(std::ostream& os) const {
		os << "[";
		for (unsigned int i = 0; i < size() - 1; i++) {
			os << m_items[i] << ",";
		}
		os << m_items[size() - 1] << "]" << std::endl;
		return os;
	}

	// Mutator to return reference to element at given index
	template <typename T, unsigned int C>
	T& Collection<T, C>::operator[](unsigned int index) {
		if (index <= m_size) {
			return m_items[index];
		}
		throw std::out_of_range("Index out of range");
	}

	// Mutator to increase the size count by 1
	template <typename T, unsigned int C>
	void Collection<T, C>::incrSize() {
		if (m_size < C) {
			++m_size;
		}
	}

	// template 특수화1
	template<>
	Book Collection<Book, 10>::m_smallestItem = Book("", 1, 10000);
	// template 특수화2
	template<>
	Book Collection<Book, 10>::m_largestItem = Book("", 10000, 1);
	
	// part2
	// template 특수화1 - 멤버변수 초기화
	template<>
	Book Collection<Book, 72>::m_smallestItem = Book("", 1, 10000);
	template<>
	Book Collection<Book, 72>::m_largestItem = Book("", 10000, 1);

	// template 특수화2 - 멤버함수 구현
	template<>
	std::ostream& Collection<Book, 10>::print(std::ostream& os) const {
		
		// Print first line
		os << "| ";
		for (int i = 0; i < 75; i++) {
			os << "-";
		}
		os << "|";
		os << std::endl;
		// Print information of Book 
		for (unsigned int i = 0; i < size(); i++) {
			os << "| ";
			m_items[i].print(os);
			os << " |";
			os << std::endl;
		}
		// Print last line
		os << "| ";
		for (int i = 0; i < 75; i++) {
			os << "-";
		}
		os << "|";
		os << std::endl;
		return os;
	}

	template<>
	std::ostream& Collection<Book, 72>::print(std::ostream& os) const {
		// Print first line
		os << "| ";
		for (int i = 0; i < 75; i++) {
			os << "-";
		}
		os << "|";
		os << std::endl;
		// Print information of Book 
		for (unsigned int i = 0; i < size(); i++) {
			os << "| ";
			m_items[i].print(os);
			os << " |";
			os << std::endl;
		}
		// Print last line
		os << "| ";
		for (int i = 0; i < 75; i++) {
			os << "-";
		}
		os << "|";
		os << std::endl;
		return os;
	}


}
#endif