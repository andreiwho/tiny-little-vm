set CONAN_USER_HOME=%cd%
conan install . -s build_type=Debug -if conan -b spdlog -b fmt -b poco --build=missing