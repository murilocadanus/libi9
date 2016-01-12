/*
* Copyright (c) 2012, Seed Developers
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* 1. The origin of this software must not be misrepresented; you must not
*    claim that you wrote the original software.
* 2. Altered source versions must be plainly marked as such, and must not be
*    misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
* 4. A credit line is required in the game credits, as the following line:
*    Powered by Seed Framework
* 5. A Seed Framework logo should be displayed within a splash screen, or in
*    the case where the game haven't or cannot have a splash, a logo should be
*    displayed somewhere in the game (eg. menu, credits, other place).
*
* THIS SOFTWARE IS PROVIDED BY SEED DEVELOPERS ''AS IS'' AND ANY
* EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL SEED DEVELOPERS BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "Configuration.hpp"
#include "File.hpp"
#include "Reader.hpp"
#include "util/Log.hpp"
#include "ResourceManager.hpp"
#include "Memory.hpp"
#include "I9Init.hpp"
#include <algorithm>

namespace Sascar {

SEED_SINGLETON_DEFINE(Configuration)

Configuration::Configuration()
	: sWorkingDirectory("./")
	, sTitle("")
	, sDescription("")
	, sPublisherName("")
	, nReaderType(eReaderType::Default)
{
}

Configuration::~Configuration()
{
}

void Configuration::Load(const String &file)
{
	// This must not be async, it is a starting configuration file
	File *f = sdNew(File(file));
	if (f && f->GetData())
	{
		Reader r(f);

		// Overwritten by command line
		if (!Private::bDisableResourceLoader)
			Private::bDisableResourceLoader = r.ReadBool("bDisableResourceLoader", false);
		if (!Private::bDisableThread)
			Private::bDisableThread = r.ReadBool("bDisableThread", false);

		sWorkingDirectory = r.ReadString("sWorkingDirectory", "./");
		sTitle = r.ReadString("sTitle", "");
		sDescription = r.ReadString("sDescription", "");
		sPublisherName = r.ReadString("sPublisherName", "");
	}

	sdDelete(f);
}

void Configuration::SetWorkingDirectory(const String path)
{
	sWorkingDirectory = path;
}

const String &Configuration::GetWorkingDirectory() const
{
	return sWorkingDirectory;
}

void Configuration::SetApplicationTitle(const String &title)
{
	sTitle = title;
}

const String &Configuration::GetApplicationTitle() const
{
	return sTitle;
}

void Configuration::SetApplicationDescription(const String &desc)
{
	sDescription = desc;
}

const String &Configuration::GetPublisherName() const
{
	return sPublisherName;
}

void Configuration::SetPublisherName(const String desc)
{
	sPublisherName = desc;
}

const String &Configuration::GetApplicationDescription() const
{
	return sDescription;
}

void Configuration::SetReaderType(eReaderType readerType)
{
	nReaderType = readerType;
}

eReaderType Configuration::GetReaderType() const
{
	return nReaderType;
}

} // namespace
