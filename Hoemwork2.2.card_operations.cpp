#include "card_operations.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <limits>

using std::cout;
using std::cin;
using std::endl;
using std::string;

// ========== 模块二：命名空间与格式化输出 ==========
namespace card {
	void printLine(char c, int len) {
		for (int i = 0; i < len; ++i) cout << c;
		cout << endl;
	}

	void title(const string& s) {
		printLine('=', 60);
		// 简单的居中处理
		int padding = (60 - static_cast<int>(s.length())) / 2;
		for (int i = 0; i < padding; ++i) cout << " ";
		cout << s << endl;
		printLine('=', 60);
	}
}

// ========== 模块三：动态内存管理 ==========
Card* createCards(int n) {
	if (n <= 0) {
		throw std::invalid_argument("账户数量必须为正整数");
	}
	return new Card[n];
}

void destroyCards(Card* p) {
	delete[] p;
}

void inputCards(Card* arr, int n) {
	for (int i = 0; i < n; ++i) {
		while (true) {
			try {
				cout << "请输入第 " << (i + 1) << " 个账户 (学号 姓名 初始余额): ";
				int id;
				string name;
				double balance;

				if (!(cin >> id >> name >> balance)) {
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					throw std::runtime_error("输入格式错误，请重新输入");
				}
				if (balance < 0.0) {
					throw std::invalid_argument("初始余额不能为负数，请重新输入");
				}

				arr[i].id = id;
				arr[i].name = name;
				arr[i].balance = balance;
				arr[i].transactions = 0;
				break;
			}
			catch (const std::exception& e) {
				cout << "  [错误] " << e.what() << endl;
			}
		}
	}
}

// ========== 模块四：账户操作 ==========
void deposit(Card& c, double amount, double fee) {
	if (amount <= 0.0) {
		throw std::invalid_argument("充值金额必须大于 0");
	}
	if (fee < 0.0 || fee >= 1.0) {
		throw std::invalid_argument("手续费率不合法");
	}
	double actual = amount * (1.0 - fee);   // 扣除手续费后实际入账
	c.balance += actual;
	c.transactions++;

	cout << "  充值 " << std::fixed << std::setprecision(2) << amount
		<< " 元，手续费 " << (amount * fee)
		<< " 元，实际入账 " << actual << " 元" << endl;
}

bool spend(Card& c, double cost) {
	if (cost < 0.0) {
		throw std::invalid_argument("消费金额不能为负数");
	}
	if (c.balance < cost) {
		return false;              // 余额不足
	}
	c.balance -= cost;
	c.transactions++;
	return true;
}

bool spend(Card& c, double cost, const string& item) {
	cout << "  消费项目: " << item
		<< "，金额: " << std::fixed << std::setprecision(2) << cost << endl;
	if (cost < 0.0) {
		throw std::invalid_argument("消费金额不能为负数");
	}
	if (!spend(c, cost)) {
		throw std::runtime_error("余额不足，消费失败");
	}
	return true;
}

void showBalance(const Card& c) {
	cout << "  账户 [" << c.name << "] 当前余额: "
		<< std::fixed << std::setprecision(2) << c.balance << " 元" << endl;
}

void viewStudentID(const Card* p) {
	cout << "  账户学号: " << p->id << endl;
}

// ========== 模块五：金额单位换算 ==========
int toCent(double amount) {
	return static_cast<int>(amount * 100.0);
}

// ========== 模块六：报表输出 ==========
void printReport(const Card* arr, int n) {
	card::title("账户报表");
	cout << std::left << std::setw(10) << "ID"
		<< std::left << std::setw(15) << "Name"
		<< std::right << std::setw(12) << "Balance"
		<< std::right << std::setw(15) << "Transactions" << endl;
	card::printLine();

	cout << std::fixed << std::setprecision(2);
	for (int i = 0; i < n; ++i) {
		cout << std::left << std::setw(10) << arr[i].id
			<< std::left << std::setw(15) << arr[i].name
			<< std::right << std::setw(12) << arr[i].balance
			<< std::right << std::setw(15) << arr[i].transactions << endl;
		if (arr[i].balance < WARNING_BALANCE) {
			cout << "  [警告] 余额低于警戒值 " << WARNING_BALANCE << " 元" << endl;
		}
	}
	card::printLine();
}
