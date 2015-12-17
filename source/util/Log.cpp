/*
* Copyright (c) 2015, Sascar
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

#include "util/Log.hpp"

#include <stdio.h>
#include "RevGeoInit.hpp"

void Info(const char *pMessage, ...)
{
	char t[2048];
	va_list ap;

	va_start(ap, pMessage);
	vsnprintf(t, 2048, pMessage, ap);
	va_end(ap);

	if (Sascar::Private::pApplication)
		Sascar::Private::pApplication->WriteOut(t);
}

#if defined(DEBUG)

void Log(const char *pMessage, ...)
{
	char t[2048];
	va_list ap;

	va_start(ap, pMessage);
	vsnprintf(t, 2048, pMessage, ap);
	va_end(ap);

	if (Sascar::Private::pApplication)
		Sascar::Private::pApplication->WriteOut(t);
}

void Dbg(const char *pMessage, ...)
{
	char t[2048];
	va_list ap;

	va_start(ap, pMessage);
	vsnprintf(t, 2048, pMessage, ap);
	va_end(ap);

	if (Sascar::Private::pApplication)
		Sascar::Private::pApplication->WriteDbg(t);
}

void Error(const char *pMessage, ...)
{
	char t[2048];
	va_list ap;

	va_start(ap, pMessage);
	vsnprintf(t, 2048, pMessage, ap);
	va_end(ap);

	if (Sascar::Private::pApplication)
		Sascar::Private::pApplication->WriteErr(t);
}

#endif // DEBUG

