#pragma once
#include <string>
#include <variant>

#include "type.h"

namespace tlvm::data {
    using Data = std::variant<
            std::int32_t,
            std::string,
            // ...
            std::monostate
    >;

    struct Value {
        std::string    identifier{};
        type::TypeInfo info{};
        Data* data{};

        Value() = default;

        template<typename T>
        Value(std::string id, T&& data, type::Type type, type::Specifier spec = {}, type::Advance adv = {})
                :   identifier(std::move(id)),
                    info({type, spec, adv}),
                    data(new Data(data)) {

        }

        ~Value() {
            delete data;
        }

        Value(const Value& other) {
            ConstSwap(other);
        }

        Value& operator=(const Value& other) {
            delete data;
            identifier = other.identifier;
            info       = other.info;
            data       = new Data(*other.data);
            return *this;
        }

        Value(Value&& other) noexcept {
            Swap(other);
        }

        Value& operator=(Value&& other) noexcept {
            Swap(other);
            return *this;
        }

    private:
        void Swap(Value& other) noexcept {
            delete data;
            identifier = other.identifier;
            info       = other.info;
            data       = other.data;
            other.data = nullptr;
        }

        void ConstSwap(const Value& other) {
            delete data;
            identifier = other.identifier;
            info       = other.info;
            data       = new Data(*other.data);
        }
    };
}