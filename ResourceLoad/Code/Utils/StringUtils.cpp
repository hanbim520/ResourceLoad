//
//  StringUtils.cpp
//  ResourceLoad
//
//  Created by 张海军 on 8/25/19.
//  Copyright © 2019 张海军. All rights reserved.
//
#include "StringUtils.h"
#include "source/utf8.h"

namespace EasyLoad
{
namespace utils
{
    std::string StringUtils::Printf(const char* format, ...)
    {
        va_list argsToCheckSize;
        int n;
        std::string ret;

        va_start(argsToCheckSize, format);
#if EasyLoad_COMPILER_MSVC
        // MS vsnprintf always returns -1 if string doesn't fit, rather than
        // the needed size. Used their 'special' function instead to get required size
        n = _vscprintf_p(format, argsToCheckSize);
#else
        // use a temporary buffer as some docs indicate we cannot pass NULL to vsnprintf
        char buf[1];
        n = vsnprintf(buf, 0, format, argsToCheckSize);
#endif
        if (n == -1)
            return NULL;

        ret.resize(n + 1, 0);
        va_end(argsToCheckSize);

        va_list argsToFormat;

        va_start(argsToFormat, format);
        n = vsnprintf(&ret[0], ret.size(), format, argsToFormat);
        va_end(argsToFormat);

        EasyLoad_ASSERT(n < (int)ret.size());

        if (n == -1)
            return NULL;

        // The v*printf methods might put a trailing NUL character, which should not not be in a
        // std::string, so strip it out.
        if (!ret.empty() && ret[ret.size() - 1] == '\0')
            ret = ret.substr(0, ret.size() - 1);

        return ret;
    }

    std::string StringUtils::NPrintf(const char* format, size_t max_n, ...)
    {
        va_list argsToCheckSize;
        size_t n;
        std::string ret;

        va_start(argsToCheckSize, max_n);
#if EasyLoad_COMPILER_MSVC
        // MS vsnprintf always returns -1 if string doesn't fit, rather than
        // the needed size. Used their 'special' function instead to get required size
        n = _vscprintf_p(format, argsToCheckSize);
#else
        // use a temporary buffer as some docs indicate we cannot pass NULL to vsnprintf
        char buf[1];
        n = vsnprintf(buf, 0, format, argsToCheckSize);
#endif
        if (n == -1)
            return NULL;

        n = (max_n < ++n) ? max_n : n;

        ret.resize(n, 0);
        va_end(argsToCheckSize);

        va_list argsToFormat;

        va_start(argsToFormat, max_n);
        n = vsnprintf(&ret[0], n, format, argsToFormat);
        va_end(argsToFormat);

        EasyLoad_ASSERT(n < ret.size());

        if (n == -1)
            return NULL;

        // The v*printf methods might put a trailing NUL character, which should not not be in a
        // std::string, so strip it out.
        if (!ret.empty() && ret[ret.size() - 1] == '\0')
            ret = ret.substr(0, ret.size() - 1);

        return ret;
    }

    UTF16String StringUtils::Utf8ToUtf16(const char* utf8String)
    {
        return Utf8ToUtf16(utf8String, strlen(utf8String));
    }

    UTF16String StringUtils::Utf8ToUtf16(const char* utf8String, size_t length)
    {
        UTF16String utf16String;

        if (utf8::is_valid(utf8String, utf8String + length))
        {
            utf16String.reserve(length);
            utf8::unchecked::utf8to16(utf8String, utf8String + length, std::back_inserter(utf16String));
        }

        return utf16String;
    }

    UTF16String StringUtils::Utf8ToUtf16(const std::string& utf8String)
    {
        return Utf8ToUtf16(utf8String.c_str(), utf8String.length());
    }

    char* StringUtils::StringDuplicate(const char *strSource)
    {
        char* result = NULL;

        if (!strSource)
            return NULL;

        size_t length = strlen(strSource) + 1;

        if ((result = (char*)EasyLoad_MALLOC(length)))
#ifdef TARGET_WIN
            strcpy_s(result, length, strSource);
#elif TARGET_UNIX
            strncpy(result, strSource, length);
#else
            strlcpy(result, strSource, length);
#endif

        return result;
    }

    bool StringUtils::EndsWith(const std::string& string, const std::string& suffix)
    {
        const size_t stringLength = string.length();
        const size_t suffixLength = suffix.length();

        if (suffixLength > stringLength)
            return false;

        return string.rfind(suffix.c_str(), stringLength - suffixLength, suffixLength) != std::string::npos;
    }
} /* utils */
} /* EasyLoad */
