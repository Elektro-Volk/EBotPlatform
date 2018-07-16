/*
net_curlsetup.h
Copyright (C) 2018 Elektro-Volk
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
*/
#pragma once
#include <curl/curl.h>
#include <string>

class curltuner {
public:
    CURL *handle;
    std::string buffer;

    curltuner(std::string url);
    ~curltuner();
};
