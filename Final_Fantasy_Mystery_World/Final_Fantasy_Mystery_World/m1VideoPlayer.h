#ifndef _VIDEOPLAYER_H_
#define _VIDEOPLAYER_H_

#define VIDEO_INTRO_ID 1


struct SDL_Texture;
struct AVFormatContext;
struct AVFrame;
struct AVCodecContext;
struct AVStream;
struct SwsContext;
struct SwrContext;
struct AVPacket;
struct AVPacketList;

#include "m1Module.h"
#include "p2Timer.h"

class u1Label;

struct PacketQueue {
	AVPacketList *first_pkt = nullptr, *last_pkt = nullptr;
	int nb_packets;
	int size;
	SDL_mutex* mutex = nullptr;
	SDL_cond* cond = nullptr;
	bool paused = false;

	void Init();
	int PutPacket(AVPacket* pkt);
	int GetPacket(AVPacket* pkt, bool block);
	int Clear();
};

struct StreamComponent
{
	AVStream* stream = nullptr;
	AVCodecContext* context = nullptr;
	AVFrame* frame = nullptr;
	AVFrame* converted_frame = nullptr;
	PacketQueue pktqueue;

	double clock = 0.0;
	int stream_index = 0;
	bool finished = false;

	void Clear();
};

class m1VideoPlayer : public m1Module
{
public:
	m1VideoPlayer();
	~m1VideoPlayer();
	bool Awake(pugi::xml_node&);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

	int PlayVideo(std::string file_path, const int & id = 0, const float &delay_time = 0.0F);
	bool Pause();
	void CloseVideo();


	int DecodeAudio();

private:
	void OpenStreamComponent(int stream_index);
	void DecodeVideo();

	int PlayVideoNow();

	void LogicAfterVideo();
	void SkipVideo();
public:
	StreamComponent audio;
	StreamComponent video;
	AVFormatContext* format = nullptr;

	bool refresh = false;
	bool playing = false;
	bool paused = false;
	bool quit = false;
	std::string file = "";

	//Audio stream stuff, this should probably not be here...
	uint8_t audio_buf[(192000 * 3) / 2]; //buffer where we store the audio data
	unsigned int audio_buf_size = 0;
	unsigned int audio_buf_index = 0;

private:
	SDL_Texture * texture = nullptr;

	SwsContext* sws_context = nullptr;
	SwrContext* swr_context = nullptr;

	SDL_Thread* parse_thread_id = nullptr;

	bool play_video_with_delay = false;
	p2Timer delay;
	float delay_time = 0.0F;
	int id_video = 0;

	u1Label* skip_video_label = nullptr;
	p2Timer skip_time{false};
	float time_started = 0.0F;

};

#endif
