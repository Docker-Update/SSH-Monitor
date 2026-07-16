#include "Includes/Webhook.h"

#include "curl/curl.h"

Webhook::Webhook(const std::string& url) : m_url(url) {}


bool Webhook::sendAlert(const std::string& username, const std::string& ip) {

    CURL * curl = curl_easy_init();

    if (!curl)
        return false;

    std::string json =
    "{"
    "\"user\":\"" + username + "\","
    "\"ip\":\"" + ip + "\""
    "}";

    struct curl_slist* headers = nullptr;

    headers = curl_slist_append(
        headers,
        "Content-Type: application/json"
    );

    curl_easy_setopt(curl, CURLOPT_URL, m_url.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json.c_str());

    CURLcode result = curl_easy_perform(curl);

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    return result == CURLE_OK;
}


