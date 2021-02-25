#pragma once

namespace tlvm::type {
    enum class Type {
        None,
        i32,
        string
    };

    enum class Specifier {
        None,
        Static,
        Mutable
    };

    enum class Advance {
        None,               // no
        Array,              // []
    };

    struct TypeInfo {
        Type      type{};
        Specifier specifier{};
        Advance   advance{};

    };
}