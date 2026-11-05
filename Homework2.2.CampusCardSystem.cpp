#include "card_operations.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <new>
#include <windows.h>  // 👈 引入 Windows API 用于解决乱码

using std::cout;
using std::cin;
using std::endl;
using std::exception;

int main() {
	// 设置控制台输出编码为 UTF-8，防止中文乱码
	SetConsoleOutputCP(65001);

	try {
		// 1. 系统标题与数量输入
		card::title("校园一卡通消费管理系统");
		cout << "请输入学生账户数量: ";
		int n;
		if (!(cin >> n) || n <= 0) {
			throw std::invalid_argument("账户数量必须为正整数");
		}

		// 2. 动态创建账户数组并录入
		Card* cards = createCards(n);
		inputCards(cards, n);

		// 3. 对第一个账户充值 / 消费
		card::printLine();
		cout << "对第一个账户进行操作：" << endl;
		try {
			deposit(cards[0], 100.0);
		}
		catch (const exception& e) {
			cout << "  [充值失败] " << e.what() << endl;
		}

		try {
			spend(cards[0], 8.5, "食堂午餐");
		}
		catch (const exception& e) {
			cout << "  [消费失败] " << e.what() << endl;
		}

		// 4. 查询余额与学号（常引用 / 指向常量的指针）
		card::printLine();
		cout << "账户查询：" << endl;
		showBalance(cards[0]);
		viewStudentID(&cards[0]);

		// 5. 余额换算为分
		int cent = toCent(cards[0].balance);
		cout << "  余额换算为分: " << cent << " 分" << endl;

		// 6. 输出报表并释放内存
		card::printLine();
		printReport(cards, n);
		destroyCards(cards);

	}
	catch (const std::bad_alloc& e) {
		cout << "[内存分配失败] " << e.what() << endl;
		return 1;
	}
	catch (const exception& e) {
		cout << "[程序异常] " << e.what() << endl;
		return 1;
	}

	// 暂停一下，防止程序直接闪退看不到结果
	system("pause");
	return 0;
}
