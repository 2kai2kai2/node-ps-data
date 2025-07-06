{
    "conditions": [
        ["OS=='win'", {
            "targets": [{
                    "target_name": "node_ps_data",
                    "sources": [
                        "napi.cc",
                        "lib_win.cc",
                        "lib_nvidia_nvml.cc",
                    ],
                    "include_dirs": [
                        "./node_modules/node-addon-api",
                        "<!(echo %CUDA_PATH%)/include",
                        "<!(echo %CONDA_PREFIX%)/Library/include",
                    ],
                    "ldflags": [
                        "-lpsapi", # gcc/g++
                        "-lnvidia-ml",
                    ],
                    "link_settings": {
                        "libraries": [
                            "psapi.lib", # msvc
                        ],
                        "variables": {
                            'has_cuda_path': '<!(if defined CUDA_PATH (echo 1) else (echo 0))',
                        },
                        "conditions": [
                            ['has_cuda_path==1', { # normal cuda toolkit install (used locally)
                                "libraries": ["<!(echo %CUDA_PATH%)/lib/x64/nvml.lib"],
                            }],
                            ['has_cuda_path==0', { # conda (used in github actions)
                                "libraries": ["<!(echo %CONDA_PREFIX%)/Library/lib/nvml.lib"],
                            }],
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
                    "sources": ["napi.cc", "lib_linux.cc", "lib_nvidia_nvml.cc"],
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
                    "sources": ["napi.cc", "lib_mac.cc", "lib_nvidia_stub.cc"],
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