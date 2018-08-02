/*
    Copyright Elektro-Volk 2018
    EMail: elektro-volk@yandex.ru
    VK: https://vk.com/ebotp

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#pragma once
#include "common.hpp"
#include <curl/curl.h>
#include <map>
#include <thread>
#include <mutex>


class ENetException {
public:
    CURLcode errcode;

    ENetException(CURLcode code) { errcode = code; }
    const char* what() { return curl_easy_strerror(errcode); }
};

size_t curlWriteCallback(char *ptr, size_t size, size_t nmemb, void *data);
class CurlHandle {
public:
    CURL* handle;
    std::mutex lock;

    CurlHandle(CURL* handle) { this->handle = handle; }
};


class ENet {
private:
public:
    std::thread::id main_thread_id  = std::this_thread::get_id();
    std::map<std::thread::id, CurlHandle*> handles;

    ENet();
    string urlEncode(string str);
    string urlDecode(string str);
    void setup_curl(CURL *handle, string *buffer);
    string sendGet(string url);
    string sendPost(string url, std::map<string, string> params);
    string sendPost(string url, string postdata);
    void initThread();
    void closeThread();
    ~ENet();
};

extern ENet *e_net;
