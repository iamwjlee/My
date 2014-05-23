// tutorial02.c
// A pedagogical video player that will stream through every video frame as fast as it can.
//
// This tutorial was written by Stephen Dranger (dranger@gmail.com).
//
// Code based on FFplay, Copyright (c) 2003 Fabrice Bellard, 
// and a tutorial by Martin Bohme (boehme@inb.uni-luebeckREMOVETHIS.de)
// Tested on Gentoo, CVS version 5/01/07 compiled with GCC 4.1.1
//
// Use the Makefile to build all examples.
//
// Run using
// tutorial02 myvideofile.mpg
//
// to play the video stream on your screen.


#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>

#include <SDL.h>
#include <SDL_thread.h>


#include <stdio.h>

static void write_ascii_frame(const char *szFileName, const AVFrame *pVframe);

int main(void)
{
	const char *szFilePath = "2.avi";

	///> Initialize libavformat and register all the muxers, demuxers and protocols.
	av_register_all();

	///> Do global initialization of network components.
	avformat_network_init();

	int ret;
	AVFormatContext *pFmtCtx = NULL;

	///> Open an input stream and read the header. 
	ret = avformat_open_input( &pFmtCtx, szFilePath, NULL, NULL );
	if( ret != 0 ) {
		av_log( NULL, AV_LOG_ERROR, "File [%s] Open Fail (ret: %d)\n", ret );
		exit( -1 );
	}
	av_log( NULL, AV_LOG_INFO, "File [%s] Open Success\n", szFilePath );
	av_log( NULL, AV_LOG_INFO, "Format: %s\n", pFmtCtx->iformat->name );

	///> Read packets of a media file to get stream information. 
	ret = avformat_find_stream_info( pFmtCtx, NULL );
	if( ret < 0 ) {
		av_log( NULL, AV_LOG_ERROR, "Fail to get Stream Information\n" );
		exit( -1 );
	}
	av_log( NULL, AV_LOG_INFO, "Get Stream Information Success\n" );

	///> Find Video Stream
	int nVSI = -1;
	int nASI = -1;
	int i;
	for( i = 0 ; i < pFmtCtx->nb_streams ; i++ ) {
		if( nVSI < 0 && pFmtCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO ) {
			nVSI = i;
		}
		else if( nASI < 0 && pFmtCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO ) {
			nASI = i;
		}
	}

	if( nVSI < 0 && nASI < 0 ) {
		av_log( NULL, AV_LOG_ERROR, "No Video & Audio Streams were Found\n");
		exit( -1 );
	}

	///> Find Video Decoder
	AVCodec *pVideoCodec = avcodec_find_decoder( pFmtCtx->streams[nVSI]->codec->codec_id );
	if( pVideoCodec == NULL ) {
		av_log( NULL, AV_LOG_ERROR, "No Video Decoder was Found\n" );
		exit( -1 );
	}

	///> Initialize Codec Context as Decoder
	if( avcodec_open2( pFmtCtx->streams[nVSI]->codec, pVideoCodec, NULL ) < 0 ) {
		av_log( NULL, AV_LOG_ERROR, "Fail to Initialize Decoder\n" );
		exit( -1 );
	}

	///> Find Audio Decoder
	AVCodec *pAudioCodec = avcodec_find_decoder( pFmtCtx->streams[nASI]->codec->codec_id );
	if( pAudioCodec == NULL ) {
		av_log( NULL, AV_LOG_ERROR, "No Audio Decoder was Found\n" );
		exit( -1 );
	}

	///> Initialize Codec Context as Decoder
	if( avcodec_open2( pFmtCtx->streams[nASI]->codec, pAudioCodec, NULL ) < 0 ) {
		av_log( NULL, AV_LOG_ERROR, "Fail to Initialize Decoder\n" );
		exit( -1 );
	}

	AVCodecContext *pVCtx = pFmtCtx->streams[nVSI]->codec;
	AVCodecContext *pACtx = pFmtCtx->streams[nASI]->codec;

	AVPacket pkt;
	AVFrame* pVFrame, *pAFrame;
	int bGotPicture = 0;	// flag for video decoding
	int bGotSound = 0;		// flag for audio decoding

	int bPrint = 0;	// 비디오 첫 장면만 파일로 남기기 위한 임시 flag 입니다

	pVFrame = avcodec_alloc_frame();
	pAFrame = avcodec_alloc_frame();

	while( av_read_frame( pFmtCtx, &pkt ) >= 0 ) {
		///> Decoding
		if( pkt.stream_index == nVSI ) {
			if( avcodec_decode_video2( pVCtx, pVFrame, &bGotPicture, &pkt ) >= 0 ) {
				if( bGotPicture ) {
					///> Ready to Render Image
					av_log( NULL, AV_LOG_INFO, "Got Picture\n" );
					if( !bPrint ) {
						write_ascii_frame( "output.txt", pVFrame );
						bPrint = 1;
					}
				}
			}
			// else ( < 0 ) : Decoding Error
		}
		else if( pkt.stream_index == nASI ) {
			if( avcodec_decode_audio4( pACtx, pAFrame, &bGotSound, &pkt ) >= 0 ) {
				if( bGotSound ) {
					///> Ready to Render Sound
					av_log( NULL, AV_LOG_INFO, "Got Sound\n" );
				}
			}
			// else ( < 0 ) : Decoding Error
		}

		///> Free the packet that was allocated by av_read_frame
		av_free_packet( &pkt );
	}

	av_free( pVFrame );
	av_free( pAFrame );

	///> Close an opened input AVFormatContext. 
	avformat_close_input( &pFmtCtx );

	///> Undo the initialization done by avformat_network_init.
	avformat_network_deinit();

	return 0;
}

static void write_ascii_frame(const char *szFileName, const AVFrame *frame)
{
    int x, y;
    uint8_t *p0, *p;
	const char arrAsciis[] = " .-+#";

	FILE* fp = fopen( szFileName, "w" );
	if( fp ) {
		/* Trivial ASCII grayscale display. */
		p0 = frame->data[0];		
		for (y = 0; y < frame->height; y++) {
			p = p0;
			for (x = 0; x < frame->width; x++)
				putc( arrAsciis[*(p++) / 52], fp );
			putc( '\n', fp );
			p0 += frame->linesize[0];
		}
		fflush(fp);
		fclose(fp);
	}
}

