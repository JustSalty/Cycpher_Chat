#ifndef RSA_H_INCLUDED
#define RSA_H_INCLUDED

#include <string>
#include <vector>

using namespace std;


void set_args(long long p1, long long q1, long long e1);
long long binpowM(long long a, long long n, long long m);
long long gcd(long long a, long long b, long long & x, long long & y);
long long reverse(long long fi, long long e);
void encode(vector<long long>& v, long long e, long long n);
void decode(vector<long long>& v, long long d, long long n);
void read(vector<long long>& v);
void output(vector<long long>& v);

vector<long long> encrypt_string_v(string msg);
string decrypt_string_v(vector<long long> nums);
vector<long long> encrypt_string_v_args(string msg, long long p, long long q, long long e);
string decrypt_string_v_args(vector<long long> nums, long long p, long long q, long long e);
string encrypt_string(string msg, string key);
string decrypt_string(string msg, string key);

#endif // RSA_H_INCLUDED
