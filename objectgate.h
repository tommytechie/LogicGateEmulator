#pragma once
#include "tommylogic.h"

using std::pair;

class ObjGate {
private:
	int AND(vector<int> input) {
		return (input[0] == 1 && input[1] == 1);
	}

	int OR(vector<int> input) {
		return (input[0] == 1 || input[1] == 1);
	}

	int NOT(vector<int> input) {
		if (input[0] != 0) return 0;
		else return 1;
	}

	ObjGate* LocalgateA;
	ObjGate* LocalgateB;

	vector<int> input;

	int output = 2; //affected by logic_func (function pointer)

	int (ObjGate::* logic_func)(vector<int>);

	int WhichContructor = 0;

public:
	ObjGate() {
		
	}
	ObjGate(ObjGate* gateA) {
		LocalgateA = gateA; input.push_back(LocalgateA->returnValue());
	}
	ObjGate(ObjGate* gateA, ObjGate* gateB) {
		LocalgateA = gateA; input.push_back(LocalgateA->returnValue());
		LocalgateB = gateB; input.push_back(LocalgateB->returnValue());
	}
	ObjGate(int inputA) {
		input.push_back(inputA);
	}
	ObjGate(int inputA, int inputB) {
		input.push_back(inputA);
		input.push_back(inputB);
	}
	ObjGate(ObjGate* gateA, int inputB) {
		LocalgateA = gateA; input.push_back(LocalgateA->returnValue());
		input.push_back(inputB);
	}
	ObjGate(int inputA, ObjGate* gateB) {
		input.push_back(inputA); 
		LocalgateB = gateB; input.push_back(LocalgateB->returnValue());
	}

	int a(ObjGate* gateA) {
		LocalgateA = gateA;
		input.push_back(LocalgateA->returnValue());
		calculation();
		return output;
	}
	int a(ObjGate* gateA, ObjGate* gateB) { //TODO
		LocalgateA = gateA;
		LocalgateB = gateB;
		input.push_back(LocalgateA->returnValue());
		input.push_back(LocalgateB->returnValue());
		calculation();
		return output;
	}
	int a(int inputA) {
		input.push_back(inputA);
		calculation();
		return output;
	}
	int a(int inputA, int inputB) {
		input.push_back(inputA);
		input.push_back(inputB);
		calculation();
		return output;
	}
	int a(int inputA, ObjGate* gateB) {
		input.push_back(inputA);
		LocalgateB = gateB; input.push_back(LocalgateB->returnValue());
		calculation();
		return output;
	}
	int a(ObjGate* gateA, int inputB) {
		LocalgateA = gateA; input.push_back(LocalgateA->returnValue());
		input.push_back(inputB);
		calculation();
		return output;
	}


	void calculation() {
		if (input.size() < 2) { cout << "You are using a gate with INSUFFICIENT input(s)" << endl; return; }
		output = (this->*logic_func)(input);
	}

	void define(int GateNumber) {
		switch (GateNumber)
		{
		case 1:
			logic_func = &ObjGate::AND;
			break;
		case 2:
			logic_func = &ObjGate::OR;
			break;
		case 3:
			logic_func = &ObjGate::NOT;
			break;
		default:
			logic_func = &ObjGate::AND;
		}
	}

	int returnValue() {//return the output
		calculation();
		return output;
	}

};

