#pragma once
#include <iostream>
#include <chrono>
#include <ctime>
#include <memory>
struct numFactory {

	static inline int randNum(int range) // returns a random number based on time. 
	{
		const std::time_t cTime = std::time(0);
		const std::tm* time = std::localtime(&cTime);
		srand(floor((time->tm_sec + time->tm_hour) * 3.141592653));
		delete time; // make sure this is deleted each call.
		return (rand() % range);
	}	
	static inline int randNumDT(int range, unsigned int dt) // returns a random number based on time. 
	{
		srand(floor(dt * 3.141592653));
		return (rand() % range);
	}
};
