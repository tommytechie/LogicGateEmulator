#include "tommylogic.h"
#include "objectgate.h"

using std::vector; using std::cout; using std::endl; using std::string;
using tommylogic::generateTruthtableXY;
/*
TRUTH TABLE

AND----OR----NAND----NOR----XNOR----XOR
00 0   00 0  00 1    00 1   00 1    00 0   
01 0   01 1  01 1    01 0   01 0    01 1
10 0   10 1  10 1    10 0   10 0    10 1
11 1   11 1  11 0    11 0   11 1    11 0

*/

void gateLoop(LogicGate inputGate, int NumOfInputs, int i);

int main() {
	
	RecurObjTest obj11("obj11"), obj12("obj12"), obj13("obj13"), obj14("obj14");
	RecurObjTest obj21("obj21"), obj22("obj22");
	RecurObjTest obj31("obj31");

	obj21.input({ &obj11,&obj12 });
	obj22.input({ &obj13,&obj14 });

	obj31.input({ &obj21,&obj22 });

	obj31.calling();

	obj31.print();
	obj21.print();
	obj22.print();
	obj11.print();
	obj12.print();
	obj13.print();
	obj14.print();

}

void gateLoop(LogicGate inputGate, int NumOfInputs, int iterations) {
	//0 Yes, 1 And, 2 Or, 3 Not, 4 Nand, 5 Nor, 6 Xnor, 7 Xor
	vector<vector<int>> TheTruthTable = generateTruthtableXY(NumOfInputs);
	for (int i = 0; i < iterations; i++) {
		srand(time(0) * i);
		int Rand = rand() % (int)pow(2, NumOfInputs);
		cout << "Gate Name: " << inputGate.name << " | " << "Rand: " << Rand << endl;
		vector<int> inputarr = TheTruthTable[Rand];
		cout << "input arr: "; printVector<int>(inputarr); cout << endl;
		inputGate.inputValues(inputarr); //TODO Figure out assigning values to internal objects
		if (inputGate.ObjectTypeIdentifier == 1)inputGate.parallelCalc();
		else if (inputGate.ObjectTypeIdentifier == 2)inputGate.Calc(); //TODO calculate them and Figure out passing out internal objects' outputs correctly
		else cout << "Complex Gates coming soon..." << endl;
		inputGate.printValue();
		cout << endl;
	}
}

//TODO find out how many inputs the obj inputs and how many outputs the obj outputs and then process it inside the big object and then output accordingly...
//TODO Map the Outputs of the Object Gates to the Input of the Bigger Gate itself (current Object)
//TODO Figure out how many Inputs should itself take, for it to be used for other bigger gates in the future.
//TODO Map the future Inputs into the smaller inside object gates...

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

/*

LogicGate obj1; LogicGate obj2; LogicGate obj3; LogicGate multi1; LogicGate multi2; LogicGate Complex1;

	//obj1.inputValues({ 1,1,1,0 });

	obj1.define({ 1,2,3 }); obj1.setName("AND,OR,NOT");
	obj2.define({ 2,1,3 }); obj2.setName("OR,AND,NOT");
	obj3.define({ 1,1 }); obj3.setName("AND,AND");

	multi1.define({ obj1, obj2, obj3 }); multi1.setName("multi-1");
	multi2.define({ obj3, obj2, obj1 }); multi2.setName("multi-2");

	Complex1.define({ multi1,multi2 }); Complex1.setName("Complex-1");

	gateLoop(obj1, 5, 10);
	gateLoop(multi1, 14, 5);
	gateLoop(multi2, 14, 5);
	//gateLoop(Complex1, 28, 10);


	cout << "NumOfInputs: " << multi1.NumOfInputs << endl;
	cout << "NumOfOutputs: " << multi1.NumOfOutputs << endl;

*/