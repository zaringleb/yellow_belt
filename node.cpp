#include "node.h"

EmptyNode::EmptyNode() {}

bool EmptyNode::Evaluate(const Date& date, const string& event) const {
    return true;
}

DateComparisonNode::DateComparisonNode(const Comparison& cmp, const Date& date): _cmp(cmp), _date(date) {}

bool DateComparisonNode::Evaluate(const Date& date, const string& event) const {
    switch (_cmp)
    {
    case Comparison::Less:
        return date < _date;
        break;

    case Comparison::LessOrEqual:
        return date <= _date;
        break;

    case Comparison::Greater:
        return date > _date;
        break;

    case Comparison::GreaterOrEqual:
        return date >= _date;
        break;

    case Comparison::Equal:
        return date == _date;
        break;

    case Comparison::NotEqual:
        return date != _date;
        break;
    
    default:
        throw logic_error("Unknown date comparison token");
        break;
    }
}

EventComparisonNode::EventComparisonNode(const Comparison& cmp, const string& value): _cmp(cmp), _value(value) {}

bool EventComparisonNode::Evaluate(const Date& date, const string& event) const {
    switch (_cmp)
    {
    case Comparison::Less:
        return event < _value;
        break;

    case Comparison::LessOrEqual:
        return event <= _value;
        break;

    case Comparison::Greater:
        return event > _value;
        break;

    case Comparison::GreaterOrEqual:
        return event >= _value;
        break;

    case Comparison::Equal:
        return event == _value;
        break;

    case Comparison::NotEqual:
        return event != _value;
        break;
    
    default:
        throw logic_error("Unknown event comparison token");
        break;
    }
}


LogicalOperationNode::LogicalOperationNode(const LogicalOperation& logical_operation, shared_ptr<Node> left, shared_ptr<Node> right): _logical_operation(logical_operation), _left(left), _right(right) {}

bool LogicalOperationNode::Evaluate(const Date& date, const string& event) const {
    switch (_logical_operation)
    {
    case LogicalOperation::And:
        return _left->Evaluate(date, event) && _right->Evaluate(date, event);
        break;

    case LogicalOperation::Or:
        return _left->Evaluate(date, event) || _right->Evaluate(date, event);
        break;
    
    default:
        throw logic_error("Unknown Logical Operation token");
        break;
    }
}