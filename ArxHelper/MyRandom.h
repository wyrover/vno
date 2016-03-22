#pragma once

class TRandomMersenne;

/*
* ���ڿ���ʹ��boost���Random�����棬��˵�ÿ��Ч�ʻ��������ܱȽ�ȫ�棨�ṩ�˶���random generator��
* �����ҵĴ���ʹ�ù���mersenneҲ�����е�һ��random generator
*/
class MyRandom
{
public:
    MyRandom();

    MyRandom( unsigned long seed );

    ~MyRandom();

    double randomDouble();                /**< Get a double in the interval 0.0 <= x <= 1.0   */

    int randomInt( int min, int max ); /**< Get an integer in the interval min <= x <= max */

    void init( unsigned int seed );  /**< Seed the random number generator               */
    bool flip();

private:
    TRandomMersenne* pTwister;
};

extern MyRandom rng;