#pragma once

#include <optional>
#include <string>
#include <variant>

using Literal = std::variant<std::string, double>;
using OptionalLiteral = std::optional<Literal>;

std::string getLiteralString(const Literal& value);

OptionalLiteral makeOptionalLiteral(double dVal);

OptionalLiteral makeOptionalLiteral(const std::string& lexeme);