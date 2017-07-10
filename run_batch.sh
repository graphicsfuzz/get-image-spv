#!/bin/bash

OGL_TESTING_PATH=~
source ~/VulkanSDK/1.0.46.0/setup-env.sh
GET_IMAGE_PATH=~/workspace/get-image-spv

output_file="output.txt"
vertex_file=../../shaders/vert.spv

rm $output_file
rm *.vk.*
rm *.png
errors=0
tests=0

for i in *.frag
do
	((tests++))
	vulkan_name=`basename $i .frag`.vk
	spv_name=`basename $i .frag`.vk.spv
	png_name=`basename $i .frag`.png
	java -cp $OGL_TESTING_PATH/OGLTesting/assembly/target/assembly-1.0/jar/tool-1.0.jar uk.ac.ic.doc.multicore.ogltesting.common.tool.Vulkanize --strip_header $i $vulkan_name
	glslangValidator -s -V $vulkan_name.frag -o $spv_name
	if ! RESULT="$($GET_IMAGE_PATH/get_image_spv --vertex $vertex_file  --output $png_name $spv_name 2>&1 >> output.txt )" || [[ $RESULT == *"ERROR"* ]]; then
		((errors++))
		echo "Variant ${vulkan_name//[!0-9]/} failed!!!!"
	fi
	echo $RESULT >> $output_file 
	echo $'\n' >> $output_file

	rm $vulkan_name.frag
	rm $vulkan_name.json
	rm $spv_name
done 

echo "Performed $tests tests and $errors failed" >> output.txt 
