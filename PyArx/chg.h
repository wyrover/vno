// �ο�: http://www.cnblogs.com/linyilong3/p/4171503.html
// ���Կ�����ʱ�����Ǿ����������������������һ����Ŀ�Ѿ�������lib python�⣬
// ������ȴ����ȥ����python��dll�⣬�������Ϊ����һ����Ŀ��ָ��Ҫ����python��lib�⣬
// ����ΪC++��include�Ļ��ƣ�ֻҪ��������һ����Ŀ�ݹ�include���ļ������а���python��ͷ�ļ���
// ��ô�ͻᴥ������Զ����ӻ��ƣ�����ȴû��������һ����ĿҲָ�����Ӿ�̬�⣬�ͻ�������һ����Ŀ��ȥ����DLL��
// ����������Ҫ�����������궨��:
//    BOOST_PYTHON_STATIC_MODULE
//    BOOST_PYTHON_STATIC_LIB
// ע:�����ҵĲ���, ֻ��Ҫ����BOOST_PYTHON_STATIC_LIB�Ϳ���!!!

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