#pragma once

#include <cstdio>

#if defined(DEBUG) | defined(_DEBUG)
	#ifndef ASSERT
		#define ASSERT(expr, msg) \
		{ \
			if (!(expr)) \
			{ \
				fprintf(stderr, "%s, %s, %s(%d)", (msg), (#expr), __FILE__, __LINE__); \
				__debugbreak(); \
			} \
		}
	#endif
#else
	#ifndef ASSERT
		#define ASSERT(expr, msg) ((void)0)
	#endif
#endif

#ifndef RELEASE
#define RELEASE(x) \
	if ((x) != nullptr) \
	{ \
		delete (x); \
		(x) = nullptr; \
	}
#endif

#ifndef RELEASE_ARRAY
	#define RELEASE_ARRAY(x) \
	if ((x) != nullptr) \
	{ \
		delete[] (x); \
		(x) = nullptr; \
	}
#endif