/*/////////////////////////////////////////////////////////////////////////
Full Name  : Hanbi Gong
Student ID#: 111932224
Email      : hgong12@myseneca.ca
Section    : OOP 345

I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. 
This submitted piece of work has not been shared with any other student or 3rd party content provider.

/////////////////////////////////////////////////////////////////////////*/

#ifndef SENECA_DATABASE_H
#define SENECA_DATABASE_H

#include <iostream>
#include <memory>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

namespace seneca
{
	enum class Err_Status
	{
		Err_Success,
		Err_NotFound,
		Err_OutOfMemory,
	};

	// T represents the type of value
	template<typename T>
	class Database {
		// Prevent copy and assignment by deleting copy constructor and assignment operator
	private:
		Database& operator=(const Database&) = delete;
		// Static instance pointer
		// This is a smart pointer. It helps with dynamic memory management and prevents memory leaks
		// std::shared_ptr; Provides shared ownership of an object, allowing multiple pointers to own and reference the same object.
		static std::shared_ptr<Database> m_instance;
		int m_numberOfEntries;
		std::string m_keys[20];
		T m_values[20];
		std::string m_filename;
		
		// Check if the string is a number
		bool isDigit(const std::string& str) {
			for (char c : str) {
				if (!std::isdigit(c)) {
					return false;
				}
			}
			return true;
		}

		// Specialize for each type T
		void encryptDecrypt(T& value);

		// Private constructor: prevents creating instances from outside the class
		Database(const std::string& filename) {
			m_numberOfEntries = 0;
			m_filename = "";
			// Print the address of the current object and the constructor's prototype
			std::cout << "[" << this << "] Database(const std::string&)" << std::endl;

			// Open the file and store key/value in member variables (arrays). Assume the file always exists!
			std::ifstream file(filename);
			m_filename = filename;
			std::string str = "";

			// Until the end of the file
			while (!file.eof()) {
				std::getline(file, str);

				// Extract key and value using whitespace as a delimiter
				std::istringstream iss(str);
				std::string keys;
				T values{};
				iss >> keys >> values;

				// P2 -------------------------------------------------
				// The values in the file are encrypted, so decrypt them
				encryptDecrypt(values);
				//  ---------------------------------------------------
				
				// Replace "_" in the key with " " and store
				std::string::size_type pos = keys.find("_");
				if (pos != std::string::npos) {
					keys.replace(pos, 1, " ");
				}

				m_keys[m_numberOfEntries] = keys;
				m_values[m_numberOfEntries] = values;
				m_numberOfEntries += 1;
			}

			file.close();
		}
		
 	public:
		// Static method to return a Database instance
		static std::shared_ptr<Database>getInstance(const std::string& filename) {
			// If the pointer is empty, create an object and store its address
			if (!m_instance) {
				m_instance = std::shared_ptr<Database>(new Database(filename));
			}
			return m_instance;
		};
		
		// Use template (T) so definition must be in the header file 
		Err_Status GetValue(const std::string& key, T& value) {
			for (int i = 0; i < m_numberOfEntries; i++) {
				if (m_keys[i] == key) {
					value = m_values[i];
					return Err_Status::Err_Success;
				}
			}
			return Err_Status::Err_NotFound;
		};

		// Use template (T) so definition must be in the header file
		Err_Status SetValue(const std::string& key, const T& value) {
			if (m_numberOfEntries >= 20) {
				return Err_Status::Err_OutOfMemory;
			}
			m_keys[m_numberOfEntries] = key;
			m_values[m_numberOfEntries] = value;
			m_numberOfEntries += 1;
			return Err_Status::Err_Success;
		};

		~Database() {
			// Print the address of the current object and the destructor's prototype
			std::cout << "[" << this << "] ~Database()" << std::endl;

			// Backup key and values to another file!
			std::string filesname = m_filename + ".bkp.txt";

			std::ofstream file(filesname);
			if (!file.is_open()) {
				std::cerr << "Failed to open backup file: " << filesname << std::endl;
				return;
			}

			for (int i = 0; i < m_numberOfEntries; ++i) {
				// Format: KEY -> VALUE
				// P2 -------------------------------------------------
				// The values stored in memory are decrypted, so encrypt them
				encryptDecrypt(m_values[i]);
				//  ---------------------------------------------------
				file << std::left << std::setw(25) << m_keys[i] << " -> " << m_values[i] << std::endl;
			}

			// Close the backup file
			file.close();
		}
	};

	template<typename T>
	std::shared_ptr<Database<T>> Database<T>::m_instance = nullptr;

	// Template class specialization: string
	template<>
	void Database<std::string>::encryptDecrypt(std::string& value) {
		// Pseudocode
		// const char secret[]{ "secret encryption key" };

		// For each character C in the parameter
		//	For each character K in the secret
		//	C = C ^ K
		const char secret[]{ "secret encryption key" };
		size_t size_secrets = sizeof(secret) / sizeof(secret[0]);
		for (size_t i = 0; i < value.size(); i++) {
			for (size_t j = 0; j < size_secrets; j++) {
				value[i] ^= secret[j];
			}
		}
	}

	// Template class specialization: long long
	template<>
	void Database<long long>::encryptDecrypt(long long& value) {
		// Pseudocode
		// const char secret[]{ "super secret encryption key" };

		// For each byte B in the parameter
		//	For each character K in the secret
		//	B = B ^ K

		const char secret[]{ "super secret encryption key" };
		// Number of bytes in long long
		constexpr size_t numBytes = sizeof(long long);
		size_t size_secrets = sizeof(secret) / sizeof(secret[0]);

		// Pointer to access each byte
		unsigned char* bytePtr = reinterpret_cast<unsigned char*>(&value);

		// Perform XOR operation on each byte
		for (size_t i = 0; i < numBytes; ++i) {
			for (size_t j = 0; j < size_secrets; ++j) {
				bytePtr[i] ^= secret[j];
			}
		}
	}
}

#endif

