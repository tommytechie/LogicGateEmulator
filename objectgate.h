#pragma once
#include "tommylogic.h"

using std::pair;

class ObjGate {
private:
	void AND(vector<int> input) {
		output = (input[0] == 1 && input[1] == 1);
	}

	void OR(vector<int> input) {
		output = (input[0] == 1 || input[1] == 1);
	}

	void NOT(vector<int> input) {
		if (input[0] != 0) output = 0;
		else output = 1;
	}

	ObjGate* LocalgateA;
	ObjGate* LocalgateB;

	vector<int> input;

	int output = 2; //affected by logic_func (function pointer)

	void (ObjGate::* logic_func)(vector<int>);

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

	ObjGate a(ObjGate* gateA, ObjGate* gateB) { //TODO
		LocalgateA = gateA;
		LocalgateB = gateB;

		input.push_back(LocalgateA->returnValue());
		input.push_back(LocalgateB->returnValue());

		vector<int> logic_func(input);

		return gateA;
	}

	void calculation() {
		vector<int> logic_func(input);
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
		calculation();
	}

	int returnValue() {//return the output
		return output;
	}

};

