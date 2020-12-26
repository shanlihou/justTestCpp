// leetcode.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include "q11.h"
const vector<string> explode(const string& s, string c)
{
	string buff{ "" };
	vector<string> v;
	int cur = 0;
	while (1) {
		int pos = s.find(c, cur);
		if (pos != -1) {
			v.push_back(s.substr(cur, pos - cur));
			cur = pos + c.size();
		}
		else {
			v.push_back(s.substr(cur));
			break;
		}

	}

	return v;
}

string getDigit(string& str) {
	string ret;
	for (auto i : str) {
		if ((i >= '0' && i <= '9') || i == '-') {
			ret += i;
		}
	}
	return ret;
}

VI getVI(string& str) {
	auto _ret = explode(str, string(","));
	VI ret;
	for (auto j : _ret) {
		ret.push_back(stoi(getDigit(j)));
	}
	return ret;
}

VVI getVVI(string &str) {
	VVI ret;
	auto _ret = explode(str, string("],"));
	for (auto i : _ret) {
		ret.push_back(getVI(i));
	}

	return ret;
}
int main()
{
    auto so = Solution();
    //int nums[] = { 3,8,12,9,10,14,14,1,11,3,11,6,14,4,10};
	string str("[10,-5,-2,4,0,3]");
	auto v = getVI(str);


	string str2("[[-37,-50,-3,44],[-37,46,13,-32],[47,-42,-3,-40],[-17,-22,-39,24]]");
	auto v2 = getVVI(str2);
	auto ret = so.matrixRankTransform(v2);
	for (auto i : ret) {
		for (auto j : i) {
			cout << j;
		}
		cout << endl;
	}
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
