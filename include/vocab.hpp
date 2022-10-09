#pragma once
#include <boost/algorithm/string.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/unordered_map.hpp>
#include <boost/serialization/set.hpp>
#include <string>
#include <vector>
#include <fstream>
#include <set>

template <class T>
void save(const std::string &filename, const T &obj)
{
  std::ofstream file{filename};
  boost::archive::binary_oarchive oa{file};
  oa << obj;
}

template <class T>
void load(const std::string &filename, T &obj)
{
  std::ifstream file{filename};
  boost::archive::binary_iarchive ia{file};
  ia >> obj;
}


std::vector<std::string> tokenize(std::string filename)
{
    std::ifstream f(filename);
    if (!f) throw std::runtime_error("File " + filename + " opening failed");
    std::vector<std::string> tokens;
    while(!f.eof()) {
        std::string token;
        f >> token;
        tokens.push_back(token);
    }
    f.close();
    return tokens;
}

std::set<size_t> to_hash(std::vector<std::string> tokens)
{
    std::set<size_t> hashes;
    for (auto t: tokens) {
        if (t.size()) hashes.insert(std::hash<std::string>{}(t));
    }
    return hashes;
}
