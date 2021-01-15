#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <iostream>
#include <utility>
#include <deque>

namespace Debug {

    template<typename First, typename Second>
    std::ostream& operator << (std::ostream &out, std::pair<First, Second> lhs) {
        out << "(" << lhs.first << ", " << lhs.second << ")";
        return out;
    }

    template<typename Collection>
    std::string Join(const Collection &c, char d) {
        bool _isFirst = true;
        std::stringstream ss;
        for (const auto &it : c) {
            if (!_isFirst) {
                ss << d;
            }
            _isFirst = false;
            ss << it;
        }
        return ss.str();
    }

    template<typename T>
    std::ostream& operator << (std::ostream &out, std::vector<T> lhs) {
        out << '[' << Join(lhs, ',') << ']';
        return out;
    }

    template<typename Key, typename Value>
    std::ostream& operator << (std::ostream &out, std::map<Key, Value> lhs) {
        out << '{' << Join(lhs, ',') << '}';
        return out;
    }

    template<typename T>
    std::ostream& operator << (std::ostream &out, std::set<T> lhs) {
        out << '(' << Join(lhs, ',') << ')';
        return out;
    }

    template<typename Key, typename Value>
    std::ostream& operator << (std::ostream &out, std::unordered_map<Key, Value> lhs) {
        out << '{' << Join(lhs, ',') << '}';
        return out;
    }

    template<typename T>
    std::ostream& operator << (std::ostream &out, std::unordered_set<T> lhs) {
        out << '(' << Join(lhs, ',') << ')';
        return out;
    }

    template<typename T>
    std::ostream& operator << (std::ostream &out, std::deque<T> lhs) {
        out << '[' << Join(lhs, ',') << ']';
        return out;
    }

}
