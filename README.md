# Get-Image-Spv

Get image for Vulkan

## Install steps

1. Download and install [Lunar Vulkan SDK](https://vulkan.lunarg.com/ "Lunar Vulkan SDK").

On Debian / Ubuntu:

   Build the tools with the `build_tools.sh` script provided. To test if Vulkan is able to run on your graphics card, you can also run the `build_examples.sh` script and then try to run the **cube** example found in examples/build

On Windows:

   Everything should work out of the box. Run the **cube** example from
   the bin folder to test if your graphic card is Vulkan capable. You
   may have to update the graphics drivers, for instance latest intel
   drivers are available at:
   [https://downloadcenter.intel.com/product/80939/Graphics-Drivers](https://downloadcenter.intel.com/product/80939/Graphics-Drivers)

2. Install dependencies (NOTE: please update the README if need be!):
   * GLFW3
   * GLM
   * the platform vulkan drivers
   * [For Windows] Visual Studio

On Debian / Ubuntu:

   ```
	sudo apt-get install libglfw3-dev libglm-dev mesa-vulkan-drivers
   ```

On Windows
   * For GLFW3 go [here](http://www.glfw.org/download.html "GLFW3") and download and extract binaries. I used the 64-bit ones
   * For GLM go [here](http://glm.g-truc.net/0.9.8/index.html "GLM") and download and extract. You do not need to compile.
   * For the latest graphics drivers, search on the web. Intel ones are [here](https://downloadcenter.intel.com/product/80939/Graphics-Drivers).

3. Open CMakeLists and change VULKAN_SDK_PATH, GLM_PATH and GLFW3_PATH accordingly. If you installed using apt-get on Ubuntu, it will only care about the Vulkan path.

4. Compile

On Debian / Ubuntu:

   ```
	mkdir build
	cd build
	cmake ..
	make
   ```

On Windows:
	Open a developer prompt for Visual Studio:

   ```
	mkdir build
	cd build
    # Adapt the generator string, e.g. it can be "Visual Studio 15 Win64"
	cmake -G "Visual Studio 15 2017 Win64" --config Release ..
	msbuild get_image_spv.vcxproj  /p:Configuration=Release /m
   ```
## Demo
   To test if it is working corectly, try the following command:
   
   ```
   # From the top folder
   .\build\Release\get_image_spv.exe shaders\vert.spv shaders\recipient.vk.spv
   ```

   Check resulting image in `output.png`.

## Vulkanize shaders

"Vulkanize" the shaders and the json from the GLSL dialect to the Vulkan dialect. For this you need
   ```
   java -cp /path/to/OGLTesting/assembly/target/assembly-1.0/jar/tool-1.0.jar uk.ac.ic.doc.multicore.ogltesting.common.tool.Vulkanize <recipient>.frag <recipient.vk>
   ```



## Run
1. Option 1.
   * Use glslangvalidator from you Vulkan SDK instalation to compile your "vulkanized" shaders to spv format.
   ```
   /path/to/Vulkan/x86_64/bin/glslvalidator -V <recipient.vk>.frag -o <recipient.vk>.spv
   ```
   * Set an environmental variable to point to your Lunar Vulkan SDK libary path (not necessary on Windows):
   ```
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/path/to/Vulkan/x86_64/lib/
   ```
   * Run `get_image_spv` with the shader argument
   ```
	./get_image_spv <vertex_file>.spv <shader_file>.spv
    ```


2. Option 2. Just run **run_get_image.py** script which takes as input a "vulkanized" fragment shader and does all the above steps
   ```
	./run_get_image.py <shader_file>.frag <json_file>.json
    ```

## Flipped Image

In the OpenGl get_image programs I have noticed that the image is flipped at the end. I have made the same think for Vulkan but I have also added a command line option to not flip the image if so desired.
