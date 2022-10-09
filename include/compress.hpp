#pragma once

#include <fstream>
#include <iostream>
#include <search.hpp>
#include <bitset>
#include <vocab.hpp>

namespace compress 
{

using itu_t = std::map<size_t, std::string>;
using ttd_t = Request::map_t;

namespace 
{

const uint8_t end_flag = 0b10000000;

void save_num(std::ofstream &os, size_t num)
{
    int num_len = 0;
    char buf[10];
    for (; num >= 128; num /= 128) {
        const uint8_t byte = num  & (~end_flag);
        buf[num_len++] = byte;
    }
    num &= ~end_flag;
    buf[num_len] = num;
    buf[0] |= end_flag;
    char write_buf[10];

    for (int i = num_len; i >= 0; --i) {
        write_buf[num_len - i] = buf[i];
        // std::bitset<8> b(buf[i]);
        // std::cout << "writing " << b << std::endl;
    }
    os.write(write_buf, num_len + 1);
}

void save_set(std::ofstream &os, const Request::docs_t docs)
{
    size_t size = docs.size();
    save_num(os, size);
    for (auto val: docs) {
        save_num(os, val);
    }
}

} // anon namespace


void save_ttd(const std::string &filename, ttd_t &ttd)
{
    std::ofstream fout(filename, std::ios::binary | std::ios::out | std::ios::trunc);
    size_t size = ttd.size();
    save_num(fout, size);
    for (auto kval: ttd) {
        save_num(fout, kval.first);
        save_set(fout, kval.second);
    }
}

namespace
{

size_t load_num(std::ifstream &os)
{
    size_t num = 0;
    char byte = 0;
    while(!os.eof() && os.read(&byte, 1)) {
        // std::cout << "reading..." << std::endl;
        // std::bitset<8> bt(byte);
        // std::cout << bt << std::endl;
        num <<= 7;
        num |= char(byte & (~end_flag));
        // std::bitset<64> b(num);
        // std::cout << b << std::endl;
        if (byte & end_flag) {
            break;
        }
    }

    return num;
}

Request::docs_t load_set(std::ifstream &os)
{
    Request::docs_t doc;
    size_t size = load_num(os);
    for (size_t i = 0; i < size; ++i) {
        doc.insert(load_num(os));
    }
    return doc;
}

} // anon namespace

void load_ttd(const std::string &filename, ttd_t &ttd)
{
    std::ifstream fin(filename, std::ios::binary | std::ios::in);
    size_t size = load_num(fin);
    for (size_t i = 0; i < size; ++i) {
        size_t doc_id = load_num(fin);
        Request::docs_t doc = load_set(fin);
        ttd[doc_id] = doc;
    }
}

} // compress namespace