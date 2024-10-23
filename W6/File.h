/*/////////////////////////////////////////////////////////////////////////
Full Name  : Hanbi Gong
Student ID#: 111932224
Email      : hgong12@myseneca.ca
Section    : OOP 345

I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. 
This submitted piece of work has not been shared with any other student or 3rd party content provider.

/////////////////////////////////////////////////////////////////////////*/
#ifndef SENECA_FILE_H
#define SENECA_FILE_H

#include "Resource.h"
#include <string>

namespace seneca
{
    // Implements the interface Resource
    class File: public Resource {
    private:
        // Stores the content of the file
		std::string m_contents{};
	public:
		File(std::string file_name, std::string file_reps = "");
		void update_parent_path(const std::string&) override;
		NodeType type() const override;
		std::string path() const override;
		std::string name() const override;
		int count() const override;
		size_t size() const override;
	};
}

#endif