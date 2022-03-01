#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

using std::vector; using std::cout; using std::endl; using std::string;

namespace tommylogic {
	bool vectorSizeChecker(int InputSize, vector<vector<int>> InputVector) { //Check V[i][?], the size of the row to see if it matches InputSize
		for (int i = 0; i < InputVector.size(); i++) {
			if (InputVector[i].size() != InputSize)return false;
		}
		return true;
	}

	template <typename T>
	void printVector(vector<T> input) {
		for (int i = 0; i < input.size(); i++) cout << input[i] << endl;
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
}

using tommylogic::printVector; using tommylogic::vectorSizeChecker; using tommylogic::printTruthtable;

class logic1 {
	vector<int> testresult;
public:
	vector<int> result;

	string GN;
	vector<string> GateNameArr = { "NOT" };
	logic1(string GateName) {
		GN = GateName;
		vector<string>::iterator it = std::find(GateNameArr.begin(), GateNameArr.end(), GN);
		if (it != GateNameArr.end()) {
			//gate found
		}
		else {
			//gate not found
			GN = "error";
		}
	}
	int operator()(int A) {
		if (GN == "NOT")return NOT(A);
		else { return 0; }
	}
	template <class _Fn>
	void testInput(vector<vector<int>> inputArr, _Fn _Func) {
		if (vectorSizeChecker(1, inputArr) == false) { cout << "Input Array has wrong size(s) in logic1 run" << endl; return; };
		if (_Func.GN != "error") { cout << "Truth Table for " << _Func.GN << " gate:" << endl; }
		else { cout << "WRONG GATE NAME" << endl; return; }

		for (int i = 0; i < inputArr.size(); i++) {
			cout << inputArr[i][0] << " => " << _Func(inputArr[i][0]) << endl;
		}
	}
	template <class _Fn>
	void run(vector<vector<int>> inputArr, _Fn _Func) {
		if (vectorSizeChecker(1, inputArr) == false) { cout << "Input Array has wrong size(s) in logic1 run" << endl; return; };
		if (_Func.GN != "error") { /*run without error*/ }
		else { cout << "_WRONG GATE NAME_" << endl; return; }

		for (int i = 0; i < inputArr.size(); i++) {
			result.push_back(_Func(inputArr[i][0]));
		}
	}


	int NOT(int A) {
		if (A == 1)return 0;
		else return 1;
	}
};

class logic2 : public logic1 {
	vector<int> testresult;
public:
	vector<int> result;

	string GN;
	vector<string> GateNameArr = { "AND", "OR", "NAND", "NOR", "XNOR", "XOR" };
	logic2(string GateName) : logic1(GateName) {
		GN = GateName;
		vector<string>::iterator it = std::find(GateNameArr.begin(), GateNameArr.end(), GN);
		if (it != GateNameArr.end()) {
			//gate found
		}
		else {
			//gate not found
			GN = "error";
		}
	}
	int operator()(int A, int B) {
		if (GN == "AND")return AND(A, B);
		else if (GN == "OR")return OR(A, B);
		else if (GN == "NOT")return NOT(A);
		else if (GN == "NAND")return NAND(A, B);
		else if (GN == "NOR")return NOR(A, B);
		else if (GN == "XNOR")return XNOR(A, B);
		else if (GN == "XOR")return XOR(A, B);
		else { return 0; }
	}
	template <class _Fn>
	void testInput(vector<vector<int>> inputArr, _Fn _Func) {
		if (vectorSizeChecker(2, inputArr) == false) { cout << "Input Array has wrong size(s) in logic2 testInput" << endl; return; };
		if (_Func.GN != "error") { cout << "Truth Table for " << _Func.GN << " gate:" << endl; }
		else { cout << "WRONG GATE NAME" << endl; return; }

		for (int i = 0; i < inputArr.size(); i++) {
			cout << inputArr[i][0] << " " << inputArr[i][1] << " => " << _Func(inputArr[i][0], inputArr[i][1]) << endl;
		}
	}
	template <class _Fn>
	void run(vector<vector<int>> inputArr, _Fn _Func) {
		if (vectorSizeChecker(2, inputArr) == false) { cout << "Input Array has wrong size(s) in logic2 run" << endl; return; };
		if (_Func.GN != "error") { /*run without error*/ }
		else { cout << "_WRONG GATE NAME_" << endl; return; }

		for (int i = 0; i < inputArr.size(); i++) {
			result.push_back(_Func(inputArr[i][0], inputArr[i][1]));
		}
	}

	int AND(int A, int B) {
		if (A == 1 && B == 1)return 1;
		else return 0;
	}
	int OR(int A, int B) {
		if (A == 1 || B == 1)return 1;
		else return 0;
	}
	int NAND(int A, int B) {
		return NOT(AND(A, B));
	}
	int NOR(int A, int B) {
		return NOT(OR(A, B));
	}
	int XNOR(int A, int B) {
		if (AND(A, B) == 1 || NOR(A, B) == 1)return 1;
		else return 0;
	}
	int XOR(int A, int B) {
		if (OR(A, B) == 1 && NAND(A, B) == 1)return 1;
		else return 0;
	}
};

class logic3 : public logic2 {
	vector<int> testresult;
public:
	vector<int> result;

	string GN;
	vector<string> GateNameArr = { "TEST1" };
	logic3(string GateName) : logic2(GateName) {
		GN = GateName;
		vector<string>::iterator it = std::find(GateNameArr.begin(), GateNameArr.end(), GN);
		if (it != GateNameArr.end()) {
			//gate found
		}
		else {
			//gate not found
			GN = "error";
		}
	}
	int operator()(int A, int B, int C) {
		if (GN == "TEST1")return TEST1(A, B, C);
		else { return 0; }
	}

	//Template Functions with a Functor as Parameter
	template <class _Fn>
	void testInput(vector<vector<int>> inputArr, _Fn _Func) {
		if (vectorSizeChecker(3, inputArr) == false) { cout << "Input Array has wrong size(s) in logic3 testInput" << endl; return; };
		testresult.clear(); //testInput will destroy the data in testresult
		if (_Func.GN != "error") { cout << "Truth Table for " << _Func.GN << " gate:" << endl; }
		else { cout << "WRONG GATE NAME" << endl; return; }

		for (int i = 0; i < inputArr.size(); i++) {
			testresult.push_back(_Func(inputArr[i][0], inputArr[i][1], inputArr[i][2]));
			cout << inputArr[i][0] << " " << inputArr[i][1] << " " << inputArr[i][2] << " => " << testresult[i] << endl;
		}
	}
	template <class _Fn>
	void run(vector<vector<int>> inputArr, _Fn _Func) {
		if (vectorSizeChecker(3, inputArr) == false) { cout << "Input Array has wrong size(s) in logic3 run" << endl; return; };
		if (_Func.GN != "error") { /*run without error*/ }
		else { cout << "_WRONG GATE NAME_" << endl; return; }

		for (int i = 0; i < inputArr.size(); i++) {
			result.push_back(_Func(inputArr[i][0], inputArr[i][1], inputArr[i][2]));
		}
	}

	int TEST1(int A, int B, int C) {
		return OR(AND(OR(NOT(A),B),NOR(B,AND(A,NOT(C)))),AND(A,NAND(B, C)));
	}
};

class logic4 : public logic3 {
	vector<int> testresult;
public:
	vector<int> result;

	string GN;
	vector<string> GateNameArr = { "TEST" };
	logic4(string GateName) : logic3(GateName) {
		GN = GateName;
		vector<string>::iterator it = std::find(GateNameArr.begin(), GateNameArr.end(), GN);
		if (it != GateNameArr.end()) {
			//gate found
		}
		else {
			//gate not found
			GN = "error";
		}
	}
	int operator()(int A, int B, int C, int D) {
		if (GN == "TEST")return TEST(A, B, C, D);
		else { return 0; }
	}

	//Template Functions with a Functor as Parameter
	template <class _Fn>
	void testInput(vector<vector<int>> inputArr, _Fn _Func) {
		if (vectorSizeChecker(4, inputArr) == false) { cout << "Input Array has wrong size(s) in logic4 testInput" << endl; return; };
		testresult.clear(); //testInput will destroy the data in testresult
		if (_Func.GN != "error") { cout << "Truth Table for " << _Func.GN << " gate:" << endl; }
		else { cout << "WRONG GATE NAME" << endl; return; }

		for (int i = 0; i < inputArr.size(); i++) {
			testresult.push_back(_Func(inputArr[i][0], inputArr[i][1], inputArr[i][2], inputArr[i][3]));
			cout << inputArr[i][0] << " " << inputArr[i][1] << " " << inputArr[i][2] << " " << inputArr[i][3] << " => " << testresult[i] << endl;
		}
	}
	template <class _Fn>
	void run(vector<vector<int>> inputArr, _Fn _Func) {
		if (vectorSizeChecker(4, inputArr) == false) { cout << "Input Array has wrong size(s) in logic4 run" << endl; return; };
		if (_Func.GN != "error") { /*run without error*/ }
		else { cout << "_WRONG GATE NAME_" << endl; return; }

		for (int i = 0; i < inputArr.size(); i++) {
			result.push_back(_Func(inputArr[i][0], inputArr[i][1], inputArr[i][2], inputArr[i][3]));
		}
	}

	int TEST(int A, int B, int C, int D) {
		return NOT(XOR(AND(A, B), OR(C, D)));
	}
};

class logic6 : public logic4 {
	vector<int> testresult;
public:
	vector<int> result;

	string GN;
	vector<string> GateNameArr = { "TEST1","TEST2" };
	logic6(string GateName) : logic4(GateName) {
		GN = GateName;
		vector<string>::iterator it = std::find(GateNameArr.begin(), GateNameArr.end(), GN);
		if (it != GateNameArr.end()) {
			//gate found
		}
		else {
			//gate not found
			GN = "error";
		}
	}
	int operator()(int A, int B, int C, int D, int E, int F) {
		if (GN == "TEST1")return TEST1(A, B, C, D);
		if (GN == "TEST2")return TEST2(A, B, C, D, E, F);
		else { return 0; }
	}

	//Template Functions with a Functor as Parameter
	template <class _Fn>
	void testInput(vector<vector<int>> inputArr, _Fn _Func) {
		if (vectorSizeChecker(6, inputArr) == false) { cout << "Input Array has wrong size(s) in logic6 testInput" << endl; return; };
		testresult.clear(); //testInput will destroy the data in testresult
		if (_Func.GN != "error") { cout << "Truth Table for " << _Func.GN << " gate:" << endl; }
		else { cout << "WRONG GATE NAME" << endl; return; }

		for (int i = 0; i < inputArr.size(); i++) {
			testresult.push_back(_Func(inputArr[i][0], inputArr[i][1], inputArr[i][2], inputArr[i][3], inputArr[i][4], inputArr[i][5]));
			cout << inputArr[i][0] << " " << inputArr[i][1] << " " << inputArr[i][2] << " " << inputArr[i][3] << " " << inputArr[i][4] << " " << inputArr[i][5] << " => " << testresult[i] << endl;
		}
	}
	template <class _Fn>
	void run(vector<vector<int>> inputArr, _Fn _Func) {
		if (vectorSizeChecker(6, inputArr) == false) { cout << "Input Array has wrong size(s) in logic6 run" << endl; return; };
		if (_Func.GN != "error") { /*run without error*/ }
		else { cout << "_WRONG GATE NAME_" << endl; return; }

		for (int i = 0; i < inputArr.size(); i++) {
			result.push_back(_Func(inputArr[i][0], inputArr[i][1], inputArr[i][2], inputArr[i][3], inputArr[i][4], inputArr[i][5]));
		}
	}

	int TEST1(int A, int B, int C, int D) {
		return NOT(XOR(AND(A, B), OR(C, D)));
	}

	int TEST2(int A, int B, int C, int D, int E, int F) {
		return NOT(XOR(AND(A, B), OR(C, D)));
	}


};