#include "C:\Users\Admin\Desktop\Chat2\RSA.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;


void main()
{
	long long p = 21169, q = 3967, e = 257;
	string m;
	cin >> m;
	vector<long long> d = encrypt_string_v_args(m, p, q, e);
	//cout << d << endl;
	string m0 = decrypt_string_v_args(d, p, q, e);
	cout << m0 << endl;
	/*
	string m;
	cin >> m;
	string key = "abc";
	string d = encrypt_string(m, key);
	cout << d << endl;
	string m0 = decrypt_string(d, key);
	cout << m0 << endl;
	*/
	/*
	string m;
	cin >> m;
	vector<long long> d = encrypt_string_v(m);
	//cout << d << endl;
	string m0 = decrypt_string_v(d);
	cout << m0 << endl;
	*/
	/*
	string m;
	cin >> m;
	string d = encrypt_string(m);
	cout << d << endl;
	string m0 = decrypt_string(d);
	cout << m0 << endl;
	*/
	system("pause");
}