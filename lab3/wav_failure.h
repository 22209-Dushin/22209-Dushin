#pragma once
#include <exception>

class wavFailure : public std::exception {
public:
    wavFailure(const char* massage) {
        m = massage;
    }
    wavFailure() {
        m = nullptr;
    }
    virtual const char* what() const noexcept{
        if(m == nullptr)
            return "Bad WAV format";
        else
            return m;
    }
private:
    const char* m;
};
