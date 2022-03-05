#pragma once
#include "tommylogic.h"

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

//=====================================================================================================================================

class LogicGate {
private:

	int (LogicGate::*GateFunc[20])(vector<int> inputvalue, unsigned int pos);

	int YES(vector<int> input, unsigned int pos) {
		return input[pos];
	}
	int AND(vector<int> input, unsigned int pos) {
		return (input[pos] == 1 && input[pos + 1] == 1);
	}
	int OR(vector<int> input, unsigned int pos) {
		return (input[pos] == 1 || input[pos + 1] == 1);
	}
	int NOT(vector<int> input, unsigned int pos) {
		if (input[pos] != 0) return 0;
		else return 1;
	}
	int NAND(vector<int> input, unsigned int pos) {
		if (AND(input, pos) != 0)return 0;
		else return 1;
	}
	int NOR(vector<int> input, unsigned int pos) {
		if (OR(input, pos) != 0)return 0;
		else return 1;
	}
	int XNOR(vector<int> input, unsigned int pos) {
		if (AND(input, pos) == 1 || NOR(input, pos) == 1)return 1;
		else return 0;
	}
	int XOR(vector<int> input, unsigned int pos) {
		if (OR(input, pos) == 1 && NAND(input, pos) == 1)return 1;
		else return 0;
	}

	void assignFunctions(vector<int> inputgates) {
		for (int i = 0; i < inputgates.size(); i++) {
			switch (inputgates[i])
			{
			case 0:
				GateFunc[i] = &LogicGate::YES;
				position.push_back(1);
				break;
			case 1:
				GateFunc[i] = &LogicGate::AND;
				position.push_back(2);
				break;
			case 2:
				GateFunc[i] = &LogicGate::OR;
				position.push_back(2);
				break;
			case 3:
				GateFunc[i] = &LogicGate::NOT;
				position.push_back(1);
				break;
			case 4:
				GateFunc[i] = &LogicGate::NAND;
				position.push_back(2);
				break;
			case 5:
				GateFunc[i] = &LogicGate::NOR;
				position.push_back(2);
				break;
			case 6:
				GateFunc[i] = &LogicGate::XNOR;
				position.push_back(2);
				break;
			case 7:
				GateFunc[i] = &LogicGate::XOR;
				position.push_back(2);
				break;
			default:
				break;//FOR OBJECTIFIED GATES
			}
		}
	}

	LogicGate* LocalgateA;
	LogicGate* LocalgateB;

	

public:
	//====Fundamental=======
	vector<int> position = { 0 };

	vector<int> input;

	vector<int> Fgates;

	vector<int> output;


	LogicGate(vector<int> inputvalue) {
		input = inputvalue;
	}

	void define(vector<int> inputgates) {
		Fgates = inputgates;
		assignFunctions(Fgates);
	}

	void parallelCalc() {
		output.clear();
		int Pos = 0;
		for (int i = 0; i < Fgates.size(); i++) {
			//cout << "i = " << i << endl;
			Pos += position[i];
			//cout << "Pos = " << Pos << endl;
			output.push_back((this->*GateFunc[i])(input, Pos));
			
		}
	}

	void clear() {
		position = { 0 };
		input.clear();
		Fgates.clear();
		output.clear();
	}

	vector<int> returnValue() {//return the output
		//calculation();
		return output;
	}

	//=======Objectify========================
	void define(LogicGate obj) {  //Overloading Define function for inputting previous objects into it
		//TODO
	}
};

/*

//1, 1 -> AND -> NOT -> 0

// vector<int> input

*/
