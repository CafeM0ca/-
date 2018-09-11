#include <iostream>
#include <array>
#include <stack>
#include <string>
#include <algorithm>
using namespace std;

class Expression {
public:
	Expression() { }
	Expression(string& expr) {
		this->expr = expr;
	}
	Expression(const char *expr) {
		this->expr = *expr;
	}
	~Expression() { }

	inline void reset() { expr.clear(); }
	void operator=(string& expr) {
		this->expr = expr;
	}
	void operator=(const char *expr) {
		this->expr = *expr;
	}
	auto check_prefix(const char& pf){
		switch (pf) {
		case '+':
			return '+'; 
		case '-':
			return '-';
		case '*':
			return '*';
		case '/':
			return '/';
		default:
			return '\0';
		}
	}

	string expr;
};

// Calculator has Expression
class Calculator : public Expression {
public:
	Calculator() { 
		cout << "--------------------------------" << endl;
		cout << "|Operate Tanguang Calculator!!!|" << endl;
		cout << "--------------------------------" << endl;
	}
	~Calculator() { 
		cout << "------------------------" << endl;
		cout << "|Shutdown Calculator!!!|" << endl;
		cout << "------------------------" << endl;
	}
		
	// add expr
	// undo expr
	// is_image_num?
	// is_real_num?
	template <typename T>
	void show_stack(stack<T> s, string msg) {
		cout << "copyed stack , msg:  " << msg << endl;
		while (!s.empty()) {
			cout << "stack size: " << s.size() << ", top: " << s.top() << endl;
			s.pop();
		}
	}

	bool check_minus(string& value) {
		if (value.empty()) 
			cerr << "sign_check fail. no value" << endl;
		if (value[0] == '-') return true;
		else				 return false;
	}
	void calculate() {
		cout << "Start calculate" << endl;
		parsing(expr);
		// 남은 더하기 빼기
		while (!num.empty()) {
			if (num.size() == 1) {
				solution = stoi(num.top());
				num.pop();
				break;
			}
			try{
				show_stack(num, "rvalue stack");
				const string rvalue = num.top();
				num.pop();
				show_stack(num, "lvalue stack");
				const string lvalue = num.top();
				num.pop();
				show_stack(sign, "sign stack");
				if (sign.top() == '+') {					// rvalue sign
					sign.pop();
					// 정수인지 실수인지 구분해주는 함수 필요
					cout << "lvalue: " << lvalue << ", rvalue: " << rvalue << endl;
					const auto sum = [this, &lvalue, &rvalue]()->auto{
						if (sign.empty() || sign.top() == '+' )
							return stoi(lvalue) - stoi(rvalue);
						else {
							sign.push('-');
							return stoi(lvalue) - stoi(rvalue);
						}
					}();
					cout << "sum : " << sum << endl;
					num.push(to_string(sum));
				}
				else if (sign.top() == '-') {				// lvalue sign
					sign.pop();
					// 정수인지 실수인지 구분해주는 함수 필요
					cout << "lvalue: " << lvalue << ", rvalue: " << rvalue << endl;
					const auto sum = [this, &lvalue, &rvalue]()->auto{
						if (sign.empty() || sign.top() == '+' )
							return stoi(lvalue) - stoi(rvalue);
						else {
							sign.push('-');
							return stoi(lvalue) - stoi(rvalue);
						}
					}();
					cout << "sum : " << sum << endl;
					num.push(to_string(sum));
				}
				else {
					cerr << "token not found" << endl;
				}
			}
			catch (exception& e) {
				cerr << "calculate error message: " << e.what() << endl;
			}
		}
		cout << "Finish calculate" << endl;
		cout << "solution : " << solution << endl;
	}
	auto result() const {
		return solution;
	}
	
	string get_value(string& expr) {
		string value;
		if (!expr.empty()) {
			auto expr_iter = expr.begin(); 
			for (;expr_iter != expr.end(); expr_iter++) {
				if (*expr_iter == '+' || *expr_iter == '-' || *expr_iter == '*' || *expr_iter == '/') {
					expr.erase(expr.begin(), expr_iter);												// 토큰은 처리안함
					break;
				}
				else {
					value.push_back(*expr_iter);
				}
			}
			if (expr_iter == expr.end()) expr.clear();
			cout << "value : " << value << endl;
			return value;
		}
		else {
			cerr << "no value" << endl;
		}
	}
	
	void find_token(string& expr) {
		while(!expr.empty()){
			switch (expr.at(0)) {
			case '+':
				sign.push('+');
				expr.erase(expr.begin(), expr.begin()+1);
				break;
			case '-':
				sign.push('-');
				expr.erase(expr.begin(), expr.begin()+1);
				break;
			case '*':
				expr.erase(expr.begin(), expr.begin()+1);
				try {
					string rvalue = get_value(expr);
					string lvalue = num.top();
					// 정수라고 가정
					num.pop();
					num.push(to_string(stoi(rvalue) * stoi(lvalue)));
				}
				catch (exception& e) {
					cerr << "multiple error message: " << e.what() << endl;
				}
				break;
			case '/':
				expr.erase(expr.begin(), expr.begin()+1);
				try {
					string rvalue = get_value(expr);
					string lvalue = num.top();
					// 정수라고 가정
					num.pop();
					num.push(to_string(stoi(rvalue) / stoi(lvalue)));
				}
				catch (exception& e) {
					cerr << "multiple error message: " << e.what() << endl;
				}
				break;
			default:
				cout << "남은 표현식: " << expr << endl;
				num.push(get_value(expr));
			}
		}
	}
	void parsing(string& expr) {
		string::iterator bracket_begin = find(expr.begin(), expr.end(), '(');
		if (bracket_begin != expr.end()) {					// 괄호가 있을 때
			string::iterator bracket_end = find(bracket_begin, expr.end(), ')');
			if(bracket_end == expr.end()){
				cerr << "올바르지 않은 식입니다." << endl;
				//exit(1);
			}
			string sub_expr(bracket_begin + 1, bracket_end - 1);
			parsing(sub_expr);
			expr.replace(bracket_begin, bracket_end, sub_expr);		// (something)을 값으로 치환
			while (!num.empty())									// 괄호안에서 사용한 스택 제거
				num.pop();
		} 
		else {
			find_token(expr);
		}
	}

	private:
	// result
	int solution = 0;
	stack<string> num;
	stack<char> sign;
};

int main()
{
	Calculator calculator;
	calculator.expr = "1+2-3-10";
;
	calculator.calculate();
	return 0;
}