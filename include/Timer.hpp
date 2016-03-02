#ifndef TIMER_HPP
#define TIMER_HPP

#include "Defines.hpp"
#include <thread>

#define DATETIME_FORMAT "%Y-%m-%d %H:%M:%S"

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

		time_t GetCurrentTime() const
		{
			return Clock::to_time_t(Clock::now() - std::chrono::hours(24));
		}

		std::string GetDateTimeFormat() const
		{
			return DATETIME_FORMAT;
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

}

#endif // TIMER_HPP

