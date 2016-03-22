// 参考: http://www.cnblogs.com/linyilong3/p/4171503.html
// 所以开发的时候我们经常会遇见这种情况，明明一个项目已经链接了lib python库，
// 但是他却还是去链接python的dll库，这个是因为你在一个项目中指定要链接python的lib库，
// 而因为C++的include的机制，只要你在另外一个项目递归include的文件里面有包含python的头文件，
// 那么就会触发这个自动链接机制，但是却没有在另外一个项目也指定链接静态库，就会让另外一个项目跑去链接DLL，
// 所以我们需要定义这两个宏定义:
//    BOOST_PYTHON_STATIC_MODULE
//    BOOST_PYTHON_STATIC_LIB
// 注:经过我的测试, 只需要定义BOOST_PYTHON_STATIC_LIB就可以!!!

#ifndef chg_
#define chg_

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Chg
{
public:
	Chg(): m_age(28)
	{
		m_friend.push_back("mm");
	}
	int getAge()
	{
		return m_age;
	}
	int friendSize()
	{
		return (int)m_friend.size();
	}

	int m_age;
	vector<string> m_friend;
};

void haha();

void py_acutPrintf(const string& msg);

#endif // chg_