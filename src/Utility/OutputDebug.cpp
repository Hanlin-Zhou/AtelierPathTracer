#include "OutputDebug.hpp"

namespace APT {
	void DebugOut(std::string string)
	{
		int len;
		int stringlength = (int)string.length() + 1;
		len = MultiByteToWideChar(CP_ACP, 0, string.c_str(), stringlength, 0, 0);
		wchar_t* buf = new wchar_t[len];
		MultiByteToWideChar(CP_ACP, 0, string.c_str(), stringlength, buf, len);
		OutputDebugString(buf);
	}
}