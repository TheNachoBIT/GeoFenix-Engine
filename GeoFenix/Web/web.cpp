
#include "web.h"
namespace geofenix { 
    namespace web {

        size_t writeFunction(void* ptr, size_t size, size_t nmemb, std::string* data) {

            data->append((char*)ptr, size * nmemb);
            return size * nmemb;
        }

        /*
            How to use:
            std::string string;
            get("http://google.com", string);

            Returns a vector

        */
        std::string get(char const* url, std::string& response_string) {

            auto curl = curl_easy_init();
            if (curl) {
                curl_easy_setopt(curl, CURLOPT_URL, url);
                curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
                curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
                curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);

                curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);

                std::string header_string;
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
                curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);

                char* url;
                long response_code;
                double elapsed;
                curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
                curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &elapsed);
                curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &url);

                curl_easy_perform(curl);
                curl_easy_cleanup(curl);
                curl = NULL;

                return response_string;
            }
        }
        /*
        How to use:
        web::post("website.com","username=nick&password=geofenix",string);
        std::cout << string;
        */
        void post(const char* url,const char* params,std::string& string) {
            CURL* curl;
            CURLcode res;

            /* In windows, this will init the winsock stuff */
            curl_global_init(CURL_GLOBAL_ALL);

            /* get a curl handle */
            curl = curl_easy_init();
            if (curl) {
                curl_easy_setopt(curl, CURLOPT_URL, url);
                curl_easy_setopt(curl, CURLOPT_POSTFIELDS, params);
                res = curl_easy_perform(curl);
                if (res != CURLE_OK)
                    fprintf(stderr, "curl_easy_perform() failed: %s\n",
                        curl_easy_strerror(res));

                curl_easy_setopt(curl, CURLOPT_WRITEDATA, string); //escribir la data en la string

                curl_easy_cleanup(curl);
            }
        }
    }
}

