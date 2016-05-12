#include "api/net/TCPSocket.hpp"
#include "util/Log.hpp"
#include <errno.h>

#define TAG "[TCPSocket] "

namespace Sascar { namespace Net
{

TCPSocket::TCPSocket()
	: cAddress()
	, iHandle(0)
	, bIsOpen(false)
{
	// Creating a socket
	iHandle = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	int optval = 1;
	setsockopt(iHandle, SOL_SOCKET, SO_REUSEADDR|SO_KEEPALIVE, &optval, sizeof(optval));

	if (iHandle <= 0)
	{
		Error(TAG "Failed to create socket");
	}
}

TCPSocket::~TCPSocket()
{
}

bool TCPSocket::Open(u32 port)
{
	I9_ASSERT(port <std::numeric_limits<unsigned short>::max());

	cAddress.sin_family = AF_INET;
	cAddress.sin_addr.s_addr = INADDR_ANY;
	cAddress.sin_port = htons((unsigned short) port);

	if(bind(iHandle, (const sockaddr*)&cAddress, sizeof(sockaddr_in)) < 0)
	{
		Error(TAG "Failed to bind socket: %s", strerror(errno));
		this->Close();
		bIsOpen = false;
		exit(EXIT_FAILURE);
	}
	else
	{
		// Setting the socket to listen
		if(listen(iHandle, 10) == -1)
		{
			Error(TAG "Failed to listen socket");
			return false;
		}

		bIsOpen = true;
	}

	return bIsOpen;
}

void TCPSocket::Close()
{
	shutdown(iHandle, SHUT_RDWR);
	bIsOpen = false;
}

bool TCPSocket::IsOpen() const
{
	return bIsOpen;
}

int TCPSocket::Accept()
{
	socklen_t addressSize = sizeof(sockaddr_in);
	return accept(iHandle, (struct sockaddr*)&cAddress, &addressSize);
}

}} // namespace
