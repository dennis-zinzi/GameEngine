#include "Profiler.h"

Profiler::Profiler(){
}

//Shows average execution speed per loop per second
void Profiler::ShowStats(){
	if(!update){
		return;
	}

	cout << "Average execution speed per loop per second" << endl;
	cout << "Graphics took: " << (times[Graphics] / startTime) << "s" << endl;
	cout << "Physics took: " << (times[Physics] / startTime) << "s" << endl;
	cout << "Input took: " << (times[Input] / startTime) << "s" << endl;

	float totTime = times[Graphics] + times[Physics] + times[Input];
	cout << "Single loop: " << (totTime / startTime) << "s" << endl << endl;

	times[Graphics] = 0;
	times[Physics] = 0;
	times[Input] = 0;

	startTime = time;
}

void Profiler::UpdateTime(System sys, float time){
	times[sys] += time - this->time;
	this->time = time;
}


void Profiler::ResetTime(float time){
	this->time = time;

	if(time - startTime > 1000){
		cout << time - startTime << endl;
		update = true;
	}
	else{
		update = false;
	}
}
