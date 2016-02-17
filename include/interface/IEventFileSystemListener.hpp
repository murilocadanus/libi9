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

#ifndef IEVENTFILESYSTEMLISTENER
#define IEVENTFILESYSTEMLISTENER

#include "IEvent.hpp"
#include "IEventListener.hpp"
#include "Defines.hpp"

namespace Sascar {

class EventFileSystem;

/// FileSystem Event Listener
class IEventFileSystemListener : public IEventListener
{
	public:
		IEventFileSystemListener() = default;
		virtual ~IEventFileSystemListener() {}

		/*virtual void OnFileSystemFatalError(const EventFileSystem *ev)			I9_PURE_VIRTUAL_EVENT
		virtual void OnFileSystemWrongDiskError(const EventFileSystem *ev)		I9_PURE_VIRTUAL_EVENT
		virtual void OnFileSystemNoDiskError(const EventFileSystem *ev)			I9_PURE_VIRTUAL_EVENT
		virtual void OnFileSystemRetryError(const EventFileSystem *ev)			I9_PURE_VIRTUAL_EVENT
		virtual void OnFileSystemOperationResumed(const EventFileSystem *ev)	I9_PURE_VIRTUAL_EVENT
		virtual void OnFileSystemLoadCompleted(const EventFileSystem *ev)		I9_PURE_VIRTUAL_EVENT*/

		virtual void OnFileSystemNotifyChange(const IEvent *ev)					I9_PURE_VIRTUAL_EVENT
};

} // namespace

#endif // IEVENTFILESYSTEMLISTENER

