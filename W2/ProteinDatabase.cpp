#define _CRT_SECURE_NO_WARNINGS
#include "ProteinDatabase.h"
#include <chrono>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <algorithm>

namespace seneca {
	ProteinDatabase::ProteinDatabase()
	{
		numSequences = 0;
        sequences = nullptr;
	}
    ProteinDatabase::ProteinDatabase(const char* filename): numSequences(0), sequences(nullptr)
	{
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: Unable to open file " << filename << std::endl;
            return;
        }

        // Count the number of protein sequences
        std::string line;
        while (std::getline(file, line)) {
            if (!line.empty() && line[0] == '>') {
                numSequences+=1;
            }
        }

        // Allocate memory for protein sequences
        sequences = new std::string[numSequences];

        // Read the file again to load protein sequences
        file.clear();  // Reset the file state
        file.seekg(0); // Rewind to the beginning of the file

        size_t currentIndex = 0;
        std::string sequence; // 문자열 저장
        while (std::getline(file, line)) {
            if (!line.empty() && line[0] == '>') { // 비어있지 않거나 문자열의 처음이 > 이면 읽는다.
                if (!sequence.empty() && numSequences > currentIndex) { // 만약 비어있지 않고, currentIndex가 작다면
                    sequences[currentIndex] = sequence; // currentIndex에 읽어온 sequesnce를 저장함
                    currentIndex += 1;
                    sequence.clear();
                }
            }
            else {
                sequence += line;
            }
        }
        // Store the last sequence
        if (!sequence.empty()) {
            sequences[currentIndex] = sequence;
            currentIndex += 1;
        }

        file.close();
	}
    ProteinDatabase::ProteinDatabase(const ProteinDatabase& other) : numSequences(0), sequences(nullptr)
    {
        // reuse copy assignment
        *this = other;
    }

    ProteinDatabase& ProteinDatabase::operator=(const ProteinDatabase& other)
    {
        // other이 null이거나 현재 객체와 동일하다면 바로 return *this
        if (&other == this) {
            return *this;
        }
        // 1. Release current resources
        delete[] sequences;

        // 2. Copy data from the other object
        numSequences = other.numSequences;
        if (other.sequences) {
            sequences = new std::string[numSequences];
            std::copy(other.sequences, other.sequences + numSequences, sequences);
        }
        else {
            sequences = nullptr;
        }
        // 3. return this
        return *this;
    }

	ProteinDatabase::~ProteinDatabase()
	{
        delete[] sequences;
        sequences = nullptr;
	}
	size_t ProteinDatabase::size() const
	{
		return numSequences;
	}
	std::string ProteinDatabase::operator[](size_t index) const
	{
        if (index < numSequences) {
            return sequences[index];
        }
        else {
            return ""; // Invalid index, return empty string
        }
	}

    ProteinDatabase::ProteinDatabase(ProteinDatabase&& other) noexcept :numSequences(other.numSequences), sequences(other.sequences)
    {
        other.numSequences = 0;
        other.sequences = nullptr;
    }

    ProteinDatabase& ProteinDatabase::operator=(ProteinDatabase&& other) noexcept
    {
        
        // other이 null이거나 현재 객체와 동일하다면 바로 return *this
        if (&other == this) {
            return *this;
        }

        // 1. Release current resources
        delete[] sequences;

        // 2. Steal resources from the other object
        numSequences = other.numSequences;
        sequences = other.sequences;

        other.numSequences = 0;
        other.sequences = nullptr;
        
        return *this;
    }
}