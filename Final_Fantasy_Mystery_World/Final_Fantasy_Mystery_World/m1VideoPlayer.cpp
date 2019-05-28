extern "C" {
#include "ffmpeg/include/libavcodec/avcodec.h"
#include "ffmpeg/include/libavdevice/avdevice.h"
#include "ffmpeg/include/libavfilter/avfilter.h"
#include "ffmpeg/include/libavformat/avformat.h"
#include "ffmpeg/include/libavutil/avutil.h"
#include "ffmpeg/include/libswscale/swscale.h"
#include "ffmpeg/include/libswresample/swresample.h"

#pragma comment( lib, "ffmpeg/lib/avcodec.lib" )
#pragma comment( lib, "ffmpeg/lib/avdevice.lib" )
#pragma comment( lib, "ffmpeg/lib/avfilter.lib" )
#pragma comment( lib, "ffmpeg/lib/avformat.lib" )
#pragma comment( lib, "ffmpeg/lib/avutil.lib" )
#pragma comment( lib, "ffmpeg/lib/swscale.lib" )
#pragma comment( lib, "ffmpeg/lib/swresample.lib" )
}

#include "App.h"
#include "m1Render.h"
#include "m1Input.h"
#include "m1Window.h"
#include "p2Log.h"
#include "m1VideoPlayer.h"
#include "m1MainMenu.h"

#define DEFAULT_AUDIO_BUF_SIZE 1024
#define MAX_AUDIOQ_SIZE (5 * 256 * 1024)
#define MAX_VIDEOQ_SIZE (5 * 512 * 1024)

void AudioCallback(void *userdata, Uint8 *stream, int length) {

	m1VideoPlayer *video = (m1VideoPlayer*)userdata;
	int input_length, audio_size;

	while (length > 0 && video->playing) {
		if (video->audio_buf_index >= video->audio_buf_size) {
			// All audio data sent. Get more.
			audio_size = video->DecodeAudio();
			if (audio_size < 0) {
				// If an error occured decoding, we output silence (0)
				video->audio_buf_size = DEFAULT_AUDIO_BUF_SIZE;
				memset(video->audio_buf, 0, video->audio_buf_size);
			}
			else {
				video->audio_buf_size = audio_size;
			}
			video->audio_buf_index = 0;
		}
		input_length = video->audio_buf_size - video->audio_buf_index;
		if (input_length > length)
			input_length = length;
		memcpy(stream, (uint8_t *)video->audio_buf + video->audio_buf_index, input_length);
		length -= input_length;
		stream += input_length;
		video->audio_buf_index += input_length;
	}
}

int VideoCallback(Uint32 interval, void* param)
{
	m1VideoPlayer* player = (m1VideoPlayer*)param;
	if (player->playing)
		player->refresh = true;

	return 0;
}

int ReadThread(void *param) {
	m1VideoPlayer* player = (m1VideoPlayer*)param;
	AVPacket pkt;
	int ret = 0;

	while (player->playing)
	{
		if (player->audio.pktqueue.size >= MAX_AUDIOQ_SIZE
			|| player->video.pktqueue.size >= MAX_VIDEOQ_SIZE)
		{
			SDL_Delay(10);
			continue;
		}

		//TODO 2: Read packets
		//We need to READ a FRAME from stream.
		//Function asks for the FormatContext saved in player and a AVPacket.
		//After receiving the packet we need to check the stream_index of that packet, 
		//and check if its the same as one of our STREAM INDEX from the STREAM COMPONENTS we have in player
		//If the stream index is the same as one of them, PUT the packet inside it's PACKETQUEUE
		//Make sure to UNREF the packet at the end of this loop

		// read an encoded packet from file
		ret = av_read_frame(player->format, &pkt);
		if (ret < 0)
		{
			if (ret == AVERROR_EOF) LOG("Finished reading packets");
			else LOG("Error reading packet");
			player->quit = true;
			break;
		}

		if (pkt.stream_index == player->video.stream_index) // if packet data is video we add to video queue
		{
			player->video.pktqueue.PutPacket(&pkt);
		}
		else if (pkt.stream_index == player->audio.stream_index)
		{
			player->audio.pktqueue.PutPacket(&pkt); // if packet data is audio we add to audio queue
		}
		av_packet_unref(&pkt); // release the packet
	}

	return 0;
}



m1VideoPlayer::m1VideoPlayer()
{
}


m1VideoPlayer::~m1VideoPlayer()
{
}

bool m1VideoPlayer::Awake(pugi::xml_node&)
{
	return true;
}

bool m1VideoPlayer::Start()
{
	return true;
}

bool m1VideoPlayer::PreUpdate()
{
	return true;
}

bool m1VideoPlayer::Update(float dt)
{
	//DEBUG INPUTS
	if (App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN) {
		App->main_menu->Disable();
		PlayVideo("assets/videos/World of Warcraft Wrath of the Lich King Intro Trailer.mp4");
	}
	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
		Pause();
	if (App->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN)
		CloseVideo();

	//Update texture
	if (refresh)
	{
		DecodeVideo();
		refresh = false;
	}
	if (quit && audio.finished && video.finished)
		CloseVideo();

	return true;
}

bool m1VideoPlayer::PostUpdate()
{
	if (playing)
	{
		App->render->Blit(texture, 0, 0, nullptr);
	}
	return true;
}

bool m1VideoPlayer::CleanUp()
{
	if (playing)
		CloseVideo();

	return true;
}

int m1VideoPlayer::PlayVideo(std::string file_path)
{
	if (playing)
	{
		LOG("Already playing video");
		return -1;
	}

	file = file_path;

	//Open video file
	if (avformat_open_input(&format, file.c_str(), NULL, NULL) != 0)
	{
		LOG("Error loading video file %s", file);
		return -1;
	}

	// Retrieve stream information
	if (avformat_find_stream_info(format, NULL) <0)
		return -1; // Couldn't find stream information

	int video_stream = -1, audio_stream = -1;
	// Find video and audio streams
	for (int i = 0; i < format->nb_streams; i++)
	{
		if (format->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO && video_stream < 0)
			video_stream = i;
		else if (format->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO && audio_stream < 0)
			audio_stream = i;
	}

	if (video_stream == -1)
		LOG("No video stream found");
	else
		OpenStreamComponent(video_stream); //Open video component

	if (audio_stream == -1)
		LOG("No audio stream found");
	else
		OpenStreamComponent(audio_stream); //Open audio component

										   //Everything went fine
	LOG("Video file loaded correctly, now playing: %s", file);
	playing = true;
	parse_thread_id = SDL_CreateThread(ReadThread, "ReadThread", this); //Start packet reading thread
																		//TODO 4.1 Call SDL_AddTimer with 40 ms and our VideoCallback, also dont forget to send this as parameter.
	SDL_AddTimer(40, (SDL_TimerCallback)VideoCallback, this); //First video callback
}

void m1VideoPlayer::OpenStreamComponent(int stream_index)
{
	AVCodecContext *codec_context;
	AVCodec *codec;

	if (stream_index < 0 || stream_index >= format->nb_streams) {
		LOG("Error not valid stream index");
	}
	// TODO 1: Open the codec
	// First we need to FIND the DECODER of the STREAM that we received
	// Hint: The function asks for the codec id, which can be found in format->streams[stream_index]->codecpar
	// After finding the CODEC we need to ALLOCATE the memory for the codec context, the function asks for the codec we just received last function.
	// Once we allocated the codec context, we need to give it values, since the function leaves them by default
	// We can fill the codec context using another fuction that will ask us the PARAMETERS of the codec (the variable we used on the first function codecpar).
	// Now that we have the codec_context filled with its parameters, we can actually OPEN the codec. Last function call.

	// Find the decoder for stream
	codec = avcodec_find_decoder(format->streams[stream_index]->codecpar->codec_id);
	if (codec == NULL)
		LOG("Unsupported codec for stream index %i", stream_index);

	codec_context = avcodec_alloc_context3(codec);
	// Parameter to context for video
	if (avcodec_parameters_to_context(codec_context, format->streams[stream_index]->codecpar) < 0) {
		LOG("Failed parameters to context for stream %i", stream_index);
	}

	// Open codecs
	if (avcodec_open2(codec_context, codec, NULL) < 0)
	{
		LOG("Error opening codec");
	}

	switch (codec_context->codec_type)
	{
	case AVMEDIA_TYPE_VIDEO:
		video.stream = format->streams[stream_index];
		video.context = codec_context;
		video.stream_index = stream_index;

		video.frame = av_frame_alloc();
		video.converted_frame = av_frame_alloc();

		uint dst_w, dst_h;
		App->win->GetWindowSize(dst_w, dst_h);

		//Prepare scaling frame.
		video.converted_frame->format = AVPixelFormat::AV_PIX_FMT_YUV420P; // Format used for SDL
		video.converted_frame->width = dst_w; //width of window
		video.converted_frame->height = dst_h; //height of window
		av_frame_get_buffer(video.converted_frame, 0); //get buffers for YUV format

													   //Get context to scale video frames to format, width and height of our SDL window.
		sws_context = sws_getContext(codec_context->width, codec_context->height, codec_context->pix_fmt,
			dst_w, dst_h, AVPixelFormat::AV_PIX_FMT_YUV420P,
			SWS_BILINEAR, NULL, NULL, NULL);

		video.pktqueue.Init();

		break;
	case AVMEDIA_TYPE_AUDIO:
		SDL_AudioSpec wanted_spec, spec;

		audio.stream = format->streams[stream_index];
		audio.context = codec_context;
		audio.stream_index = stream_index;

		audio.frame = av_frame_alloc();
		audio.converted_frame = av_frame_alloc();

		//Fill wanted specs for sdl audio
		wanted_spec.freq = audio.context->sample_rate;
		wanted_spec.format = AUDIO_S16SYS;
		wanted_spec.channels = audio.context->channels;
		wanted_spec.silence = 0;
		wanted_spec.samples = DEFAULT_AUDIO_BUF_SIZE;
		wanted_spec.callback = AudioCallback;
		wanted_spec.userdata = this;

		if (SDL_OpenAudio(&wanted_spec, &spec) < 0) {
			LOG("SDL_OpenAudio: %s", SDL_GetError());
		}

		//Prepare conversion context
		swr_context = swr_alloc_set_opts(NULL, audio.context->channel_layout, AV_SAMPLE_FMT_FLT, audio.context->sample_rate,
			audio.context->channel_layout, audio.context->sample_fmt, audio.context->sample_rate, 0, NULL);
		swr_init(swr_context);

		//Get buffer to output converted audio
		audio.converted_frame->format = AV_SAMPLE_FMT_FLT; // Format used for SDL Audio
		audio.converted_frame->channel_layout = audio.context->channel_layout;
		audio.converted_frame->nb_samples = audio.context->frame_size;
		av_frame_get_buffer(audio.converted_frame, 0);

		audio.pktqueue.Init();
		SDL_PauseAudio(0);

		break;
	}
}

bool m1VideoPlayer::Pause()
{


	paused = !paused;

	SDL_PauseAudio(0);
	audio.pktqueue.paused = paused;
	video.pktqueue.paused = paused;

	if (paused) LOG("Video paused");
	else LOG("Video resumed");

	return true;
}

void m1VideoPlayer::CloseVideo()
{
	if (!playing)
		return;

	playing = false;
	audio.pktqueue.paused = true;
	video.pktqueue.paused = true;

	SDL_CondSignal(video.pktqueue.cond); //In case queue is waiting for new pkts
	SDL_CondSignal(audio.pktqueue.cond); //In case queue is waiting for new pkts
	SDL_WaitThread(parse_thread_id, NULL);

	video.Clear();
	audio.Clear();

	sws_freeContext(sws_context);
	sws_context = nullptr;
	swr_free(&swr_context);

	avformat_close_input(&format);

	SDL_DestroyTexture(texture);
	texture = nullptr;
	SDL_CloseAudio();
	audio_buf_index = 0;
	audio_buf_size = 0;
	quit = false;

	LOG("Video closed");
}

void m1VideoPlayer::DecodeVideo()
{
	AVPacket pkt;
	int ret;

	if (!playing)
		return;
	if (video.pktqueue.GetPacket(&pkt, quit) < 0)
	{
		if (quit)
			video.finished = true;
		else
			SDL_AddTimer(1, (SDL_TimerCallback)VideoCallback, this);
		return;
	}

	// TODO 4: Decoding the video
	// You've done this before send the packet and receive the frame. Easy TODO. Oh wait, there's a 4.1

	//send packet to video decoder
	ret = avcodec_send_packet(video.context, &pkt);
	if (ret < 0)
	{
		LOG("Error sending video packet for decoding");
		return;
	}

	ret = avcodec_receive_frame(video.context, video.frame);

	//Scale texture
	sws_scale(sws_context, video.frame->data, video.frame->linesize,
		0, video.frame->height, video.converted_frame->data, video.converted_frame->linesize);

	//Update video texture

	if (texture == nullptr) {
		uint dst_w, dst_h;
		App->win->GetWindowSize(dst_w, dst_h);

		//Create texture where we will output the video.
		texture = SDL_CreateTexture(App->render->renderer, SDL_PIXELFORMAT_YV12, SDL_TEXTUREACCESS_STREAMING,
			dst_w, dst_h);
	}

	SDL_UpdateYUVTexture(texture, nullptr, video.converted_frame->data[0], video.converted_frame->linesize[0], video.converted_frame->data[1],
		video.converted_frame->linesize[1], video.converted_frame->data[2], video.converted_frame->linesize[2]);

	// TODO 5: Synching the video to the audio.
	// First we need to get the PTS from the FRAME that we just received.
	// After getting the pts you can uncomment this, it's a cheap way to fix that some frames may not have PTS
	/*if (pts == AV_NOPTS_VALUE)
	{
	pts = video.clock +
	(1.f / av_q2d(video.stream->avg_frame_rate)) / av_q2d(video.stream->time_base);
	}*/
	// We are not done yet, you should update the VIDEO CLOCK with the new pts
	// After that it's time to calculate the delay between the VIDEO clock and the AUDIO clock
	// Remember to multiplicate each clock for each SREAM TIME BASE (stream->time_base) to get the time in seconds.
	// Also you need to fix the delay if its too small for example if its smaller than 0.01 set it to that.
	// Now send this delay in as ms to the SDL_AddTimer function below. You remember how to convert seconds to ms right?
	// To finish you need to calculate the clock for the audio component aswell look for the TODO 5.1 you should do the same as here
	// If you did everything correctly now you should have a working video player. Enjoy the movie.
	double pts = video.frame->pts;
	if (pts == AV_NOPTS_VALUE)
	{
		pts = video.clock +
			(1.f / av_q2d(video.stream->avg_frame_rate)) / av_q2d(video.stream->time_base);
	}
	video.clock = pts;

	double delay = (video.clock*av_q2d(video.stream->time_base)) - (audio.clock*av_q2d(audio.stream->time_base));
	if (delay < 0.01)
		delay = 0.01; //Maybe skip frame if video is too far behind from audio instead of fast refresh.

					  //Debug information setup
	static char title[256];
	sprintf_s(title, 256, " Video seconds: %.2f Audio seconds: %.2f Calculated delay %.2f",
		video.clock*av_q2d(video.stream->time_base), audio.clock*av_q2d(audio.stream->time_base), delay);
	App->win->SetTitle(title);


	//Prepare VideoCallback on ms
	SDL_AddTimer((Uint32)(delay * 1000 + 0.5), (SDL_TimerCallback)VideoCallback, this);
	av_packet_unref(&pkt);
}

int m1VideoPlayer::DecodeAudio()
{
	AVPacket pkt;
	int ret;
	int len2, data_size = 0;

	if (!playing)
		return -1;

	// TODO 3: Decoding the audio
	// First thing that we need to do here is GET a PACKET from the AUDIO PACKET QUEUE
	// If the function return <0 you should call return -1
	// After getting our packet, we need to SEND the PACKET to the DECODER
	// Once the packet has been sent, its time to RECEIVE the decoded FRAME
	// If you do this correctly and uncomment the stuff below you should be able to hear the video sound. 
	// It will probably stop after a certain time, we will fix that later.

	if (audio.pktqueue.GetPacket(&pkt, quit) < 0)
	{
		if (quit)
			audio.finished = true;
		return -1;
	}


	ret = avcodec_send_packet(audio.context, &pkt);
	if (ret < 0)
	{
		LOG("Error sending audio pkt to decode");
		return -1;
	}

	ret = avcodec_receive_frame(audio.context, audio.frame);

	swr_convert(swr_context,
		audio.converted_frame->data,	// output
		audio.frame->nb_samples,
		(const uint8_t**)audio.frame->data,  // input
		audio.frame->nb_samples);

	// returns the number of samples per channel in one audio frame
	data_size = av_samples_get_buffer_size(NULL,
		audio.context->channels,
		audio.frame->nb_samples,
		AV_SAMPLE_FMT_FLT,
		1);

	memcpy(audio_buf, audio.converted_frame->data[0], data_size);
	av_packet_unref(&pkt);

	// TODO 5.1 Just copy and paste, don't forget to change the variable names like I did
	// You dont need to cal SDL_Timer here if you were wondering
	double pts = audio.frame->pts;
	if (pts == AV_NOPTS_VALUE)
	{
		pts = audio.clock +
			(1.f / av_q2d(audio.stream->avg_frame_rate)) / av_q2d(audio.stream->time_base);
	}
	audio.clock = pts;

	// We have data, return it and come back for more later
	return data_size;
}

void PacketQueue::Init()
{
	paused = false;
	mutex = SDL_CreateMutex();
	cond = SDL_CreateCond();
}

int PacketQueue::PutPacket(AVPacket* pkt)
{
	AVPacketList *pkt_list = nullptr;
	AVPacket new_pkt;

	if (paused)
		return -1;

	av_packet_ref(&new_pkt, pkt);

	pkt_list = (AVPacketList*)av_malloc(sizeof(AVPacketList));
	if (!pkt_list)
		return -1;

	pkt_list->pkt = new_pkt;
	pkt_list->next = NULL;

	SDL_LockMutex(mutex);

	if (!last_pkt)
		first_pkt = pkt_list;
	else
		last_pkt->next = pkt_list;



	last_pkt = pkt_list;
	nb_packets++;
	size += pkt_list->pkt.size;

	SDL_CondSignal(cond);
	SDL_UnlockMutex(mutex);

	return 0;
}

int PacketQueue::GetPacket(AVPacket* pkt, bool block)
{
	AVPacketList *pkt_list;
	int ret;

	SDL_LockMutex(mutex);
	while (true)
	{
		if (paused) {
			ret = -1;
			break;
		}

		pkt_list = first_pkt;

		if (pkt_list) {
			first_pkt = pkt_list->next;
			if (!first_pkt)
				last_pkt = NULL;
			nb_packets--;
			size -= pkt_list->pkt.size;
			*pkt = pkt_list->pkt;
			av_free(pkt_list);
			ret = 1;
			break;
		}
		else if (block)
		{
			ret = -1;
			break;
		}
		else {
			SDL_CondWait(cond, mutex); //Wait for pkt
		}
	}
	SDL_UnlockMutex(mutex);
	return ret;
}

int PacketQueue::Clear()
{
	AVPacketList *pkt, *pkt1;
	SDL_LockMutex(mutex);
	for (pkt = first_pkt; pkt != NULL; pkt = pkt1) {
		pkt1 = pkt->next;
		av_packet_unref(&(pkt->pkt));
		av_freep(&pkt);
	}
	last_pkt = NULL;
	first_pkt = NULL;
	nb_packets = 0;
	size = 0;
	SDL_UnlockMutex(mutex);

	SDL_DestroyMutex(mutex);
	SDL_DestroyCond(cond);

	return 0;
}

void StreamComponent::Clear()
{
	pktqueue.Clear();

	av_frame_free(&frame);
	av_frame_free(&converted_frame);

	avcodec_free_context(&context);

	clock = 0;
	stream_index = -1;
	finished = false;

}
