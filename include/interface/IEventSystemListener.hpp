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

#ifndef IEVENTSYSTEMLISTENER_HPP
#define IEVENTSYSTEMLISTENER_HPP

#include "IEventListener.hpp"
#include "Defines.hpp"

namespace Sascar {

class EventSystem;

/// System event listener
class  IEventSystemListener : public IEventListener
{
	public:
		IEventSystemListener() = default;
		virtual ~IEventSystemListener() {}

		virtual void OnSystemReset(const EventSystem *ev)				SEED_PURE_VIRTUAL_EVENT
		virtual void OnSystemShutdown(const EventSystem *ev)			SEED_PURE_VIRTUAL_EVENT
		virtual void OnSystemMenuCalled(const EventSystem *ev)			SEED_PURE_VIRTUAL_EVENT
		virtual void OnSystemDataManagerCalled(const EventSystem *ev)	SEED_PURE_VIRTUAL_EVENT
		virtual void OnSystemHomeEnded(const EventSystem *ev)			SEED_PURE_VIRTUAL_EVENT
		virtual void OnSystemSleep(const EventSystem *ev)				SEED_PURE_VIRTUAL_EVENT
		virtual void OnSystemLanguageChanged(const EventSystem *ev)		SEED_PURE_VIRTUAL_EVENT
};

} // namespace

#endif // IEVENTSYSTEMLISTENER_HPP
