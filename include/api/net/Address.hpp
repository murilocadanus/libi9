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

#ifndef ADDRESS_HPP
#define ADDRESS_HPP

#include "Defines.hpp"

namespace Sascar { namespace Net
{

class Address
{
	public:
		Address();
		Address(u32 a, u32 b, u32 c, u32 d, u32 port);
		Address(u32 address, u16 port);
		Address(const Address &) = default;

		u32 GetAddress() const;
		std::string GetAddress();
		u32 GetA() const;
		u32 GetB() const;
		u32 GetC() const;
		u32 GetD() const;
		u32 GetPort() const;

		bool operator==(const Address &other) const;
		bool operator!=(const Address &other) const;

	private:
		u32 iAddress;
		u16 iPort;
};

}} // namespace

#endif // ADDRESS_HPP
