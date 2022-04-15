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

class LogicGate {
private:

	vector<LogicGate*> ObjList;
	vector<string> ObjNames;

	pair<int, int> Input;
	vector<int> Output;

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
	string Name = "";

	int GotCalled = 0;
	int GotTriggered = 0;
	int ObjListSize = 0;

	LogicGate(string name) {
		Name = name;
	}

	void call() {
		if (ObjList.size() == 0) {
			Trigger();
			return;
		}
		Called();
	}

	void assignFunctions(int inputgates) {
		switch (inputgates)
		{
		case 0:
			TempFunc = &LogicGate::YES;
			break;
		case 1:
			TempFunc = &LogicGate::NOT;
			break;
		case 2:
			TempFunc = &LogicGate::AND;
			break;
		case 3:
			TempFunc = &LogicGate::OR;
			break;
		default:
			cout << "WARNING: Wrong Function Assigned" << endl;
			TempFunc = &LogicGate::YES;
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
	}

	void input(int first) { //for NOT and YES gates
		Input.first = first;
		Input.second = 2;
	}
	void input(int first, int second) { //other gates
		Input.first = first;
		Input.second = second;
	}
	void input(vector<LogicGate*> objList) { //Complex Object Gate
		ObjList = objList;
	}

	void print() {
		cout << Name << " Got Called: " << GotCalled << endl;
		cout << Name << " Got Triggered: " << GotTriggered << endl;
		cout << "Output: ";
		for (int i = 0; i < Output.size(); i++) {
			cout << Output[i] << " ";
		}
		cout << endl;
		cout << "Object Names: ";
		for (int i = 0; i < this->ObjList.size(); i++) {
			cout << ObjNames[i] << " ";
		}
		cout << endl << "==============" << endl;
	}
};