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

#ifndef IOBJECT_HPP
#define IOBJECT_HPP

#include "Defines.hpp"
#include "Enum.hpp"
#include "stddef.h"

namespace Sascar {

/// Object Interface
/**
Interface for basic object
*/

typedef ptrdiff_t TypeId;

#define I9_DECLARE_RTTI(type, base)	protected:														\
											virtual bool IsKindOf_Internal(TypeId t) const override		\
											{															\
												if (GetTypeId() == t)									\
													return true;										\
												else													\
													return Base::IsKindOf_Internal(t);					\
											}															\
																										\
										public:															\
											typedef type class_need_declare_rtti;						\
											typedef base Base;											\
																										\
											static const char *GetTypeName()							\
											{															\
												return #type;											\
											}															\
																										\
											static TypeId GetTypeId()									\
											{															\
												static const char s_internal_##type = 0;				\
												return (TypeId)&s_internal_##type;						\
											}															\
										private:														\

class IObject
{
	protected:
		virtual bool IsKindOf_Internal(TypeId t) const
		{
			if (this->GetTypeId() == t)
				return true;
			return false;
		}

		virtual bool IsKindOf(TypeId t) const
		{
			return IsKindOf_Internal(t);
		}

		void GenerateCloneName(const String &original)
		{
			sName = original + "FixThis";
		}

	public:
		IObject()
			: sName()
		{
		}

		virtual ~IObject()
		{
		}

		static const char *GetTypeName()
		{
			return "IObject";
		}

		static TypeId GetTypeId()
		{
			static const char s_internal = 0;
			return (TypeId)&s_internal;
		}

		template<class T>
		bool IsKindOf() const
		{
			return IsKindOf(T::GetTypeId());
		}

		String sName;
};

} // namespace

#endif // IOBJECT_HPP
