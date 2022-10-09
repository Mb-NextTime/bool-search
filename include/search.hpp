#pragma once

#include <iostream>
#include <set>
#include <vector>
#include <stack>
#include <string>
#include <sstream>
#include <map>
#include <unordered_map>
#include <vocab.hpp>

class Request
{
public:
    using docs_t = std::set<size_t>;
    using map_t = std::unordered_map<size_t, docs_t>;

    Request(const std::string &term, const map_t &term_to_doc)
    {
        term_ = term;
        size_t term_hash = std::hash<std::string>{}(term_);
        auto pos = term_to_doc.find(term_hash);
        if (pos == term_to_doc.end()) {
            docs_ = std::set<size_t>{};
        }
        else {
            docs_ = pos->second;
        }
    }

    Request(const std::string &term, docs_t docs)
        : term_(term)
        , docs_(docs)
    {}

    Request(const Request& req)
        : term_(req.term_)
        , docs_(req.docs_)
    {}

    Request& operator=(const Request& other)
    {
        term_ = other.term_;
        docs_ = other.docs_;
        return *this;
    }
        
    Request operator|(const Request& other) const
    {
        docs_t result_docs;
        std::set_union(docs_.begin(), docs_.end(),
                            other.docs_.begin(), other.docs_.end(),
                            std::inserter(result_docs, result_docs.begin()));
        return Request('(' + term_ + ")|" + other.term_, result_docs);
    }

    Request& operator|=(const Request& other)
    {
        Request res = *this | other;
        *this = res;
        return *this;
    }

    Request operator&(const Request& other) const
    {
        docs_t result_docs;
        std::set_intersection(docs_.begin(), docs_.end(),
                    other.docs_.begin(), other.docs_.end(),
                    std::inserter(result_docs, result_docs.begin()));
        return Request('(' + term_ + ")&" + other.term_, result_docs);
    }

    Request& operator&=(const Request& other)
    {
        Request res = *this & other;
        *this = res;
        return *this;
    }

    docs_t get_docs() const
    {
        return docs_;
    }

private:
    std::string term_;
    docs_t docs_;
};


class Expression
{
public:
    using expr_t = std::vector<std::string>;
    Expression(std::string args, Request::map_t &term_to_doc)
        : contents_()
        , ttd_(term_to_doc)
    {
        std::istringstream sstr(args);
        for (;!sstr.eof();) {
            std::string arg;
            sstr >> arg;
            while (arg.front() == '(') {
                contents_.push_back("(");
                arg.erase(arg.begin());
            }
            std::vector<std::string> closing_br;
            while (arg.back() == ')') {
                arg.pop_back();
                closing_br.push_back(")");
            }
            if (arg != "") contents_.push_back(arg);
            contents_.insert(std::end(contents_), std::begin(closing_br), std::end(closing_br));
        }
        std::reverse(contents_.begin(), contents_.end());
    }

    friend std::ostream& operator<<(std::ostream &os, const Expression &expr)
    {
        for (size_t i = 0; i < expr.contents_.size(); ++i) {
            os << "'" << expr.contents_[i] << "'" << " ";
        }
        return os;
    }

    Request eval()
    {
        Request result = expr_();
        return result;
    }

private:
    expr_t contents_;
    Request::map_t ttd_; // term_to_doc

    Request expr_();
    Request term_();
    Request parentheses_();
    Request factor_();
};


Request Expression::expr_()
{
    Request result = factor_();
    for (;;) {
        auto operation = contents_.back();
        if (operation == "|") {
            contents_.pop_back();
            result |= factor_();
        }
        else {
            return result;
        }
    }
}

Request Expression::factor_()
{
    Request result = parentheses_();
    for (;;) {
        auto operation = contents_.back();
        if (operation == "&") {
            contents_.pop_back();
            result &= parentheses_();
        }
        else {
            return result;
        }
    }
}

Request Expression::parentheses_()
{
    auto operation = contents_.back();
        if (operation == "(") {
            contents_.pop_back();
            Request result = expr_();
            auto closing_br = contents_.back();
            if (closing_br != ")") throw std::runtime_error("Unbalanced parentheses");
            contents_.pop_back();
            return result;
        }
        else {
            return term_();
        }
}

Request Expression::term_()
{
    auto term = contents_.back();
    contents_.pop_back();
    Request result(term, ttd_);
    return result;
}