
// Alvia Siraj, Soodeh Vanaki, Andre Jenah
// 100427178,   075782128,     134901180

#include <time.h>
#include <list>
#include <iostream>
#include <deque>

#define POSIX 1
#define WINDOWS 2
//Generally you want to use the POSIX version.  Its better, more accurate.  But, the
//function won't work on non-posix systems... so switch to WINDOWS if you are using VS
//The matrix version is POSIX
#define PLATFORM POSIX
//#define PLATFORM WINDOWS

/*This class represents a timer.  A timer can be used to calculate the 
time it took for a piece of code to be run.  It uses the actual time in 
processing as opposed to the wall clock so that differences in load on a 
system will not affect the timing of the code.  This object is like a stop 
watch.
When initialized, the timer is set to 0.  In order to start timing, the 
start() function must be used.  

The following are the member functions of Timer and their usage:
  start();  starts the clock running from the current time
  currtime();  returns the current time
  stop();  stops the clock without reseting its value
  reset();  stops the clock and resets the timer to 0
*/

class Observer;

class Subject {

    std::list<Observer*> observer_;
public:
    Subject();
    void attach(Observer* o);
    void detach(const Observer* o);
    void notify();
};

//Abstract Observer

class Observer {
public:
    virtual void print() const = 0;
    virtual void update() = 0;
};
//Concrete observers. subject of these observers is the Timer(a singleton)
//the 

class Stars :public Observer {
    double star_;
public:
    Stars();
    virtual void update();
    virtual void print() const;
};

class Seconds : public Observer {
    double seconds_;

public:
    Seconds();
    virtual void update();
    virtual void print() const;
};

class Status : public Observer {
    bool status_;

public:
    Status();
    virtual void update();
    virtual void print() const;
};

/*This class is completely empty..
It is up to you to define its interface
and implementation with accordance to
the Memento Pattern*/

class Memento {

	// private members accessible only to Originator
	friend class Timer;
public:
	// narrow public interface
	Memento();
private: 
	
	// set memento
	void SetPausedStatus(bool pausedStatus);
	void SetElapsedTime(double elapsedTime);
	
	// get memento
	bool GetPausedStatus();
	double GetElapsedTime();
	
	// private members
	double elapsedtime_;
	bool pausedStatus_;
};

//the Undo Stack
class UndoStack{
	std::deque<Memento*> curObject;
	Memento* lastObject;
	int maxSize = 5;
public:
    UndoStack();
	void save(Memento* m);
    Memento* getMemento();
};

class Timer: public Subject{

#if PLATFORM == WINDOWS
    clock_t starttime_;
    clock_t stoptime_;
#else
    struct timespec starttime_;
    struct timespec stoptime_;
#endif
    double elapsedTime_;
    bool isstop_;

protected:
	Timer();
private:
	static Timer* onlyOne;
	int counter = 0;

public:
	static Timer* getInstance() {
		if (onlyOne == nullptr) {
			onlyOne = new Timer();
		}
		return onlyOne;
	}
	void increment() {
		counter++;
	}

    void reset();
    void start();
    void stop();
    bool isPaused();
    double currtime();
    double starttime();


	Memento* createMemento();
	void restoreFromMemento(Memento* m);
};

