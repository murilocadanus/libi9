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

#ifndef CONFIG_HPP
#define CONFIG_HPP

#if defined(REVGEO_BUILD)
	#if !defined(REVGEO_USE_STATIC)
		#define REVGEO_BUILD_SHARED	1
		#define REVGEO_LICENSE		"Shared"
	#else
		#define REVGEO_LICENSE		"Static"
	#endif // REVGEO_BUILD
#else
	#if !defined(REVGEO_USE_STATIC)
		#define REVGEO_BUILD_SHARED	1
		#define REVGEO_LICENSE		"Shared"
	#else
		#define REVGEO_LICENSE		"Static"
	#endif
#endif

#define REVGEO_TAG					"[LibI9] "
#define REVGEO_VERSION_MINOR		0			// Developer version (features, fixes)
#define REVGEO_VERSION_MIDDLE		0			// Client version
#define REVGEO_VERSION_MAJOR		1			// Release version (final trunk)
#define REVGEO_VERSION_STRING		"%d.%d.%d"	//"1.1.1"
#define REVGEO_NAME					"LibI9"
#define REVGEO_COPYRIGHT			"Copyright (c) 2000-2015 Sascar"

#define REVGEO_PLATFORM_NAME		"Cloud - C/C++"

#define SEED_BANNER					REVGEO_NAME " " REVGEO_VERSION_STRING " [" REVGEO_PLATFORM_NAME " " REVGEO_TYPE " " REVGEO_LICENSE "]\n" REVGEO_COPYRIGHT

#if defined(DEBUG)
	#define REVGEO_TYPE "Debug"
#else
	#define REVGEO_TYPE "Release"
#endif // DEBUG

//================================================================================
// FEATURES CAPPING
//================================================================================
#define SEED_USE_THREAD						1
#define SEED_USE_JSON						1

/*
Toggle between instancing Singleton classes in the (0) Stack or in the (1) Heap
*/
#define REVGEO_SINGLETON_HEAP					0

#endif // CONFIG_HPP
