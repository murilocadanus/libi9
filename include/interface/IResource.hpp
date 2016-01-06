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

#ifndef IRESOURCE_HPP
#define IRESOURCE_HPP

#include "Defines.hpp"
#include "IObject.hpp"

#define sdAcquire(p)		p->Acquire()
#define sdRelease(p)		{ if (p) p->Release(); p = nullptr; }

typedef unsigned long long int 	u64;
typedef unsigned int 			u32;
typedef unsigned short int 		u16;
typedef unsigned char 			u8;
typedef signed long long int	s64;
typedef signed int 				s32;
typedef signed short int 		s16;
typedef signed char 			s8;
typedef float 					f32;

namespace Sascar {

class ResourceManager;

/// Resource interface
class IResource : public IObject
{
	friend class ResourceManager;
	I9_DECLARE_RTTI(IResource, IObject)

	public:
		IResource();
		virtual ~IResource();

		virtual bool Load(const String &filename, ResourceManager *res) = 0;
		virtual bool Unload() = 0;

		virtual u32 GetUsedMemory() const;
		const String &GetFilename() const;

		void Release();
		void Acquire();

	protected:
		void IncrementReference();
		void DecrementReference();

		u32 GetReferenceCount() const;

	protected:
		ResourceManager *pRes;
		String			sFilename;
		u32				iRefCount;
		bool			bLoaded : 1;
};

} // namespace

#endif // __IRESOURCE_H__
