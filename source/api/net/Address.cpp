#include "Defines.hpp"
#include "api/net/Address.hpp"

namespace Sascar { namespace Net {

Address::Address()
	: iAddress(0)
	, iPort(0)
{
}

Address::Address(u32 a, u32 b, u32 c, u32 d, u32 port)
{
	iAddress = ((a & 0xff) << 24) | ((b & 0xff) << 16) | ((c & 0xff) << 8) | (d & 0xff);
	iPort = port;
}

Address::Address(u32 address, u16 port)
{
	iAddress = address;
	iPort = port;
}

u32 Address::GetAddress() const
{
	return iAddress;
}

std::string Address::GetAddress()
{
	return String().append(std::to_string(GetA())).append(".")
			.append(std::to_string(GetB())).append(".")
			.append(std::to_string(GetC())).append(".")
			.append(std::to_string(GetD()));
}

u32 Address::GetA() const
{
	return u32(char(iAddress >> 24));
}

u32 Address::GetB() const
{
	return u32(char(iAddress >> 16));
}

u32 Address::GetC() const
{
	return u32(char(iAddress >> 8));
}

u32 Address::GetD() const
{
	return u32(char(iAddress));
}

u32 Address::GetPort() const
{
	return iPort;
}

bool Address::operator ==(const Address & other) const
{
	return iAddress == other.iAddress && iPort == other.iPort;
}

bool Address::operator !=(const Address & other) const
{
	return !(*this == other);
}


}} // namespace


