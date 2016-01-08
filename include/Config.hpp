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

#ifndef CONFIG_HPP
#define CONFIG_HPP

#if defined(I9_BUILD)
	#if !defined(I9_USE_STATIC)
		#define I9_BUILD_SHARED	1
		#define I9_LICENSE		"Shared"
	#else
		#define I9_LICENSE		"Static"
	#endif // I9_BUILD
#else
	#if !defined(I9_USE_STATIC)
		#define I9_BUILD_SHARED	1
		#define I9_LICENSE		"Shared"
	#else
		#define I9_LICENSE		"Static"
	#endif
#endif

#define I9_TAG					"[LibI9] "
#define I9_VERSION_MINOR		0			// Developer version (features, fixes)
#define I9_VERSION_MIDDLE		0			// Client version
#define I9_VERSION_MAJOR		1			// Release version (final trunk)
#define I9_VERSION_STRING		"%d.%d.%d"	//"1.1.1"
#define I9_NAME					"LibI9"
#define I9_COPYRIGHT			"Copyright (c) 2000-2016 Sascar"

#define I9_PLATFORM_NAME		"Cloud - C/C++"

#define I9_BANNER					I9_NAME " " I9_VERSION_STRING " [" I9_PLATFORM_NAME " " I9_TYPE " " I9_LICENSE "]\n" I9_COPYRIGHT

#if defined(DEBUG)
	#define I9_TYPE "Debug"
#else
	#define I9_TYPE "Release"
#endif // DEBUG

//================================================================================
// FEATURES CAPPING
//================================================================================
#define I9_USE_THREAD						0
#define I9_USE_JSON						1

/*
Toggle between instancing Singleton classes in the (0) Stack or in the (1) Heap
*/
#define I9_SINGLETON_HEAP					0

#endif // CONFIG_HPP
