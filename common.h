#ifndef __GETIMAGE_COMMON__
#define __GETIMAGE_COMMON__

#include <stdlib.h> // exit()
#include <stdio.h>  // printf()
#include <string>

/*---------------------------------------------------------------------------*/

typedef struct {
    int width;
    int height;
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
        printf("\n\n");                                                   \
        exit (EXIT_FAILURE);                                            \
    } while (0)

/*---------------------------------------------------------------------------*/



static void usage(char *name) {
    std::cout << std::endl << "Usage: " << name << " [options] <shader>.spv" << std::endl;
    std::cout << std::endl;

    const char *msg =
    		"The program will look for a JSON whose name is derived from the\n"
    		"shader as '<shader>.json'. This JSON file can contain uniforms\n"
    		"initialisations.\n"
            ;
    std::cout << msg;
    std::cout << std::endl;

    std::cout << "Options:" << std::endl;

    const char *options[] = {
        "--output       <file>.png", "set PNG output file name",
        "--resolution   <width> <height>", "set resolution, in Pixels",
        "--vertex       <file>.spv", "use a specific vertex shader",
		"--fragment     <file>.spv", "use a specific fragment shader",
		"--not_flipped", "do not flip the image",
    };

    for (unsigned i = 0; i < (sizeof(options) / sizeof(*options)); i++) {
        printf("  %-34.34s %s\n", options[i], options[i+1]);
        i++;
    }

    std::cout << std::endl;
}

/*---------------------------------------------------------------------------*/

static void defaultParams(Params& params) {
    params.width = 256;
    params.height = 256;
    params.fragFilename = "";
    params.vertFilename = "shaders/vert.spv";
    params.jsonFilename = "";
    params.output = "output.png";
    params.flipped = "true";
}

/*---------------------------------------------------------------------------*/

static void setParams(Params& params, int argc, char *argv[]) {
    defaultParams(params);

    for (int i = 1; i < argc; i++) {
        std::string arg = std::string(argv[i]);
        if (arg.compare(0, 2, "--") == 0) {
            if (arg == "--not_flipped") {
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
            } else if (arg == "--fragment") {
                if ((i + 1) >= argc) { usage(argv[0]); crash("Missing value for option %s", "--fragment"); }
                params.fragFilename = argv[++i];
            } else if (arg == "--json") {
                if ((i + 1) >= argc) { usage(argv[0]); crash("Missing value for option %s", "--json"); }
                params.jsonFilename = argv[++i];
            } else {
                usage(argv[0]);
                crash("Invalid option: %s", argv[i]);
            }
            continue;
        }
        if (params.fragFilename == "") {
            params.fragFilename = arg;
        } else {
            usage(argv[0]);
            crash("Unexpected extra argument: %s", arg.c_str());
        }
    }

    if (params.fragFilename == "") {
        usage(argv[0]);
        crash("Missing fragment shader argument");
    }

    if (params.jsonFilename == "") {
    	params.jsonFilename = params.fragFilename;
    	params.jsonFilename.replace(params.jsonFilename.end()-3, params.jsonFilename.end(), "json");
    	std::cout << "The JSON file that will be used is " << params.jsonFilename << std::endl;
    }
    std::cout << "The FRAG file that will be used is " << params.fragFilename << std::endl;


}


#endif
