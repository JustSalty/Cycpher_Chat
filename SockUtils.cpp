#define _CRT_SECURE_NO_WARNINGS

#include "SockUtils.h"
#include <winsock2.h>
//#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include "RSA.h"
#include "Long_str.h"

//string encrypt_string(string msg);
//string decrypt_string(string msg);

using namespace std;

WORD wVersionRequested;
WSADATA wsaData;
int err;


unsigned int DefaultPort = 10001;
const char *DefaultServerAddress = "127.0.0.1";
bool IsQuitRequested;

class ClientConnectionInfo
{
public:
	int ClientId;
	SOCKET clientSocket;
	string cliKey;
	vector<long long> args;
};

list<ClientConnectionInfo*> clients;  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

bool InitSocketsLib()
{
	wVersionRequested = MAKEWORD( 2, 2 );
	err=WSAStartup( wVersionRequested, &wsaData );
	return (err==0);
}

bool ReleaseSocketsLib()
{
	err=WSACleanup();
	return (err==0);
}

void SendToClient(ClientConnectionInfo* cli, string msg) //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
{
	SOCKET s = cli->clientSocket;
	send(s, msg.c_str(), msg.length()+1, 0);
}

unsigned long __stdcall ReceiveThreadFunction(void* pParam)
{
	ClientConnectionInfo *cli = (ClientConnectionInfo *)pParam;
	SOCKET clientSocket=cli->clientSocket;
	//string rec_key = cli->cliKey;
    int bufSize = 100;

	char *buf = new char[bufSize];
	memset(buf, 0, bufSize);

	recv(clientSocket, buf, bufSize - 1, 0);
	string s = buf;
	vector<long long> v = convert_to_vector(s);
	string rec_key = decrypt_string_v_args(v, cli->args[0], cli->args[1], cli->args[2]);
	cli->cliKey = rec_key;
	cout << " Key from client #" << cli->ClientId << " recieved : " << rec_key << endl;
	memset(buf, 0, bufSize);

	while(recv(clientSocket, buf, bufSize-1, 0))
    {
		string dec_msg = decrypt_string(buf, rec_key);
		if(strncmp(dec_msg.c_str(), "quit", 4)==0)
		{
			cout<<" Client #"<<cli->ClientId<<": quit command received!"<<endl;
			IsQuitRequested = true;
			break;
		}
		else
		{
			cout<<" Client #"<<cli->ClientId<<": "<<dec_msg<<endl;

			ostringstream msg; msg << " Client #" << cli->ClientId << ": " << dec_msg;
			for (auto other_client : clients)   //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			{
				if (other_client != cli)
				{
					string enc_msg_talk = encrypt_string(msg.str(), other_client->cliKey);
					//SendToClient(other_client, msg.str());
					SendToClient(other_client, enc_msg_talk);
				}
			}                                   //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

			//memset(dec_buf, 0, bufSize);
			memset(buf, 0, bufSize);
		}
	}

	closesocket(clientSocket);

	cout<<"Client #"<<cli->ClientId<<" disconnected."<<endl;

	int Id = cli->ClientId;
	ostringstream msg; msg << " Client #" << Id << " disconnected.";
	list<ClientConnectionInfo*>::iterator other_client;
	for (other_client = clients.begin(); other_client != clients.end(); ++other_client)   //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	{
		if ((*other_client) != cli)
		{
			string enc_msg_dis = encrypt_string(msg.str(), (*other_client)->cliKey);
			SendToClient((*other_client), enc_msg_dis);
			//SendToClient((*other_client), msg.str());
			//else clients.erase(other_client);
		}
	}                                   //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

	delete cli;

	return 0;
}

void TestSockets()
{
	int bufSize = 128;

    SOCKET s=socket(AF_INET,SOCK_STREAM,0);
    sockaddr_in dest_addr;
    dest_addr.sin_family=AF_INET;
    dest_addr.sin_port=htons(80);
    dest_addr.sin_addr.s_addr=inet_addr("91.202.128.77");
    connect(s,(sockaddr *)&dest_addr,sizeof(dest_addr));

    char *buf = new char[bufSize];
	memset(buf, 0, bufSize);

	int res = 0;

	strcpy(buf, "GET / \n\n");
    res = send(s, buf, strlen(buf), 0);

	memset(buf, 0, bufSize);
	res = recv(s, buf, bufSize-1, 0);

	cout<<"Received string:\n";
    while(res!=0)
    {
        cout<<buf;
		memset(buf, 0, bufSize);
		res = recv(s, buf, bufSize-1, 0);
    }

	cout<<endl;

    closesocket(s);
}

void TestServerSocket()
{
	int clientsCnt = 0;

	//tutorial
    SOCKET s=socket(AF_INET,SOCK_STREAM,0);

	sockaddr_in local_addr;
    local_addr.sin_family=AF_INET;
    local_addr.sin_port=htons(DefaultPort);
    local_addr.sin_addr.s_addr=0;

	bind(s,(sockaddr *) &local_addr,sizeof(local_addr));

    int c=listen(s,5);

	IsQuitRequested = false;
	cout<<"Server receive ready"<<endl;

	SOCKET client_socket;
    sockaddr_in client_addr;
    int client_addr_size=sizeof(client_addr);

//	fd_set socksToCheck;
//	TIMEVAL timeOut;
//	timeOut.tv_sec = 1;

	while(!IsQuitRequested)
	{
//		FD_ZERO(&socksToCheck);
		//FD_SET(s, &socksToCheck);
		//int res = select(1, &socksToCheck,  0, 0, &timeOut);
		//if(res==1)
		//{
			client_socket=accept(s,(sockaddr *)&client_addr, &client_addr_size);

			//send(client_socket, "AA", 2, 0);
			send(client_socket, " You successfully connected to server.\n", 40, 0);
			
			long long p0 = 21169, q0 = 3967, e0 = 257;
			vector<long long> v;
			v.push_back(p0); 
			v.push_back(q0);
			v.push_back(e0);
			string nums = convert_to_string(v);
			send(client_socket, nums.c_str(), nums.length() + 1, 0);

			//string msg = " You successfully connected to server.\n";
			//string enc_msg_conn = encrypt_string(msg);
			//send(client_socket, enc_msg_conn.c_str(), enc_msg_conn.length()+1, 0);


			clientsCnt++;
			cout<<" Client #"<<clientsCnt<<" connected."<<endl;

			ClientConnectionInfo *cli = new  ClientConnectionInfo();
			cli->ClientId = clientsCnt;
			cli->clientSocket = client_socket;
			cli->args = v;

			//ostringstream msg;
			ostringstream i_msg;
			i_msg << " Client #" << clientsCnt << " connected.";
			for (auto other_client : clients)   //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			{
				string enc_msg_con_other = encrypt_string(i_msg.str(), other_client->cliKey);
				SendToClient(other_client, enc_msg_con_other);
				//SendToClient(other_client, msg.str());
			}                                   //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

			clients.emplace_back(cli);

			DWORD threadId;
			CreateThread(NULL, NULL, ReceiveThreadFunction, cli, NULL,&threadId);
		//}
    }
	cout<<"Server shutting down."<<endl;
}

/*
void TestSendToServer()
{

    SOCKET s=socket(AF_INET,SOCK_STREAM,0);
    sockaddr_in dest_addr;
    dest_addr.sin_family=AF_INET;
	dest_addr.sin_port=htons(DefaultPort);
    dest_addr.sin_addr.s_addr=inet_addr(DefaultServerAddress);



	if(connect(s,(sockaddr *)&dest_addr,sizeof(dest_addr))!=0)
	{
		cout<<"Error connecting to server!";
		return;
	}

	string dataToSend;

	cin >> dataToSend;

	string enc_msg_send = encrypt_string(dataToSend);//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

	//while (send(s, dataToSend.c_str(), dataToSend.length(), 0) != SOCKET_ERROR)
	while (send(s, enc_msg_send.c_str(), enc_msg_send.length(), 0) != SOCKET_ERROR)
    {
		 getline(cin, dataToSend);
		 enc_msg_send = encrypt_string(dataToSend); //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    }

    closesocket(s);
}
*/