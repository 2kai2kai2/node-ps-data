{
    "conditions": [
        ["OS=='win'", {
            "targets": [{
                    "target_name": "node_ps_data",
                    "sources": ["napi.cc", "lib_win.cc", "lib_nvml.cc"],
                    "include_dirs": [
                        "./node_modules/node-addon-api",
                        "C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v12.9/include"
                    ],
                    "ldflags": [
                        "-lpsapi", # gcc/g++
                        "-lnvidia-ml",
                    ],
                    "link_settings": {
                        "libraries": [
                            "psapi.lib" # msvc
                        ]
                    },
                    "cflags!": [ "-fno-exceptions" ],
                    "cflags_cc!": [ "-fno-exceptions" ],
                    "msvs_settings": {
                        "VCCLCompilerTool": { "ExceptionHandling": 1 }
                    }
            }]
        },
        "OS=='linux'", {
            "targets": [{
                    "target_name": "node_ps_data",
                    "sources": ["napi.cc", "lib_linux.cc", "lib_nvml.cc"],
                    "include_dirs": ["./node_modules/node-addon-api"],
                    "link_settings": {
                        "libraries": [
                            "/usr/lib/x86_64-linux-gnu/libnvidia-ml.so",
                        ],
                    },
                    "ldflags": [
                        "-lnvidia-ml",
                    ],
                    "cflags!": [ "-fno-exceptions" ],
                    "cflags_cc!": [ "-fno-exceptions" ]
            }]
        },
        "OS=='mac'", {
            "targets": [{
                    "target_name": "node_ps_data",
                    "sources": ["napi.cc", "lib_mac.cc", "lib_nvml_stub.cc"],
                    "include_dirs": ["./node_modules/node-addon-api"],
                    "cflags!": [ "-fno-exceptions" ],
                    "cflags_cc!": [ "-fno-exceptions" ],
                    "xcode_settings": {
                        "GCC_ENABLE_CPP_EXCEPTIONS": "YES",
                        "CLANG_CXX_LIBRARY": "libc++",
                        "MACOSX_DEPLOYMENT_TARGET": "10.7"
                    }
            }]
        }]
    ]
}