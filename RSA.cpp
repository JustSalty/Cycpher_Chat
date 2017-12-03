#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "RSA.h"

using namespace std;

const long long p0 = 21169;
const long long q0 = 3967;
const long long e0 = 257;
long long n = p0 * q0, e = e0, fi_n = (p0 - 1)*(q0 - 1), p = p0, q = q0;
//long long d = reverse(fi_n, e);


void set_args(long long p1, long long q1, long long e1)
{
	p = p1;
	q = q1;
	e = e1;
	fi_n = (p - 1)*(q - 1);
	n = p * q;
}

long long binpowM(long long a, long long n, long long m) {
    if (n == 0)
        return 1;
    if (n % 2 == 1)
        return (binpowM(a, n - 1, m) * a) % m;
    else {
        long long b = binpowM(a, n / 2, m) % m;
        return (b * b) % m;
    }
}

long long gcd(long long a, long long b, long long & x, long long & y) {
    if (a == 0) {
        x = 0; y = 1;
        return b;
    }
    long long x1, y1;
    long long d = gcd(b%a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}

long long reverse(long long fi, long long e) //we find such d: d*e0=1 mod fi
{
    long long y, d;
    gcd(e, fi, d, y);
    d = (d % fi + fi) % fi;

    return d;
}

void encode(vector<long long>& v, long long e, long long n)
{
    for (long long i = 0, l = v.size(); i < l; ++i)
    {
        v[i] = binpowM(v[i], e, n);
    }
}

void decode(vector<long long>& v, long long d, long long n)
{
    for (long long i = 0, l = v.size(); i < l; ++i)
    {
        v[i] = binpowM(v[i], d, n);
    }
}

void read(vector<long long>& v)
{
    string c;
    getline(cin, c);
    for (int i = 0, l = c.length(); i < l; ++i)
    {
        v.push_back(c[i]);
    }
}

void output(vector<long long>& v)
{
    char c;
    for (int i = 0, l = v.size(); i < l; ++i)
    {
        c = v[i];
        cout << c;
        //cout << v[i] << " ";
    }
    cout << endl;
}

/*
string encrypt_string(string msg)
{
    vector<long long> v;
    for (int i = 0; i < msg.length(); ++i)
    {
        v.push_back(msg[i]);
    }
    encode(v, e, n);
    ostringstream enc_msg;
    char c;
    for (int i = 0; i < v.size(); ++i)
    {
        c = v[i];
        enc_msg << c;
    }
    return enc_msg.str();
}

string decrypt_string(string msg)
{
    vector<long long> v;
    for (int i = 0; i < msg.length(); ++i)
    {
        v.push_back(msg[i]);
    }
	long long d = reverse(fi_n, e);
    decode(v, d, n);
    ostringstream enc_msg;
    char c;
    for (int i = 0; i < v.size(); ++i)
    {
        c = v[i];
        enc_msg << c;
    }
    return enc_msg.str();
}
*/

string encrypt_string(string msg, string key)
{
	int m = msg.length(), k = key.length(), i = 0;
	ostringstream res("");
	char c;
	while (i < m)
	{
		c = msg[i] + key[i % k];
		res << c;
		++i;
	}
	return res.str();
}

string decrypt_string(string msg, string key)
{
	int m = msg.length(), k = key.length(), i = 0;
	ostringstream res("");
	char c;
	while (i < m)
	{
		c = msg[i] - key[i % k];
		res << c;
		++i;
	}
	return res.str();
}

vector<long long> encrypt_string_v(string msg)
{
	vector<long long> v;
	for (int i = 0; i < msg.length(); ++i)
	{
		v.push_back(msg[i]);
	}
	encode(v, e, n);
	return v;
}

string decrypt_string_v(vector<long long> nums)
{
	vector <long long> v = nums;
	long long d = reverse(fi_n, e);
	decode(v, d, n);
	ostringstream enc_msg;
	char c;
	for (int i = 0; i < v.size(); ++i)
	{
		c = v[i];
		enc_msg << c;
	}
	return enc_msg.str();
}

vector<long long> encrypt_string_v_args(string msg, long long p1, long long q1, long long e1)
{
	long long n1 = p1 * q1;
	vector<long long> v;
	for (int i = 0; i < msg.length(); ++i)
	{
		v.push_back(msg[i]);
	}
	encode(v, e1, n1);
	return v;
}

string decrypt_string_v_args(vector<long long> nums, long long p1, long long q1, long long e1)
{
	long long n1 = p1 * q1, fi_n1 = (p1 - 1)*(q1 - 1);
	vector <long long> v = nums;
	long long d1 = reverse(fi_n1, e1);
	decode(v, d1, n1);
	ostringstream enc_msg;
	char c;
	for (int i = 0; i < v.size(); ++i)
	{
		c = v[i];
		enc_msg << c;
	}
	return enc_msg.str();
}