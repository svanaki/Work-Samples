
// Alvia Siraj, Soodeh Vanaki, Andre Jenah
// 100427178,   075782128,     134901180


#include "a4.h"

#include <iostream>
#include <list>
#include <string>
#include <algorithm>

Subject::Subject() {

}

void Subject::attach(Observer* o) {

	observer_.push_back(o);
}

void Subject::detach(const Observer* o) {

	observer_.erase(find(observer_.begin(), observer_.end(), o));
}

void Subject::notify() {

	//have an iterator from the beginning of the lsit
	std::list<Observer*>::iterator iterator = observer_.begin();
	//iterate through the observer list to update all observers internal state
	while (iterator != observer_.end()) {
		(*iterator)->update();
		++iterator;
	}
}

Stars::Stars() {

	//get Timer's current time
	Timer* timer = Timer::getInstance();
	star_ = 0;
}

void Stars::update() {

	//update observer to get the current time
	Timer* timer = Timer::getInstance();
	star_ = timer->currtime();
}

void Stars::print() const {

	//print the number of elapsed seconds as a number of *'s
	double startrun = trunc(star_);
	std::cout << (std::string(startrun, '*'));
}

Seconds::Seconds() {

	//get Timer's current time
	Timer* timer = Timer::getInstance();
	seconds_ = 0;
}

void Seconds::update() {

	//update observer to get the current time
	Timer* timer = Timer::getInstance();
	seconds_ = timer->currtime();
}

void Seconds::print() const {

	//print the number of elapsed seconds as text rounded down to nearest second
	std::cout << trunc(seconds_);
}

Status::Status() {
	
	//initialize Timer's status to paused
	Timer* timer = Timer::getInstance();
	status_ = timer->isPaused() == true;
}

void Status::update() {

	//update observer to get the current status
	Timer* timer = Timer::getInstance();
	status_ = timer->isPaused();
}

void Status::print() const {

	//Prints out the status of timer (paused or unpaused)
	std::string stat;
	if (status_ == true) {
		stat = "paused";
	}
	else if (status_ == false) {
		stat = "unpaused";
	}
	std::cout << stat;
}

/******************************** UndoStack *********************************************/

UndoStack::UndoStack() : lastObject(NULL) {
	
}

// Saves m into the current object.  An UndoStack can store up to 5 mementos. 
// When doing a save operation, if the current object already stores 5 mementos, 
// the oldest object is removed to make way for the new memento.
void UndoStack::save(Memento* m) {
	
	if (curObject.size() == maxSize ) {
		
		curObject.pop_back();
		curObject.push_front(m);
	}
	else if (curObject.size() < maxSize) {
		curObject.push_front(m);
	}
	else {
		while (curObject.size() > maxSize) {
			curObject.pop_back();
		}
	}

}

// Returns the address of the newest memento from the UndoStack and 
// removes that pointer(without deallocating the Memento) from the UndoStack.
Memento* UndoStack::getMemento() {
	lastObject = curObject.front();
	curObject.pop_front();
	return lastObject;
}

/******************************************************************************************/
/************************************* Timer **********************************************/

Timer* Timer::onlyOne = nullptr;

// This function creates and returns the address of a Memento that represent the Timer's 
// current internal state.
Memento* Timer::createMemento() {
	Memento* currTimer = new Memento();
	currTimer->SetElapsedTime(currtime());
	currTimer->SetPausedStatus(isPaused());
	return currTimer;
}

// This function restores the Timer to the state represented by m. Before the function ends,
// deallocated the Memento m points at.
void Timer::restoreFromMemento(Memento* m) {

	/*this block of code gets the current time depending on platform
	.. you will need this to restore your timer */
#if PLATFORM == WINDOWS
	clock_t curr = clock();
#else
	struct timespec curr;
	clock_gettime(CLOCK_MONOTONIC_RAW, &curr);
#endif

	this->starttime_ = curr;
	
	this->elapsedTime_ = m->GetElapsedTime();
	this->isstop_ = m->GetPausedStatus();

	delete m;
	m = nullptr;
}
/*************************************************************************************/
/********************************** Memento ******************************************/
// Constructor. narrow interface
Memento::Memento() {

	elapsedtime_ = 0;
	pausedStatus_ = true;
}

// Set the pause status
void Memento::SetPausedStatus(bool pausedStatus) {

	pausedStatus_ = pausedStatus;
}

// Set the elapsed time
void Memento::SetElapsedTime(double elapsedTime) {

	elapsedtime_ = elapsedTime;
}

// get the paused status
bool Memento::GetPausedStatus() {

	return pausedStatus_;
}

// get the elapsed time
double Memento::GetElapsedTime() {

	return elapsedtime_;
}

/****************************************************************************************/

/**************************************************************/
/*   Nothing below this comment should be modified            */
/**************************************************************/

/* Timer class functions.
  start();  starts the clock running from the current time
  currtime();  returns the current time
  stop();  stops the clock without reseting its value
  reset();  stops the clock and resets the timer to 0
  isPaused(); returns true if the timer is stopped, false otherwise
*/

Timer::Timer() {
	elapsedTime_ = 0;
	isstop_ = true;

#if PLATFORM == WINDOWS
	starttime_ = 0;
	stoptime_ = 0;
#else
	clock_gettime(CLOCK_MONOTONIC_RAW, &starttime_);
	stoptime_ = starttime_;
#endif


}
void Timer::reset() {
#if PLATFORM == WINDOWS
	starttime_ = 0;
	stoptime_ = 0;
#else
	clock_gettime(CLOCK_MONOTONIC_RAW, &starttime_);
	stoptime_ = starttime_;
#endif
	elapsedTime_ = 0;
	isstop_ = true;
}
void Timer::start() {
#if PLATFORM == WINDOWS
	clock_t curr = clock();
	if (isstop_) {
		starttime_ = (stoptime_ == 0) ? curr : starttime_ + (curr - stoptime_);
		isstop_ = false;
	}
	else {
		starttime_ = curr;   //its like hitting reset and start
	}
#else
	struct timespec curr;
	clock_gettime(CLOCK_MONOTONIC_RAW, &curr);
	if (isstop_) {
		starttime_ = curr;
		isstop_ = false;
	}
	else {
		clock_gettime(CLOCK_MONOTONIC_RAW, &starttime_);
		stoptime_ = starttime_;
		elapsedTime_ = 0;
	}
#endif

}
void Timer::stop() {
#if PLATFORM == WINDOWS
	stoptime_ = clock();
#else
	clock_gettime(CLOCK_MONOTONIC_RAW, &stoptime_);
	elapsedTime_ += (stoptime_.tv_nsec - starttime_.tv_nsec) / 1000000000.0 +
		(stoptime_.tv_sec - starttime_.tv_sec);
#endif
	isstop_ = true;
}
double Timer::currtime() {
	double rc;
#if PLATFORM == WINDOWS
	clock_t curr = clock();
	clock_t elapse = (isstop_) ? stoptime_ - starttime_ : curr - starttime_;
	rc = double(elapse) / CLOCKS_PER_SEC;
#else
	struct timespec curr;
	clock_gettime(CLOCK_MONOTONIC_RAW, &curr);
	if (isstop_) {
		rc = elapsedTime_;
	}
	else {
		rc = elapsedTime_ + (curr.tv_nsec - starttime_.tv_nsec) / 1000000000.0 +
			(curr.tv_sec - starttime_.tv_sec);
	}
#endif
	return rc;
}
double Timer::starttime() {
#if PLATFORM == WINDOWS
	return (double)starttime_;
#else
	return starttime_.tv_nsec / 1000000000.0 + starttime_.tv_sec;
#endif
}
bool Timer::isPaused() {
	return isstop_;
}


