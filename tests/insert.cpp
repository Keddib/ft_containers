#include "vector.hpp"
#include <vector>
#include <iostream>
#define EQUAL(x) ((x) ? (std::cout << "\033[1;32mAC\033[0m\n") : (std::cout << "\033[1;31mWA\033[0m\n"))


int main() {
{
        /*
         * strings to store the resutls
         */
        std::string str, ft_str;
        /*
         * var to store the size and the capacity
         */
        ft::vector<std::string>::size_type s, ft_s;
        ft::vector<std::string>::size_type c, ft_c;
        /*
         * bool to store the comparison
         */
        bool cond;

        /*------------------------------- test 1: empty vector ----------------------------------------*/
        // insert at the begin
        {
            std::vector<std::string> v;
            ft::vector<std::string> ft_v;
            v.insert(v.begin(), 100, "hello");
            ft_v.insert(ft_v.begin(), 100, "hello");
            ft_v.begin()->length();

            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = ((str == ft_str) && (s == ft_s) && (c == ft_c));
            std::cout << "str : " << str << '\n';
            std::cout << "s : " << s << '\n';
            std::cout << "c : " << c << '\n';
            std::cout << "ft_str : " << ft_str << '\n';
            std::cout << "ft_s : " << ft_s << '\n';
            std::cout << "ft_c : " << ft_c << '\n';
            std::cout << ((cond) ? "true" : "false") << '\n';
        }
        // insert at the end
        {
            std::vector<std::string> v;
            ft::vector<std::string> ft_v;

            v.insert(v.end(), "hello");
            ft_v.insert(ft_v.end(), "hello");
            ft_v.begin()->length();

            str.clear();
            ft_str.clear();

            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c));
            std::cout << "str : " << str << '\n';
            std::cout << "s : " << s << '\n';
            std::cout << "c : " << c << '\n';
            std::cout << "ft_str : " << ft_str << '\n';
            std::cout << "ft_s : " << ft_s << '\n';
            std::cout << "ft_c : " << ft_c << '\n';
            std::cout << ((cond) ? "true" : "false") << '\n';
        }
        // /*---------------------------------------------------------------------------------------------------*/
        // /*------------------------------- test 2: the vector capacity >= size + n ----------------------------------------*/
        {
            std::vector<std::string> v(20, "string");
            ft::vector<std::string> ft_v(20, "string");
            ft::vector<std::string>::iterator valid_it;

            v.reserve(100);
            ft_v.reserve(100);
            valid_it = ft_v.begin();
            v.insert(v.begin() + 15, 70, "hello");
            ft_v.insert(ft_v.begin() + 15, 70, "hello");

            str.clear();
            ft_str.clear();
            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c) && (&(*valid_it) == &(*ft_v.begin())));
            std::cout << "str : " << str << '\n';
            std::cout << "s : " << s << '\n';
            std::cout << "c : " << c << '\n';
            std::cout << "ft_str : " << ft_str << '\n';
            std::cout << "ft_s : " << ft_s << '\n';
            std::cout << "ft_c : " << ft_c << '\n';
            std::cout << ((cond) ? "true" : "false") << '\n';

        }
        // /*---------------------------------------------------------------------------------------------------*/
        // /*------------------------------- test 3: the vector capacity < size + n && n > size ----------------------------------------*/
        {
            std::vector<std::string> v(20, "string");
            ft::vector<std::string> ft_v(20, "string");

            v.insert(v.begin() + 10, 100, "hello");
            ft_v.insert(ft_v.begin() + 10, 100, "hello");

            str.clear();
            ft_str.clear();
            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c));
                        std::cout << "str : " << str << '\n';
            std::cout << "s : " << s << '\n';
            std::cout << "c : " << c << '\n';
            std::cout << "ft_str : " << ft_str << '\n';
            std::cout << "ft_s : " << ft_s << '\n';
            std::cout << "ft_c : " << ft_c << '\n';
            std::cout << ((cond) ? "true" : "false") << '\n';
        }
        // /*---------------------------------------------------------------------------------------------------*/
        // /*------------------------------- test 4: the vector capacity < size + n && n <= size ----------------------------------------*/
        {
            std::vector<std::string> v(20, "string");
            ft::vector<std::string> ft_v(20, "string");

            v.insert(v.begin() + 10, 15, "hello");
            ft_v.insert(ft_v.begin() + 10, 15, "hello");

            str.clear();
            ft_str.clear();
            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c));
            std::cout << "str : " << str << '\n';
            std::cout << "s : " << s << '\n';
            std::cout << "c : " << c << '\n';
            std::cout << "ft_str : " << ft_str << '\n';
            std::cout << "ft_s : " << ft_s << '\n';
            std::cout << "ft_c : " << ft_c << '\n';
            std::cout << ((cond) ? "true" : "false") << '\n';
        }
        // /*---------------------------------------------------------------------------------------------------*/
        EQUAL(cond);
    }
}






