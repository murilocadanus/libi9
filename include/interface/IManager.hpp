/*
* Copyright (c) 2015, Sascar
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

#ifndef IMANAGER_HPP
#define IMANAGER_HPP

#include "Defines.hpp"

namespace Sascar {

class IManager
{
	public:
		IManager();
		virtual ~IManager();

		/// Initialize this module, it must initialize all module attributes.
		virtual bool Initialize();

		/// Reset all module attributes as a newly created object.
		virtual bool Reset();

		/// Terminate everything and deinitialize all dependency. Reset to before initialization state.
		virtual bool Shutdown();

		/// Disables this module
		virtual void Disable();

		/// Enabled this module
		virtual void Enable();

		/// Returns true if this module is enabled
		virtual bool IsEnabled() const;

		/// Check if the module is initialized
		bool IsInitialized() const;

		/// If this module is mandatory (it is a base subsystem or critical one)
		virtual bool IsRequired() const;

		//virtual const String GetName() const = 0;

	protected:
		bool bInitialized : 1;
		bool bEnabled : 1;
};

} // end namespace

#endif // IMANAGER_HPP
