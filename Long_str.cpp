
//#include <iostream>
#include <string>
#include <string.h>
#include <sstream>
#include <vector>
#include "Long_str.h"

using namespace std;

string make_string(const long long num)
{
	int n = num;
	ostringstream css;
	vector<char> c;
	if (n == 0) css << '0';
	else {
		int a;
		while (n > 9)
		{
			a = n % 10;
			c.push_back(a + 48);
			n /= 10;
		}
		c.push_back(n + 48);
		int cs = c.size();
		for (int i = 1; i <= cs; ++i)
		{
			css << c[cs - i];
		}
	}
	return css.str();
}

long long make_long(string num)
{
	int res = 0;
	int ten = 1;
	int l = num.length();
	for (int i = 1; i <= l; ++i)
	{
		if (num[l - i] > 57 || num[l - i] < 48) throw("\n Incorrect string passed!\n");
		res += ten * (num[l - i] - 48);
		ten *= 10;
	}
	return res;
}

string convert_to_string(const vector<long long> vect)
{
	ostringstream css;
	int s = vect.size();
	string word;
	for (int i = 0; i < s; ++i)
	{
		word = make_string(vect[i]);
		css << word << ',';
	}
	return css.str();
}

vector<long long> convert_to_vector(string msg)
{
	char c;
	int l = msg.length(), i = 0;
	//ostringstream css;
	string cs = "";
	vector<long long> res;
	long long tmp;
	char c0 = ',';
	while (i < l)
	{
		c = msg[i];
		if (c != c0) cs += c;//css << c;
		else if (c == c0) {
			//tmp = make_long(css.str());
			tmp = make_long(cs);
			res.push_back(tmp);
			tmp = 0;
			cs = "";
			//css.clear();
		}
		++i;
	}
	return res;
}

/*
void print_vector(const vector<long long> n)
{
	cout << endl;
	for (int i = 0; i < n.size(); ++i)
	{
		cout << n[i] << " ";
	}
}
*/