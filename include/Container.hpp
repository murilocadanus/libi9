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

#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <stack>

#define SEED_DECLARE_CONTAINER_HELPER(N, C) \
											\
											template <typename T> \
											class N : public C<T> \
											{ \
												public: \
													void operator+=(const T& element) \
													{ \
														SEED_ASSERT(element); \
														this->push_back(element); \
													} \
													\
													void operator-=(const T& element) \
													{ \
														SEED_ASSERT(element); \
														this->erase(std::remove(this->begin(), this->end(), element), this->end()); \
													} \
													\
													size_t Size() const \
													{ \
														return this->size(); \
													} \
													\
													void Unique() \
													{ \
														sort(this->begin(), this->end()); \
														this->erase(unique(this->begin(), this->end()), this->end()); \
													} \
													\
											};

namespace Sascar
{
	SEED_DECLARE_CONTAINER_HELPER(Vector, std::vector)
}

#define Stack std::stack
#define Map std::map
#define SEED_DECLARE_CONTAINER(cont, type)	typedef cont<type *> type##cont;									\
											typedef type##cont::iterator type##cont##Iterator;					\
											typedef type##cont::const_iterator Const##type##cont##Iterator;

#define SEED_IMPLEMENT_VAR_HELPERS(cont, type, var)																	\
											public:																	\
												type##cont::iterator begin() { return var.begin(); }				\
												type##cont::iterator end()   { return var.end();   }				\
												type##cont::const_iterator begin() const { return var.begin(); }	\
												type##cont::const_iterator end() const	 { return var.end();   }	\
																													\
												void operator+=(type *element)										\
												{																	\
													this->Add(element);												\
												}																	\
																													\
												void operator-=(type *element)										\
												{																	\
													this->Remove(element);											\
												}																	\
																													\
											private:

#endif // CONTAINER_HPP
