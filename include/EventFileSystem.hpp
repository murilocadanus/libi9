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

#ifndef EVENTFILESYSTEM_HPP
#define EVENTFILESYSTEM_HPP

#include "interface/IEvent.hpp"
#include "Defines.hpp"

namespace Sascar {

class EventFileSystem : public IEvent
{
	public:
		EventFileSystem();
		virtual ~EventFileSystem();

		inline void SetDirName(const std::string &dirName)
		{
			sDirName = dirName;
		}

		inline void SetEventType(const unsigned char eventType)
		{
			eEventType = eventType;
		}

		inline const std::string &GetDirName() { return sDirName; }
		inline const unsigned char &GetEventType() { return eEventType; }

	private:
		std::string sDirName;
		unsigned char eEventType;
};

} // end namespace

#endif // EVENTFILESYSTEM_HPP

