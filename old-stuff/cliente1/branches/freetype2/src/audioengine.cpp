/***************************************************************************
 *   Copyright (C) 2007 by Esteban Torre   *
 *   esteban.torre@gmail.com   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/



#include "audioengine.h"
#include <iostream>
#include <sstream>
#include "configdata.h"
#include <stdio.h>
#include <string.h>

int audioengine::actual_theme = 0;
Mix_Music* audioengine::music = NULL;

void audioengine::end_play()
{
	
	Mix_FreeMusic(music);
	std::stringstream theme;
	actual_theme++;
	
	if(actual_theme>3) //TODO: hardcode
		actual_theme=1;
	theme << ConfigData::GetPath("audio") << actual_theme << ".ogg";
	
	music = Mix_LoadMUS(theme.str().c_str());
	if(music != NULL) 
	{
		if(Mix_PlayMusic(music, 1) == -1) //Ad infinitum :D
		{
			//TODO:BLA BLA
		}
	}
}
void audioengine::init()
{
	if(ConfigData::Mute) return;
	std::cout << "Iniciando sistema de musiquitas:";
	if(SDL_InitSubSystem(SDL_INIT_AUDIO)!=0){
		//TODO: bla bla bla
		std::cout << " No andubo =(" << std::endl;
	}
	std::cout << " casiii";
	int audio_rate = 44100;
	Uint16 audio_format = AUDIO_S16SYS;
	int audio_channels = 2;
	int audio_buffers = 4096;
	if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) {
		//TODO: ble bli blo blu
		std::cout << " pero no llegó :-(" << std::endl;
	}
	Mix_AllocateChannels(32);
	std::cout << " Y ADENTROOO!" << std::endl;
	memset(sounds,0,sizeof(Mix_Chunk*)*255);
	initialized=true;
}

void audioengine::play_music()
{
	if(ConfigData::Mute) return;
	if(!initialized) return;
	std::stringstream theme;
	actual_theme = 1;
	theme << ConfigData::GetPath("audio") << actual_theme << ".ogg";

	music = Mix_LoadMUS(theme.str().c_str());
	Mix_HookMusicFinished(audioengine::end_play);
	
	if(music != NULL) 
	{
		if(Mix_PlayMusic(music, 1) == -1) //Ad infinitum :D
		{
			//TODO:BLA BLA
		}
	}
	Mix_VolumeMusic(MIX_MAX_VOLUME/5);
}

void audioengine::play_wav(Uint32 que)
{
	if(ConfigData::Mute) return;
	if(!initialized) return;
	//TODO: Algo mejor para el magnament de memoria de los sonidos.
	if ((que >= 255) || (que<1)) return;
	if(!sounds[que]){
		std::stringstream wav;
		wav.str("");
		wav << ConfigData::GetPath("audio") << que << ".wav";
 		sounds[que] = Mix_LoadWAV(wav.str().c_str());
	}

	if(Mix_PlayChannel(-1, sounds[que], 0)==-1) {
		printf("Mix_PlayChannel: %s\n",Mix_GetError());
	}
}

audioengine::~audioengine(){
	for(int i=0;i<255;i++){
		if(sounds[i])
			Mix_FreeChunk(sounds[i]);
	}
	Mix_HaltMusic();
	Mix_FreeMusic(music);
	Mix_CloseAudio();
}
