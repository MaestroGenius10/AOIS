#pragma once
class BooleanExpression {
private:
    bool value;

public:
    BooleanExpression() : value(false) {}
    explicit BooleanExpression(bool value);

    BooleanExpression operator!() const;

    BooleanExpression operator&(const BooleanExpression& rhs) const;

    BooleanExpression operator+(const BooleanExpression& rhs) const;

    BooleanExpression operator>(const BooleanExpression& rhs) const;

    BooleanExpression operator=(const BooleanExpression& rhs) const;

    bool toBool() const;
};


