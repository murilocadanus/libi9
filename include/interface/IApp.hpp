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

#ifndef IAPP_HPP
#define IAPP_HPP

#include "interface/IManager.hpp"
#include "interface/IUpdatable.hpp"

namespace Sascar {

class IApp : public IManager, public IUpdatable
{
	I9_DECLARE_MANAGER(IApp)
	public:
		IApp();
		virtual ~IApp();

		/// Print output level string
		virtual void WriteOut(const char *msg);

		/// Print error level string
		virtual void WriteInfo(const char *msg);

		/// Print error level string
		virtual void WriteErr(const char *msg);

		/// Print debug level string
		virtual void WriteDbg(const char *msg);

		/// Get user resource manager
		//ResourceManager *GetResourceManager();

		// IManager
		virtual bool Shutdown() override;

	public:
		bool bIsFinished;
};

} // namespace

#endif // IAPP_HPP
