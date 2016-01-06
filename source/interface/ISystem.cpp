
#include "interface/ISystem.hpp"
#include "interface/IEventSystemListener.hpp"
#include "EventSystem.hpp"

namespace Sascar {

const char *pcLanguageTable[] =
{
	"en_US",
	"pt_BR",
	"es_ES",
	"de_DE",
	"ja_JA",
	"cn_CN",
	"Unknown"
};

ISystem::ISystem()
	: mTimer()
	, vListeners()
	, pStrAppName(nullptr)
	, pStrAppDescription(nullptr)
	, nLanguage(eLanguage::en_US)
	, bDefaultCursorEnabled(false)
{
}

ISystem::~ISystem()
{
	ListenerVector(vListeners).swap(vListeners);
}

void ISystem::SetLanguage(Sascar::eLanguage lang)
{
	if (nLanguage != lang)
	{
		EventSystem ev(nLanguage, lang);

		nLanguage = lang;
		this->SendEventLanguageChanged(&ev);
	}
}

Sascar::eLanguage ISystem::GetLanguage() const
{
	return nLanguage;
}

const char *ISystem::GetLanguageString() const
{
	return pcLanguageTable[static_cast<u32>(nLanguage)];
}

const char *ISystem::GetUsername() const
{
	SEED_ABSTRACT_METHOD;
	return nullptr;
}

const char *ISystem::GetHomeFolder() const
{
	SEED_ABSTRACT_METHOD;
	return nullptr;
}

const char *ISystem::GetApplicationDataFolder() const
{
	SEED_ABSTRACT_METHOD;
	return nullptr;
}

const char *ISystem::GetSaveGameFolder() const
{
	SEED_ABSTRACT_METHOD;
	return nullptr;
}

void ISystem::EnableDefaultCursor(bool b)
{
	bDefaultCursorEnabled = b;
}

bool ISystem::IsDefaultCursorEnabled() const
{
	return bDefaultCursorEnabled;
}

void ISystem::AddListener(IEventSystemListener *listener)
{
	vListeners += listener;
}

void ISystem::RemoveListener(IEventSystemListener *listener)
{
	vListeners -= listener;
}

void ISystem::SendEventReset(const EventSystem *ev)
{
	for (auto target: vListeners)
		target->OnSystemReset(ev);
}

void ISystem::SendEventShutdown(const EventSystem *ev)
{
	for (auto target: vListeners)
		target->OnSystemShutdown(ev);
}

void ISystem::SendEventSystemMenu(const EventSystem *ev)
{
	for (auto target: vListeners)
		target->OnSystemMenuCalled(ev);
}

void ISystem::SendEventSystemDataManager(const EventSystem *ev)
{
	for (auto target: vListeners)
		target->OnSystemDataManagerCalled(ev);
}

void ISystem::SendEventHomeEnded(const EventSystem *ev)
{
	for (auto target: vListeners)
		target->OnSystemHomeEnded(ev);
}

void ISystem::SendEventSleep(const EventSystem *ev)
{
	for (auto target: vListeners)
		target->OnSystemSleep(ev);
}

void ISystem::SendEventLanguageChanged(const EventSystem *ev)
{
	for (auto target: vListeners)
		target->OnSystemLanguageChanged(ev);
}

bool ISystem::IsRequired() const
{
	return true;
}

} // namespace
