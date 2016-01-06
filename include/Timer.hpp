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

#ifndef TIMER_HPP
#define TIMER_HPP

#include "Defines.hpp"
#include <thread>

namespace Sascar {

class Timer
{
	public:
		Timer()
		{
			mStart = Clock::now();
		}

		~Timer()
		{
		}

		Timer(const Timer &t)
			: mStart(t.mStart)
		{
		}

		Timer(Timer &&t)
			: mStart(std::move(t.mStart))
		{
			mStart = TimePoint{};
		}

		Timer &operator=(const Timer &t)
		{
			mStart = t.mStart;
			return *this;
		}

		Timer &operator=(Timer &&t)
		{
			mStart = std::move(t.mStart);
			return *this;
		}

		Milliseconds GetMilliseconds() const
		{
			auto now = Clock::now();
			return std::chrono::duration_cast<std::chrono::duration<Milliseconds, std::milli>>(now - mStart).count();
		}

		Seconds GetSeconds() const
		{
			auto now = Clock::now();
			return std::chrono::duration_cast<std::chrono::duration<Seconds>>(now - mStart).count();
		}

		void Sleep(Seconds s) const
		{
			this->Sleep(Duration(Milliseconds(s * 1000.0f)));
		}

		void Sleep(Milliseconds ms) const
		{
			this->Sleep(Duration(ms));
		}

		void Sleep(Duration ms) const
		{
			std::this_thread::sleep_for(ms);
		}

		void Reset()
		{
			mStart = Clock::now();
		}

	public:
		TimePoint mStart;
};

} // namespace

#endif // TIMER_HPP
