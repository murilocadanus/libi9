#include "Updater.hpp"
#include "interface/IUpdatable.hpp"
#include "Profiler.hpp"

namespace Sascar {

I9_SINGLETON_DEFINE(Updater)

Updater::Updater()
	: vUpdatable()
{
}

Updater::~Updater()
{
	IUpdatableVector().swap(vUpdatable);
}

void Updater::Add(IUpdatable *obj)
{
	vUpdatable += obj;
}

void Updater::Remove(IUpdatable *obj)
{
	vUpdatable -= obj;
}

void Updater::Run(Seconds dt)
{
	I9_FUNCTION_PROFILER;

	for (auto each: vUpdatable)
		each->Update(dt);
}

} // namespace
