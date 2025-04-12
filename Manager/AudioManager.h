#pragma once

enum class MediaSong;
enum class MediaSFX;

class AudioManager {

private:

	const int MAX_CHANNEL = 1028;
	const float MAX_DISTANCE = 300.0f;
	// How fast the volume falls off, calulated by (maxVolume - minVolume) / (minVolume * maxDistance),
	// with minVolume = 48
	const float VOLUME_FALLOFF_COEFFICIENT = 0.0055f;

private:

	static AudioManager* instance;

public:

	AudioManager();
	~AudioManager();
	void PlayOneShot(MediaSFX mediaSFX, float distance = 0.0f);
	void PlaySound(MediaSong mediaAudio);
	void StopSound(MediaSong mediaAudio);
	void PauseSound(MediaSong mediaAudio);
	void ResumeSound(MediaSong mediaAudio);

	static AudioManager* Instance();

};