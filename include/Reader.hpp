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

#ifndef READER_HPP
#define READER_HPP

#include "Defines.hpp"
#include "interface/IReader.hpp"

namespace Sascar {

extern IReader cNullReader;

/// Data Reader
class Reader : public IReader
{
	public:
		Reader();
		Reader(File *file);
		Reader(Reader &reader);
		virtual ~Reader();

		// IReader
		virtual const char *ReadString(const char *key, const char *value = "") const override;
		virtual s32 ReadS32(const char *key, s32 value) const override;
		virtual u32 ReadU32(const char *key, u32 value) const override;
		virtual f32 ReadF32(const char *key, f32 value) const override;
		virtual bool ReadBool(const char *key, bool value = false) const override;

		virtual u32 GetU32(u32 value) const override;
		virtual const char *GetKey(u32 atPos) const override;

		virtual bool IsNode(const char *key) const override;
		virtual u32 SelectArray(const char *key) override;
		virtual void SelectNext() override;
		virtual void UnselectArray() override;
		virtual bool SelectNode(const char *key) override;
		virtual void UnselectNode() override;

	private:
		Reader operator=(const Reader &rhs);

		void Init();
		IReader	*pOpaque;
};

} // namespace

#endif // READER_HPP
