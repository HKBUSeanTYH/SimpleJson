#include "JsonValue.h"

namespace {
    void parse_array(std::istreambuf_iterator<char>&, const std::istreambuf_iterator<char>&, std::vector<JsonValue>&);
    void parse_obj(std::istreambuf_iterator<char>&, const std::istreambuf_iterator<char>&, std::map<std::string, JsonValue>&);

    void skip_whitespace(std::istreambuf_iterator<char>& start, const std::istreambuf_iterator<char>& end, char& c) {
        while (start != end) {
            if (!std::isspace(*start)) {
                c = *start; 
                return;
            }
            ++start;
        }
    }

    void read_string(std::istreambuf_iterator<char>& start, const std::istreambuf_iterator<char>& end, std::string& str) {
        while (start != end) {
            char c {*start};
            ++start;
            if (c == '"') {
                return;
            } else {
                str.push_back(c);
            }
        }
        throw std::runtime_error("JSON syntax exception - Unterminated string");
    }

    void parse_numeric(std::istreambuf_iterator<char>& start, const std::istreambuf_iterator<char>& end, JsonValue& json_val) {
        std::string str{};
        bool floating_point{false};
        while (start != end) {
            char c {*start};
            if (std::isdigit(c) || c == '-' || c == 'e' || c == '+') {
                str.push_back(c);
            } else if (c == '.') {
                if (floating_point) {
                    throw std::runtime_error("JSON syntax exception - malformed value");
                }
                str.push_back(c);
                floating_point = true;
            } else if (c == ',' || std::isspace(c) || c == '}' || c == ']') {
                break;
            } else {
                throw std::runtime_error("JSON syntax exception - malformed value");
            }
            ++start;
        }
        if (floating_point) {
            json_val.data_ = std::stod(str);
        } else {
            json_val.data_ = std::stoi(str);
        }
    }

    void parse_null(std::istreambuf_iterator<char>& start, const std::istreambuf_iterator<char>& end, JsonValue& json_val) {
        std::string str{};
        for (int i = 0; i < 4 && start != end; ++i, ++start) {
            str.push_back(*start);
        }
        if (str == "null") {
            json_val.data_ = nullptr;
        } else {
            throw std::runtime_error("JSON syntax exception - malformed value");
        }
    }

    void parse_true(std::istreambuf_iterator<char>& start, const std::istreambuf_iterator<char>& end, JsonValue& json_val) {
        std::string str{};
        for (int i = 0; i < 4 && start != end; ++i, ++start) {
            str.push_back(*start);
        }
        if (str == "true") {
            json_val.data_ = true;
        } else {
            throw std::runtime_error("JSON syntax exception - malformed value");
        }
    }

    void parse_false(std::istreambuf_iterator<char>& start, const std::istreambuf_iterator<char>& end, JsonValue& json_val) {
        std::string str{};
        for (int i = 0; i < 5 && start != end; ++i, ++start) {
            str.push_back(*start);
        }
        if (str == "false") {
            json_val.data_ = false;
        } else {
            throw std::runtime_error("JSON syntax exception - malformed value");
        }
    }

    void parse_array(std::istreambuf_iterator<char>& start, const std::istreambuf_iterator<char>& end, std::vector<JsonValue>& array) {
        char c {*start};
        while (start != end) {
            skip_whitespace(start, end, c);
            JsonValue nested{};
            if (c == ']') {
                ++start;
                return;
            } else if (c == '{') {
                std::map<std::string, JsonValue> nested_map{};
                nested.data_ = nested_map;
                parse_obj(++start, end, nested_map);
                array.push_back(nested);
            } else if (c == '[') {
                std::vector<JsonValue> nested_arr{};
                nested.data_ = nested_arr;
                parse_array(start, end, nested_arr);
                array.push_back(nested);
            } else if (c == '"') {
                std::string str{};
                read_string(++start, end, str);
                nested.data_ = str;
                array.push_back(nested);
            } else if (std::isdigit(c) || c == '-' || c == '.') {
                parse_numeric(start, end, nested);
                array.push_back(nested);
            } else if (c == 'n') {
                parse_null(start, end, nested);
                array.push_back(nested);
            } else if (c == 't') {
                parse_true(start, end, nested);
                array.push_back(nested);
            } else if (c == 'f') {
                parse_false(start, end, nested);
                array.push_back(nested);
            }
            skip_whitespace(start, end, c);
            if (c == ',') {
                ++start;
                continue;
            } else if (c == ']') {
                ++start;
                return;
            } else {
                throw std::runtime_error("JSON syntax exception - malformed key-value pairs");
            }
        }
        throw std::runtime_error("JSON syntax exception - unterminated array");
    }

    void parse_obj(std::istreambuf_iterator<char>& start, const std::istreambuf_iterator<char>& end, std::map<std::string, JsonValue>& map) {
        char c {*start};
        while (start != end) {
            skip_whitespace(start, end, c);
            std::string key{};
            if (c == '}') {
                ++start;
                return;
            } else if (c == '"') {
                read_string(++start, end, key);
            } else {
                throw std::runtime_error("JSON syntax exception - expected JSON field");
            }
            skip_whitespace(start, end, c);
            if (c == ':') {
                skip_whitespace(++start, end, c);
            } else {
                throw std::runtime_error("JSON syntax exception - expected colon");
            }
            JsonValue nested{};
            if (c == '{') {
                std::map<std::string, JsonValue> nested_map{};
                nested.data_ = nested_map;
                parse_obj(++start, end, nested_map);
                map.emplace(key, nested);
            } else if (c == '[') {
                std::vector<JsonValue> nested_arr{};
                nested.data_ = nested_arr;
                parse_array(start, end, nested_arr);
                map.emplace(key, nested);
            } else if (c == '"') {
                std::string str{};
                read_string(++start, end, str);
                nested.data_ = str;
                map.emplace(key, nested);
            } else if (std::isdigit(c) || c == '-' || c == '.') {
                parse_numeric(start, end, nested);
                map.emplace(key, nested);
            } else if (c == 'n') {
                parse_null(start, end, nested);
                map.emplace(key, nested);
            } else if (c == 't') {
                parse_true(start, end, nested);
                map.emplace(key, nested);
            } else if (c == 'f') {
                parse_false(start, end, nested);
                map.emplace(key, nested);
            }
            skip_whitespace(start, end, c);
            if (c == ',') {
                ++start;
                continue;
            } else if (c == '}') {
                ++start;
                return;
            } else {
                throw std::runtime_error("JSON syntax exception - malformed key-value pairs");
            }
        }
        throw std::runtime_error("JSON syntax exception - unterminated object");
    }

    void process_stream(std::istreambuf_iterator<char>& start, const std::istreambuf_iterator<char>& end, JsonValue& json_val) {
        char c {*start};
        if (c =='{') {
            std::map<std::string, JsonValue> map{};
            parse_obj(++start, end, map);
            json_val.data_ = map;
        } else if (c == '[') {
            std::vector<JsonValue> arr{};
            parse_array(++start, end, arr);
            json_val.data_ = arr;
        } else if (c == '"') {
            std::string str{};
            read_string(++start, end, str);
            json_val.data_ = str;
        } else if (std::isdigit(c) || c == '-' || c == '.') {
            parse_numeric(start, end, json_val);
        } else if (c == 'n') {
            parse_null(start, end, json_val);
        } else if (c == 't') {
            parse_true(start, end, json_val);
        } else if (c == 'f') {
            parse_false(start, end, json_val);
        }
        skip_whitespace(start, end, c);
        if (start != end) {
            throw std::runtime_error("JSON syntax exception - malformed JSON");
        } 
    }
}

std::istream& operator>>(std::istream& is, JsonValue& json_val) {
    std::istream::sentry sentry{is};  //trims leading whitespace
    if (sentry) {
        std::istreambuf_iterator<char> start(is), end;
        process_stream(start, end, json_val);
    } else {
        is.setstate(is.rdstate() | std::ios_base::failbit);
        json_val = JsonValue{};
    }
    return is;
}

// std::ostream& operator<<(std::ostream& os, const SimpleJson::JsonValue& json_val) {

// }