{
    "conditions": [
        ["OS=='win'", {
            "targets": [{
                    "target_name": "node_ps_data",
                    "sources": ["napi.cc", "lib_win.cc"],
                    "include_dirs": ["./node_modules/node-addon-api"],
                    "ldflags": [
                        "-lpsapi" # gcc/g++
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
                    "sources": ["napi.cc", "lib_linux.cc"],
                    "include_dirs": ["./node_modules/node-addon-api"],
                    "cflags!": [ "-fno-exceptions" ],
                    "cflags_cc!": [ "-fno-exceptions" ]
            }]
        },
        "OS=='mac'", {
            "targets": [{
                    "target_name": "node_ps_data",
                    "sources": ["napi.cc", "lib_mac.cc"],
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