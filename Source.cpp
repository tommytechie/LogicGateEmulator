#include "tommylogic.h"
#include "objectgate.h"

using std::vector; using std::cout; using std::endl; using std::string;
using tommylogic::transposeArr; using tommylogic::generateTruthtable;
/*
TRUTH TABLE

AND----OR----NAND----NOR----XNOR----XOR
00 0   00 0  00 1    00 1   00 1    00 0   
01 0   01 1  01 1    01 0   01 0    01 1
10 0   10 1  10 1    10 0   10 0    10 1
11 1   11 1  11 0    11 0   11 1    11 0

*/

int AND(int A, int B) {
	return (A == 1 && B == 1);
}

int OR(int A, int B) {
	return (A == 1 || B == 1);
}

void foo(vector<vector<int>> input, int i);

int main() {
	vector<vector<int>> input1 = transposeArr(generateTruthtable(1)); //{ { 0 }, { 1 } };
	vector<vector<int>> input2 = transposeArr(generateTruthtable(2)); //{ { 0 , 0 }, { 0 , 1 }, { 1 , 0 }, { 1 , 1 } };
	vector<vector<int>> input3 = transposeArr(generateTruthtable(3));
	vector<vector<int>> input4 = transposeArr(generateTruthtable(4)); //{ { 0, 0, 0, 0 }, { 0 , 0 , 0 , 1 }, { 0 , 0 , 1 , 0 }, { 0 , 0 , 1 , 1 }, { 0 , 1 , 0 , 0 },{ 0 , 1 , 0 , 1 },{ 0 , 1 , 1 , 0 },{ 0 , 1 , 1 , 1 },{ 1 , 0 , 0 , 0 },{ 1 , 0 , 0 , 1 },{ 1 , 0 , 1 , 0 },{ 1 , 0 , 1 , 1 },{ 1 , 1 , 0 , 0 },{ 1 , 1 , 0 , 1 },{ 1 , 1 , 1 , 0 },{ 1 , 1 , 1 , 1} };
	vector<vector<int>> input6 = transposeArr(generateTruthtable(6));

	
	
	for (int i = 0; i < input4.size(); i++) {
		for (int j = 0; j < input4[i].size(); j++) {
			cout << input4[i][j] << " ";
		}
		cout << "| "; foo(input4, i); cout << endl;
	}


}

void foo(vector<vector<int>> input, int i) {
	LogicGate obj3(input[i]);
	obj3.define({ 4,7 });
	obj3.parallelCalc();
	for (int i = 0; i < obj3.output.size(); i++) {
		cout << obj3.output[i] << " ";
	}
	cout << endl;
	obj3.clear();
}

// TODO and also create other objects to represent gates, not functions, i know it's hard for my stupid brain to do so...


/*  
	//class logic1 - 6...
	//Example Driver Code:

	logic6 L6(""); logic4 L4(""); logic3 L3(""); logic2 L2(""); logic1 L1("");

	L2.testInput(input2, logic2("AND")); cout << endl;
	L2.testInput(input2, logic2("OR")); cout << endl;
	L1.testInput(input1, logic1("NOT")); cout << endl;
	L2.testInput(input2, logic2("NAND")); cout << endl;
	L2.testInput(input2, logic2("NOR")); cout << endl;
	L2.testInput(input2, logic2("XNOR")); cout << endl;
	L2.testInput(input2, logic2("XOR")); cout << endl;
	L4.run(input4, logic4("TEST")); cout << endl;

	printTruthtable(4, input4, L4.result);

	cout << "L6: " << endl;
	L6.run(input6, logic6("TEST2"));
	printTruthtable(6, input6, L6.result);
	cout << "=================" << endl;

	///L3.testInput(input3, logic3("TEST1"));
	//L3.run(input3, logic3("TEST1"));
	//printTruthtable(3, input3, L3.result);

*/

/*
	//class ObjGate...
	//Example Driver Code:

	ObjGate AND(1, 0); ObjGate OR(1, 1); ObjGate AND1; ObjGate AND2;
	AND.define(1); OR.define(2); AND1.define(1); AND2.define(1);

	cout << "AND: " << AND.returnValue() << endl;
	cout << "OR: " << OR.returnValue() << endl;

	cout << "==============" << endl;
	AND2.a(AND1.a(&AND, &OR),1);

	cout << "AND1 " << AND1.returnValue() << endl;

	cout << "AND2 " << AND2.returnValue() << endl;
*/

/*
	//class LogicGate...
	//Example Driver Code! Unfinished.

	cout << "====INPUT====" << endl;
	for (int i = 0; i < obj1.input.size(); i++) {
		cout << i << ". " << obj1.input[i] << endl;
	}

	cout << "====POS====" << endl;
	for (int i = 0; i < obj1.position.size(); i++) {
		cout << obj1.position[i] << endl;
	}

	//for (int i = 0; i < obj2.position.size(); i++) {
	//	cout << obj2.position[i] << endl;
	//}

	cout << "====OUTPUT====" << endl;
	obj1.parallelCalc();

	for (int i = 0; i < obj1.output.size(); i++) {
		cout << obj1.output[i] << endl;
	}
*/