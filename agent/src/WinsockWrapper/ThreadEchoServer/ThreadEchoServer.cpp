// ThreadEchoServer.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "AcceptThread.h"

int _tmain(int argc, _TCHAR* argv[])
{
	// Start
	AcceptThread acceptThread;
	acceptThread.start(5000);

	// Wait for stop
	printf("Press Another Enter to quit the server...\n");
	getchar();
	acceptThread.stop();
	return 0;
}

