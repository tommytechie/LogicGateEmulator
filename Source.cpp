#include "tommylogic.h"

using std::vector; using std::cout; using std::endl; using std::string;
/*
TRUTH TABLE

AND----OR----NAND----NOR----XNOR----XOR
00 0   00 0  00 1    00 1   00 1    00 0   
01 0   01 1  01 1    01 0   01 0    01 1
10 0   10 1  10 1    10 0   10 0    10 1
11 1   11 1  11 0    11 0   11 1    11 0

*/
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

vector<vector<int>> generateTruthtable(int n) {
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

int main() {
	vector<vector<int>> input1 = transposeArr(generateTruthtable(1)); //{ { 0 }, { 1 } };
	vector<vector<int>> input2 = transposeArr(generateTruthtable(2)); //{ { 0 , 0 }, { 0 , 1 }, { 1 , 0 }, { 1 , 1 } };
	vector<vector<int>> input3 = transposeArr(generateTruthtable(3));
	vector<vector<int>> input4 = transposeArr(generateTruthtable(4)); //{ { 0, 0, 0, 0 }, { 0 , 0 , 0 , 1 }, { 0 , 0 , 1 , 0 }, { 0 , 0 , 1 , 1 }, { 0 , 1 , 0 , 0 },{ 0 , 1 , 0 , 1 },{ 0 , 1 , 1 , 0 },{ 0 , 1 , 1 , 1 },{ 1 , 0 , 0 , 0 },{ 1 , 0 , 0 , 1 },{ 1 , 0 , 1 , 0 },{ 1 , 0 , 1 , 1 },{ 1 , 1 , 0 , 0 },{ 1 , 1 , 0 , 1 },{ 1 , 1 , 1 , 0 },{ 1 , 1 , 1 , 1} };
	vector<vector<int>> input6 = transposeArr(generateTruthtable(6));

	logic6 L6(""); logic4 L4(""); logic3 L3(""); logic2 L2(""); logic1 L1("");
	
	L3.run(input3, logic3("TEST1"));
	printTruthtable(3, input3, L3.result);

}

/*  //Example Driver Code:
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
*/
