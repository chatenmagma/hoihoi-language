#ifndef HOIHOI_FORMATER_HPP
#define HOIHOI_FORMATER_HPP

#include <algorithm>
#include <string>

#include "value/value.hpp"

namespace hoihoi {
    inline std::string source_str_to_str(const std::string& str) {
        if(str.size() < 2) return "";
        
        std::string s = str;

        s.erase(s.begin());
        s.pop_back();

        for(std::size_t i = 0UL; i < s.size(); ++i) {
            if(s[i] != '\\' || i + 1 >= s.size())
                continue;

            switch(s[i + 1]) {
                case '\\': s.replace(i, 2, "\\"); break;
                case 'n': s.replace(i, 2, "\n"); break;
                case 't': s.replace(i, 2, "\t"); break;
                case '\'': s.replace(i, 2, "\'"); break;
                case '\"': s.replace(i, 2, "\""); break;
                case '0': s.replace(i, 2, "\0"); break;
                default: continue;
            }
        }

        return s;
    }

    inline std::string str_to_print_without_quote(char c) {
        if(c == '\0') return "\\0";
        if(c == '\n') return "\\n";
        if(c == '\t') return "\\t";
        if(c == '\'') return "\\\'";
        if(c == '\"') return "\\\"";
        if(c == '\\') return "\\\\";

        return std::string(1, c);
    } 

    inline std::string str_to_print(char c) { return '\'' + str_to_print_without_quote(c) + '\''; }

    inline std::string str_to_print(const std::string& s) {
        if(s.empty()) return "\"\"";
        if(s.size() == 1) return str_to_print(s);

        std::string res = "\"";
        for(auto c: s) res += str_to_print_without_quote(c);
        return res + "\"";
    }

    inline std::string vector_to_print(const std::vector<ObjectPtr> values) {
        std::string res;

        for(std::size_t i = 0UL; i < values.size(); i++) {
            if((values[i]->get_class() == Class::cluster_string) || (values[i]->get_class() == Class::terminal_character))
                res += str_to_print(values[i]->to_string());
            else
                res += values[i]->to_string();
            
            if(i < values.size() - 1)
                res += ", ";
        }

        return res;
    }
}

#endif /* HOIHOI_FORMATER_HPP */
