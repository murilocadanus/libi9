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

#ifndef RESOURCEGROUP_HPP
#define RESOURCEGROUP_HPP

#include "util/Log.hpp"
#include "Enum.hpp"
#include "Container.hpp"
#include "interface/IObject.hpp"

namespace Sascar {

class IResource;

/// Group of Resources for Loading
class ResourceGroup
{
	friend class ResourceLoader;

	public:
		ResourceGroup();
		virtual ~ResourceGroup();

		void Add(const String &filename, TypeId resourceType, ResourceManager *res = pResourceManager);

	protected:
		/// Item for loading with Resource Group
		typedef struct QueueItem
		{
			String				filename;
			IResource			*resource;
			TypeId				resourceType;
			ResourceManager		*resManager;
			Milliseconds		startTime;
			bool				erased : 1;

			QueueItem()
				: filename()
				, resource(nullptr)
				, resourceType()
				, resManager(nullptr)
				, startTime(0)
				, erased(false)
			{}
		} QueueItem;

		typedef Vector<QueueItem *>		QueueVector;
		typedef QueueVector::iterator	QueueVectorIterator;

	protected:
		bool Load();
		bool Unload();

		void SetLoaded();
		bool IsLoaded() const;

	protected:
		QueueVector		queue;
		bool			bLoaded : 1;
};

} // namespace

#endif // RESOURCEGROUP_HPP
