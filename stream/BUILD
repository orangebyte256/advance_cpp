first = glob(["*.hpp"]);
second = glob(["functions/*.hpp"]);

cc_library(
    name = "stream",
    hdrs = first + second,
    srcs = ["stream.cpp"],
    deps = [],
    copts = ["-O0","-std=c++14 "],
    visibility = ["//test:__pkg__"],
)
