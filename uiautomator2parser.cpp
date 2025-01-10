#define _CRT_SECURE_NO_WARNINGS
#include <array>
#include <cctype>
#include <cmath>
// #include <csignal>
#include <cstdint>
#include <iostream>
#include <ostream>
#include <ranges>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string_view>
#include <vector>

#ifdef _WIN32

#define EXEC_CMD(command, mode) _popen(command, mode)
#define CLOSE_CMD(pipe) _pclose(pipe)
#else
#include <unistd.h>
#define EXEC_CMD(command, mode) popen(command, mode)
#define CLOSE_CMD(pipe) pclose(pipe)
#endif

constexpr static bool is_digit(char c)
{
    return c <= '9' && c >= '0';
}

constexpr static int32_t satoll_impl(const char *str, int32_t value = 0)
{
    return *str ? is_digit(*str) ? satoll_impl(str + 1, (*str - '0') + value * 10) : 0 : value;
}

int32_t static constexpr mystoi(std::string &&str)
{
    return satoll_impl(str.c_str());
}

static void const convert_bounds_to_array(std::string_view bounds, std::array<int32_t, 4> &bounds_array)
{
    std::array<size_t, 2> open_brackets_indices{};
    std::array<size_t, 2> closed_brackets_indices{};
    std::array<size_t, 2> comma_indices{};

    size_t index_open_brackets_indices{0};
    size_t index_closed_brackets_indices{0};
    size_t index_comma_indices{0};

    for (size_t i{}; i < bounds.size(); i++)
    {

        if (bounds[i] == '[')
            open_brackets_indices[index_open_brackets_indices++] = i;
        else if (bounds[i] == ']')
            closed_brackets_indices[index_closed_brackets_indices++] = i;
        else if (bounds[i] == ',')
            comma_indices[index_comma_indices++] = i;
    }
    std::string_view first_number{
        bounds.substr(open_brackets_indices[0] + 1, comma_indices[0] - open_brackets_indices[0] - 1)};
    std::string_view second_number{
        bounds.substr(comma_indices[0] + 1, closed_brackets_indices[0] - comma_indices[0] - 1)};
    std::string_view third_number{
        bounds.substr(open_brackets_indices[1] + 1, comma_indices[1] - open_brackets_indices[1] - 1)};
    std::string_view fourth_number{
        bounds.substr(comma_indices[1] + 1, closed_brackets_indices[1] - comma_indices[1] - 1)};
    bounds_array[0] = mystoi(std::string(first_number));
    bounds_array[1] = mystoi(std::string(second_number));
    bounds_array[2] = mystoi(std::string(third_number));
    bounds_array[3] = mystoi(std::string(fourth_number));
}

typedef struct result_struct
{
    int64_t index;
    size_t indent;
    std::string text;
    std::string resource_id;
    std::string clazz;
    std::string package;
    std::string content_desc;
    std::string checkable;
    std::string checked;
    std::string clickable;
    std::string enabled;
    std::string focusable;
    std::string focused;
    std::string scrollable;
    std::string long_clickable;
    std::string password;
    std::string selected;
    std::string visible_to_user;
    std::string bounds;
    std::string drawing_order;
    std::string hint;
    std::string display_id;
    int64_t line_index;
    std::vector<int64_t> children;
    std::vector<int64_t> parents;
    int32_t aa_center_x;
    int32_t aa_center_y;
    int32_t aa_area;
    int32_t aa_width;
    int32_t aa_height;
    int32_t aa_start_x;
    int32_t aa_start_y;
    int32_t aa_end_x;
    int32_t aa_end_y;
    int32_t aa_is_square;
    float_t aa_w_h_relation;
} result_struct;

std::string_view splitstring{R"(\r\n)"};
static bool constexpr compare2strings(const std::string_view s1, const std::string_view s2)
{
    if (s1.size() != s2.size())
    {
        return false;
    }
    auto it1 = s1.begin();
    auto it2 = s2.begin();
    while (it1 != s1.end())
    {
        if (*it1 != *it2)
        {
            return false;
        }
        it1++;
        it2++;
    }
    return true;
}
static constexpr std::array<std::string_view, 21> splitstrings_with_spaces{
    R"( index=\")",           R"( text=\")",           R"( resource-id=\")",   R"( class=\")",
    R"( package=\")",         R"( content-desc=\")",   R"( checkable=\")",     R"( checked=\")",
    R"( clickable=\")",       R"( enabled=\")",        R"( focusable=\")",     R"( focused=\")",
    R"( scrollable=\")",      R"( long-clickable=\")", R"( password=\")",      R"( selected=\")",
    R"( visible-to-user=\")", R"( bounds=\")",         R"( drawing-order=\")", R"( hint=\")",
    R"( display-id=\")",
};
static constexpr std::array<std::string_view, 21> splitstrings_without_spaces{
    R"(index=\")",           R"(text=\")",           R"(resource-id=\")",   R"(class=\")",
    R"(package=\")",         R"(content-desc=\")",   R"(checkable=\")",     R"(checked=\")",
    R"(clickable=\")",       R"(enabled=\")",        R"(focusable=\")",     R"(focused=\")",
    R"(scrollable=\")",      R"(long-clickable=\")", R"(password=\")",      R"(selected=\")",
    R"(visible-to-user=\")", R"(bounds=\")",         R"(drawing-order=\")", R"(hint=\")",
    R"(display-id=\")",
};
static constexpr std::string_view delim_csv{"\",\""};
static constexpr std::string_view true_string{"true"};
static constexpr std::string_view sv_index{R"(index=\")"};
static constexpr std::string_view sv_text{R"(text=\")"};
static constexpr std::string_view sv_resource_id{R"(resource-id=\")"};
static constexpr std::string_view sv_class{R"(class=\")"};
static constexpr std::string_view sv_package{R"(package=\")"};
static constexpr std::string_view sv_content_desc{R"(content-desc=\")"};
static constexpr std::string_view sv_checkable{R"(checkable=\")"};
static constexpr std::string_view sv_checked{R"(checked=\")"};
static constexpr std::string_view sv_clickable{R"(clickable=\")"};
static constexpr std::string_view sv_enabled{R"(enabled=\")"};
static constexpr std::string_view sv_focusable{R"(focusable=\")"};
static constexpr std::string_view sv_focused{R"(focused=\")"};
static constexpr std::string_view sv_scrollable{R"(scrollable=\")"};
static constexpr std::string_view sv_long_clickable{R"(long-clickable=\")"};
static constexpr std::string_view sv_password{R"(password=\")"};
static constexpr std::string_view sv_selected{R"(selected=\")"};
static constexpr std::string_view sv_visible_to_user{R"(visible-to-user=\")"};
static constexpr std::string_view sv_bounds{R"(bounds=\")"};
static constexpr std::string_view sv_drawing_order{R"(drawing-order=\")"};
static constexpr std::string_view sv_hint{R"(hint=\")"};
static constexpr std::string_view sv_display_id{R"(display-id=\")"};
bool static constexpr is_rect_in_rect(const std::array<int64_t, 4> &rect1, const std::array<int64_t, 4> &rect2)
{

    return (rect1[0] >= rect2[0] && rect1[1] >= rect2[1] && rect1[2] <= rect2[2] && rect1[3] <= rect2[3]);
}
static constexpr void clear_struct(result_struct &rs)
{
    rs.index = 0;
    rs.indent = 0;
    rs.text.clear();
    rs.resource_id.clear();
    rs.clazz.clear();
    rs.package.clear();
    rs.content_desc.clear();
    rs.checkable.clear();
    rs.checked.clear();
    rs.clickable.clear();
    rs.enabled.clear();
    rs.focusable.clear();
    rs.focused.clear();
    rs.scrollable.clear();
    rs.long_clickable.clear();
    rs.password.clear();
    rs.selected.clear();
    rs.visible_to_user.clear();
    rs.bounds.clear();
    rs.drawing_order.clear();
    rs.hint.clear();
    rs.display_id.clear();
    rs.aa_center_x = 0;
    rs.aa_center_y = 0;
    rs.aa_area = 0;
    rs.aa_width = 0;
    rs.aa_height = 0;
    rs.aa_start_x = 0;
    rs.aa_start_y = 0;
    rs.aa_end_x = 0;
    rs.aa_end_y = 0;
    rs.aa_is_square = 0;
    rs.aa_w_h_relation = 0;
}

std::string static vector_to_string(std::vector<int64_t> &vec)
{
    if (vec.empty())
    {
        return "()";
    }
    std::string result;
    result.reserve(vec.size() * 3 + 2);
    result += '(';
    for (const auto &str : vec)
    {
        result += std::to_string(str) + ',';
    }
    result += ')';
    return result;
}

char static constexpr bool2int(const std::string_view str)
{
    if (str.size() == 4 && compare2strings(str, true_string))
    {
        return '1';
    }
    return '0';
}

static std::string dump_struct_vector_as_csv(std::vector<result_struct> &v)
{
    std::string outputstring;
    outputstring.reserve(v.size() * 256);
    for (result_struct &it : v)
    {
        outputstring += '"';
        outputstring.append(std::to_string(it.index));
        outputstring.append(delim_csv);
        outputstring.append(std::to_string(it.indent));
        outputstring.append(delim_csv);
        outputstring.append((it.text));
        outputstring.append(delim_csv);
        outputstring.append((it.resource_id));
        outputstring.append(delim_csv);
        outputstring.append((it.clazz));
        outputstring.append(delim_csv);
        outputstring.append((it.package));
        outputstring.append(delim_csv);
        /////////////////////////////
        outputstring += (bool2int(it.content_desc));
        outputstring.append(delim_csv);
        outputstring += (bool2int(it.checkable));
        outputstring.append(delim_csv);
        outputstring += (bool2int(it.checked));
        outputstring.append(delim_csv);
        outputstring += (bool2int(it.clickable));
        outputstring.append(delim_csv);
        outputstring += (bool2int(it.enabled));
        outputstring.append(delim_csv);
        outputstring += (bool2int(it.focusable));
        outputstring.append(delim_csv);
        outputstring += (bool2int(it.focused));
        outputstring.append(delim_csv);
        outputstring += (bool2int(it.scrollable));
        outputstring.append(delim_csv);
        outputstring += (bool2int(it.long_clickable));
        outputstring.append(delim_csv);
        outputstring += (bool2int(it.password));
        outputstring.append(delim_csv);
        outputstring += (bool2int(it.selected));
        outputstring.append(delim_csv);
        outputstring += (bool2int(it.visible_to_user));
        /////////////////////////////
        outputstring.append(delim_csv);
        outputstring.append((it.bounds));

        outputstring.append(delim_csv);
        outputstring.append((it.drawing_order));
        outputstring.append(delim_csv);
        outputstring.append((it.hint));
        outputstring.append(delim_csv);
        outputstring.append((it.display_id));
        outputstring.append(delim_csv);
        outputstring.append(std::to_string(it.line_index));
        outputstring.append(delim_csv);
        outputstring.append(std::to_string(it.line_index));
        outputstring.append(delim_csv);
        outputstring.append(vector_to_string(it.children));
        outputstring.append(delim_csv);
        outputstring.append(vector_to_string(it.parents));
        outputstring.append(delim_csv);
        outputstring.append(std::to_string(it.aa_start_x));
        outputstring.append(delim_csv);
        outputstring.append(std::to_string(it.aa_start_y));
        outputstring.append(delim_csv);
        outputstring.append(std::to_string(it.aa_end_x));
        outputstring.append(delim_csv);
        outputstring.append(std::to_string(it.aa_end_y));
        outputstring.append(delim_csv);
        outputstring.append(std::to_string(it.aa_center_x));
        outputstring.append(delim_csv);
        outputstring.append(std::to_string(it.aa_center_y));
        outputstring.append(delim_csv);
        outputstring.append(std::to_string(it.aa_width));
        outputstring.append(delim_csv);
        outputstring.append(std::to_string(it.aa_height));
        outputstring.append(delim_csv);
        outputstring.append(std::to_string(it.aa_area));
        outputstring.append(delim_csv);
        outputstring.append(std::to_string(it.aa_w_h_relation));
        outputstring.append(delim_csv);
        outputstring += '"';
        outputstring += '\n';
    }
    return outputstring;
}

int main(int argc, char *argv[])

{
    std::string s;
    s.reserve(81920);
    std::string cmd2execute;
    if (argc > 1)
    {
        cmd2execute = argv[1];
    }
    else
    {
        cmd2execute = "curl -X POST -d '{\"jsonrpc\": \"2.0\", \"id\": \"1\", \"method\": \"dumpWindowHierarchy\", "
                      "\"params\": [true, 10000]}' 'http://127.0.0.1:9008/jsonrpc/0' 2>/dev/null";
    }
    FILE *fp{EXEC_CMD(cmd2execute.c_str(), "r")};
    if (fp == NULL)
    {
        std::cerr << "Failed to run command: " << cmd2execute << std::endl;
        exit(EXIT_FAILURE);
    }
    static constexpr size_t buffersize{32};
    char buffer[buffersize]{};
    while (fgets(buffer, buffersize, fp) != NULL)
    {
        for (size_t i{}; i < buffersize; i++)
        {
            if (buffer[i] == '\0')
            {
                continue;
            }
            s += buffer[i];
            buffer[i] = '\0';
        }
    }
    CLOSE_CMD(fp);
    auto strs2 = s | std::views::split(splitstring);
    result_struct rs{};
    std::array<int32_t, 4> bounds_array{};
    std::vector<result_struct> line_resultvec;
    size_t resultvecsize{0};
    bool found_bounds{false};
    for (const auto &ref : strs2)
    {
        resultvecsize += 1;
    }
    line_resultvec.reserve(resultvecsize);
    int64_t line_index{};
    for (const auto &ref : strs2)
    {
        std::string st{ref.begin(), ref.end()};
        std::size_t indent{st.find_first_not_of(" \t\n\r\v\f")};
        for (const std::string_view &sv : splitstrings_with_spaces)
        {
            size_t foundstring{st.find(sv)};
            if (foundstring != std::string::npos)
            {
                st[foundstring] = '\n';
            }
        }

        auto strs3 = st | std::views::split('\n');
        clear_struct(rs);
        rs.indent = indent;
        found_bounds = false;

        for (const auto &ref2 : strs3)
        {
            std::string st2{ref2.begin(), ref2.end()};
            for (const std::string_view &sv2 : splitstrings_without_spaces)
            {
                size_t foundstring{st2.find(sv2)};
                if (foundstring != 0)
                {
                    continue;
                }
                size_t index_last_quote{st2.find_last_of("\"")};
                if (index_last_quote != std::string::npos && foundstring > 0)
                {
                    index_last_quote = index_last_quote - 1;
                }
                size_t start_substring{sv2.size()};
                size_t size_of_substring{index_last_quote - start_substring - 1};

                if (compare2strings(sv2, sv_index))
                {
                    rs.index = mystoi(st2.substr(start_substring, size_of_substring));
                    continue;
                }
                else if (compare2strings(sv2, sv_text))
                {
                    rs.text.append(st2.substr(start_substring, size_of_substring));
                    continue;
                }
                else if (compare2strings(sv2, sv_resource_id))
                {
                    rs.resource_id.append(st2.substr(start_substring, size_of_substring));
                    continue;
                }
                else if (compare2strings(sv2, sv_class))
                {
                    rs.clazz.append(st2.substr(start_substring, size_of_substring));
                    continue;
                }
                else if (compare2strings(sv2, sv_package))
                {
                    rs.package.append(st2.substr(start_substring, size_of_substring));
                    continue;
                }
                else if (compare2strings(sv2, sv_content_desc))
                {
                    rs.content_desc.append(st2.substr(start_substring, size_of_substring));
                    continue;
                }
                else if (compare2strings(sv2, sv_checkable))
                {
                    rs.checkable.append(st2.substr(start_substring, size_of_substring));
                    continue;
                }
                else if (compare2strings(sv2, sv_checked))
                {
                    rs.checked.append(st2.substr(start_substring, size_of_substring));
                    continue;
                }
                else if (compare2strings(sv2, sv_clickable))
                {
                    rs.clickable.append(st2.substr(start_substring, size_of_substring));
                    continue;
                }
                else if (compare2strings(sv2, sv_enabled))
                {
                    rs.enabled.append(st2.substr(start_substring, size_of_substring));
                    continue;
                }
                else if (compare2strings(sv2, sv_focusable))
                {
                    rs.focusable.append(st2.substr(start_substring, size_of_substring));
                    continue;
                }
                else if (compare2strings(sv2, sv_focused))
                {
                    rs.focused.append(st2.substr(start_substring, size_of_substring));
                    continue;
                }
                else if (compare2strings(sv2, sv_scrollable))
                {
                    rs.scrollable.append(st2.substr(start_substring, size_of_substring));
                    continue;
                }
                else if (compare2strings(sv2, sv_long_clickable))
                {
                    rs.long_clickable.append(st2.substr(start_substring, size_of_substring));
                    continue;
                }
                else if (compare2strings(sv2, sv_password))
                {
                    rs.password.append(st2.substr(start_substring, size_of_substring));
                    continue;
                }
                else if (compare2strings(sv2, sv_selected))
                {
                    rs.selected.append(st2.substr(start_substring, size_of_substring));
                    continue;
                }
                else if (compare2strings(sv2, sv_visible_to_user))
                {
                    rs.visible_to_user.append(st2.substr(start_substring, size_of_substring));
                    continue;
                }
                else if (compare2strings(sv2, sv_bounds))
                {
                    rs.bounds.append(st2.substr(start_substring, size_of_substring));
                    found_bounds = true;
                    bounds_array[0] = 0;
                    bounds_array[1] = 0;
                    bounds_array[2] = 0;
                    bounds_array[3] = 0;
                    convert_bounds_to_array(rs.bounds, bounds_array);
                    rs.aa_start_x = bounds_array[0];
                    rs.aa_start_y = bounds_array[1];
                    rs.aa_end_x = bounds_array[2];
                    rs.aa_end_y = bounds_array[3];
                    rs.aa_center_y = (rs.aa_start_y + rs.aa_end_y) / 2;
                    rs.aa_area = (rs.aa_end_x - rs.aa_start_x) * (rs.aa_end_y - rs.aa_start_y);
                    rs.aa_width = rs.aa_end_x - rs.aa_start_x;
                    rs.aa_height = rs.aa_end_y - rs.aa_start_y;
                    rs.aa_center_x = (rs.aa_start_x + rs.aa_end_x) / 2;
                    rs.aa_is_square = (rs.aa_width == rs.aa_height);
                    if (rs.aa_height > 0)
                    {
                        rs.aa_w_h_relation = (float_t)rs.aa_width / rs.aa_height;
                    }
                    continue;
                }
                else if (compare2strings(sv2, sv_drawing_order))
                {
                    rs.drawing_order.append(st2.substr(start_substring, size_of_substring));
                    continue;
                }
                else if (compare2strings(sv2, sv_hint))
                {
                    rs.hint.append(st2.substr(start_substring, size_of_substring));
                    continue;
                }
                else if (compare2strings(sv2, sv_display_id))
                {
                    rs.display_id.append(st2.substr(start_substring, size_of_substring));
                    continue;
                }
            }
        }

        if (found_bounds)
        {
            rs.line_index = line_index;
            line_resultvec.emplace_back(rs);
            line_resultvec.back().children.reserve(resultvecsize);
            line_resultvec.back().parents.reserve(resultvecsize);
            line_index++;
        }
    }
    std::array<int64_t, 4> rect1{0, 0, 0, 0};
    std::array<int64_t, 4> rect2{0, 0, 0, 0};
    for (size_t i{}; i < line_resultvec.size(); i++)
    {

        rect1[0] = line_resultvec[i].aa_start_x;
        rect1[1] = line_resultvec[i].aa_start_y;
        rect1[2] = line_resultvec[i].aa_end_x;
        rect1[3] = line_resultvec[i].aa_end_y;
        for (size_t j{}; j < line_resultvec.size(); j++)
        {
            if (j == i)
            {
                continue;
            }
            rect2[0] = line_resultvec[j].aa_start_x;
            rect2[1] = line_resultvec[j].aa_start_y;
            rect2[2] = line_resultvec[j].aa_end_x;
            rect2[3] = line_resultvec[j].aa_end_y;
            if (is_rect_in_rect(rect1, rect2))
            {
                line_resultvec[i].parents.emplace_back(line_resultvec[j].line_index);
                line_resultvec[j].children.emplace_back(line_resultvec[i].line_index);
            }
        }
    }
    std::cout << dump_struct_vector_as_csv(line_resultvec);
    return EXIT_SUCCESS;
}
