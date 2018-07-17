#pragma once
#include "common.hpp"
#include <curl/curl.h>
#include <unordered_map>
#include <map>
#include <thread>

class ENetException {
public:
    CURLcode errcode;

    ENetException(CURLcode code) { errcode = code; }
    const char* what() { return curl_easy_strerror(errcode); }
};

size_t curlWriteCallback(char *ptr, size_t size, size_t nmemb, void *data);

class ENet {
private:
public:
    std::thread::id main_thread_id  = std::this_thread::get_id();
    std::unordered_map<std::thread::id, CURL*> handles;

    ENet();
    string urlEncode(string str);
    string urlDecode(string str);
    void setup_curl(CURL *handle, string *buffer);
    string sendGet(string url);
    string sendPost(string url, std::map<string, string> params);
    string sendPost(string url, string postdata);
    ~ENet();
};

extern ENet *e_net;
