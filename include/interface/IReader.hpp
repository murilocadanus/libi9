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

#ifndef IREADER_HPP
#define IREADER_HPP

#include "Defines.hpp"
#include "File.hpp"

namespace Sascar {

/// Data reader interface
class IReader
{
	public:
		IReader();
		IReader(const File &file);
		virtual ~IReader();

		IReader(const IReader &other);
		IReader &operator=(const IReader &other);

		virtual bool Load(const void *data);
		virtual bool Load(IReader &reader);
		virtual const char *ReadString(const char *key, const char *value) const;
		virtual u32 ReadU32(const char *key, u32 value) const;
		virtual s32 ReadS32(const char *key, s32 value) const;
		virtual f32 ReadF32(const char *key, f32 value) const;
		virtual bool ReadBool(const char *key, bool value) const;

		virtual u32 GetU32(u32 value) const;
		virtual const char *GetKey(u32 atPos) const;

		virtual bool IsNode(const char *key) const;
		virtual u32 SelectArray(const char *key);
		virtual void UnselectArray();
		virtual void SelectNext();
		virtual bool SelectNode(const char *key);
		virtual void UnselectNode();
};

} // namespace

#endif // IREADER_HPP
