idf_component_register(SRCS "app_main.c" "dht11.c" "oled1306.c"
                    INCLUDE_DIRS ".")
target_compile_options(${COMPONENT_LIB} PRIVATE "-Wno-format")

