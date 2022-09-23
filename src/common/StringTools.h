#pragma once
#include <string>
#include <regex>


class Strings
{
public:
    static bool matches(const std::string& s, const std::string& pattern) {
        std::regex pattern_regex(pattern);
        return std::regex_search(std::string(s), pattern_regex);
    }

    static std::string wildcardToRegex(const std::string& s)
    {
        std::string res = std::regex_replace(s, std::regex("\\."), "\\.");
        res = std::regex_replace(res, std::regex("\\?"), ".");
     
        return std::regex_replace(res, std::regex("\\*"), ".*");
        
    }
    static bool matchesWildCard(const std::string& s, const std::string& wildcardPattern, bool caseSensitive = true)
    {
        return std::regex_match(s, std::regex(wildcardToRegex(wildcardPattern)));
    }
};
