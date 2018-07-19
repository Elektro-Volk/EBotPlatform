#pragma once
#include "common.hpp"

class ELuaError {
private:
    string error_msg;
public:
    ELuaError (string str) { error_msg = str; }
    string what () { return error_msg; }
    ~ELuaError() {}
};
