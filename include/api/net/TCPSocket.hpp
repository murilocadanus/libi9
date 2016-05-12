/*
* Copyright (c) 2016, Sascar
* All rights reserved.
*
* THIS SOFTWARE IS PROVIDED BY SASCAR ''AS IS'' AND ANY
* EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL SASCAR BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef TCP_SOCKET_HPP
#define TCP_SOCKET_HPP

#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "Address.hpp"

namespace Sascar { namespace Net
{

class TCPSocket
{
	public:
		TCPSocket();
		~TCPSocket();

		bool Open(u32 port);
		void Close();
		bool IsOpen() const;
		int Accept();

		inline const char *GetServerName() const { return inet_ntoa(cAddress.sin_addr); }
		inline u32 GetSocketHandler() { return iHandle; }
		inline sockaddr_in GetAddress() { return cAddress; }

	private:
		sockaddr_in cAddress;
		u32 iHandle;
		bool bIsOpen : 1;
};

}} // namespace

#endif // TCP_SOCKET_HPP

