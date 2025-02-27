#ifndef FFMPEG_SCALE_H
#define FFMPEG_SCALE_H


extern "C" {
	#include <libavformat/avformat.h>
	#include <libavcodec/avcodec.h>
	#include <libavutil/avutil.h>
	#include <libavutil/pixdesc.h>
	#include <libavutil/imgutils.h>
	#include <libswscale/swscale.h>
}

namespace FFMPEG_SCALE {

    AVFrame* RGB24(AVFrame* src, AVCodecContext* codec);

}

#endif /* FFMPEG_SCALE_H */
