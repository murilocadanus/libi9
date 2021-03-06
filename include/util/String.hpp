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

#ifndef STRING_HPP
#define STRING_HPP

#include <string>
#include <strings.h>
#include <vector>
#include <sstream>

typedef std::string String;

#define REVGEO_strcasecmp strcasecmp

struct StringUtil
{
	inline static bool Equals(std::string a, std::string b)
	{
		return (REVGEO_strcasecmp(a.c_str(), b.c_str()) == 0);
	}

	inline static bool Equals(std::string a, const char *b)
	{
		return (REVGEO_strcasecmp(a.c_str(), b) == 0);
	}

	inline static bool Equals(const char *a, const char *b)
	{
		return (REVGEO_strcasecmp(a, b) == 0);
	}

	inline std::vector<std::string> static split(const std::string &s, char delim)
	{
		std::stringstream ss(s);
		std::string item;
		std::vector<std::string> tokens;
		while (getline(ss, item, delim))
		{
			tokens.push_back(item);
		}
		return tokens;
	}
};

#endif // STRING_HPP
