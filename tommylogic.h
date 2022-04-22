#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

using std::vector; using std::cout; using std::endl; using std::string; using std::pair;
namespace tommylogic {
	bool vectorSizeChecker(int InputSize, vector<vector<int>> InputVector) { //Check V[i][?], the size of the row to see if it matches InputSize
		for (int i = 0; i < InputVector.size(); i++) {
			if (InputVector[i].size() != InputSize)return false;
		}
		return true;
	}

	template <typename T>
	void printVector(vector<T> input) {
		for (int i = 0; i < input.size(); i++) cout << input[i] << " ";
	}

	void printTruthtable(int InputSize, vector<vector<int>> TruthTableInput, vector<int> TruthTableResult) {
		if (vectorSizeChecker(InputSize, TruthTableInput)) {
			for (int i = 0; i < TruthTableResult.size(); i++) {
				for (int j = 0; j < InputSize; j++) {
					cout << TruthTableInput[i][j] << " ";
				}
				cout << "=> " << TruthTableResult[i] << endl;
			}
		}
		else {
			cout << "Wrong Table Input Size" << endl;
		}
	}

	vector<vector<int>> generateTruthtableYX(int n) {
		std::vector<std::vector<int> > output(n, std::vector<int>(1 << n));

		unsigned num_to_fill = 1U << (n - 1);
		for (unsigned col = 0; col < n; ++col, num_to_fill >>= 1U)
		{
			for (unsigned row = num_to_fill; row < (1U << n); row += (num_to_fill * 2))
			{
				std::fill_n(&output[col][row], num_to_fill, 1);
			}
		}

		// These loops just print out the results, nothing more.
		for (unsigned x = 0; x < (1 << n); ++x)
		{
			for (unsigned y = 0; y < n; ++y)
			{
				//std::cout << output[y][x] << " ";
			}
			//std::cout << std::endl;
		}

		return output;
	}

	vector<vector<int>> transposeArr(vector<vector<int>> input) {
		vector<vector<int>> output;
		for (size_t i = 0; i < input[0].size(); i++) {
			output.push_back({});
			for (size_t j = 0; j < input.size(); j++) {
				output[i].push_back(0);
			}
		}

		for (unsigned x = 0; x < output.size(); ++x)
		{
			for (unsigned y = 0; y < output[x].size(); ++y)
			{
				output[x][y] = input[y][x];
				//std::cout << output[x][y] << " ";
			}
			//std::cout << std::endl;
		}
		return output;
	}

	vector<vector<int>> generateTruthtableXY(int decimal_places) {
		vector<vector<int>> output = transposeArr(generateTruthtableYX(decimal_places));
		return output;
	}
}

using tommylogic::printVector; using tommylogic::vectorSizeChecker; using tommylogic::printTruthtable;
class LogicGate;

struct ObjectStore {
	vector<LogicGate*> ObjTree;
};

class LogicGate {
protected:
	vector<LogicGate*> TmpObjTree;

	void recurObjFunc(ObjectStore* obj) { //Return a whole list of objects in the hierarchy instead of just the one below
		//cout << "Object Name: " << this->Name << " | ObjList.size() = " << ObjList.size() << endl;
		TmpObjTree.push_back(this);
		obj->ObjTree.push_back(this);
		for (int i = 0; i < ObjList.size(); i++) {
			ObjList[i]->recurObjFunc(obj);
		}
	}

private:
	vector<string> ObjNames;

	pair<int, int> Input = {2,2};
	vector<int> Output;
	
	vector<int> CalculatedInput;	//Put the Output into CalculatedInput because intermiediate gates and the final gate for result also function as gates
	pair<int,int> CalculatedInputPair;
	
	int NumOfInputs = NULL;

	int (LogicGate::* TempFunc) (pair<int, int> inputvalue);

	int YES(pair<int, int> inputvalue) {
		return inputvalue.first;
	}
	int AND(pair<int, int> inputvalue) {
		return (inputvalue.first == 1 && inputvalue.second == 1);
	}
	int OR(pair<int, int> inputvalue) {
		return (inputvalue.first == 1 || inputvalue.second == 1);
	}
	int NOT(pair<int, int> inputvalue) {
		if (inputvalue.first != 0) return 0;
		else return 1;
	}

	

public:
	vector<LogicGate*> ObjList;

	string Name = "";
	string FundamentalGateName = "";

	vector<int> CalculatedOutput;

	int GotCalled = 0;
	int GotTriggered = 0;
	int ObjListSize = 0;

	int TriggerGateNum = NULL;

	LogicGate(string name) {
		Name = name;
	}

	void call() {
		ObjListSize = this->ObjList.size();
		if (ObjList.size() == 0) {
			Trigger();
			return;
		}
		Called();
		
	}

	void clearOutput() {
		this->Output = {};
		for (int i = 0; i < ObjList.size(); i++) {
			ObjList[i]->clearOutput();

			ObjList[i]->Output = {};
		}
	}

	void assignFunctions(int inputgates) {
		TriggerGateNum = inputgates;
		switch (inputgates)
		{
		case 1:
			TempFunc = &LogicGate::YES;
			FundamentalGateName = "YES";
			NumOfInputs = 1;
			break;
		case 2:
			TempFunc = &LogicGate::NOT;
			FundamentalGateName = "NOT";
			NumOfInputs = 1;
			break;
		case 3:
			TempFunc = &LogicGate::AND;
			FundamentalGateName = "AND";
			NumOfInputs = 2;
			break;
		case 4:
			TempFunc = &LogicGate::OR;
			FundamentalGateName = "OR";
			NumOfInputs = 2;
			break;
		default:
			cout << "WARNING: Wrong Function Assigned" << endl;
			TempFunc = &LogicGate::YES;
			FundamentalGateName = "WRONG GATE";
			break;//Nothing...
		}
	}

	void Trigger() { //to calculate using fundamental gates
		GotTriggered++;

		this->Output.push_back((this->*TempFunc)(this->Input));
	}

	void Called() { //to summarize calculations from lower objects
		GotCalled++;
		for (int i = 0; i < ObjList.size(); i++) {
			ObjList[i]->call(); //Recursive calling into the hierarchy

			this->ObjNames.push_back(ObjList[i]->Name);//Get ObjNames down from the hierarchy, put into this-> ObjNames array.

			for (int j = 0; j < this->ObjList[i]->Output.size(); j++) {//Get Fundamental Gates result from their Output down from the hierarchy, put into this-> Output array
				this->Output.push_back(ObjList[i]->Output[j]);
			}
		}

		if (TriggerGateNum != NULL) { //When the intermiediate object is assigned a gate function
			
			for (int i = 0; i < this->Output.size(); i++) {
				CalculatedInput.push_back(this->Output[i]);
			}
			//cout << "Call Calculating, CalculatedInput.size(): " << CalculatedInput.size() << endl;
			if (CalculatedInput.size() == 1) {
				CalculatedInputPair.first = CalculatedInput[0];
				CalculatedInputPair.second = 2;
				this->CalculatedOutput.push_back((this->*TempFunc)(this->CalculatedInputPair));
			}
			if (CalculatedInput.size() >= 2) {
				CalculatedInputPair.first = CalculatedInput[0];
				CalculatedInputPair.second = CalculatedInput[1];
				this->CalculatedOutput.push_back((this->*TempFunc)(this->CalculatedInputPair));
			}
			Output = CalculatedOutput;
		}
		
	}

	void input(int first) { //for NOT and YES gates
		Input.first = first;
		Input.second = 2;
	}
	void input(int first, int second) { //for AND and OR or maybe more in the future for performance purposes
		Input.first = first;
		Input.second = second;
	}
	void input(vector<LogicGate*> objList) { //Complex Object Gate
		ObjList = objList;
		this->ObjListSize = this->ObjList.size();
	}

	void print() {
		cout << Name; if (FundamentalGateName != "") { cout << " (" << FundamentalGateName << ")"; } cout << " // Number of Inputs: " << NumOfInputs << " // Trigger Gate Number: " << TriggerGateNum << endl;
		cout << Name << " Got Called: " << GotCalled << " // Object List Size: " << ObjListSize << endl;
		cout << Name << " Got Triggered: " << GotTriggered << endl;
		if (Input.first == 2) {
			if (CalculatedInputPair.first == 2) {
				cout << "Input: N/A" << endl;
			}
			else if (CalculatedInputPair.second == 2) {
				cout << "Input from Obj: " << CalculatedInputPair.first << endl;
			}
			else {
				cout << "Input from Obj: " << CalculatedInputPair.first << " , " << CalculatedInputPair.second << endl;
			}
		}else if(Input.second == 2) {
			cout << "Input: " << Input.first << endl;
		}else {
			cout << "Input: " << Input.first << " , " << Input.second << endl;
		}
		cout << "Output: ";
		for (int i = 0; i < Output.size(); i++) {
			cout << Output[i] << " ";
		}
		cout << endl;
		cout << "ObjList.size() = " << this->ObjList.size() << " Object Names: " << endl;
		for (int i = 0; i < this->ObjNames.size(); i++) {
			cout << ObjNames[i] << " ";
		}
		cout << endl << "==============" << endl;
	}
};

class UseGate:LogicGate {
private:
	LogicGate* Obj;

	vector<LogicGate*> CurrentObjArr;

public:
	UseGate(LogicGate* ObjGate):LogicGate(*ObjGate) {
		Obj = ObjGate;
		//cout << "ObjGate.ObjListSize = " << ObjGate.ObjListSize << endl;
		
		ObjectStore objtree;
		this->recurObjFunc(&objtree);
		CurrentObjArr = objtree.ObjTree;
	}

	void call() {
		Obj->call();
	}

	void inputAll(vector<int> inputBool) {
		int Counter = 0;
		for (int i = 0; i < CurrentObjArr.size(); i++) {
			if (Counter >= inputBool.size()) {
				cout << "WRONG NUMBER OF INPUT PROVIDED (UseGate:LogicGate void inputAll)" << endl;
				return;
			}
			if (CurrentObjArr[i]->ObjListSize == 0) {
				switch (CurrentObjArr[i]->TriggerGateNum) {
				case 1:
					CurrentObjArr[i]->input(inputBool[Counter]);
					Counter++;
					break;
				case 2:
					CurrentObjArr[i]->input(inputBool[Counter]);
					Counter++;
					break;
				case 3:
					CurrentObjArr[i]->input(inputBool[Counter],inputBool[Counter+1]);
					Counter = Counter + 2;
					break;
				case 4:
					CurrentObjArr[i]->input(inputBool[Counter], inputBool[Counter + 1]);
					Counter = Counter + 2;
					break;
				default:
					cout << "Wrong Gate Number (UseGate:LogicGate void inputAll)" << endl;
					break;
				}
			}
		}
	}

	void printAll() {
		cout << "RESULT: ";
		for (int i = 0; i < Obj->CalculatedOutput.size(); i++) {
			cout << Obj->CalculatedOutput[i] << " | ";
		}cout << endl << "---------------" << endl;
		Obj->print();
		for (int i = 1; i < CurrentObjArr.size(); i++) {
			CurrentObjArr[i]->print();
		}
		cout << "=================================" << endl;
		cout << endl << "INPUT ORDER: " << endl;
		for (int i = 0; i < CurrentObjArr.size(); i++) {
			if (CurrentObjArr[i]->ObjListSize == 0) {
				cout << CurrentObjArr[i]->Name << "(" << CurrentObjArr[i]->FundamentalGateName << "), ";
			}
		}
		cout << endl << "=================================" << endl;
	}

	void clear() {
		Obj->clearOutput();
	}
};