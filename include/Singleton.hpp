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

#ifndef SINGLETON_HPP
#define SINGLETON_HPP

#define I9_SINGLETON_HEAP_DECLARE(type)		\
											protected: \
												type(); \
											public: \
												virtual ~type(); \
												\
												static type *Instance; \
												\
												static inline type *GetInstance() \
												{ \
													if (type::Instance == nullptr) \
														type::Instance = new type(); \
													return type::Instance; \
												} \
												static inline void DestroyInstance() \
												{ \
													delete type::Instance; \
													type::Instance = nullptr; \
												}

#define I9_SINGLETON_HEAP_DEFINE(type)		type *type::Instance = nullptr;
												//type *const p##type = type::GetInstance();

#define I9_SINGLETON_STACK_DECLARE(type)	\
											public: \
												type(); \
												virtual ~type(); \
												\
												static type instance; \
												\
												static inline type *GetInstance() \
												{ \
													return &type::instance; \
												} \
												static inline void DestroyInstance() \
												{ \
												}

#define I9_SINGLETON_STACK_DEFINE(type)		type type::instance;
												//type *type::Instance = &type::instance;
												//type *const p##type = type::GetInstance();


#if I9_SINGLETON_HEAP == 1

#define I9_DECLARE_SINGLETON					I9_SINGLETON_HEAP_DECLARE
#define I9_SINGLETON_DEFINE					I9_SINGLETON_HEAP_DEFINE

#else

#define I9_DECLARE_SINGLETON					I9_SINGLETON_STACK_DECLARE
#define I9_SINGLETON_DEFINE					I9_SINGLETON_STACK_DEFINE

#endif

//#define I9_SINGLETON_EXTERNALIZE(type)		extern type *const p##type = &type::instance;

#endif // SIGNLETON_HPP
