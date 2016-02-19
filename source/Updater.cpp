#include "Updater.hpp"
#include "interface/IUpdatable.hpp"

namespace Sascar {

Updater Updater::instance;

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
	for (auto each: vUpdatable)
		each->Update(dt);
}

} // namespace
