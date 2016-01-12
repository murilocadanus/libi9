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

#ifndef __FILE_H__
#define __FILE_H__

#include "Defines.hpp"
#include "interface/IObject.hpp"
#include <physfs.h>
#include "Job.hpp"

namespace Sascar {

/// File
class File : public IObject
{
	SEED_DECLARE_RTTI(File, IObject)

	public:
		File();
		File(const String &filename);
		virtual ~File();

		void Close();
		u32 GetSize() const;
		u8 *GetData() const;
		const String &GetName() const;

		bool Load(const String &filename);
		bool Unload();

	protected:
		bool Check() const;
		bool Open();

	private:
		PHYSFS_file		*pHandle;
		mutable u8		*pData;
		String			sFilename;
		u32				iSize;
};

class FileLoader : public Job
{
	public:
		FileLoader(const String &filename, JobCallback fun);
		virtual ~FileLoader();

		virtual bool Run() override;

		const String sFilename;
		File *pFile;
};

} // namespace

#endif // __FILE_H__
