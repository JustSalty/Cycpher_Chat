#include <WinSock2.h>
#include "C:\Users\Admin\Desktop\Chat2\SockUtils.h"
#include <iostream>

void main()
{
	try
	{
		InitSocketsLib();
		TestServerSocket();

		ReleaseSocketsLib();
	}
	catch (...) { cout << "\n Unidentified exception caught!\n"; }
}