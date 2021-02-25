#include "compiler.h"
#include <Poco/StringTokenizer.h>

using Poco::StringTokenizer;

namespace tlvm {
    static std::unordered_map<std::string, KeywordToken> keywords = {
            {"proc", KeywordToken("proc", Keyword::proc)},
            {"end",  KeywordToken("end", Keyword::end)},
            {"val",  KeywordToken("val", Keyword::val)},
            {"print", KeywordToken("print", Keyword::print)}
    };

    static std::unordered_map<std::string, TypeToken> types = {
            {"i32", TypeToken("i32", type::Type::i32)},
            {"string", TypeToken("string", type::Type::string)}
    };


    static std::unordered_map<std::string, SpecifierToken> specifiers{
            {"static", SpecifierToken("static", type::Specifier::Static)},
            {"mut", SpecifierToken("mut", type::Specifier::Mutable)}
    };


    static std::unordered_map<std::string, AdvanceToken> advances{
            {"[]", AdvanceToken("[]", type::Advance::Array)}
    };

    static std::unordered_map<std::string, BinOpToken> binops{
            {"+", BinOpToken("+", BinOp::add)},
            {"-", BinOpToken("-", BinOp::sub)},
            {"*", BinOpToken("*", BinOp::mul)},
            {"/", BinOpToken("/", BinOp::div)},
            {"=", BinOpToken("=", BinOp::eq)},
    };

    std::vector<std::string> Compiler::split_into_lines(std::string&& text) {
        //Poco::trimInPlace(text);
        StringTokenizer tokenizer(text, "\n\t\r",
                                  StringTokenizer::Options::TOK_IGNORE_EMPTY |
                                  StringTokenizer::Options::TOK_TRIM);

        std::vector<std::string> return_value;
        for (const auto& token : tokenizer) {
            return_value.emplace_back(token);
        }
        return return_value;
    }

    std::vector<std::shared_ptr<Token>> Compiler::tokenize(const std::string& line) {
        StringTokenizer tokenizer(line, " ");
        std::vector<std::shared_ptr<Token>> return_value;

        for(const auto& s : tokenizer) {
            // Search for keywords
            if(keywords.find(s) != keywords.end()) {
                return_value.push_back(std::make_shared<KeywordToken>(keywords.at(s)));
                continue;
            }

            // Search for types
            if(types.find(s) != types.end()) {
                return_value.push_back(std::make_shared<TypeToken>(types.at(s)));
                continue;
            }

            // Search for specifiers
            if(specifiers.find(s) != specifiers.end()) {
                return_value.push_back(std::make_shared<SpecifierToken>(specifiers.at(s)));
                continue;
            }

            // Search for advances
            if(advances.find(s) != advances.end()) {
                return_value.push_back(std::make_shared<AdvanceToken>(advances.at(s)));
                continue;
            }

            // Search for binops
            if(binops.find(s) != binops.end()) {
                return_value.push_back(std::make_shared<BinOpToken>(binops.at(s)));
                continue;
            }

            // In other case
            // Check if this is a literal
            {
                type::Type type = type::Type::None;
                for(const char c : s) {
                    if(c == '"') {
                        type = type::Type::string;
                        break;
                    }

                    if(std::isdigit(c)) {
                        type = type::Type::i32;
                        break;
                    }
                }

                if(type != type::Type::None) {
                    return_value.push_back(std::make_shared<LiteralToken>(s, type));
                    continue;
                }
            }

            // In the last case
            return_value.push_back(std::make_shared<IdentifierToken>(s));

        }

        return return_value;
    }

    std::vector<proc::Procedure> Compiler::compile(std::string&& text) {
        std::vector<proc::Procedure> return_value;

        std::vector<TokenType> local_expected;

        auto lines = split_into_lines(std::forward<std::string>(text));
        for(const auto& line : lines) {
            for(const auto& token : tokenize(line)) {
                switch(token->type){
                    case TokenType::none:
                        break;
                    case TokenType::identifier:
                        local_expected.push_back(TokenType::none);
                        local_expected.push_back(TokenType::type);
                        local_expected.push_back(TokenType::specifier);
                        break;
                    case TokenType::keyword:
                        break;
                    case TokenType::literal:
                        break;
                    case TokenType::type:
                        break;
                    case TokenType::specifier:
                        break;
                    case TokenType::advance:
                        break;
                    case TokenType::binop:
                        break;
                }
            }
        }

        return return_value;
    }
}