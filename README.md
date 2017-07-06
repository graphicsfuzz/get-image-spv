# Get-Image-Spv

Get image for Vulkan

## Install steps

1. Download and install [Lunar Vulkan SDK](https://vulkan.lunarg.com/ "Lunar Vulkan SDK"). 

   Build the tools with the `build_tools.sh` script provided. To test if Vulkan is able to run on your graphics card, you can also run the `build_examples.sh` script and then try to run the `cube` example found in examples/build

2. Install dependencies (NOTE: please update the README if need be!):
   * GLFW3
   * GLM
   * the platform vulkan drivers

On Debian / Ubuntu:

```
sudo apt-get install libglfw3-dev libglm-dev mesa-vulkan-drivers
```

3. Change Vulkan SDK path in the Makefile and the python script

## Run
To run it should be sufficient to just run the **run_get_image.py** script
