#ifndef CARD_OPERATIONS_H
#define CARD_OPERATIONS_H

#include <string>

// ===== 模块一：系统常量 =====
const double FEE_RATE = 0.02;          // 充值手续费率
const double WARNING_BALANCE = 10.0;   // 低余额警戒值

// ===== 模块一：账户结构体 =====
struct Card {
	int id;               // 学号
	std::string name;     // 姓名
	double balance;       // 当前余额
	int transactions;     // 交易次数
};

// ===== 模块二：命名空间与格式化输出 =====
namespace card {
	void printLine(char c = '-', int len = 60);
	void title(const std::string& s);
}

// ===== 模块三：动态内存管理与账户录入 =====
Card* createCards(int n);
void destroyCards(Card* p);
void inputCards(Card* arr, int n);

// ===== 模块四：账户操作（默认参数 / 重载 / 常引用 / 指向常量的指针） =====
void deposit(Card& c, double amount, double fee = FEE_RATE);
bool spend(Card& c, double cost);
bool spend(Card& c, double cost, const std::string& item);
void showBalance(const Card& c);
void viewStudentID(const Card* p);

// ===== 模块五：强制类型转换 =====
int toCent(double amount);

// ===== 模块六：报表输出 =====
void printReport(const Card* arr, int n);

#endif // CARD_OPERATIONS_H
