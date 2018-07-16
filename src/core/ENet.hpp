#pragma once
#include <curl/curl.h>
#include <unordered_map>
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
    void setup_curl(CURL *handle, std::string *buffer);
    std::string sendGet(std::string url);
    ~ENet();
  /*void init();
  void setup_curl(CURL *handle, string *buffer);
  size_t _curlWriteCallback(char *ptr, size_t size, size_t nmemb, void *data);
  string makeFields(map<string, string> &fields);
  string GET(string url);
  string POST(string url, const char* data);
  string POST(string url, map<string, string> &fields);*/
};

extern ENet *e_net;
