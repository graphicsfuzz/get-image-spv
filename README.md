# Get-Image-Spv

Get image for Vulkan

## Install steps

1. Download and install [Lunar Vulkan SDK](https://vulkan.lunarg.com/ "Lunar Vulkan SDK").

   Build the tools with the `build_tools.sh` script provided. To test if Vulkan is able to run on your graphics card, you can also run the `build_examples.sh` script and then try to run the **cube** example found in examples/build

2. Install dependencies (NOTE: please update the README if need be!):
   * GLFW3
   * GLM
   * the platform vulkan drivers

On Debian / Ubuntu:

   ```
	sudo apt-get install libglfw3-dev libglm-dev mesa-vulkan-drivers
   ```

3. Change Vulkan SDK path in the Makefile and the python script


## Vulkanzie shaders

"Vulkanize" the shaders and the json from the GLSL dielect to the Vulkan dialect. For this you need
   ```
   java -cp /path/to/OGLTesting/assembly/target/assembly-1.0/jar/tool-1.0.jar uk.ac.ic.doc.multicore.ogltesting.common.tool.Vulkanize <recipient>.frag <recipient.vk>
   ```

## Run
1. Option 1.
   * make
   * Use glslangvalidator from you Vulkan SDK instalation to compile your "vulkanized" shaders to spv format.
   ```
   /path/to/Vulkan/x86_64/bin/glslvalidator -V <recipient.vk>.frag -o <recipient.vk>.spv
   ```
   * Set an environmental variable to point to your Lunar Vulkan SDK libary path:
   ```
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/path/to/Vulkan/x86_64/lib/
   ```
   * Run `get_image_spv` with the shader argument
   ```
	./get_image_spv <shader_file>.spv
    ```


2. Option 2. Just run **run_get_image.py** script which takes as input a "vulkanized" fragment shader and does all the above steps
   ```
	./run_get_image.py <shader_file>.frag <json_file>.json
    ```

##Flipped Image

In the OpenGl get_image programs I have noticed that the image is flipped at the end. I have made the same think for Vulkan but I have also added a command line option to not flip the image if so desired.
