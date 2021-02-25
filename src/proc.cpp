#include "proc.h"
#include "type.h"
#include <iostream>
#include <stdexcept>

#include <fmt/format.h>

namespace tlvm::proc {

    // -----------------------------------------
    Procedure Procedure::define_value(data::Value value) {
        commands.emplace(std::make_shared<DefineValue>(std::move(value)));
        return *this;
    }

    // -----------------------------------------
    void Procedure::run() {
        while (!commands.empty()) {
            auto& cmd = commands.front();
            cmd->invoke(this);
            commands.pop();
        }
    }

    Procedure Procedure::print(std::string id) {
        commands.emplace(std::make_shared<PrintValue>(std::move(id)));
        return *this;
    }

    // -----------------------------------------
    void DefineValue::invoke(struct Procedure* proc) {
        if(proc->frame.find(value.identifier) != proc->frame.end()) {
            throw std::runtime_error(fmt::format("Value redefinition: {0}. '{0}' already exists!", value.identifier));
        } else {
            proc->frame[value.identifier] = value;
        }
    }

    void PrintValue::invoke(struct Procedure* proc) {
        if(proc->frame.find(identifier) != proc->frame.end()) {
            auto& val = proc->frame.at(identifier);
            switch (val.info.type) {
                case type::Type::i32:
                    std::cout << std::get<std::int32_t>(*val.data) << '\n';
                    break;
                case type::Type::string:
                    std::cout << std::get<std::string>(*val.data) << '\n';
                    break;
                case type::Type::None:
                    throw std::runtime_error("Missing type");
                    break;
            }
        }
    }
}