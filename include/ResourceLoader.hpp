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

#ifndef RESOURCE_LOADER_HPP
#define RESOURCE_LOADER_HPP

#include "interface/IManager.hpp"
#include "interface/IUpdatable.hpp"
#include "Thread.hpp"
#include "Singleton.hpp"
#include "Container.hpp"

namespace Sascar {

class ResourceGroup;
class EventResourceLoader;
class IEventResourceLoaderListener;

/// Resource Loader
/*!
Manager responsible for loading resources
*/
class ResourceLoader : public IManager, public IUpdatable, public Thread
{
	I9_DECLARE_SINGLETON(ResourceLoader)
	I9_DECLARE_MANAGER(ResourceLoader)

	public:
		typedef Vector<IEventResourceLoaderListener *> 	ListenerVector;
		typedef ListenerVector::iterator				ListenerIterator;

		typedef Vector<ResourceGroup *> 				GroupVector;
		typedef GroupVector::iterator					GroupIterator;

	public:
		//! Add a load request to the queue.
		/*!
			Add a load request to the queue.
		 */
		virtual void Add(ResourceGroup *group);

		//! Resource loader thread loop
		/*!
			Resource loader thread loop, if it returns false then it has finished.
		 */
		virtual bool Run(); // Thread

		/// Listeners pattern methods
		void AddListener(IEventResourceLoaderListener *listener);
		void RemoveListener(IEventResourceLoaderListener *listener);

		// IUpdatable
		virtual bool Update(Seconds dt);

		// IManager
		virtual bool Initialize();
		virtual bool Shutdown();
		virtual bool Reset();

	protected:
		void SendEventGroupLoaded(const EventResourceLoader *ev);
		void SendEventQueueEmpty(const EventResourceLoader *ev);

	private:
		ListenerVector 	vListeners;
		GroupVector		vGroups;
		Mutex			cMutex;
};

#define pResourceLoader ResourceLoader::GetInstance()

} // namespace

#endif // RESOURCE_LOADER_HPP
