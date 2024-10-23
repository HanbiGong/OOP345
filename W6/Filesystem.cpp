/*/////////////////////////////////////////////////////////////////////////
Full Name  : Hanbi Gong
Student ID#: 111932224
Email      : hgong12@myseneca.ca
Section    : OOP 345

I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. 
This submitted piece of work has not been shared with any other student or 3rd party content provider.

/////////////////////////////////////////////////////////////////////////*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Filesystem.h"

namespace seneca {

	// Custom private members
	std::string Filesystem::remove_trim(std::string input)
	{
		size_t first = input.find_first_not_of(' ');
		size_t end = input.find_last_not_of(' ');
		if (first == std::string::npos) {
			return "";
		}
		return input.substr(first, end - first + 1);
	}

	std::vector<std::string> Filesystem::splitPath(const std::string& path)
	{
		// ex: a/b/c/d.png -> parts = [a, b, c, d.png]
		std::vector<std::string> parts;
		std::stringstream ss(path);
		std::string item;

		while (std::getline(ss, item, '/')) {
			if (!item.empty()) {
				parts.push_back(item);
			}
		}
		return parts;
	}
	// move constructor
	Filesystem::Filesystem(Filesystem&& other) noexcept
		: m_root(other.m_root), m_current(other.m_current) {
		other.m_root = nullptr;
		other.m_current = nullptr;
	}

	// move operation
	Filesystem& Filesystem::operator=(Filesystem&& other) noexcept {
		if (this != &other) {
			// Clean up existing resources
			delete m_root;

			// Move the resources from the other object
			m_root = other.m_root;
			m_current = other.m_current;

			// Nullify the other object's pointers
			other.m_root = nullptr;
			other.m_current = nullptr;
		}
		return *this;
	}
	void Filesystem::createDir(const std::string& dirPath)
	{
		std::vector<std::string> parts = splitPath(dirPath);
		Directory* current = m_root;
		Resource* find_dir = nullptr;
		for (const auto& name : parts) {
			find_dir = current->find(name+"/");
			if (find_dir == nullptr) {
				Directory* dir = new Directory(name + "/");
				*current += dir;
			}
			current = dynamic_cast<seneca::Directory*>(find_dir);
		}
	}
	void Filesystem::createFile(const std::string& filePath, std::string& contents)
	{
		std::vector<std::string> parts = splitPath(filePath);
		Directory* current = m_root;
		Resource* find_dir = nullptr;

		// file path의 맨 끝은 파일명임으로 parts.size()-1까지 봐야함
		for (size_t i = 0; i < parts.size() - 1; ++i) {
			find_dir= current->find(parts[i]+"/");
			if (find_dir == nullptr) {
				Directory* dir = new Directory(parts[i]+"/");
				*current += dir;
				dir->update_parent_path(current->path());
				current = dir;
			}
			else {
				current = static_cast<seneca::Directory*>(find_dir);
			}
		}

		File* file = new File(parts.back(), contents);
		*current += file;
		file->update_parent_path(current->path());
	}

	Filesystem::Filesystem(std::string file_name, std::string root_dir_name)
	{
		// 파일에서 정보들을 추출
		std::ifstream file(file_name);
	
		if (!file.is_open()) { // 파일 읽는데 에러가 나면 return
			throw "";
			return; 
		}

		// 파일 이름, root_dir name = ""
		m_root = new Directory(root_dir_name);
		m_current = m_root;

		std::string str = "";

		while (!file.eof()) {
			// 문장 한개 가져오고
			std::getline(file, str); 
			// | 를 기준으로 문자열을 자른다. 
			
			// start_pos를 못찾으면 Dir, 있으면 File
			size_t start_pos = 0;
			if (str.find("|") != std::string::npos) { // FILE
				start_pos = str.find("|");
				std::string file_path = remove_trim(str.substr(0, start_pos)); // path = images/file.png or file.png. 
				start_pos += 1;

				std::string file_contents = remove_trim(str.substr(start_pos, str.find('\n', start_pos) - start_pos));
				
				createFile(file_path, file_contents);
			}
			else { // DIR
				std::string dir_path = remove_trim(str);
				createDir(dir_path);
			}
		}
		file.close();
	}


	Filesystem& Filesystem::operator+=(Resource* r_str)
	{
		// m_current에 r_str추가
		*m_current += r_str;
		return *this;
	}
	Directory* Filesystem::change_directory(const std::string& str)
	{
		if (str == "") {
			m_current = m_root;
			return m_current;
		}
		Resource* dir = m_current->find(str);
		if (dir == nullptr ||  dir->type() == NodeType::FILE) {
			throw std::invalid_argument("Cannot change directory! " + str + " not found!");
			return nullptr;
		}
		return dynamic_cast<seneca::Directory*>(dir);
	}
	Directory* Filesystem::get_current_directory() const
	{
		return m_current;
	}
	Filesystem::~Filesystem()
	{
		delete m_root;
	}
}