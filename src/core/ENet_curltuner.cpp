//std::lock_guard<std::mutex> lock(mutex);
/*
    ENet_curltuner.cpp
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
#include "ENet.hpp"
#include "ENet_curltuner.hpp"
#include <thread>

curltuner::curltuner(std::string url)
{
    handle = e_net->handles[std::this_thread::get_id()];
    e_net->setup_curl(handle, &buffer);
    curl_easy_setopt(handle, CURLOPT_URL, url.c_str());
}

curltuner::~curltuner()
{
    curl_easy_reset(handle);
}
