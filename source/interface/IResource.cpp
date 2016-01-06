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
#include "interface/IResource.hpp"

namespace Sascar {

IResource::IResource()
	: pRes(nullptr)
	, sFilename()
	, iRefCount(0)
	, bLoaded(false)
{
}

IResource::~IResource()
{
}

void IResource::Release()
{
	this->DecrementReference();
}

void IResource::Acquire()
{
	this->IncrementReference();
}

u32 IResource::GetUsedMemory() const
{
	return sizeof(this);
}

void IResource::IncrementReference()
{
	iRefCount++;
}

void IResource::DecrementReference()
{
	iRefCount--;
}

u32 IResource::GetReferenceCount() const
{
	return iRefCount;
}

const String &IResource::GetFilename() const
{
	return sFilename;
}

} // namespace

