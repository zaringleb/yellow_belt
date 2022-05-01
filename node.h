#pragma once

#include <memory>
#include <iostream>
#include "date.h"


enum class Comparison {
  Less,
  LessOrEqual,
  Greater,
  GreaterOrEqual,
  Equal,
  NotEqual
};


enum class LogicalOperation {
  And,
  Or
};


class Node {
public:
    virtual bool Evaluate(const Date& date, const string& event) const = 0;
};

class EmptyNode : public Node {
public:
    EmptyNode();
    bool Evaluate(const Date& date, const string& event) const override;
};

class DateComparisonNode : public Node {
private:
    const Comparison _cmp;
    const Date _date;
public:
    DateComparisonNode(const Comparison& cmp, const Date& date);

    bool Evaluate(const Date& date, const string& event) const override;
};

class EventComparisonNode : public Node {
private:
    const Comparison _cmp;
    const string _value;
public:
    EventComparisonNode(const Comparison& cmp, const string& value);

    bool Evaluate(const Date& date, const string& event) const override;
};

class LogicalOperationNode : public Node {
private:
    const LogicalOperation _logical_operation;
    shared_ptr<const Node> _left, _right;
public:
    LogicalOperationNode(const LogicalOperation& logical_operation, shared_ptr<Node> left, shared_ptr<Node> right);

    bool Evaluate(const Date& date, const string& event) const override;
};