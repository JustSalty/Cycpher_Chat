#pragma once;

#include <string>
//#include "RSA.h"

using namespace std;

//string encrypt_string(string msg);
//string decrypt_string(string msg);

class ClientConnectionInfo;

bool InitSocketsLib();
bool ReleaseSocketsLib();

void TestSockets();

//void TestSendToServer();
void TestServerSocket();

void SendToClient(ClientConnectionInfo*, std::string msg);//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//-----------------------------------------------------NEXT_IS_AN_RSA_FILE_COPY------------------------------------------------------------
/*

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

const long long p0 = 21169;
const long long q0 = 3967;
const long long e0 = 257;
long long n = p0 * q0;
long long e = e0;

//string encrypt_string(string msg);
//string decrypt_string(string msg);

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
	decode(v, e, n);
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