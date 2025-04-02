#include <AudioManager.h>

#include <exception>
#include <iostream>

#include <MediaManager.h>
#include <SDL_mixer.h>

AudioManager* AudioManager::instance = nullptr;

AudioManager::AudioManager() {

	if (instance)
		throw std::exception("AudioManager can only have one instance!");

	instance = this;

	Mix_AllocateChannels(MAX_CHANNEL);

}

AudioManager::~AudioManager() {

	instance = nullptr;

}

void AudioManager::PlayOneShot(MediaSFX mediaSFX) {

	Mix_PlayChannel(-1, MediaManager::Instance()->GetSFX(mediaSFX), 0);

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