/*/////////////////////////////////////////////////////////////////////////
Full Name  : Hanbi Gong
Student ID#: 111932224
Email      : hgong12@myseneca.ca
Section    : OOP 345

I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. 
This submitted piece of work has not been shared with any other student or 3rd party content provider.

/////////////////////////////////////////////////////////////////////////*/
#ifndef SENECA_DIRECTORY_H
#define SENECA_DIRECTORY_H

#include "Resource.h"
#include <vector>

namespace seneca
{
    // Can hold multiple files and directories like a file system
    class Directory:public Resource{
    private:
        // The vector data type is a dynamic array container -> the size of the array can be adjusted freely
        // Stores pointers to Resource objects, which can be a File or a Directory
		std::vector<Resource*> m_contents;
	public:
        // Directory names always end with /
		Directory(std::string dir_name = "/");
		void update_parent_path(const std::string&) override;
		NodeType type() const override;
		std::string path() const override;
		std::string name() const override;
		int count() const override;
		size_t size() const override;
		Directory& operator+=(Resource*);
		Resource* find(const std::string&, const std::vector<OpFlags>& flags = std::vector<OpFlags>());
		~Directory();
		// add for p2
		void remove(const std::string&, const std::vector<OpFlags>& flags = std::vector<OpFlags>());
		void display(std::ostream&, const std::vector<FormatFlags>& ops = std::vector<FormatFlags>()) const;
	};
}

#endif