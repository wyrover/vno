#include "MyRandom.h"

#include "randomc.h"
#include <ctime>

MyRandom::MyRandom()
{
    pTwister = new TRandomMersenne( ( unsigned long )time( NULL ) );
}

MyRandom::MyRandom( unsigned long seed )
{
    pTwister = new TRandomMersenne( seed );
}

MyRandom::~MyRandom()
{
    delete pTwister;
}

double MyRandom::randomDouble()
{
    return pTwister->Random();
}

int MyRandom::randomInt( int min, int max )
{
    return pTwister->IRandom( min, max );
}

void MyRandom::init( unsigned int seed )
{
    pTwister->RandomInit( seed );
}

bool MyRandom::flip()
{
    return randomDouble() > 0.5;
}

//ȫ�ֱ�������Ϊga�õ�random generator
//���ⲿʹ�õ�ʱ��ʹ��extern MyRandom rng; ����
// Ϊ�˱��ڲ��ԣ�ʹ��MyRandom rng(100)��ʽ
// ����ʽ�ĳ����У���Ҫ�޸ĳ�MyRandom rng()��ʹ�õ�ǰʱ����Ϊseed
//MyRandom rng(19847); // 19847����������ָ���ģ�û���κ���������
MyRandom rng;
