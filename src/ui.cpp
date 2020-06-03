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
	cout << "1.输入 2.混合运算 5.求根 6.查看 7.退出" << endl;
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

