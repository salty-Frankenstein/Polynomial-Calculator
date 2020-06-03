#include"ui.h"
#include<iostream>
#include<cstdlib>
using namespace std;

UI::UI(){
	state = MENU;
}

void UI::Run(){
	while(state != EXIT){
		switch(state){
		case MENU:
			ShowUI();
			cout << "请选择：";
			GetCommand();
			break;
		case INPUT:
			GetInput();
			break;
		case SHOW:
			ShowPoly();
			break;
		case CALCULATE:
			Calculate();
			break;
		case INVERSE:
			Inverse();
			break;
		case DIVIDE:
			Divide();
			break;
		case ROOT:
			Root();
			break;
		defalt:break;
		}
	}
	system("clear");
}

void UI::ShowUI(){
	system("clear");
	cout << "================多项式计算器===============" << endl;
	cout << "1.输入 2.混合运算 3.求逆 4.除法、取模运算 5.求根 6.查看 7.退出" << endl;
	cout << "===========================================" << endl;
}

void UI::GetCommand(){
	char c;
	cin >> c;
	switch(c){
	case '1':
		state = INPUT;
		break;
	case '2':
		state = CALCULATE;
		break;
	case '3':
		state = INVERSE;
		break;
	case '4':
		state = DIVIDE;
		break;
	case '5':
		state = ROOT;
		break;
	case '6':
		state = SHOW;
		break;
	case '7':
		state = EXIT;
		break;
	defalt:
		cout << "无效操作" << endl;
		cin.clear();
		break;
	}
}

void UI::GetInput(){
	string name;
	int num;
	vector<double> v;
	cout << "多项式长度：";
	cin >> num;
	if(CheckCin())return;
	cout << "请输入：" << endl;
	for(int i = 1; i <= num; i++){
		int t;
		cin >> t;
		if(CheckCin())return;
		v.push_back(t);
	}
	cout << "多项式名为：";
	cin >> name;
	auto res = parser.BindName(name, v);
	if(res)cout << "输入成功，绑定的值已更新";
	else cout << "输入成功";
	cout << "，是否继续输入(y/n):";
	char c;
	cin >> c;
	if(c != 'y')
		state = MENU;
}

void UI::ShowPoly(){
	string name;
	cout << "多项式名为：";
	cin >> name;
	auto res = parser.nameMap.find(name);
	if(res == parser.nameMap.end())
		cout << "未定义的多项式" << endl;
	else{
		cout << name << " = ";
		res->second.Show();
		cout << endl;
	}
	cout << "是否继续查看(y/n):";
	char c;
	cin >> c;
	if(c != 'y')
		state = MENU;
}

void UI::Calculate(){
	string expr;
	cout << "请输入表达式：" << endl;
	cin >> expr;
	try{
		auto res = parser.Parse(expr)->Eval();
		cout << expr << " = ";
		res.Show();
		cout << "\n运算成功，";
	}
	catch(char const*){
		cout << "表达式错误，";
	}
	cout << "是否继续(y/n):";
	char c;
	cin >> c;
	if(c != 'y')
		state = MENU;
}

void UI::Inverse(){
	cout << "多项式名为：";
	string name;
	cin >> name;
	auto res = parser.nameMap.find(name);
	if(res == parser.nameMap.end()){
		cout << "未定义的多项式";
	}
	else{
		try{
			cout << name << "的逆元为：";
			res->second.Inverse().Show();
		}
		catch(char const*){
			cout << "逆元不存在";
		}
	}
	cout << '\n' << "是否继续(y/n):";
	char c;
	cin >> c;
	if(c != 'y')
		state = MENU;
}

void UI::Divide(){
	string a, b;
	cout << "输入被除数多项式名：";
	cin >> a;
	cout << "输入除数多项式名：";
	cin >> b;
	auto resA = parser.nameMap.find(a),
	resB = parser.nameMap.find(b);
	if(resA == parser.nameMap.end() || resB == parser.nameMap.end()){
		cout << "未定义的多项式";
	}
	else{
		try{
			auto res = (resA->second / resB->second);
			cout << "商为：";
			res.Show();
			cout << "，余数为";
			(resA->second - res * resB->second).Show();
		}
		catch(char const*){
			cout << "除数为0";
		}
	}	
	cout << '\n' << "是否继续(y/n):";
	char c;
	cin >> c;
	if(c != 'y')
		state = MENU;
}

void UI::Root(){
	cout << "多项式名为：";
	string name;
	cin >> name;
	auto res = parser.nameMap.find(name);
	if(res == parser.nameMap.end()){
		cout << "未定义的多项式";
	}
	else{
		try{
			auto poly = res->second;
			auto ans = poly.Root(1.41);
			cout << name << "的存在实根为：" << ans;
		}
		catch(char const*){
			cout << "无实根";
		}
	}
	cout << '\n' << "是否继续(y/n):";
	char c;
	cin >> c;
	if(c != 'y')
		state = MENU;
}

bool UI::CheckCin(){
	string buf;
	if(cin.fail()){
		cout << "输入错误！" << endl;
		cin.clear();
		cin >> buf;
		return true;
	}
	return false;
}

