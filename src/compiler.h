#pragma once
#include <vector>
#include <string>
#include <memory>
#include <unordered_map>

#include "type.h"

namespace tlvm {
    enum class Keyword {
        proc,
        end,
        val,
        print,
    };

    enum class TokenType {
        identifier,
        keyword,
        literal,
        type,
        specifier,
        advance,
        binop
    };

    enum class BinOp {
        add,
        sub,
        mul,
        div,
        eq
    };

    static inline constexpr const char* ToString(TokenType type) {
        switch (type) {
            case TokenType::identifier:
                return "identifier";
                break;
            case TokenType::keyword:
                return "keyword";
                break;
            case TokenType::literal:
                return "literal";
                break;
            case TokenType::type:
                return "type";
                break;
            case TokenType::specifier:
                return "specifier";
                break;
            case TokenType::advance:
                return "advance";
                break;
            case TokenType::binop:
                return "binop";
                break;
        }
        return nullptr;
    }

    struct Token {
        Token(std::string word, TokenType type) : word(std::move(word)), type(type) {}

        std::string word{};
        TokenType type{};
    };

    struct KeywordToken : public Token {
        KeywordToken(std::string word, Keyword keyword) : Token(word, TokenType::keyword), keyword(keyword) {}
        Keyword keyword{};
    };

    struct TypeToken : public Token {
        TypeToken(std::string word, type::Type type) : Token(word, TokenType::type), type(type) {}
        type::Type type;
    };

    struct SpecifierToken : public Token {
        SpecifierToken(std::string word, type::Specifier specifier) : Token(word, TokenType::specifier),  specifier(specifier){}
        type::Specifier specifier;
    };

    struct AdvanceToken : public Token {
        AdvanceToken(std::string text, type::Advance advance) : Token(text, TokenType::advance), advance(advance) {}
        type::Advance advance;
    };

    struct BinOpToken : public Token {
        BinOpToken(std::string text, BinOp op) : Token(text, TokenType::binop), op(op) {}
        BinOp op;
    };

    struct IdentifierToken : public Token {
        IdentifierToken(std::string word) : Token(word, TokenType::identifier) {}
    };

    struct LiteralToken : public Token {
        LiteralToken(std::string word, type::Type type) : Token(word, TokenType::literal), type(type) {}
        type::Type type;
    };

    struct Compiler {
        [[nodiscard]] static std::vector<std::string> split_into_lines(std::string&& text);
        [[nodiscard]] static std::vector<std::shared_ptr<Token>> tokenize(const std::string& line);
    };
}