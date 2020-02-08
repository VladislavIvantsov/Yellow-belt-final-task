#pragma once

#include "date.h"
#include <string>
#include <memory>
#include <iostream>

using namespace std;

enum Comparison {
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual
};

enum LogicalOperation {
    Or,
    And
};

struct Node {
    virtual bool Evaluate(const Date &date, const string &event) const = 0;
};

struct EmptyNode : public Node {
    bool Evaluate(const Date &date, const string &event) const override;
};

struct DateComparisonNode : public Node {
private:
    Comparison _cmp;
    Date _date;
public:
    DateComparisonNode(const Comparison &cmp, const Date &date) : _cmp(cmp), _date(date) {}

    bool Evaluate(const Date &date, const string &event) const override;
};

struct EventComparisonNode : public Node {
private:
    string _event;
    Comparison _cmp;
public:
    EventComparisonNode(const Comparison &cmp, const string &event) : _event(event), _cmp(cmp) {}

    bool Evaluate(const Date &date, const string &event) const override;
};

struct LogicalOperationNode : public Node {
private:
    LogicalOperation _lop;
    shared_ptr<Node> _left, _right;
public:
    LogicalOperationNode(const LogicalOperation &lop, shared_ptr<Node> left, shared_ptr<Node> right)
            : _lop(lop),
              _left(left),
              _right(right) {}

    bool Evaluate(const Date &date, const string &event) const override;
};


