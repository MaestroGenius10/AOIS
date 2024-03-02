#include "BooleanExpression.h"

BooleanExpression::BooleanExpression(bool value) : value(value) {}

BooleanExpression BooleanExpression::operator!() const {
    return BooleanExpression(!value);
}

BooleanExpression BooleanExpression::operator&(const BooleanExpression& rhs) const {
    return BooleanExpression(value && rhs.value);
}

BooleanExpression BooleanExpression::operator+(const BooleanExpression& rhs) const {
    return BooleanExpression(value || rhs.value);
}

BooleanExpression BooleanExpression::operator>(const BooleanExpression& rhs) const {
    return BooleanExpression(!value || rhs.value);
}

BooleanExpression BooleanExpression::operator=(const BooleanExpression& rhs) const {
    return BooleanExpression((value && rhs.value) || (!value && !rhs.value));
}

bool BooleanExpression::toBool() const {
    return value;
}
