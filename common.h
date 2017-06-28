#ifndef __GETIMAGE_COMMON__
#define __GETIMAGE_COMMON__

#include <stdlib.h> // exit()
#include <stdio.h>  // printf()
#include <string>

/*---------------------------------------------------------------------------*/

typedef struct {
    int width;
    int height;
    int version;
    std::string fragFilename;
    std::string vertFilename;
    std::string jsonFilename;
    std::string output;
    bool flipped;
} Params;


/*---------------------------------------------------------------------------*/

#define errcode_crash(errcode, fmt, ...) do {                           \
        printf("%s:%d (%s) ERROR: ", __FILE__, __LINE__, __func__);     \
        printf(fmt, ##__VA_ARGS__);                                     \
        printf("\n");                                                   \
        exit (errcode);                                                 \
    } while (0)

/*---------------------------------------------------------------------------*/

// Hugues: we should just call errcode_crash(EXIT_FAILURE, fmt,
// __VA_ARGS__), but compiler complains.

#define crash(fmt, ...) do {                           \
        printf("%s:%d (%s) ERROR: ", __FILE__, __LINE__, __func__);     \
        printf(fmt, ##__VA_ARGS__);                                     \
        printf("\n");                                                   \
        exit (EXIT_FAILURE);                                            \
    } while (0)

/*---------------------------------------------------------------------------*/



static void usage(char *name) {
    std::cout << "Usage: " << name << " [options] <shader>.frag" << std::endl;
    std::cout << std::endl;

    const char *msg =
        "The program will look for a JSON whose name is derived from the\n"
        "shader as '<shader>.json'. This JSON file can contain uniforms\n"
        "initialisations. If no JSON file is found, the program uses default\n"
        "values for some uniforms.\n"
        ;
    std::cout << msg;
    std::cout << std::endl;

    std::cout << "Options:" << std::endl;

    const char *options[] = {
        "--output file.png", "set PNG output file name",
        "--resolution <width> <height>", "set resolution, in Pixels",
        "--vertex shader.vert", "use a specific vertex shader",
    };

    for (unsigned i = 0; i < (sizeof(options) / sizeof(*options)); i++) {
        printf("  %-34.34s %s\n", options[i], options[i+1]);
        i++;
    }

    std::cout << std::endl;
    std::cout << "Return values:" << std::endl;

    const char *errcode[] = {
        "0", "Successful rendering",
        "1", "Error",
        "101", "Shader compilation error (either fragment or vertex)",
        "102", "Shader linking error",
    };

    for (unsigned i = 0; i < (sizeof(errcode) / sizeof(*errcode)); i++) {
        printf("  %-4.4s %s\n", errcode[i], errcode[i+1]);
        i++;
    }

    std::cout << std::endl;
}

/*---------------------------------------------------------------------------*/

static void defaultParams(Params& params) {
    params.width = 256;
    params.height = 256;
    params.version = 0;
    params.fragFilename = "shaders/frag.spv";
    params.vertFilename = "shaders/vert.spv";
    params.jsonFilename = "shaders/frag.json";
    params.output = "output.png";
    params.flipped = "true";
}

/*---------------------------------------------------------------------------*/

static void setParams(Params& params, int argc, char *argv[]) {
    defaultParams(params);

    for (int i = 1; i < argc; i++) {
        std::string arg = std::string(argv[i]);
        if (arg.compare(0, 2, "--") == 0) {
            if        (arg == "--not_flipped") {
                params.flipped = false;
            } else if (arg == "--output") {
                if ((i + 1) >= argc) { usage(argv[0]); crash("Missing value for option %s", "--output"); }
                params.output = argv[++i];
            } else if (arg == "--resolution") {
                if ((i + 2) >= argc) { usage(argv[0]); crash("Missing value for option %s", "--resolution"); }
                params.width = atoi(argv[++i]);
                params.height = atoi(argv[++i]);
            } else if (arg == "--vertex") {
                if ((i + 1) >= argc) { usage(argv[0]); crash("Missing value for option %s", "--vertex"); }
                params.vertFilename = argv[++i];
            } else {
                usage(argv[0]);
                crash("Invalid option: %s", argv[i]);
            }
            continue;
        }
    }

    if (params.fragFilename == "") {
        usage(argv[0]);
        crash("Missing fragment shader argument");
    }
}

/*---------------------------------------------------------------------------*/

int getVersion(const std::string& fragContents) {
    size_t pos = fragContents.find('\n');
    if (pos == std::string::npos) {
        crash("cannot find end-of-line in fragment shader");
    }
    std::string sub = fragContents.substr(0, pos);
    if (std::string::npos == sub.find("#version")) {
        crash("cannot find ``#version'' in first line of fragment shader");
    }

    // TODO: use sscanf of c++ equivalent
    if (std::string::npos != sub.find("110")) { return 110; }
    if (std::string::npos != sub.find("120")) { return 120; }
    if (std::string::npos != sub.find("130")) { return 130; }
    if (std::string::npos != sub.find("140")) { return 140; }
    if (std::string::npos != sub.find("150")) { return 150; }
    if (std::string::npos != sub.find("330")) { return 330; }
    if (std::string::npos != sub.find("400")) { return 400; }
    if (std::string::npos != sub.find("410")) { return 410; }
    if (std::string::npos != sub.find("420")) { return 420; }
    if (std::string::npos != sub.find("430")) { return 430; }
    if (std::string::npos != sub.find("440")) { return 440; }
    if (std::string::npos != sub.find("450")) { return 450; }
    // The following are OpenGL ES
    if (std::string::npos != sub.find("100")) { return 100; }
    if (std::string::npos != sub.find("300")) { return 300; }
    crash("Cannot find a supported GLSL version in first line of fragment shader: ``%.80s''", sub.c_str());
}

#endif
