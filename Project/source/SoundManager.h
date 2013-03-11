#ifndef SOUNDMGR_H
#define SOUNDMGR_H

#include <iostream>
#include <string>
#include <map>
#include <fmod.hpp>
#include <fmod_errors.h>
#include <fmod_event.hpp>
#include <fmod_event_net.hpp>


#define MAX_SOUNDS	32
#define MAX_SONGS	32
#define MAX_CHANNELS	64


class SoundManager
{
public:
	void Initialize( const char* p_MediaPath, const char* m_FEV );
	void Update();

	void PlayEvent(std::string eventName);
	void StopEvent( std::string eventName );
	
	static SoundManager* Instance();

	void Destroy();
	FMOD::System *m_system;
	FMOD::EventSystem *m_eventsystem;
	FMOD::EventGroup *m_eventgroup;

private:
	SoundManager();
	SoundManager( const SoundManager& );
	SoundManager& operator=( const SoundManager& );
	~SoundManager();
	
	static SoundManager *m_instance; 

	std::map<std::string, FMOD::Event*> m_eventMap;

	FMOD_VECTOR	m_listenerpos;
	FMOD_VECTOR	m_lastpos;
	FMOD_VECTOR	m_forward;
	FMOD_VECTOR	m_up;
	FMOD_VECTOR	m_velocity;

	FMOD_RESULT	result;
	unsigned int m_version;
	FMOD_SPEAKERMODE m_speakermode;
	FMOD_CAPS m_caps;

	float DISTANCEFACTOR;

	float m_deltaTime;
	bool m_bInitialized;

	std::string m_MediaPath;
	std::string	m_FEV;
	int	userdata;

	void ERRCHECK(FMOD_RESULT result);
};


#endif