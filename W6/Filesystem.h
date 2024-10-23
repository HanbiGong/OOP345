/*/////////////////////////////////////////////////////////////////////////
Full Name  : Hanbi Gong
Student ID#: 111932224
Email      : hgong12@myseneca.ca
Section    : OOP 345

I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. 
This submitted piece of work has not been shared with any other student or 3rd party content provider.

/////////////////////////////////////////////////////////////////////////*/

#ifndef SENECA_FILESYSTEM_H
#define SENECA_FILESYSTEM_H

#include "Resource.h"
#include "File.h"
#include "Directory.h"
#include <vector>

namespace seneca
{
    // Can hold multiple files and directories like a file system
    class Filesystem {
    private:
        Directory* m_root; // Stores the root directory of the file system
        Directory* m_current; // Stores the current working directory of the file system
        std::string remove_trim(std::string input); // Removes trim
        std::vector<std::string> splitPath(const std::string& path); // Splits from resource path
        void createDir(const std::string& dirPath); // Creates a directory
        void createFile(const std::string& filePath, std::string& contents); // Creates a file
    public:
        Filesystem(std::string file_name, std::string root_dir_name = "");
        // move constructor, operation
        Filesystem& operator=(Filesystem&& other) noexcept;
        Filesystem(Filesystem&& other) noexcept;

        Filesystem& operator+=(Resource*);
        Directory* change_directory(const std::string& str = "");
        Directory* get_current_directory() const;
        ~Filesystem(); // Deallocates root directory
	};
}

#endif