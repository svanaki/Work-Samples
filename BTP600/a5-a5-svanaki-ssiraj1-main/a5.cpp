/*****************************************/
/* Soodeh Vanaki            SID:075782128*/
/* Alvia Siraj              SID:100427178*/
/*****************************************/

#include "a5.h"
#include <iostream>
#include <string>
/****************** FeatureState Class ********************/
void FeatureStatus::accept() {
	stateid_->accept(this);
}
void FeatureStatus::reject() {
	stateid_->reject(this);
}
void FeatureStatus::print() {
	std::cout << "-----------------------" << std::endl;
	std::cout << stateName() << std::endl;
	stateid_->print(this);
}
std::string FeatureStatus::stateName() const {
	return stateid_->stateName();
}
FeatureStatus::FeatureStatus() {
	stateid_ = ClassDesign::Instance();
	theCode_ = "";
	theDesign_ = "";
	comment_ = "";
}
void FeatureStatus::update(const std::string& s) {
	stateid_->update(this, s);
}
void FeatureStatus::changeState(FState* state) {
	stateid_ = state;
}

std::string FeatureStatus::getCode()
{
	return theCode_;
}

std::string FeatureStatus::getComment()
{
	return comment_;
}

std::string FeatureStatus::getDesign()
{
	return theDesign_;
}

void FeatureStatus::setCode(std::string s)
{
	theCode_ = s;
}

void FeatureStatus::setComment(std::string s)
{
	comment_ = s;
}

void FeatureStatus::setDesign(std::string s)
{
	theDesign_ = s;
}

/***************************************************************************************/
/*********************************** ClassDesign Class *********************************/

ClassDesign::ClassDesign() {
	state = CLASSDESIGN;
}

StateID ClassDesign::getState(){
	return state;
}

FState* ClassDesign::Instance(){
	ClassDesign* state = new ClassDesign();
	return state;
}

std::string ClassDesign::stateName() const{
	std::string name;
	name = "Class Design";
	return name;
}

void ClassDesign::print(FeatureStatus* fstatus)
{
	std::cout << fstatus->getDesign() << std::endl;
}

void ClassDesign::update(FeatureStatus* fstatus, const std::string& s){
	fstatus->setDesign(s);
}

void ClassDesign::accept(FeatureStatus* fstatus){
	changeState(fstatus, CodeUpdate::Instance());
}

void ClassDesign::reject(FeatureStatus* fstatus){
	changeState(fstatus, ClassDesign::Instance());
}

/***************************************************************************************/
/*********************************** CodeUpdate Class **********************************/

CodeUpdate::CodeUpdate() {
	state = CODEUPATE;
}

StateID CodeUpdate::getState() {
	return state;
}

FState* CodeUpdate::Instance() {
	CodeUpdate* state = new CodeUpdate();
	return state;
}

std::string CodeUpdate::stateName() const {
	std::string name;
	name = "Code Update";
	return name;
}

void CodeUpdate::print(FeatureStatus* fstatus)
{
	std::cout << fstatus->getCode() << std::endl;
}

void CodeUpdate::update(FeatureStatus* fstatus, const std::string& s) {
	fstatus->setCode(s);
}

void CodeUpdate::accept(FeatureStatus* fstatus) {
	changeState(fstatus, UnitTest::Instance());
}

void CodeUpdate::reject(FeatureStatus* fstatus) {
	changeState(fstatus, ReDesignREQ::Instance());
}

/***************************************************************************************/
/*********************************** ReDesignREQ Class **********************************/

ReDesignREQ::ReDesignREQ() {
	state = REDESIGNREQ;
}

StateID ReDesignREQ::getState() {
	return state;
}

FState* ReDesignREQ::Instance() {
	ReDesignREQ* state = new ReDesignREQ();
	return state;
}

std::string ReDesignREQ::stateName() const {
	std::string name;
	name = "Redesign Requested";
	return name;
}

void ReDesignREQ::print(FeatureStatus* fstatus)
{
	std::cout << fstatus->getComment() << std::endl;
	std::cout << fstatus->getDesign() << std::endl;
}

void ReDesignREQ::update(FeatureStatus* fstatus, const std::string& s) {
	fstatus->setComment(s);
}

void ReDesignREQ::accept(FeatureStatus* fstatus) {
	changeState(fstatus, ClassDesign::Instance());
}

void ReDesignREQ::reject(FeatureStatus* fstatus) {
	changeState(fstatus, CodeUpdate::Instance());
}

/***************************************************************************************/
/*********************************** UnitTest Class **********************************/

UnitTest::UnitTest() {
	state = UNITTEST;
}

StateID UnitTest::getState() {
	return state;
}

FState* UnitTest::Instance() {
	UnitTest* state = new UnitTest();
	return state;
}

std::string UnitTest::stateName() const {
	std::string name;
	name = "Unit Test";
	return name;
}

void UnitTest::print(FeatureStatus* fstatus) {
	std::cout << fstatus->getCode() << std::endl;
	std::cout << fstatus->getComment() << std::endl;
}

void UnitTest::update(FeatureStatus* fstatus, const std::string& s) {
	std::string comment = fstatus->getComment();
	fstatus->setComment(comment+"\n"+s);
}

void UnitTest::accept(FeatureStatus* fstatus) {
	changeState(fstatus, PullRequest::Instance());
}

void UnitTest::reject(FeatureStatus* fstatus) {
	changeState(fstatus, CodeFixREQ::Instance());
}

/***************************************************************************************/
/*********************************** CodeFixREQ Class **********************************/

CodeFixREQ::CodeFixREQ() {
	state = CODEFIXREQ;
}

StateID CodeFixREQ::getState() {
	return state;
}

FState* CodeFixREQ::Instance() {
	CodeFixREQ* state = new CodeFixREQ();
	return state;
}

std::string CodeFixREQ::stateName() const {
	std::string name;
	name = "Code Fix Requested";
	return name;
}

void CodeFixREQ::print(FeatureStatus* fstatus)
{
	std::cout << fstatus->getComment() << std::endl;
	std::cout << fstatus->getCode() << std::endl;
}

void CodeFixREQ::update(FeatureStatus* fstatus, const std::string& s) {
	fstatus->setComment(fstatus->getComment() + " " + s);
}

void CodeFixREQ::accept(FeatureStatus* fstatus) {
	changeState(fstatus, CodeUpdate::Instance());
}

void CodeFixREQ::reject(FeatureStatus* fstatus) {
	changeState(fstatus, ReDesignREQ::Instance());
}

/***************************************************************************************/
/*********************************** PullRequest Class **********************************/

PullRequest::PullRequest() {
	state = PULLREQUEST;
}

StateID PullRequest::getState() {
	return state;
}

FState* PullRequest::Instance() {
	PullRequest* state = new PullRequest();
	return state;
}

std::string PullRequest::stateName() const {
	std::string name;
	name = "Pull Request";
	return name;
}

void PullRequest::print(FeatureStatus* fstatus)
{
	std::cout << fstatus->getCode() << std::endl;
	std::cout << fstatus->getComment() << std::endl;
}

void PullRequest::update(FeatureStatus* fstatus, const std::string& s) {
	fstatus->setComment(s);
}

void PullRequest::accept(FeatureStatus* fstatus) {
	changeState(fstatus, ChangeAccepted::Instance());
}

void PullRequest::reject(FeatureStatus* fstatus) {
	changeState(fstatus, CodeFixREQ::Instance());
}

/***************************************************************************************/
/*********************************** ChangeAccepted Class **********************************/

ChangeAccepted::ChangeAccepted() {
	state = CHANGEACCEPTED;
}

StateID ChangeAccepted::getState() {
	return state;
}

FState* ChangeAccepted::Instance() {
	ChangeAccepted* state = new ChangeAccepted();
	return state;
}

std::string ChangeAccepted::stateName() const {
	std::string name;
	name = "Change Accepted";
	return name;
}

void ChangeAccepted::print(FeatureStatus* fstatus)
{
	std::cout << fstatus->getDesign() << std::endl;
	std::cout << fstatus->getCode() << std::endl;
	std::cout << fstatus->getComment() << std::endl;
}

void ChangeAccepted::update(FeatureStatus* fstatus, const std::string& s) {
	fstatus->setComment("Change Accepted");
}

void ChangeAccepted::accept(FeatureStatus* fstatus) {
	// do nothing
}

void ChangeAccepted::reject(FeatureStatus* fstatus) {
	// do nothing
}