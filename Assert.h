#pragma once

namespace CLib {
	#ifdef _DEBUG
		#define Assert(expression, string) if(\
		!!(expression))throw string;
	#else
		#define Assert(Statement, string) ((void)0)
	#endif
}