{
    "targets": [
        {
            "target_name": "xcb",
            "cflags!": [ "-fno-exceptions" ],
            "cflags_cc!": [ "-fno-exceptions" ],
            "sources": [
                "lib/main.cc",
                "lib/connection.cc"
            ],
            "include_dirs": [
                "<!@(node -p \"require('node-addon-api').include\")"
            ],
            "defines": [ "NAPI_DISABLE_CPP_EXCEPTIONS" ],
            "link_settings": {
                "libraries": [
                    "-lxcb"
                ]
            }
        }
    ]
}