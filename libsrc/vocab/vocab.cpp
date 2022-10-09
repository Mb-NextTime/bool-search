#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <chrono>

#include <vocab.hpp>
#include <search.hpp>
#include <compress.hpp>

static const bool DEBUG = false;

int main(int argc, char* argv[])
{
    Request::map_t term_to_doc;
    std::map<size_t, std::string> id_to_url;
    for (int i = 1; i < argc; ++i) {
        try {
            std::string filename = argv[i];
            std::vector<std::string> tokens = tokenize(filename);
            std::replace(filename.begin(), filename.end(), '|', '/');
            size_t doc_id = std::hash<std::string>{}(filename);
            id_to_url[doc_id] = filename;
            for (auto x: tokens) {
            }
            std::set<size_t> hashes = to_hash(tokens);
            for (auto x: hashes) {
                term_to_doc[x].insert(doc_id);
            }
        }
        catch (const std::runtime_error &e) {
            std::cerr << e.what() << std::endl;
        }
    }

    if (DEBUG) {
        auto start = std::chrono::system_clock::now();
        // save("../index/term_to_doc.bin", term_to_doc);                  // boost::archive
        compress::save_ttd("../index/term_to_doc.bin", term_to_doc);    // varbyte
        save("../index/id_to_url.bin", id_to_url);
        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        std::cout << "Serializing time: " << elapsed_seconds.count() << std::endl;
    }
    else {
        // save("../index/term_to_doc.bin", term_to_doc);                  // boost::archive
        compress::save_ttd("../index/term_to_doc.bin", term_to_doc);    // varbyte
        save("../index/id_to_url.bin", id_to_url);
    }
}