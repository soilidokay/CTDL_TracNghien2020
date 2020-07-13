#ifndef OUTBUF_H
#define OUTBUF_H

#include <Windows.h>
#include<streambuf>

class outbuf : public std::streambuf {
    HANDLE h;
public:
    outbuf(HANDLE h) : h(h) {}
protected:
    virtual int_type overflow(int_type c) override {
        if (c != EOF) {
            DWORD written;
            WriteConsole(h, &c, 1, &written, nullptr);
        }
        return c;
    }

    virtual std::streamsize xsputn(char_type const* s, std::streamsize count) override {
        DWORD written;
        WriteConsole(h, s, count, &written, nullptr);
        return written;
    }
};
#endif // !OUTBUF_H
