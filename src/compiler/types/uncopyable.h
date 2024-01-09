/*
    types that have no copy constructors available
    used in AST node types
*/

#pragma once

struct Uncopyable {
    explicit Uncopyable() = default;
    virtual ~Uncopyable() = default;
    Uncopyable(const Uncopyable&) = delete;
    auto operator=(const Uncopyable&) -> Uncopyable& = delete;
    Uncopyable(Uncopyable&&) = delete;
    auto operator=(Uncopyable &&) -> Uncopyable& = delete;
};