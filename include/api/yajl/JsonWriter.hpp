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

#ifndef JSONWRITER_HPP
#define JSONWRITER_HPP

#include "Defines.hpp"

#if I9_USE_JSON == 1

#include "yajl/api/yajl_gen.h"
#include "interface/IWriter.h"
#include "Container.hpp"

namespace Sascar {

/// JSON Data writer
class JsonWriter: public IWriter
{
	public:
		JsonWriter();
		virtual ~JsonWriter();

		// IWriter
		virtual bool Save(const String &file) override;
		virtual void WriteString(const char *key, const char *value) const override;
		virtual void WriteU32(u32 value) const override;
		virtual void WriteU32(const char *key, u32 value) const override;
		virtual void WriteS32(const char *key, s32 value) const override;
		virtual void WriteF32(const char *key, f32 value) const override;
		virtual void WriteBool(const char *key, bool value) const override;
		virtual void OpenArray(const char *key) override;
		virtual void CloseArray() override;
		virtual void OpenNode(const char *key = "") override;
		virtual void CloseNode() override;

	private:
		yajl_gen gen;
};

} // namespace

#endif // I9_USE_JSON

#endif // JSONWRITER_HPP
