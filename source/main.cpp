#include <iostream>
#include <fstream>
#include <unistd.h>
#include "ffmpeg_file.h" 
#include "ffmpeg_scale.h"

void decode_thread(FFMPEG_FILE* file);

int main(int argc, char* argv[]) {

	// -- Check for args

	if (argc != 2) {
		
		std::cout << "Invalid args." << std::endl;
		return -1;

	}

	// -- Open file. Start async decode thread
		
	// FFMPEG_FILE file(argv[1]);
	// file.AsyncDecode();

	// AVFrame* frame = nullptr;
	// std::ofstream audio_file("audio_extract.pcm", std::ios::binary);


/*
	for (int x = 0; x < 1000; ++x) {

		frame = file.ReadAudio();

		printf("nb_samples: %d.\n", frame->nb_samples);
		const char* str = av_get_sample_fmt_name(static_cast<AVSampleFormat>(frame->format));
		printf("Frame format: %s.\n", str);

		printf("channels: %d.\n", frame->ch_layout.nb_channels);

		int sample_size = av_get_bytes_per_sample(static_cast<AVSampleFormat>(frame->format));
		printf("sample size: %d.\n", sample_size);

		// -- Buffer size
		// BUF_SIZE = SAMPLE_SIZE * NR_CHANNELS * NR_SAMPLES
		int buffer_size = sample_size * frame->ch_layout.nb_channels * frame->nb_samples;
		printf("Buffer size: %d.\n", buffer_size);

		int padded_buffer_size = ((buffer_size / 4096) * 4096) + 4096; 
		printf("Padded buffer size: %d.\n", padded_buffer_size);

		printf("Linesize: %d.\n", frame->linesize[0]);

		printf("Sample rate: %d.\n", frame->sample_rate);

		uint8_t buf[padded_buffer_size];
		uint8_t* buf_pos = &buf[0];
		int offset = 0;

		for (int i = 0; i < frame->nb_samples; ++i) {
			for (int j = 0; j < frame->ch_layout.nb_channels; ++j) {
				memcpy(buf_pos, &frame->extended_data[j][offset], sample_size);
				buf_pos += sample_size;
			}
			offset += sample_size;
		}

		audio_file.write(reinterpret_cast<char*>(buf), buffer_size);

		av_frame_free(&frame);
	}
*/

	FFMPEG_FILE file(argv[1]);
	file.AsyncDecode();

	// usleep(100000);

	AVFrame* frame = nullptr;
	for (int i = 0; i < 60; ++i) frame = file.AsyncReadVideo();

    uint8_t* buf = nullptr;
    AVFrame* rgb_frame = FFMPEG_SCALE::RGB(frame, file.video_codec_context, &buf, AV_PIX_FMT_RGBA);

	std::ofstream img_file("image_extract.data", std::ios::binary);

	for (int i = 0; i < rgb_frame->height; ++i) {
		uint8_t* pixel_ptr = (rgb_frame->data[0] + i * rgb_frame->linesize[0]);
		img_file.write((char*)pixel_ptr, rgb_frame->width*4);
	}

	av_freep(reinterpret_cast<void*>(&buf));
	av_frame_free(&rgb_frame);
    av_frame_free(&frame);

	file.StopAsyncDecode();

	return 0;

}

void decode_thread(FFMPEG_FILE* file) {

	return;

}
