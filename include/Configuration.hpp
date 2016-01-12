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

#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include "Defines.hpp"
#include "interface/IObject.hpp"
#include "Enum.hpp"
#include "Singleton.hpp"

namespace Sascar {

/// Run-time Configuration
class Configuration : public IObject
{
	SEED_DECLARE_SINGLETON(Configuration)

	public:
		void Load(const String &file);

		void SetWorkingDirectory(const String path);
		const String &GetWorkingDirectory() const;

		//! Sets the application title.
		/*!
			Sets the application title, mainly used for savegame data.
			\param title Title of the application;
		 */
		void SetApplicationTitle(const String &title);

		//! Returns the application title.
		/*!
			Returns the application title.
			\returns a const char * string;
		 */
		const String &GetApplicationTitle() const;

		//! Sets the application description.
		/*!
			Sets the application description, mainly used for savegame data.
			\param descr Description of the application ;
		 */
		void SetApplicationDescription(const String &desc);

		//! Returns the application description.
		/*!
			Returns the application description.
			\returns a const char * string;
		 */
		const String &GetApplicationDescription() const;

		//! Sets the application publisher name.
		/*!
			Sets the application publisher name, mainly used for savegame data.
			\param descr Publisher of the application ;
		 */
		void SetPublisherName(const String desc);

		//! Returns the application publisher name.
		/*!
			Returns the application publisher name.
			\returns a const char * string;
		 */
		const String &GetPublisherName() const;

		void SetReaderType(eReaderType readerType);
		eReaderType GetReaderType() const;

	private:
		String sWorkingDirectory;
		String sTitle;
		String sDescription;
		String sPublisherName;

		eReaderType nReaderType;
};

#define pConfiguration Configuration::GetInstance()

} // namespace

#endif // CONFIGURATION_HPP
