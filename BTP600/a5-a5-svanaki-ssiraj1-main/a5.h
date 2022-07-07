/*****************************************/
/* Soodeh Vanaki            SID:075782128*/
/* Alvia Siraj              SID:100427178*/
/*****************************************/

#ifndef A5_H
#define A5_H

#include <string>

enum StateID {
	CLASSDESIGN, CODEUPATE, REDESIGNREQ, UNITTEST,
	CODEFIXREQ, PULLREQUEST, CHANGEACCEPTED
};

class FState;

class FeatureStatus {

	friend class FState;
	FState* stateid_;
	
	std::string theCode_;
	std::string comment_;
	std::string theDesign_;
public:
	FeatureStatus();
	std::string stateName() const;
	void print();
	void update(const std::string& s);
	void accept();
	void reject();
	void changeState(FState* state);
	std::string getCode();
	std::string getComment();
	std::string getDesign();
	void setCode(std::string s);
	void setComment(std::string s);
	void setDesign(std::string s);
};

class FState {
public:
	virtual std::string stateName() const {}
	virtual void print(FeatureStatus*) {}
	virtual void update(FeatureStatus*, const std::string& s) {}
	virtual void accept(FeatureStatus*) {}
	virtual void reject(FeatureStatus*) {}
protected:
	void changeState(FeatureStatus* fstatus, FState* state) {
		fstatus->changeState(state);
	}
};

class ClassDesign : public FState {
	StateID state;
public:
	ClassDesign();
	StateID getState();
	static FState* Instance();

	virtual std::string stateName() const;
	virtual void print(FeatureStatus*);
	virtual void update(FeatureStatus*, const std::string& s);
	virtual void accept(FeatureStatus*);
	virtual void reject(FeatureStatus*);
};

class CodeUpdate : public FState {
	StateID state;
public:
	CodeUpdate();
	StateID getState();
	static FState* Instance();

	virtual std::string stateName() const;
	virtual void print(FeatureStatus*);
	virtual void update(FeatureStatus*, const std::string& s);
	virtual void accept(FeatureStatus*);
	virtual void reject(FeatureStatus*);
};

class ReDesignREQ : public FState {
	StateID state;
public:
	ReDesignREQ();
	StateID getState();
	static FState* Instance();

	virtual std::string stateName() const;
	virtual void print(FeatureStatus*);
	virtual void update(FeatureStatus*, const std::string& s);
	virtual void accept(FeatureStatus*);
	virtual void reject(FeatureStatus*);
};

class UnitTest : public FState {
	StateID state;
public:
	UnitTest();
	StateID getState();
	static FState* Instance();

	virtual std::string stateName() const;
	virtual void print(FeatureStatus*);
	virtual void update(FeatureStatus*, const std::string& s);
	virtual void accept(FeatureStatus*);
	virtual void reject(FeatureStatus*);
};

class CodeFixREQ : public FState {
	StateID state;
public:
	CodeFixREQ();
	StateID getState();
	static FState* Instance();


	virtual std::string stateName() const;
	virtual void print(FeatureStatus*);
	virtual void update(FeatureStatus*, const std::string& s);
	virtual void accept(FeatureStatus*);
	virtual void reject(FeatureStatus*);
};

class PullRequest : public FState {
	StateID state;
public:
	PullRequest();
	StateID getState();
	static FState* Instance();


	virtual std::string stateName() const;
	virtual void print(FeatureStatus*);
	virtual void update(FeatureStatus*, const std::string& s);
	virtual void accept(FeatureStatus*);
	virtual void reject(FeatureStatus*);
};

class ChangeAccepted : public FState {
	StateID state;
public:
	ChangeAccepted();
	StateID getState();
	static FState* Instance();


	virtual std::string stateName() const;
	virtual void print(FeatureStatus*);
	virtual void update(FeatureStatus*, const std::string& s);
	virtual void accept(FeatureStatus*);
	virtual void reject(FeatureStatus*);
};

#endif
