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
				NumOfInputs = NumOfInputs + 1; input.push_back(0);
				break;
			case 1:
				GateFunc[i] = &LogicGate::AND;
				position.push_back(2);
				NumOfInputs = NumOfInputs + 2; input.push_back(0); input.push_back(0);
				break;
			case 2:
				GateFunc[i] = &LogicGate::OR;
				position.push_back(2);
				NumOfInputs = NumOfInputs + 2; input.push_back(0); input.push_back(0);
				break;
			case 3:
				GateFunc[i] = &LogicGate::NOT;
				position.push_back(1);
				NumOfInputs = NumOfInputs + 1; input.push_back(0);
				break;
			case 4:
				GateFunc[i] = &LogicGate::NAND;
				position.push_back(2);
				NumOfInputs = NumOfInputs + 2; input.push_back(0); input.push_back(0);
				break;
			case 5:
				GateFunc[i] = &LogicGate::NOR;
				position.push_back(2);
				NumOfInputs = NumOfInputs + 2; input.push_back(0); input.push_back(0);
				break;
			case 6:
				GateFunc[i] = &LogicGate::XNOR;
				position.push_back(2);
				NumOfInputs = NumOfInputs + 2; input.push_back(0); input.push_back(0);
				break;
			case 7:
				GateFunc[i] = &LogicGate::XOR;
				position.push_back(2);
				NumOfInputs = NumOfInputs + 2; input.push_back(0); input.push_back(0);
				break;
			default:
				break;//Nothing...
			}
		}
	}

	int getNumOfInputs() {
		int tmpNumOfInputs = 0;
		for (int i = 0; i < LogicGateArr.size(); i++) {
			tmpNumOfInputs += LogicGateArr[i].input.size();
		}
		NumOfInputs = tmpNumOfInputs;
		return tmpNumOfInputs;
	}

	int getNumOfOutputs() {
		int tmpNumOfOutputs = 0;
		for (int i = 0; i < LogicGateArr.size(); i++) {
			tmpNumOfOutputs += LogicGateArr[i].output.size();
		}
		NumOfOutputs = tmpNumOfOutputs;
		return tmpNumOfOutputs;
	}

	LogicGate* LocalgateA;
	LogicGate* LocalgateB;

	template <typename T>
	void printVector(vector<T> input) {
		for (int i = 0; i < input.size(); i++) {
			cout << input[i] << " ";
		}
	}

public:

	string name = "example gate";

	vector<int> position = { 0 }; //used in fundamental only

	vector<int> input = {};

	vector<int> Fgates;

	vector<int> output;

	int NumOfInputs; //Current Object NumOfInputs
	int NumOfOutputs; //Current Object NumOfOutputs

	vector<LogicGate> LogicGateArr;

	LogicGate() {

	}
	LogicGate(vector<int> inputvalue) {
		input = inputvalue;
	}

	void inputValues(vector<int> inputvalue) { //input value, if you didn't input when initializing...
		input = inputvalue;
		output.clear();
	}

	void define(vector<int> inputgates) { //define fundamental gates... (not useful when you are using objects as gates)
		Fgates = inputgates;
		assignFunctions(Fgates);
	}
	void define(vector<LogicGate> LogicGateArrayInput) { //input from array of Logic Gates, if you didn't input when initializing...
		input.clear();
		LogicGateArr = LogicGateArrayInput;
		for (int i = 0; i < LogicGateArr.size(); i++) {
			LogicGateArr[i].parallelCalc();
			for (int j = 0; j < LogicGateArr[i].output.size(); j++) {
				input.push_back(LogicGateArr[i].output[j]);
			}
			//cout << "Logic Gate " << i << ": "; printVector<int>(input); cout << endl;
		}
		getNumOfOutputs();
		getNumOfInputs();
		//cout << "Input Size Gate 1: " << LogicGateArr[0].input.size() << endl;
		//cout << "Input Size Gate 2: " << LogicGateArr[1].input.size() << endl;
		//cout << "Output Size Gate 1: " << LogicGateArr[0].output.size() << endl;
		//cout << "Output Size Gate 2: " << LogicGateArr[1].output.size() << endl;
	}

	void Calc() { //Object Gate Calculation(complex objects) //TODO FIX IT
		vector<int> tmpInputArr;
		vector<int> tmpPos = {0};
		int tmpMaxInputSize = 0;
		for (int i = 0; i < LogicGateArr.size(); i++) {
			tmpMaxInputSize += LogicGateArr[i].NumOfInputs;
			tmpPos.push_back(tmpMaxInputSize);
		}
		tmpPos.push_back(tmpMaxInputSize);
		if (input.size() < tmpMaxInputSize) {
			vector<int> tmp(50, 0);
			input = tmp;
			cout << "INPUT SIZE TOO SMALL" << endl;
		}
		for (int i = 0; i < LogicGateArr.size(); i++) {
			for (int j = tmpPos[i]; j < tmpPos[i + 1]; j++) {
				tmpInputArr.push_back(input[j]);
			}
			LogicGateArr[i].inputValues(tmpInputArr);
			LogicGateArr[i].parallelCalc();
		}
		for (int i = 0; i < LogicGateArr.size(); i++) {
			for (int j = 0; j < LogicGateArr[i].output.size(); j++) {
				output.push_back(LogicGateArr[i].output[j]);
			}
		}
		cout << "input arr: ";  printVector<int>(input); cout << endl;
		//cout << "inputs of calc: ";  printVector<int>(tmpInputArr); cout << endl;
	}

	void parallelCalc() { //Fundamental Gate Calculation
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

	void setName(string display_name) {
		name = display_name;
	}

	void printValue() {//return the output
		cout << "Answer for " << name << " is: ";
		for (int i = 0; i < output.size(); i++) {
			cout << output[i] << " ";
		}cout << endl;
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
