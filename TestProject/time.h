#pragma once
#include "namespaces.hpp"
struct timer
{
	bool debounce = false;
	bool resetOnce = false;
	void start_delayMS(unsigned int ms, unsigned int deltaTime);
	bool c_delay();

	void start_recursiveTimerMS(unsigned int ms, unsigned int deltaTime); // start call. First parameter is time to wait in MS second is DeltaTime of system
	bool c_recursiveTimerDelay(); // it will automatically reset and return true every said ms
	
	inline void resetTimer() 
	{
		if (!resetOnce)
		{
			timeStarted = 0;
			timeDest = 0; 
			resetOnce = true;
		}
	}

	unsigned int timeStarted = 0;
	unsigned int timeDest = 0;
};