/*/////////////////////////////////////////////////////////////////////////
Full Name  : Hanbi Gong
Student ID#: 111932224
Email      : hgong12@myseneca.ca
Section    : OOP 345

I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. 
This submitted piece of work has not been shared with any other student or 3rd party content provider.

/////////////////////////////////////////////////////////////////////////*/


// Workshop 9 - Multi-Threading, Thread Class

#include <iostream>
#include <fstream>
#include <functional>
#include <string>
#include <vector>
#include <thread>
#include <numeric>
#include "ProcessData.h"

namespace seneca
{
	// The following function receives array (pointer) as the first argument, number of array 
	//   elements (size) as second argument, divisor as the third argument, and avg as fourth argument. 
	//   size and divisor are not necessarily same. When size and divisor hold same value, avg will 
	//   hold average of the array elements. When they are different, avg will hold a value called 
	// 	 as average-factor. For part 1, you will be using same value for size and double. Use of 
	//   different values for size and divisor will be useful for multi-threaded implementation in part-2.
	void computeAvgFactor(const int* arr, int size, int divisor, double& avg) {
		avg = 0;
		for (int i = 0; i < size; i++)
		{
			avg += arr[i];
		}
		avg /= divisor;
	}

	// The following function receives array (pointer) as the first argument, number of array elements  
	//   (size) as second argument, divisor as the third argument, computed average value of the data items
	//   as fourth argument, and var as fifth argument. Size and divisor are not necessarily same as in the 
	//   case of computeAvgFactor. When size and divisor hold same value, var will get total variance of 
	//   the array elements. When they are different, var will hold a value called as variance factor. 
	//   For part 1, you will be using same value for size and double. Use of different values for size 
	//   and divisor will be useful for multi-threaded implementation in part-2.
	void computeVarFactor(const int* arr, int size, int divisor, double avg, double& var) {
		var = 0;
		for (int i = 0; i < size; i++)
		{
			var += (arr[i] - avg) * (arr[i] - avg);
		}
		var /= divisor;
	}

	ProcessData::operator bool() const {
		return total_items > 0 && data != nullptr && num_threads>0 && averages && variances && p_indices;
	}

	// The following constructor of the functor receives name of the data file, opens it in 
	//   binary mode for reading, reads first int data as total_items, allocate memory space 
	//   to hold the data items, and reads the data items into the allocated memory space. 
	//   It prints first five data items and the last three data items as data samples.
	ProcessData::ProcessData(const std::string& filename, int n_threads) {
		// TODO: Open the file whose name was received as parameter and read the content
		//         into variables "total_items" and "data". Don't forget to allocate
		//         memory for "data".
		//       The file is binary and has the format described in the specs.
		total_items = 0;
		data = nullptr;

		std::ifstream file(filename, std::ios::binary);
		if (!file) {
			throw std::runtime_error("Could not open file " + filename);
		}

		file.read(reinterpret_cast<char*>(&total_items), sizeof(total_items));
		if (!file) {
			throw std::runtime_error("Error reading total_items from file " + filename);
		}

		data = new int[total_items];

		file.read(reinterpret_cast<char*>(data), total_items * sizeof(int));
		if (!file) {
			throw std::runtime_error("Error reading data from file " + filename);
		}

		file.close();

		std::cout << "Item's count in file '"<< filename << "': " << total_items << std::endl;
		std::cout << "  [" << data[0] << ", " << data[1] << ", " << data[2] << ", ... , "
		          << data[total_items - 3] << ", " << data[total_items - 2] << ", "
		          << data[total_items - 1] << "]\n";

		// Following statements initialize the variables added for multi-threaded 
		//   computation
		num_threads = n_threads; 
		averages = new double[num_threads] {};
		variances = new double[num_threads] {};
		p_indices = new int[num_threads+1] {};
		for (int i = 0; i < num_threads+1; i++)
			p_indices[i] = i * (total_items / num_threads);
	}

	ProcessData::~ProcessData() {
		delete[] data;
		delete[] averages;
		delete[] variances;
		delete[] p_indices;
	}

	// TODO Improve operator() function from part-1 for multi-threaded operation. Enhance the
	//   function logic for the computation of average and variance by running the
	//   functions `computeAvgFactor` and `computeVarFactor` in multiple threads.
	// The function divides the data into a number of parts, where the number of parts is
	//   equal to the number of threads. Use multi-threading to compute average-factor for
	//   each part of the data by calling the function `computeAvgFactor`. Add the obtained
	//   average-factors to compute total average. Use the resulting total average as the
	//   average value argument for the function computeVarFactor, to compute variance-factors
	//   for each part of the data. Use multi-threading to compute variance-factor for each
	//   part of the data. Add computed variance-factors to obtain total variance.
	// Save the data into a file with filename held by the argument `target_file`.
	// Also, read the workshop instruction.
	int ProcessData::operator()(const std::string& targetFilename, double& avg, double& var) {

		// Vectors to hold partial results
		std::vector<double> avg_factors(num_threads, 0.0);
		std::vector<double> var_factors(num_threads, 0.0);

		std::vector<std::thread> avg_threads;
		for (int i = 0; i < num_threads; ++i) {
			int start_index = p_indices[i];
			int size = p_indices[i + 1] - start_index;
			avg_threads.emplace_back(std::bind(computeAvgFactor, data + start_index, size, total_items, std::ref(avg_factors[i])));
		}

		for (auto& thread : avg_threads) {
			thread.join();
		}

		double total_avg = 0.0;
		for (const auto& factor : avg_factors) {
			total_avg += factor;
		}
		avg = total_avg;

		std::vector<std::thread> var_threads;
		for (int i = 0; i < num_threads; ++i) {
			int start_index = p_indices[i];
			int size = p_indices[i + 1] - start_index;
			var_threads.emplace_back(std::bind(computeVarFactor, data + start_index, size, total_items, avg, std::ref(var_factors[i])));
		}

		for (auto& thread : var_threads) {
			thread.join();
		}

		double total_var = 0.0;
		for (const auto& factor : var_factors) {
			total_var += factor;
		}
		var = total_var;

		std::ofstream file(targetFilename, std::ios::binary);
		if (!file) {
			throw std::runtime_error("Could not open target file");
		}

		file.write(reinterpret_cast<const char*>(&total_items), sizeof(total_items));
		if (!file) {
			throw std::runtime_error("Error writing total_items to target file ");
		}

		file.write(reinterpret_cast<const char*>(data), total_items * sizeof(int));
		if (!file) {
			throw std::runtime_error("Error writing data to target file ");
		}

		file.close();

		return 0;
	}

}
