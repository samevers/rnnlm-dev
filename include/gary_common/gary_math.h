#ifndef __GARY_MATH_H_
#define __GARY_MATH_H_

#include <cmath>

//using namespace std;

namespace spaceGary
{

//���ֵ
template <typename T>
inline
T GMax(T t1, T t2)
{
	if (t1 >= t2)
	{
		return t1;
	}
	else 
	{
		return t2;
	}
}

//��Сֵ
template <typename T>
inline 
T GMin(T t1, T t2)
{
	if (t1 <= t2)
	{
		return t1;
	}
	else 
	{
		return t2;
	}
}
template <typename T>
inline 
T GAbs_(T t1, T t2)
{
	return t1 < t2 ? t2 - t1 : t1 - t2;
}
};

#endif


