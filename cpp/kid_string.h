#pragma once

#include <utility>
#include <cassert>
#include <cstring>
#include <iostream>

namespace kid
{
    class String
    {
    public:
        String()
            : data_(new char[1])
        {
            // std::cout << "default-ctor" << std::endl;
            *data_ = '\0';
        }

        String(const char *str)
            : data_(new char[strlen(str) + 1])
        {
            // std::cout << "(const char*)-ctor" << std::endl;
            strcpy(data_, str);
        }

        String(const String &rhs)
            : data_(new char[rhs.size() + 1])
        {
            // std::cout << "copy-ctor" << std::endl;
            strcpy(data_, rhs.c_str());
        }
        /* Implement copy-ctor with delegating constructor in C++11
        String(const String& rhs)
            : String(rhs.data_)
        {
        }
        */

        ~String() noexcept
        {
            // std::cout << "dtor" << std::endl;
            delete[] data_;
        }

        /* Traditional:
        String& operator=(const String& rhs)
        {
            String(rhs).swap(*this); // copy-ctor--RAII | Non-throwing swap
            return *this;
        }// Old resources released when destructor of _ is called.
        */
        // In C++11, this is unifying assignment operator
        // the pass-by-value parameter serves as a temporary
        // http://en.wikibooks.org/wiki/More_C++_Idioms/Copy-and-swap
        String &operator=(String rhs) // yes, pass-by-value
        {
            // std::cout << "copy-assignment-operator" << std::endl;
            this->swap(rhs); // Non-throwing swap
            return *this;
        } // Old resources released when destructor of rhs is called.
        //

        // C++11 move-ctor
        String(String &&rhs) noexcept
            : data_(rhs.data_)
        {
            // std::cout << "move-ctor" << std::endl;
            rhs.data_ = nullptr;
        }

        /* Not needed if we have pass-by-value operator=() above, and it conflits.
        http://stackoverflow.com/questions/17961719/
        String& operator=(String&& rhs)
        {
            this->swap(rhs);
            return *this;
        }
        */

        // Accessors
        size_t size() const { return strlen(data_); }

        const char *c_str() const { return data_; }

        void swap(String &rhs) { std::swap(data_, rhs.data_); }

    private:
        char *data_;
    };
} // namespace kid
