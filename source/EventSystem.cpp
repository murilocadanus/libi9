
#include "EventSystem.hpp"

namespace Sascar {

EventSystem::EventSystem()
	: IEvent()
	, nCurrentLang(eLanguage::en_US)
	, nNewLang(eLanguage::en_US)
	, nReason(eShutdownReason::None)
{
}

EventSystem::EventSystem(eLanguage curLang, eLanguage newLang)
	: EventSystem()
{
	nCurrentLang = curLang;
	nNewLang = newLang;
}

EventSystem::EventSystem(eShutdownReason reason)
	: EventSystem()
{
	nReason = reason;
}

EventSystem::~EventSystem()
{
}

Sascar::eLanguage EventSystem::GetLanguageCurrent() const
{
	return nCurrentLang;
}

Sascar::eLanguage EventSystem::GetLanguageNew() const
{
	return nNewLang;
}

Sascar::eShutdownReason EventSystem::GetShutdownReason() const
{
	return nReason;
}

} // namespace
