#ifndef _HELPER_H_
#define _HELPER_H_
#include <string>

//=================================================================
//helper function to convert to odd char type used by Microsoft stuff
//=================================================================

struct Helper
{
	static wchar_t* charToWChar(const char* _text)
	{
		size_t size = strlen(_text) + 1;
		static wchar_t* wa = NULL;
		if (wa)
		{
			delete[] wa;
			wa = NULL;
		}
		wa = new wchar_t[size];
		mbstowcs_s(nullptr, wa, size, _text, size);
		return wa;
	}
};
#endif