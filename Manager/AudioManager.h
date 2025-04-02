#pragma once

enum class MediaSong;
enum class MediaSFX;

class AudioManager {

private:

	const int MAX_CHANNEL = 1028;

private:

	static AudioManager* instance;

public:

	AudioManager();
	~AudioManager();
	void PlayOneShot(MediaSFX mediaSFX);
	void PlaySound(MediaSong mediaAudio);
	void StopSound(MediaSong mediaAudio);
	void PauseSound(MediaSong mediaAudio);
	void ResumeSound(MediaSong mediaAudio);

	static AudioManager* Instance();

};