/*/////////////////////////////////////////////////////////////////////////
Full Name  : Hanbi Gong
Student ID#: 111932224
Email      : hgong12@myseneca.ca
Section    : OOP 345

I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. 
This submitted piece of work has not been shared with any other student or 3rd party content provider.

/////////////////////////////////////////////////////////////////////////*/



#include "Directory.h"
#include <iomanip>
#include <algorithm>

namespace seneca {
	Directory::Directory(std::string dir_name)
	{
		m_name = dir_name;
	}
	void Directory::update_parent_path(const std::string& parent_path)
	{
		m_parent_path = parent_path;
	}
	NodeType Directory::type() const
	{
		return NodeType::DIR;
	}
	std::string Directory::path() const
	{
		return m_parent_path + m_name;
	}
	std::string Directory::name() const
	{
		return m_name;
	}
	int Directory::count() const
	{
		return int(m_contents.size());
	}
	size_t Directory::size() const
	{
		// If the directory is empty, return 0u
		if (count() == 0) {
			return 0u;
		}
		size_t total_size = 0;
		for (int i = 0; i < count(); i++) {
			total_size += m_contents[i]->size();
		}
		return total_size;
	}
	Directory& Directory::operator+=(Resource* r)
	{
		// If m_contents already has a resource with the same name as r, throw an exception and do nothing
		// Otherwise, add the resource and update its absolute path with the directory's full path
		// Adding a file to the current folder -> What's the file path? Update it with the folder path + file name
		// Adding a "folder" to the current folder -> What's the directory path? Update it with the folder path + folder name

		for (int i = 0; i < count(); i++) {
			if (r->name() == m_contents[i]->name()) {
				throw "";
			}
		}
		m_contents.push_back(r);
		r->update_parent_path(path());
		return *this;
	}
	Resource* Directory::find(const std::string& name, const std::vector<OpFlags>& opf)
	{
		if (name == m_name) {
			return this;
		}
		if (count()<=0) return nullptr;

		// Find and return the address of the resource within the folder that matches the name, or return nullptr if not found
		for (size_t i = 0; i < opf.size(); i++) {
			if (opf[i] == OpFlags::RECURSIVE) {
				for (int j = 0; j < count(); j++) {
					if (m_contents[j]->name() == name) {
						return m_contents[j];
					}
					if (m_contents[j]->type() == NodeType::DIR) {
						// Convert the object of type Resource* in m_contents[i] to Directory*
						Directory* d = dynamic_cast<Directory*>(m_contents[j]);
						if (d) {
							return d->find(name, opf);
						}
					}
				}
			}
		}
		
		for (int i = 0; i < count(); i++) {
			if (m_contents[i]->name() == name) {
				return m_contents[i];
			}
		}
		return nullptr;
	} 
	
	Directory::~Directory() {
		// Delete all Resource pointers in the m_contents vector
		for (Resource* res : m_contents) {
			delete res;
		}
	}
	
	void Directory::remove(const std::string& resource_name, const std::vector<OpFlags>& flags)
	{
		// Remove the resource with the resource name within the directory (release memory allocation)
		// If the resource name is a directory, also delete the resources within the directory recursively
		// Check if the resource_name exists in m_contents

		auto it = std::find_if(m_contents.begin(), m_contents.end(),
			[&](Resource* res) { return res->name() == resource_name; });

		// If resource_name does not exist in m_contents, throw an error
		if (it == m_contents.end()) {
			throw std::string(resource_name + " does not exist in " + this->m_name);
		}

		Resource* resource = *it;
		if (resource->type() == NodeType::DIR) {
			// If it's a directory, the RECURSIVE flag must be passed as an argument, as stated in the project description
			// Check if the flags vector contains the RECURSIVE flag

			bool recursiveFlag = std::find(flags.begin(), flags.end(), OpFlags::RECURSIVE) != flags.end();
			if (!recursiveFlag) { // 없으면  에러 throw
				throw std::invalid_argument(resource_name + " is a directory. Pass the recursive flag to delete directories.");
			}
			
			// If set, delete the directory and its sub-resources.
			Directory* subdir = static_cast<Directory*>(resource);
			for (int i = 0; i < subdir->count(); i++){
				Resource* del = subdir->m_contents[i];
				if (del->type() == NodeType::FILE) {
					subdir->m_contents.erase(subdir->m_contents.begin() + i);
					delete del;
				}
				else {
					// If it's a directory, recursively remove items within the directory.
					subdir->remove(del->name(), flags);
				}
			}
		}
		// Remove the `resource_name` from `m_contents`.
		m_contents.erase(it);
		// Delete the `resource`.
		delete resource;

	}
	void Directory::display(std::ostream& os, const std::vector<FormatFlags>& ops) const
	{
		os << "Total size: " << size() << " bytes\n";

		auto it = std::find(ops.begin(), ops.end(), FormatFlags::LONG);
		if (it != ops.end()) { 
			for (int i = 0; i < count(); i++) {
				if(m_contents[i]->type() == NodeType::DIR) {
					std::cout << "D | " << std::left << std::setw(15) << m_contents[i]->name() << " | "
						<< std::right << std::setw(2) << m_contents[i]->count() << " | "
						<< std::right << std::setw(4) << m_contents[i]->size() << " bytes | \n";
				}
				else {
					std::cout << "F | " << std::left << std::setw(15) << m_contents[i]->name() << " | "
						<< std::right << std::setw(2) << "   | "
						<< std::right << std::setw(4) << m_contents[i]->size() << " bytes | \n";
				}
			}
		}
		else {
			for (int i = 0; i < count(); i++) {
				if (m_contents[i]->type() == NodeType::DIR) {
					std::cout << "D | " << std::left << std::setw(15) << m_contents[i]->name() << " |\n";
				}
				else {
					std::cout << "F | " << std::left << std::setw(15) << m_contents[i]->name() << " |\n";
				}
			}
		}
	}

}