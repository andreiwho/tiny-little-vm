#pragma once

#include <memory>
#include <queue>
#include <stack>
#include <unordered_map>

#include "type.h"
#include "data.h"

namespace tlvm::proc {
    struct Cmd {
        virtual ~Cmd() = default;

        virtual void invoke(struct Procedure*) = 0;
    };

    struct DefineValue : public Cmd {
        ~DefineValue() override = default;

        data::Value value;

        explicit DefineValue(data::Value val) : value(std::move(val)) {
        }

        void invoke(struct Procedure* proc) override;
    };

    struct PrintValue : public Cmd {
        std::string identifier;

        explicit PrintValue(std::string id) : identifier(std::move(id)) {}

        void invoke(struct Procedure* proc) override;
    };

    struct Procedure {
        Procedure() = default;

        explicit Procedure(std::string id) : identifier(std::move(id)) {}

        std::string identifier{};
        std::unordered_map<std::string, data::Value> frame{};
        std::queue<std::shared_ptr<Cmd>>             commands{};

        Procedure define_value(data::Value value);

        Procedure print(std::string id);

        void run();
    };


}