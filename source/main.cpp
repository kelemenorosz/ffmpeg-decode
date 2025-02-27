#include <iostream>
#include <fstream>
#include "ffmpeg_file.h" 
#include "ffmpeg_scale.h"

int main(int argc, char* argv[]) {

	// -- Check for args

	if (argc != 2) {
		
		std::cout << "Invalid args." << std::endl;
		return -1;

	}
		
	FFMPEG_FILE file(argv[1]);
	AVFrame* frame = nullptr;
    for (int i = 0; i < 60; ++i) frame = file.Read(); 

    AVFrame* rgb_frame = FFMPEG_SCALE::RGB24(frame, file.codec_context);

	std::ofstream img_file("image_extract.data", std::ios::binary);

	for (int i = 0; i < rgb_frame->height; ++i) {
		uint8_t* pixel_ptr = (rgb_frame->data[0] + i * rgb_frame->linesize[0]);
		img_file.write((char*)pixel_ptr, rgb_frame->width*4);
	}

	av_freep(reinterpret_cast<void*>(&rgb_frame));
	av_frame_free(&rgb_frame);
    av_frame_free(&frame);

	return 0;

}
