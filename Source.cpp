#include "tommylogic.h"

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

int main() {

	LogicGate obj11("obj11"), obj12("obj12"), obj13("obj13"), obj14("obj14"), obj15("obj15"), obj16("obj16"), obj17("obj17"), obj18("obj18");
	LogicGate obj21("obj21"), obj22("obj22"), obj23("obj23"), obj24("obj24");
	LogicGate obj31("obj31"), obj32("obj32");
	LogicGate obj41("obj41");

	obj11.assignFunctions(1);
	obj12.assignFunctions(2);
	obj13.assignFunctions(3);
	obj14.assignFunctions(4);
	obj15.assignFunctions(1);
	obj16.assignFunctions(2);
	obj17.assignFunctions(3);
	obj18.assignFunctions(4);

	obj11.input(0);
	obj12.input(1);
	obj13.input(1, 0);
	obj14.input(0, 0);
	obj15.input(1);
	obj16.input(0);
	obj17.input(1, 1);
	obj18.input(0, 1);

	obj21.input({ &obj11,&obj12 });
	obj22.input({ &obj13,&obj14 });
	obj23.input({ &obj15,&obj16 });
	obj24.input({ &obj17,&obj18 });

	obj31.input({ &obj21,&obj22 });
	obj32.input({ &obj23,&obj24 });

	obj41.input({ &obj31,&obj32 });

	obj41.call();

	obj41.print();

	obj31.print();
	obj32.print();

	obj21.print();
	obj22.print();
	obj23.print();
	obj24.print();

	obj11.print();
	obj12.print();
	obj13.print();
	obj14.print();
	obj15.print();
	obj16.print();
	obj17.print();
	obj18.print();

	cout << "=================================" << endl;
	cout << "=================================" << endl;
	cout << "=================================" << endl;

	obj41.clearOutput();

	obj11.input(1);
	obj12.input(0);
	obj13.input(1, 1);
	obj14.input(1, 0);
	obj15.input(0);
	obj16.input(1);
	obj17.input(0, 1);
	obj18.input(0, 0);

	obj21.input({ &obj11,&obj12 });
	obj22.input({ &obj13,&obj14 });
	obj23.input({ &obj15,&obj16 });
	obj24.input({ &obj17,&obj18 });

	obj31.input({ &obj21,&obj22 });
	obj32.input({ &obj23,&obj24 });

	obj41.input({ &obj31,&obj32,&obj11 });

	obj41.call();

	obj41.print();

	obj31.print();
	obj32.print();

	obj21.print();
	obj22.print();
	obj23.print();
	obj24.print();

	obj11.print();
	obj12.print();
	obj13.print();
	obj14.print();
	obj15.print();
	obj16.print();
	obj17.print();
	obj18.print();

	cout << "=================================" << endl;
	cout << "=================================" << endl;
	cout << "=================================" << endl;

	LogicGate obj1("obj1"), obj2("obj2"), obj3("obj3"), obj4("obj4"), obj5("obj5"), obj6("obj6"), obj7("obj7"), obj8("obj8"), obj9("obj9"), obj10("obj10");

	obj1.assignFunctions(3);//AND
	obj2.assignFunctions(2);//NOT
	
	obj3.assignFunctions(4);//OR
	obj4.assignFunctions(2);//NOT

	obj5.assignFunctions(3);//AND

	obj6.assignFunctions(4);//OR
	obj7.assignFunctions(1);//YES

	obj10.assignFunctions(1);//YES

	obj8.assignFunctions(3);//AND

	obj9.assignFunctions(3);//AND

	
	obj2.input({ &obj1 });
	
	obj4.input({ &obj3 });

	obj5.input({ &obj2, &obj4 });
	
	obj7.input({ &obj6 });

	obj8.input({ &obj7, &obj10 });

	obj9.input({ &obj5, &obj8 });

	obj1.input(0, 1);
	obj3.input(0, 0);
	obj6.input(0, 1);
	obj10.input(0);

	obj9.call();
	//obj9.clearOutput();

	obj1.print();
	obj2.print();
	obj3.print();
	obj4.print();
	obj5.print();
	obj6.print();
	obj7.print();
	obj8.print();
	obj9.print();
	obj10.print();

	cout << "=================================" << endl;
	cout << "=================================" << endl;
	cout << "=================================" << endl;

	UseGate gate1(obj9);
	//gate1.printAll();

	gate1.inputAll({ 0,1,0,0,0,1,0 });

	gate1.call();

	gate1.printAll();
}