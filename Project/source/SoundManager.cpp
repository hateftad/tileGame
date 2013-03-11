
#include "SoundManager.h"

FMOD_RESULT F_CALLBACK eventcallback(FMOD_EVENT *event, FMOD_EVENT_CALLBACKTYPE type, void *param1, void *param2, void *userdata)
{
#ifdef _DEBUG
	if (type == FMOD_EVENT_CALLBACKTYPE_NET_MODIFIED)
	{
		unsigned int t = (unsigned int)param2;
		printf("%p %s %f (%d)\n", event,
			(unsigned int)param1 == FMOD_EVENTPROPERTY_VOLUME ? "volume" : FMOD_EVENTPROPERTY_PITCH ? "pitch" : "???",
			*((float *)&t),
			(unsigned int)userdata);
	}
#endif

	return FMOD_OK;
}



SoundManager::SoundManager()
{
	m_eventsystem = 0;
	m_system = 0;
	m_bInitialized = false;

	ERRCHECK( result = FMOD::EventSystem_Create(&m_eventsystem) );
	ERRCHECK( result = m_eventsystem->getSystemObject(&m_system) );


	ERRCHECK( result = FMOD::NetEventSystem_Init(m_eventsystem, 17997) );

	int numdrivers = 0;
	int driver = 0;

	ERRCHECK( result = m_system->getNumDrivers(&numdrivers) );
	ERRCHECK( result = m_system->getDriverCaps(driver, &m_caps, 0, &m_speakermode) );
	ERRCHECK( result = m_system->setSpeakerMode(m_speakermode) );
	ERRCHECK( result = m_system->setSoftwareChannels(100) );	

	if (m_caps & FMOD_CAPS_HARDWARE_EMULATED)						
	{										
		ERRCHECK( result = m_system->setDSPBufferSize(1024, 10) );	
	}

	char name[256];
	ERRCHECK( result = m_system->getDriverInfo(0, name, 256, 0) );
	std::cout << "Using sound driver: " << name << std::endl;

	if (strstr(name, "SigmaTel"))	
	{
		ERRCHECK( result = m_system->setSoftwareFormat(48000, FMOD_SOUND_FORMAT_PCMFLOAT, 0,0, FMOD_DSP_RESAMPLER_LINEAR) );
	}



}

void SoundManager::Initialize( const char* p_MediaPath, const char* p_FEV )
{
	if (m_bInitialized) return;

	m_MediaPath = p_MediaPath;
	m_FEV = p_FEV;
	userdata = 0;

	m_lastpos.x = 0.0f; m_lastpos.y = 0.0f; m_lastpos.z = 0.0f;
	m_forward.x = 0.0f; m_forward.y = 0.0f; m_forward.z = 1.0f;
	m_up.x = 0.0f; m_up.y = 1.0f; m_up.z = 0.0f;

	m_listenerpos = m_lastpos;

	DISTANCEFACTOR = 100.0f;
	ERRCHECK( result = m_system->set3DSettings(1.0, DISTANCEFACTOR, 1.0f) );

	ERRCHECK( result = m_eventsystem->init(256, FMOD_INIT_NORMAL, 0, FMOD_EVENT_INIT_NORMAL) );

	if (result == FMOD_ERR_OUTPUT_CREATEBUFFER)   
	{
		ERRCHECK( result = m_system->setSpeakerMode(FMOD_SPEAKERMODE_STEREO) );

		//result = system->init(100, FMOD_INIT_NORMAL, 0); /* Replace with whatever channel count and flags you use! */
		//result = system->init(100, FMOD_INIT_3D_RIGHTHANDED, 0);
		ERRCHECK( result = m_eventsystem->init(256, FMOD_INIT_NORMAL, 0, FMOD_EVENT_INIT_NORMAL) );
	}

	ERRCHECK( result = m_eventsystem->setMediaPath(static_cast<const char*>(p_MediaPath)) );
	ERRCHECK( result = m_eventsystem->load(p_FEV, 0, 0) );
	ERRCHECK( result = m_eventsystem->getGroup("GameSounds/SFX", FMOD_EVENT_DEFAULT, &m_eventgroup) );

	m_bInitialized = true;
}

void SoundManager::Update()
{

	m_lastpos = m_listenerpos;


	ERRCHECK( result = m_system->set3DListenerAttributes(0, &m_listenerpos, &m_velocity, &m_forward, &m_up) );


	ERRCHECK( result = m_system->update() );

	ERRCHECK( result = m_eventsystem->update() );

	ERRCHECK( result = FMOD::NetEventSystem_Update() );
}

SoundManager* SoundManager::m_instance = nullptr;

SoundManager* SoundManager::Instance()
{
	if (m_instance == nullptr)
	{
		m_instance = new SoundManager();
		return m_instance;
	}

	return m_instance;
}


void SoundManager::Destroy()
{
	delete m_instance;
	m_instance = nullptr;
}


void SoundManager::PlayEvent( std::string eventName )
{
	ERRCHECK( result = m_eventgroup->getEvent(eventName.c_str(), FMOD_EVENT_DEFAULT, &m_eventMap[eventName]) );
	ERRCHECK( result = m_eventMap[eventName]->setCallback(eventcallback, (void *)(userdata++)) );

	ERRCHECK( result = m_eventMap[eventName]->start() );
}

void SoundManager::StopEvent( std::string eventName )
{
	if (m_eventMap[eventName])
	{
		ERRCHECK( result = m_eventMap[eventName]->stop() );

#ifdef _DEBUG
		std::cout << "Stopping event " << std::endl;
#endif
	}
}

void SoundManager::ERRCHECK(FMOD_RESULT result)
{
#ifdef _DEBUG

	if (result != FMOD_OK)
	{
		std::cout << "FMOD error! (" << result << ") " << FMOD_ErrorString(result) << std::endl;
	}

#endif
}

SoundManager::~SoundManager()
{


	if (m_eventsystem)
	{
		ERRCHECK( result = m_eventsystem->release() );
	}

	ERRCHECK( result = FMOD::NetEventSystem_Shutdown() );
}
