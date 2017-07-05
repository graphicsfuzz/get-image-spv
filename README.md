# Get-Image-Spv

Get image for Vulkan

## Install steps

1. Download and install Lunar Vulkan SDK. We need glslangValidator, if
   you do not already have it in your path, you can get it with the SDK
   tools: build VulkanSDK tools with the `build_tools.sh` script
   provided by the SDK.

2. Install dependencies (NOTE: please update the README if need be!):
   - GLFW3
   - GLM
   - the platform vulkan drivers

On Debian / Ubuntu:

```
sudo apt-get install libglfw3-dev libglm-dev mesa-vulkan-drivers
```

3. Change Vulkan SDK path in the Makefile and the python script

## Run
To run it should be sufficient to just run the **run_get_image.py** script
