#include "util/Log.hpp"
#include "api/net/UDPSocket.hpp"
#include <limits>

#define TAG "[SocketUDP] "

namespace Sascar { namespace Net
{

UDPSocket::UDPSocket()
	: cAddress()
	, iHandle(0)
	, bIsOpen(false)
{
	// Creating a socket
	iHandle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	int optval = 1;
	setsockopt(iHandle, SOL_SOCKET, SO_BROADCAST, &optval, sizeof(optval));

	if (iHandle <= 0)
	{
		Log(TAG "failed to create socket");
	}
}

UDPSocket::~UDPSocket()
{
}

bool UDPSocket::Open(u32 port)
{
	//ASSERT(port < std::numeric_limits<unsigned short>::max());

	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons((unsigned short) port);

	if (bind(iHandle, (const sockaddr*) &address, sizeof(sockaddr_in)) < 0)
	{
		Log(TAG "failed to bind socket" );
		this->Close();
		bIsOpen = false;
	}
	else
	{
		// Setting the socket as non-blocking
		int nonBlocking = 1;
		if (fcntl(iHandle, F_SETFL, O_NONBLOCK, nonBlocking ) == -1)
		{
			Log(TAG "failed to set non-blocking socket");
			return false;
		}

		bIsOpen = true;
	}

	return bIsOpen;
}

void UDPSocket::Close()
{
	shutdown(iHandle, SHUT_RDWR);

	bIsOpen = false;
}

bool UDPSocket::IsOpen() const
{
	return bIsOpen;
}

bool UDPSocket::Send(const Address &destination, const void *data, u32 size)
{
	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(destination.GetAddress());
	address.sin_port = htons((unsigned short) destination.GetPort());

	int sentBytes = sendto(iHandle, (const char*)data, size, 0, (sockaddr*)&address, sizeof(sockaddr_in));

	return sentBytes == s32(size);
}

u32 UDPSocket::Receive(Address &sender, void *data, u32 size)
{
	sockaddr_in from;
	socklen_t fromLength = sizeof(from);

	int receivedBytes = recvfrom(iHandle, (char*)data, size, 0, (sockaddr*)&from, &fromLength);

	if (receivedBytes <= 0)
		return 0;

	unsigned int address = ntohl(from.sin_addr.s_addr);
	unsigned short port = ntohs(from.sin_port);

	sender = Address(address, port);

	return receivedBytes;
}

}} // namespace
