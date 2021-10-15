//Windows benchmarking class made from Ram�nster's benchamrking functions
#pragma once
#include <windows.h>
#include <stdio.h>

class WinBench {
	private:
		double PCFreq = 0.0;
		__int64 CounterStart = 0;
	public:
		void StartCounter();
		double GetCounter();
		double GetCounter(double divisor);
		double GetCounter(int divisor);
};

