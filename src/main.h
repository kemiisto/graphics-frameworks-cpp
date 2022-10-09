#ifndef GRAPHICS_FRAMEWORKS_CPP_MAIN_H
#define GRAPHICS_FRAMEWORKS_CPP_MAIN_H

#define MAIN                                     \
int main()                                       \
{                                                \
    try {                                        \
        tinygl::init(3, 3);                      \
        Window window(1024, 1024, NAME, true);   \
        window.run();                            \
    } catch (const std::exception& e) {          \
        tinygl::terminate();                     \
        std::cerr << e.what() << std::endl;      \
        return EXIT_FAILURE;                     \
    }                                            \
                                                 \
    return EXIT_SUCCESS;                         \
}                                                \

#endif // GRAPHICS_FRAMEWORKS_CPP_MAIN_H
