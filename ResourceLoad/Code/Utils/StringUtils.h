//
//  StringUtils.h
//  ResourceLoad
//
//  Created by 张海军 on 8/25/19.
//  Copyright © 2019 张海军. All rights reserved.
//
#pragma once
#include <string>
#include <vector>
#include <limits>
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>

#include "../OSGlobalConfig.h"


namespace EasyLoad
{
namespace utils
{
#include <string>

	typedef std::basic_string<EasyCppChar> UTF16String;
	typedef std::basic_string<EasyCppNativeChar> EasyCppNativeString;
    class  StringUtils
    {
    public:
        static std::string Printf(const char* format, ...);
        static std::string NPrintf(const char* format, size_t max_n, ...);
        static UTF16String Utf8ToUtf16(const char* utf8String);
        static UTF16String Utf8ToUtf16(const char* utf8String, size_t length);
        static UTF16String Utf8ToUtf16(const std::string& utf8String);
		static char* StringDuplicate(const char *strSource);
        static bool EndsWith(const std::string& string, const std::string& suffix);

        template<typename CharType, size_t N>
        static inline size_t LiteralLength(const CharType(&str)[N])
        {
            return N - 1;
        }

        template<typename CharType>
        static size_t StrLen(const CharType* str)
        {
            size_t length = 0;
            while (*str)
            {
                str++;
                length++;
            }

            return length;
        }

        // Taken from github.com/Microsoft/referencesource/blob/master/mscorlib/system/string.cs
        template<typename CharType>
        static inline size_t Hash(const CharType *str, size_t length)
        {
            EasyLoad_ASSERT(length <= static_cast<size_t>(std::numeric_limits<int>::max()));

            size_t hash1 = 5381;
            size_t hash2 = hash1;
            size_t i = 0;

            CharType c;
            const CharType* s = str;
            while (true)
            {
                if (i++ >= length)
                    break;
                c = s[0];
                hash1 = ((hash1 << 5) + hash1) ^ c;
                if (i++ >= length)
                    break;
                c = s[1];
                hash2 = ((hash2 << 5) + hash2) ^ c;
                s += 2;
            }

            return hash1 + (hash2 * 1566083941);
        }

        template<typename CharType>
        static inline size_t Hash(const CharType *str)
        {
            size_t hash1 = 5381;
            size_t hash2 = hash1;

            CharType c;
            const CharType* s = str;
            while ((c = s[0]) != 0)
            {
                hash1 = ((hash1 << 5) + hash1) ^ c;
                c = s[1];
                if (c == 0)
                    break;
                hash2 = ((hash2 << 5) + hash2) ^ c;
                s += 2;
            }

            return hash1 + (hash2 * 1566083941);
        }

        template<typename StringType>
        struct StringHasher
        {
            typedef typename StringType::value_type CharType;

            size_t operator()(const StringType& value) const
            {
                return Hash(value.c_str(), value.length());
            }
        };

        template<typename CharType>
        struct StringHasher<const CharType*>
        {
            size_t operator()(const CharType* value) const
            {
                return Hash(value);
            }
        };
    };
} /* utils */
} /* EasyLoad */

// Assumes str is not NULL
#if defined(_MSC_VER)
#define DECLARE_EasyLoad_STRING_AS_STRING_VIEW_OF_NATIVE_CHARS(variableName, str) \
    EasyLoad::utils::StringView<EasyCppNativeChar> variableName(reinterpret_cast<EasyLoadString*>(str)->chars, reinterpret_cast<EasyLoadString*>(str)->length);
#define DECLARE_NATIVE_C_STRING_AS_STRING_VIEW_OF_EasyLoad_CHARS(variableName, str) \
    EasyLoad::utils::StringView<EasyCppChar> variableName(str, wcslen(str));
#define DECLARE_NATIVE_STRING_AS_STRING_VIEW_OF_EasyLoad_CHARS(variableName, str) \
    EasyLoad::utils::StringView<EasyCppChar> variableName(str);
#else
#define DECLARE_EasyLoad_STRING_AS_STRING_VIEW_OF_NATIVE_CHARS(variableName, str) \
    EasyCppNativeString variableName##_native_string_storage = EasyLoad::utils::StringUtils::Utf16ToUtf8(reinterpret_cast<EasyLoadString*>(str)->chars, reinterpret_cast<EasyLoadString*>(str)->length); \
    EasyLoad::utils::StringView<EasyCppNativeChar> variableName(variableName##_native_string_storage.c_str(), variableName##_native_string_storage.length());
#define DECLARE_NATIVE_C_STRING_AS_STRING_VIEW_OF_EasyLoad_CHARS(variableName, str) \
    UTF16String variableName##_utf16String = EasyLoad::utils::StringUtils::Utf8ToUtf16(str); \
    EasyLoad::utils::StringView<EasyCppChar> variableName(variableName##_utf16String);
#define DECLARE_NATIVE_STRING_AS_STRING_VIEW_OF_EasyLoad_CHARS DECLARE_NATIVE_C_STRING_AS_STRING_VIEW_OF_EasyLoad_CHARS
#endif
