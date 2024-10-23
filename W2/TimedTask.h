#ifndef SENECA_TIMEDTASK_H
#define SENECA_TIMEDTASK_H

#include <iostream>
#include <string>
#include <chrono>

namespace seneca {
	struct Task { 
		std::string name; // string이기 때문에 memory leack 걱정할 필요없음. 왜냐하면 컴파일러가 관리해 주기 때문
		std::string timeUnit;
		std::chrono::steady_clock::duration s_duration;
	};
	class TimedTask {
		// statically "Task 객체 배열"을 관리하는 클래스
		// 이벤트 객체의 최대 갯수를 10으로 predefine함
	private:
		static const size_t maxTasks = 10;  // 최대 작업 수
		Task tasks[maxTasks];               // // struct 타입의 Task 배열
		int m_number; // Task배열에 저장된 record 갯수
		std::chrono::steady_clock::time_point m_startTime; // 현재 task의 시작 시간
		std::chrono::steady_clock::time_point m_endTime; // 현재 task의 끝난 시간
	public:
		TimedTask();
		void startClock(); // modifier
		void stopClock(); // modifier
		void addTask(const char* c_name); // modifier
		friend std::ostream& operator<<(std::ostream& os, const TimedTask& tt);
	};
}
#endif