#include "node.h"

using namespace std;

bool EmptyNode::Evaluate(const Date &date, const string &event) const {
return true;
}

bool DateComparisonNode::Evaluate(const Date &date, const string &event) const {
    if (_cmp == Comparison::Less) {
        return date < _date;
    } else if (_cmp == Comparison::LessOrEqual) {
        return (date < _date) || !((date < _date) || (_date < date));
    } else if (_cmp == Comparison::Greater) {
        return !(date < _date) && ((date < _date) || (_date < date));
    } else if (_cmp == Comparison::GreaterOrEqual) {
        return !(date < _date);
    } else if (_cmp == Comparison::Equal) {
        return !((date < _date) || (_date < date));
    }
    return (date < _date) || (_date < date);
}

bool EventComparisonNode::Evaluate(const Date &date, const string &event) const {
    bool res;
    if (_cmp == Comparison::Less) {
        return event < _event;
    } else if (_cmp == Comparison::LessOrEqual) {
        return event <= _event;
    } else if (_cmp == Comparison::Greater) {
        return event > _event;
    } else if (_cmp == Comparison::GreaterOrEqual) {
        return event >= _event;
    } else if (_cmp == Comparison::Equal) {
        return event == _event;
    }
    return event != _event;
}

bool LogicalOperationNode::Evaluate(const Date &date, const string &event) const {
    if (_lop == LogicalOperation::Or) {
        return _left->Evaluate(date, event) || _right->Evaluate(date, event);
    }
    return _left->Evaluate(date, event) && _right->Evaluate(date, event);
}
