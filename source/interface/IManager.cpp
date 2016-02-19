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

#include "interface/IManager.hpp"
#include "util/Log.hpp"
#include "Enum.hpp"

namespace Sascar
{

IManager::IManager()
	: bInitialized(false)
	, bEnabled(true)
{
}

IManager::~IManager()
{
	this->Shutdown();
}

bool IManager::Initialize()
{
	bInitialized = true;
	return true;
}

bool IManager::Reset()
{
	return true;
}

bool IManager::Shutdown()
{
	bInitialized = false;
	return true;
}

void IManager::Disable()
{
	bEnabled = false;
}

void IManager::Enable()
{
	bEnabled = true;
}

bool IManager::IsEnabled() const
{
	return bEnabled;
}

bool IManager::IsInitialized() const
{
	return bInitialized;
}

bool IManager::IsRequired() const
{
	return false;
}

} // end namespace
