VULKAN_SDK_PATH = /home/dan/VulkanSDK/1.0.46.0/x86_64

CC = g++
CFLAGS = -std=c++11 -I$(VULKAN_SDK_PATH)/include
LDFLAGS = -L$(VULKAN_SDK_PATH)/lib `pkg-config --static --libs glfw3` -lvulkan
OBJS = main.o lodepng.o
OUTPUT = get_image_spv

all: $(OUTPUT)

$(OUTPUT): $(OBJS)
	$(CC) $(OBJS) -o $(OUTPUT) $(LDFLAGS)

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp 

lodepng.o: lodepng.cpp
	$(CC) $(CFLAGS) -c lodepng.cpp 

.PHONY: run clean

run: $(OUTPUT)
	LD_LIBRARY_PATH=$(VULKAN_SDK_PATH)/lib VK_LAYER_PATH=$(VULKAN_SDK_PATH)/etc/explicit_layer.d ./$(OUTPUT)

clean:
	rm -f $(OUTPUT) *.o
