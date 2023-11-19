#ifndef PASSWORDCONTAINERPROD_EMAILSENDER_H
#define PASSWORDCONTAINERPROD_EMAILSENDER_H

#include <curl/curl.h>
#include <cstring>
#include <cstdio>
#include <string>
#include <iostream>
#include <QRandomGenerator>

#define FROM_ADDR    "passcontprod@gmail.com"
#define FROM_MAIL "Password Container " FROM_ADDR
#define TO_MAIL   "A Receiver "

class EmailSender
{
public:
    static bool SendEmail(const std::string &recipient);
    static std::string CodeGeneration();//Поменять в будущем!!!!!!!!!!!!!
    static std::string getCode();
    ~EmailSender();
private:
    static size_t payload_source(char *ptr, size_t size, size_t nmemb, void *userp);
    static const char *payload_text;
    struct upload_status {
        size_t bytes_read;
    };
    static std::string code;

};


#endif //PASSWORDCONTAINERPROD_EMAILSENDER_H
