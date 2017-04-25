 /**
 * Simple Profiler class to keep track of engine memory/timing
 * @author: Dennis Zinzi (130301136)
 */

#pragma once

#include <iostream>

using std::cout;
using std::endl;

//Represent excecution for appropriate subsystem
enum System{
	Graphics,
	Physics,
	Input,
	InitShutdown,
	FileIO,
	Audio
};

class Profiler{
	public:
		Profiler();

		//Output execution timing of subsystems
		void ShowStats();

		//Update appropriate time tracker
		void UpdateTime(System sys, float time);

		//Reset class time counter
		void ResetTime(float time);

	private:
		float times[3];
		float time;
		float startTime;
		bool update;
};