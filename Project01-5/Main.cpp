#include<iostream>
#include<string>
#include<stack>
using namespace std;

//Convert infix into posfix
string infix_to_posfix(string input) {
	stack<char> pos;
	string temp;

	for (int i = 0; i < input.length(); i++) {
		//Add digits to a the string
		if (isdigit(input[i])) {
			temp += input[i];
			//Pop * and / first
			if (pos.top() == '*' || pos.top() == '/') {
				temp += pos.top();
				pos.pop();
			}
		}
		else if (input[i] == ')') {
			while (pos.top() != '(') {
				temp += pos.top();
				pos.pop();
			}
			//Pop the character (
			pos.pop();
		}
		else
			pos.push(input[i]);
	}
	//Pop the remaining operators
	while (pos.top()) {
		temp += pos.top();
		pos.pop();
	}

	return temp;
}

//Perform calculation on the posfix expression
double pos_calculator(string str) {
	double result;
	int num;
	string temp = "";
	stack<double> st;

	for (int i = 0; i < str.size(); i++) {
		//Read digits into a stack
		if (isdigit(str[i]))
			temp += str[i];
		else if (str[i] == ' ' && temp.size() != 0) {
			st.push(stoi(temp));
			temp = "";
		}
		//Perform arithmetic
		else if (str[i] != ' ') {
			num = st.top();
			st.pop();
			result = st.top();
			st.pop();
			switch (str[i]) {
			case '+':
				result += num;
				break;
			case '-':
				result -= num;
				break;
			case '*':
				result *= num;
				break;
			case '/':
				result /= static_cast<double>(num);
				break;
			}
			//Push result back into stack 
			st.push(result);
		}
	}
	result = st.top();
	return result;
}

int main() {
	string input;
	double result;
	char play = 'y';

	while (play == 'y') {
		cout << "Enter the infix arithmetic expression (no spaces)" << endl;
		cin.ignore();
		getline(cin, input);

		//Convert infix to posfix
		input = infix_to_posfix(input);
		cout << input << endl;
		//Calculate 
		result = pos_calculator(input);
		cout << "Result: " << result << endl;

		//Continue calculate another expression
		cout << "Do you want to calculate another one?(y/n) ";
		cin >> play;
		cout << endl;
	}

	system("pause");
	return 0;
}