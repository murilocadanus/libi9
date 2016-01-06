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

#ifndef IUPDATABLE_HPP
#define IUPDATABLE_HPP

#include "Defines.hpp"

#define UNUSED(var)				(void)var;

namespace Sascar {

typedef float Seconds; // same here

//! Updatable interface
/**
Interface for objects that need be updated each frame.
*/
class IUpdatable
{
	public:
		IUpdatable() = default;
		virtual ~IUpdatable() {}

		//! Method to be called each frame.
		/*!
			\return If update was sucessful
		 */
		virtual bool Update(Seconds dt);
};

inline bool IUpdatable::Update(Seconds dt)
{
	UNUSED(dt);
	return true;
}

} // namespace

#endif // IUPDATABLE_HPP
