#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <filesystem>
#include <algorithm>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <chrono>
#include <thread>
#include <workez.hpp>

namespace fs = std::filesystem;
using json = nlohmann::json;

size_t wClBk(U0* cnt, size_t sz, size_t nmemb, std::string* userp){
    userp->append(static_cast<I8*>(cnt), sz*nmemb);
    return sz*nmemb;
}

std::string ccp(const fs::path& act){
    std::stringstream ss;
    //if there are anymore extension, put it right here
    std::vector<std::string> exts = {".cpp", ".cc", ".cxx", ".c", ".h", ".hpp", ".py", ".js", ".ts", ".hs", ".rs"};
    std::vector<std::string> esp_arc = {"CMakeLists.txt", "Makefile", "package.json"};
    std::vector<std::string> gnore = {".git", "build", "cmake-build-debug", "bin", "obj", "node_modules", ".vscode", ".target", ".mcfg"};
    for(auto it = fs::recursive_directory_iterator(act); it != fs::recursive_directory_iterator(); ++it){
        std::string nm = it->path().filename().string();
        if (it->is_directory()) {
            if (std::find(gnore.begin(), gnore.end(), nm) != gnore.end()) {
                it.disable_recursion_pending();
            }
            continue;
        }
        if (it->is_regular_file()) {
            std::string ext = it->path().extension().string();
            bool vld = std::find(exts.begin(), exts.end(), ext) != exts.end() || std::find(esp_arc.begin(), esp_arc.end(), nm) != esp_arc.end();
            if(vld){
                std::ifstream arq(it->path());
                if (arq.is_open()) {
                    ss << "\n---Archive: " << it->path().string() << "---\n";
                    ss << arq.rdbuf();
                }
            }
        }
    }
    return ss.str();
}

std::string rdfl(const fs::path& act){
    if (!fs::exists(act) || !fs::is_regular_file(act)) {
        throw "INVALID FILE";
        return "";
    }
    std::ifstream arq(act);
    if (arq.is_open()) {
        throw "Coudn't open the file";
        return "";
    }
    std::stringstream ss;
    ss << "---Archive: " << act.string() << "---\n";
    ss << arq.rdbuf();
    return ss.str();
}

U0 api(I32 mode, I8** arg){
    auto call = [&](std::string code){
        const I8* envk = std::getenv("GEMINI_API_KEY");
        if (!envk) {
            throw "Doesn't have the API key";
        }
        std::string apik = envk;
        if(code.empty()){
            throw "nothing found";
        }
        //if you want other idiom, switch it here
        std::string api_call = "Write an professional README and beatiful in english\n"
                                "May have: Title, description, folder structure (But don't say about any README on folder structure), how to compile, how to use and dependencies\n"
                                "code: " + code;
        json payload = {
            {"contents", {{
                {"parts",{{
                    {"text", api_call}
                }}}
            }}}
        };
        std::string bck = payload.dump();
        std::string url = "https://generativelanguage.googleapis.com/v1beta/models/gemini-3.5-flash-lite:generateContent";
        CURL* cl = curl_easy_init();
        if (!cl) {
            std::this_thread::sleep_for(std::chrono::seconds(5));
        }
        std::string resp;
        I8 er_buff[CURL_ERROR_SIZE] = {};
        if (cl) {
            curl_slist* hrds = nullptr;
            hrds = curl_slist_append(hrds, "Content-Type: application/json");

            std::string ahrds = "x-goog-api-key: "+apik;
            hrds = curl_slist_append(hrds, ahrds.c_str());

            curl_easy_setopt(cl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(cl, CURLOPT_HTTPHEADER, hrds);
            curl_easy_setopt(cl, CURLOPT_POSTFIELDS, bck.c_str());
            curl_easy_setopt(cl, CURLOPT_WRITEFUNCTION, wClBk);
            curl_easy_setopt(cl, CURLOPT_WRITEDATA, &resp);

            curl_easy_setopt(cl, CURLOPT_ERRORBUFFER, er_buff);
            curl_easy_setopt(cl, CURLOPT_CONNECTTIMEOUT, 15L);
            curl_easy_setopt(cl, CURLOPT_TIMEOUT, 120L);
            curl_easy_setopt(cl, CURLOPT_NOSIGNAL, 1L);

            CURLcode rs = curl_easy_perform(cl);

            if (rs == CURLE_OK) {
                try {
                    auto resp_j = json::parse(resp);
                    if(resp_j.contains("error")){
                        std::cerr << "API ERROR: " << resp_j["error"]["message"] << '\n';
                    }
                    else{
                        std::string rme = resp_j["candidates"][0]["content"]["parts"][0]["text"];
                        std::ofstream out("README.md");
                        out << rme;
                        out.close();
                    }
                } catch (const std::exception& e) {
                    std::cerr<<"ERROR: "<<e.what();
                }
            }
            else{
                std::cerr << "HTTP FAILURE: " << curl_easy_strerror(rs) << "\n";
            }
            curl_slist_free_all(hrds);
            curl_easy_cleanup(cl);
        }
    };
    if (mode == 3 && strncmp(arg[2], "local", 5) == 0) {
        call(ccp("."));
    }
    else if (mode == 4 && strncmp(arg[2], "file", 4) == 0) {
        try {
            std::string fl = rdfl(arg[3]);
            call(fl);
        } catch (std::string msg) {
            std::cerr<<msg;
        }
    }
}

I32 main(I32 argc, I8** argv){
    auto argn = [&](){
        //api says to use the api readme gen, local says to use the whole directory and file says to use just one file
        if (strncmp(argv[1], "api", 3) == 0) {
            api(argc, argv);
            return;
        }
        else if (strncmp(argv[1], "raw", 3) == 0) {
            return;
        }
        throw "unknown argument";
    };
    if (argc == 4 || argc == 3) {
        try {
            argn();
        } catch (const I8* msg) {
            std::cout<<msg;
            return 418;
        }
        
    }
    else {
        return 418;
    }
    return 0;
}