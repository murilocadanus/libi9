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

#ifndef EVENTSYSTEM_HPP
#define EVENTSYSTEM_HPP

#include "interface/IEvent.hpp"
#include "Enum.hpp"

namespace Sascar {

/// System Event
class EventSystem : public IEvent
{
	I9_DECLARE_RTTI(EventSystem, IEvent)

	public:
		EventSystem();
		EventSystem(eLanguage curLang, eLanguage newLang);
		EventSystem(eShutdownReason reason);

		virtual ~EventSystem();

		virtual eLanguage GetLanguageCurrent() const;
		virtual eLanguage GetLanguageNew() const;
		virtual eShutdownReason GetShutdownReason() const;

	private:
		eLanguage nCurrentLang;
		eLanguage nNewLang;
		eShutdownReason nReason;
};

} // namespace

#endif // EVENTSYSTEM_HPP
