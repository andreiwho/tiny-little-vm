#include <utility>
#include <vector>

#include "data.h"

#include "proc.h"

#include "compiler.h"

#include <spdlog/spdlog.h>

namespace tlvm {
    struct Vm {
        // Replace with std::unordered_map
        std::unordered_map<std::string, proc::Procedure> app;

        void define_proc(proc::Procedure proc) {
            if (app.find(proc.identifier) != app.end()) {
                throw std::runtime_error(fmt::format("Failed to create procedure '{}'. It already exists.", proc.identifier));
            } else {
                app[proc.identifier] = std::move(proc);
            }
        }

        void run() {
            if (app.find("main") != app.end()) {
                app.at("main").run();
            }
        }
    };
}

[[maybe_unused]]
static constexpr const char* script = R"script(
    proc main
        val i i32 = 5
    end
)script";

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    using namespace tlvm;
    using namespace data;
    using namespace proc;
    using namespace type;

    try {
        auto lines = Compiler::split_into_lines(script);

        for (const auto& line : lines) {
            spdlog::info("------------line-----------------");
            for (const auto& token : Compiler::tokenize(line)) {
                spdlog::info("Token: '{}' {}", token->word, ToString(token->type));
            }
            spdlog::info("---------------------------------");
        }


        tlvm::Vm vm;
        vm.define_proc(Procedure()
                               .set_id("main")
                               .define_value(Value("i", 5, Type::i32))
                               .define_value(Value("hello_str", "Hello, world!", Type::string))
                               .print("i")
                               .print("hello_str"));
        vm.run();
    } catch (const std::exception& e) {
        spdlog::critical("TLVM EXCEPTION: {}", e.what());
        return -1;
    }
    return 0;
}