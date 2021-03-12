// leetcode.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include "q.h"
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
		auto dig = getDigit(j);
		if (!dig.size()) {
			ret.push_back(0);
			continue;
		}
		ret.push_back(stoi(dig));
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


string getTwo(int val) {
	string ret;
	for (int i = 31; i >= 0; i--) {
		if (val & twop(i)) {
			ret += "1";
		}
		else {
			if (ret.size()) {
				ret += "0";
			}
		}
	}
	return ret;
}

void test() {
	int mask = 97;
	for (int i = mask; i; i = (i - 1) & mask) {
		printf("cur:%d, %s\n", i, getTwo(i).c_str());
	}
}

void question() {

    auto so = Solution();
    //int nums[] = { 3,8,12,9,10,14,14,1,11,3,11,6,14,4,10};
    string str("[6, 9, 2, 1, 2, 3, 6, 6, 6, 5, 9, 7, 0, 4, 5, 9, 1, 18, 8, 9]");
    auto v = getVI(str);
    string str1("[83,315,-442,-714,461,920,-737,-93,-818,-760,558,-584,-358,-228,-220]");
    auto v1 = getVI(str1);


    string str2("[[14, 15, 100, 9, 3], [32, 1, 9, 3, 5], [15, 29, 2, 6, 8, 7], [7, 10]]");
    auto vv = getVVI(str2);
	vector<string> vs({"####F","#C...","M...."});
	string s("aabcb");
	auto ret = so.computeSimilarities(vv);
	for (auto& i : ret) {
		cout << i << endl;
	}

}
int main()
{
	question();
	//vector<string> listStr({ "Fancy","append","append","getIndex","append","getIndex","addAll","append","getIndex","getIndex","append","append","getIndex","append","getIndex","append","getIndex","append","getIndex","multAll","addAll","getIndex","append","addAll","getIndex","multAll","getIndex","multAll","addAll","addAll","append","multAll","append","append","append","multAll","getIndex","multAll","multAll","multAll","getIndex","addAll","append","multAll","addAll","addAll","multAll","addAll","addAll","append","append","getIndex" });
	//string strVV("[[],[12],[8],[1],[12],[0],[12],[8],[2],[2],[4],[13],[4],[12],[6],[11],[1],[10],[2],[3],[1],[6],[14],[5],[6],[12],[3],[12],[15],[6],[7],[8],[13],[15],[15],[10],[9],[12],[12],[9],[9],[9],[9],[4],[8],[11],[15],[9],[1],[4],[10],[9]]");
	//auto vv = getVVI(strVV);
	//auto f = Fancy();
	//REP(i, 0, listStr.size()) {
	//	if (listStr[i] == "append") {
	//		f.append(vv[i][0]);
	//	}
	//	else if (listStr[i] == "getIndex") {
	//		printf("%d\n", f.getIndex(vv[i][0]));
	//	}
	//	else if (listStr[i] == "addAll") {
	//		f.addAll(vv[i][0]);
	//	}
	//	else if (listStr[i] == "multAll") {
	//		f.multAll(vv[i][0]);
	//	}
	//}
	return 0;
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
