#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include "LogicGateCore.h"

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

	void loopInputUseGate(UseGate obj, vector<vector<int>> input) {
		for (int i = 0; i < input.size(); i++) {
			cout << "Input: ";
			for (int j = 0; j < input[i].size(); j++) {
				cout << input[i][j] << " , ";
			}cout << endl;
			obj.inputAll(input[i]);
			obj.call();
			obj.printResult();
			cout << endl << "===============" << endl;
		}
	}
	void loopInputUseGate(UseGate obj, vector<vector<int>> input, vector<LogicGate*> OtherGatesResults) {
		for (int i = 0; i < input.size(); i++) {
			obj.inputAll(input[i]);
			obj.call();
			cout << "Input: ";
			for (int j = 0; j < input[i].size(); j++) {
				cout << input[i][j] << " , ";
			}cout << endl;
			cout << "(" << obj.getName() << ") ";
			obj.printResult();
			cout << endl << "---------other gate's results--------" << endl;
			for (int j = 0; j < OtherGatesResults.size(); j++) {
				cout << OtherGatesResults[j]->Name << ": ";
				for (int k = 0; k < OtherGatesResults[j]->CalculatedOutput.size(); k++) {
					cout << OtherGatesResults[j]->CalculatedOutput[k] << " | ";
				}
				cout << endl;
			}
			cout << endl << "===============" << endl;
		}
	}
}


