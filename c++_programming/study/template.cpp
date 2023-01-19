#include <iostream>

using namespace std;

template <class T>
void swapValue(T &a, T &b)
{
	T temp = a;
	a = b;
	b = temp;
}

template <class T>
class PFArray
{
public:
	PFArray();
	P
};
void main()
{
	int a = 10, b = 20;
	char c = 30, d = 40;

	cout << a << b << endl;
	swapValue(a, b);
	cout << a << b << endl;

	cout << c << d << endl;
	swapValue(c, d);
	cout << c << d << endl;
}