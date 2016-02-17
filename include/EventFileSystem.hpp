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

#ifndef EVENTFILESYSTEM_HPP
#define EVENTFILESYSTEM_HPP

#include <sys/inotify.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <thread>
#include <map>
#include "interface/IEvent.hpp"
#include "Defines.hpp"
#define EVENT_BUFFER_LENGTH 100000

namespace Sascar {

class EventFileSystem : public IEvent
{
	public:
		enum listenerParam {LOCAL_PATH, RECURSIVE_PATH};

		EventFileSystem(listenerParam param, std::string path);
		EventFileSystem();
		virtual ~EventFileSystem();
		virtual void setListenerParam(listenerParam param);
		virtual void setPath(std::string path);
		virtual std::string getPath();
		virtual void setListnerEventFileSystem(void (*function)(std::string));
		virtual void start();
		virtual void stop();

	private:
		listenerParam param;
		std::string path;
		int notify_fd;
		bool processing;
		void (*notifica)(std::string path);
		std::map<int,std::string> listPath;
		void init();
		void listDir(std::string directory);
		void listenPath(std::string path);
		void process();
		void processEvent(struct inotify_event *event);

};

} // namespace

#endif // EVENTFILESYSTEM_HPP

