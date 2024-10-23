#ifndef SENECA_PROTEINDATABASE_H
#define SENECA_PROTEINDATABASE_H

#include <iostream>
#include <string>

namespace seneca {
	class ProteinDatabase {
	private:
		size_t numSequences;       // Number of protein sequences stored
		std::string* sequences; // Array to store protein sequences
	public:
		ProteinDatabase();
		ProteinDatabase(const char* filename);
		// copy constructor & assignment
		ProteinDatabase(const ProteinDatabase& other);
		ProteinDatabase& operator=(const ProteinDatabase& other);
		// destructor
		~ProteinDatabase();
		size_t size() const;
		std::string operator[](size_t index) const;
		// move constructor & assignment
		// 사용하는 이유: 자원을 복사 하는게 아니라 "이동" 시키기 떄문에 효율적
		// -> 메모리 할당이나 데이터 복사가 필요 없음
		// -> 복사 생성자, 할당자와 다르게 &&를 인자로 받음
		// 이동 생성자: 다른 객체(other)의 자원을 현재 객체로 이동시키고 다른 객체의 포인터를 nullptr로 설정
		ProteinDatabase(ProteinDatabase&& other) noexcept;
		// 이동 대입 연산자: 현재 객체의 자원을 해제하고 다른 객체의 자원을 현재 객체로 이동시키고 다른 객체의 포인터를 nullptr로 설정
		ProteinDatabase& operator=(ProteinDatabase&& other) noexcept;
	};
}
#endif