/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <AudioManager.h>

#include <exception>
#include <iostream>

#include <MediaManager.h>
#include <SDL_mixer.h>

/// ----------------------------------
/// STATIC FIELDS
/// ----------------------------------

AudioManager* AudioManager::instance = nullptr;

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

AudioManager::AudioManager() {

	if (instance)
		throw std::exception("AudioManager can only have one instance!");

	instance = this;

	Mix_AllocateChannels(MAX_CHANNEL);

}

AudioManager::~AudioManager() {

	instance = nullptr;

}

void AudioManager::PlayOneShot(MediaSFX mediaSFX, float distance) {

	if (distance > MAX_DISTANCE)
		// To far
		return;

	Mix_Chunk* chunk = MediaManager::Instance()->GetSFX(mediaSFX);

	Mix_VolumeChunk(chunk, MIX_MAX_VOLUME / (1.0f + VOLUME_FALLOFF_COEFFICIENT * distance));

	Mix_PlayChannel(-1, chunk, 0);

}

void AudioManager::PlaySound(MediaSong mediaAudio) {

}

void AudioManager::StopSound(MediaSong mediaAudio) {

}

void AudioManager::PauseSound(MediaSong mediaAudio) {

}

void AudioManager::ResumeSound(MediaSong mediaAudio) {

}

AudioManager* AudioManager::Instance() { return instance; }