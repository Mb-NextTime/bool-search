#include <search.hpp>
#include <vocab.hpp>
#include <compress.hpp>
#include <chrono>

int main(int argc, char* argv[])
{
    auto start = std::chrono::system_clock::now();

    Request::map_t term_to_doc;
    std::map<size_t, std::string> id_to_url;
    // load("data/index/term_to_doc.bin", term_to_doc);
    compress::load_ttd("data/index/term_to_doc.bin", term_to_doc);
    load("data/index/id_to_url.bin", id_to_url);

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;

    std::cout << "Loading time: " << elapsed_seconds.count() << std::endl;

    if (std::string(argv[1]) == "") {
        std::cout << "запрос пустой, используйте \nsearch \"ваш запрос\"" << std::endl;
        return 0;
    }
    Expression expr(argv[1], term_to_doc);
    std::cout << argv[1] << std::endl;
    Request::docs_t result = expr.eval().get_docs();
    if (!result.size()) {
        std::cout << "ничего не нашлось, попробуйте переформулировать запрос." << std::endl;
    }
    else {
        std::cout << result.size() << std::endl;
        for (auto x: result) {
            std::cout << id_to_url[x] << std::endl;
        }
    }
}