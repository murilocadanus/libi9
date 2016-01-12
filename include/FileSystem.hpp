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

#ifndef __FILESYSTEM_H__
#define __FILESYSTEM_H__

#include "Defines.hpp"
#include "interface/IManager.hpp"
#include "Singleton.hpp"

namespace Sascar {

/// FileSystem Manager
class  FileSystem : public IManager
{
	SEED_DECLARE_SINGLETON(FileSystem)
	I9_DECLARE_MANAGER(FileSystem)

	public:
		void Prepare() const;
		const char *GetWorkDirectory() const;
		const char *GetWriteableDirectory() const;

		// IManager
		virtual bool Initialize() override;
		virtual bool Shutdown() override;
		virtual bool IsRequired() const override;
};

#define pFileSystem FileSystem::GetInstance()

} // namespace

#endif // __FILESYSTEM_H__
