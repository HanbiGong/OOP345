#define _CRT_SECURE_NO_WARNINGS
#include "TimedTask.h"
#include <chrono>
#include <iomanip>

namespace seneca {
	TimedTask::TimedTask()
	{
		m_number = 0;
		startClock();
		stopClock();
	}
	void TimedTask::startClock()
	{
		m_startTime = std::chrono::steady_clock::now();
	}
	void TimedTask::stopClock()
	{
		m_endTime = std::chrono::steady_clock::now();
	}
	void TimedTask::addTask(const char* c_name)
	{
		if (m_number < static_cast<int>(maxTasks)) {
			tasks[m_number++] = { c_name, "nanosesconds", std::chrono::duration_cast<std::chrono::nanoseconds>(m_endTime-m_startTime) };
		}
		else {
			std::cout << "Error" << std::endl;
		}
	}
	
	std::ostream& operator<<(std::ostream& os, const TimedTask& tt)
	{
		os << "--------------------------" << std::endl;
		os << "Execution Times:" << std::endl;
		os << "--------------------------" << std::endl;
		for (int i = 0; i < tt.m_number; i++) {
			os << std::left << std::setw(21) << tt.tasks[i].name;
			os << std::right << std::setw(13) << tt.tasks[i].s_duration.count();
			os <<" " << tt.tasks[i].timeUnit;
			os << std::endl;
		}
		os << "--------------------------" << std::endl;
		return os;
	}
}