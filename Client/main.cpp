#include <WinSock2.h>
#include <thread>
#include <iostream>
#include <sstream>
#include <ctype.h>
#include "C:\Users\Admin\Desktop\Chat2\SockUtils.h"
#include "C:\Users\Admin\Desktop\Chat2\RSA.h"
#include "C:\Users\Admin\Desktop\Chat2\Long_str.h"

using namespace std;

unsigned int DefaultPort_ = 10001;
const char *DefaultServerAddress_ = "127.0.0.1";
SOCKET s;
bool onServer = false;
string myKey;

//string encrypt_string(string msg);
//string decrypt_string(string msg);

void TestSendToServer0()
{
	string dataToSend;

	cin >> dataToSend;

	string enc_msg = encrypt_string(dataToSend, myKey);//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	//while (send(s, dataToSend.c_str(), dataToSend.length(), 0) != SOCKET_ERROR)
	while (send(s, enc_msg.c_str(), enc_msg.length(), 0) != SOCKET_ERROR)
	{
		getline(cin, dataToSend);
		enc_msg = encrypt_string(dataToSend, myKey); //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	}

	closesocket(s);
}

void ConnectToServer()
{
	s = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in dest_addr;
	dest_addr.sin_family = AF_INET;
	dest_addr.sin_port = htons(DefaultPort_);
	dest_addr.sin_addr.s_addr = inet_addr(DefaultServerAddress_);



	if (connect(s, (sockaddr *)&dest_addr, sizeof(dest_addr)) != 0)
	{
		cout << "Error connecting to server!";
		return;
	}

	int bufSize = 101;
	char* buf = new char[bufSize];
	memset(buf, 0, bufSize);
	ostringstream dec_msg;
	string msg;
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	recv(s, buf, bufSize - 1, 0);
	msg = buf;
	cout << msg << endl;
	memset(buf, 0, bufSize);

	recv(s, buf, bufSize - 1, 0);
	string nums = buf;
	vector<long long> v = convert_to_vector(nums);
	long long p = v[0], q = v[1], e = v[2];
	// set_args(p, q, e);
	memset(buf, 0, bufSize);

	cout << "\n Please enter encryption keyword (only one word): ";
	string key; cin >> key;
	/* char c;
	while (cin >> c && !isspace(c))
	{
		key += c;
	} */
	myKey = key;

	vector<long long> enc_key = encrypt_string_v(myKey);
	string enc_key_s = convert_to_string(enc_key);
	send(s, enc_key_s.c_str(), enc_key_s.length(), 0);
}

void RecieveFromServer0()
{
	onServer = true;
	int bufSize = 101;
	char* buf = new char[bufSize];
	memset(buf, 0, bufSize);
	string msg;

	while (onServer && recv(s, buf, bufSize - 1, 0))
	{
		ostringstream dec_msg("");
		dec_msg << buf;
		msg = decrypt_string(dec_msg.str(), myKey);
		cout << msg << endl;
		memset(buf, 0, bufSize);
	}
}

void main()
{
	InitSocketsLib();

	ConnectToServer();

	//thread send(TestSendToServer0);
	
	thread recieve(RecieveFromServer0);

	/*
	onServer = true;
	int bufSize = 100;
	char* buf = new char[bufSize];
	memset(buf, 0, bufSize);
	while (onServer && recv(s, buf, bufSize - 1, 0))
	{
		cout << buf << endl;
		memset(buf, 0, bufSize);
	}
	*/
	
	// Next code is equivalent to SendToServer
	string dataToSend;
	cin >> dataToSend;
	string enc_msg = encrypt_string(dataToSend, myKey);//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	//while (send(s, dataToSend.c_str(), dataToSend.length(), 0) != SOCKET_ERROR)
	while (send(s, enc_msg.c_str(), enc_msg.length(), 0) != SOCKET_ERROR)
	{
		getline(cin, dataToSend);
		enc_msg = encrypt_string(dataToSend, myKey); //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	}
	//closesocket(s);
	
	//send.join();
	recieve.join();
	
	closesocket(s);

	//TestSendToServer();
	//TestSockets();

	ReleaseSocketsLib();
}