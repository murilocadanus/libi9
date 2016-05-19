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

#ifndef FILESYSTEM_HPP
#define FILESYSTEM_HPP

#include <iostream>
#include <stdint.h>
#include <dirent.h>

#include "interface/IManager.hpp"
#include "interface/IUpdatable.hpp"
#include "interface/IEventFileSystem.hpp"

#define EVENT_SIZE				(sizeof(struct inotify_event))
#define EVENT_BUFFER_LENGTH		(1024 * (EVENT_SIZE + 16))

namespace Sascar {

enum WatchType { LOCAL_PATH, RECURSIVE_PATH };

class FileSystem : public IManager, public IEventFileSystem
{
	I9_DECLARE_MANAGER(EventFileSystem)

	public:

		/** \class FileNotFoundException
		 *  \brief Specialized exception class.
		 */
		class FileNotFoundException{};

		/** \class PathNotFoundException
		 *  \brief Specialized exception class.
		 */
		class PathNotFoundException{};

		/** \class FileReadException
		 *  \brief Specialized exception class.
		 */
		class FileReadException{};

		/** \class FileWriteException
		 *  \brief Specialized exception class.
		 */
		class FileWriteException{};

		/** \class PathCreateException
		 *  \brief Specialized exception class.
		 */
		class PathCreateException{};

		/** \class PathNotDefinedException
		 *  \brief Specialized exception class.
		 */
		class PathNotDefinedException{};

		/** \class NotSpaceAvaiableException
		 *  \brief Specialized exception class.
		 */
		class NotSpaceAvaiableException{};

		FileSystem();
		virtual ~FileSystem();

		static FileSystem instance;

		static inline FileSystem *GetInstance()
		{
			return &FileSystem::instance;
		}

		static inline void DestroyInstance(){}

		// IManager
		virtual bool Initialize() override;
		virtual bool Shutdown() override;

		//void SetPath(const std::string &path) { sPath = path; }
		void SetPath(std::string path);
		inline const std::string &GetPath() { return sPath; }

		virtual void SaveFile(std::string pathClient, std::string pathPlate, std::string pathFile, const uint8_t *bufferFile, uint32_t sizeBufferFile);

	private:
		void AddPath(const std::string &path);
		void WatchPath(const std::string &path);

	private:
		std::map<int,std::string> mWatchingPaths;
		std::string sPath;
		uint32_t iNotifier;
		WatchType eWatchType;

		DIR *pDirPath;
		int iDirFd;
};

#define pFileSystem FileSystem::GetInstance()

} // namespace

#endif // FILESYSTEM_HPP

