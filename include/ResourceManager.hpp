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

#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include "interface/IResource.hpp"
#include "Enum.hpp"
#include "Container.hpp"

namespace Sascar {

typedef IResource *(*pResourceLoaderFunc)(const String &filename, ResourceManager *res);

typedef Map<String, IResource *> ResourceMap;
typedef ResourceMap::iterator ResourceMapIterator;

typedef Map<TypeId, pResourceLoaderFunc> LoaderMap;
typedef LoaderMap::iterator LoaderMapIterator;

/// Resource Manager
/*!
Resource Cache and Manager for loading resources
*/
class ResourceManager
{
	public:
		ResourceManager(const String &name);
		~ResourceManager();

		void Reset();
		IResource *Get(const String &filename, TypeId resourceType);
		void GarbageCollect();

		u32 GetTotalUsedMemory();
		void PrintUsedMemoryByResource();

		static void Register(TypeId resourceType, pResourceLoaderFunc pfunc);
		static void Unregister(TypeId resourceType);

		void Unload(TypeId resourceType);
		void Reload(TypeId resourceType);
		void Print();

	private:
		void Add(const String &filename, IResource *res);
		void Remove(const String &filename);

	private:
		const String sName;
		ResourceMap mapResources;
		static LoaderMap mapLoaders;
};

} // namespace

#endif // RESOURCE_MANAGER_HPP
