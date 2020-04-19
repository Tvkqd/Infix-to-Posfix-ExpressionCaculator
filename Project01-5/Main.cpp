#include<iostream>
#include<string>
#include<stack>
using namespace std;

//Pop operator from the stack, add it to the posfix string
void pop_operator(stack<char>& oper, string& tp) {
	tp += " ";
	tp += oper.top();
	oper.pop();
}

//Convert infix into posfix
string infix_to_posfix(string input) {
	stack<char> pos;
	//Prevent the error for .top() empty stack
	pos.push('e');
	string temp = "";
	temp += input[0];
	int changeCheck = 0;

	for (int i = 1; i < input.length(); i++) {
		//Add digits to a the string
		if (isdigit(input[i])) {
			//Handle digits greater then 9
			if (isdigit(input[i - 1])) {
				temp += input[i];
				continue;
			}
			temp += " ";
			temp += input[i];
			//Pop * and / first
			if (pos.top() == '*' || pos.top() == '/') {
				pop_operator(pos, temp);
				if (pos.top() == '-')
					changeCheck--;
			}

		}
		//Pop all operators inside the ()
		else if (input[i] == ')') {
			while (pos.top() != '(') 
				pop_operator(pos, temp);
			//Pop the character (
			pos.pop();
			//Check for * and / 
			if (pos.top() == '*' || pos.top() == '/')
				pop_operator(pos, temp);
		}
		else {
			int before_change;
			//Do not change if there is ()
			if (pos.top() == '(') {
				before_change = changeCheck;
				changeCheck = 0;
			}
			else if (pos.top() == ')')
				changeCheck = before_change;
			else if (pos.top() == '-') 
				changeCheck++;
			//Change (+ to -) or (- to +) if there is - in front of it
			if (changeCheck%2 != 0){
				if (input[i] == '+') {
					input[i] = '-';
				}
				else if (input[i] == '-') {
					input[i] = '+';
				}
			}
			pos.push(input[i]);
		}
		
	}
	//Pop the remaining operators
	while (pos.top() != 'e') 
		pop_operator(pos, temp);
	
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
		cout << "Enter the infix arithmetic expression (no spaces): ";
		getline(cin, input);

		//Convert infix to posfix
		input = infix_to_posfix(input);
		//cout << "Postfix form: " << input << endl;
		//Calculate 
		result = pos_calculator(input);
		cout << "Result: " << result << endl;

		//Continue calculate another expression
		cout << "Do you want to calculate another one?(y/n) ";
		cin >> play;
		cout << endl;
		cin.ignore();
	}

	system("pause");
	return 0;
}