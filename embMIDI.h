#ifndef EMBMIDI_INCLUDED
#define EMBMIDI_INCLUDED
#include "soundbank.h"
#define SHIFT 12
#define NOTE 50
#define INTERPOLATION
/*unsigned int midiFrequencies[128]={0x82d0, 0x8a97, 0x92d5, 0x9b90, 0xa4d0, 0xae9d, 0xb8ff, 0xc3ff, 
								0xcfa7, 0xdc00, 0xe914, 0xf6f1, 0x105a0, 0x1152e, 0x125aa, 0x13720, 
								0x149a0, 0x15d3a, 0x171fe, 0x187fe, 0x19f4e, 0x1b800, 0x1d229, 0x1ede2, 
								0x20b40, 0x22a5d, 0x24b54, 0x26e41, 0x29341, 0x2ba74, 0x2e3fd, 0x30ffd, 
								0x33e9c, 0x37000, 0x3a453, 0x3dbc4, 0x41680, 0x454bb, 0x496a8, 0x4dc82, 
								0x52682, 0x574e9, 0x5c7fa, 0x61ffb, 0x67d38, 0x6e000, 0x748a7, 0x7b788, 
								0x82d01, 0x8a976, 0x92d51, 0x9b904, 0xa4d05, 0xae9d3, 0xb8ff4, 0xc3ff6, 
								0xcfa70, 0xdc000, 0xe914f, 0xf6f11, 0x105a02, 0x1152ec, 0x125aa2, 0x137208, 
								0x149a0a, 0x15d3a6, 0x171fe9, 0x187fed, 0x19f4e0, 0x1b8000, 0x1d229e, 0x1ede22, 
								0x20b404, 0x22a5d8, 0x24b545, 0x26e410, 0x293415, 0x2ba74d, 0x2e3fd2, 0x30ffda, 
								0x33e9c0, 0x370000, 0x3a453d, 0x3dbc44, 0x416809, 0x454bb0, 0x496a8b, 0x4dc820, 
								0x52682a, 0x574e9b, 0x5c7fa4, 0x61ffb5, 0x67d380, 0x6e0000, 0x748a7b, 0x7b7888, 
								0x82d013, 0x8a9760, 0x92d517, 0x9b9041, 0xa4d054, 0xae9d37, 0xb8ff49, 0xc3ff6a, 
								0xcfa700, 0xdc0000, 0xe914f6, 0xf6f110, 0x105a026, 0x1152ec0, 0x125aa2e, 0x1372082, 
								0x149a0a8, 0x15d3a6e, 0x171fe92, 0x187fed4, 0x19f4e00, 0x1b80000, 0x1d229ec, 0x1ede220, 
								0x20b404c, 0x22a5d80, 0x24b545c, 0x26e4104, 0x2934150, 0x2ba74dc, 0x2e3fd24, 0x30ffda8};*/
unsigned int midiOctave[12]={0x105a02, 0x1152ec, 0x125aa2, 0x137208, 0x149a0a, 0x15d3a6, 0x171fe9, 0x187fed, 0x19f4e0, 0x1b8000, 0x1d229e, 0x1ede22};
/*unsigned int bendTable[256]={0xf1a, 0xf1b, 0xf1d, 0xf1f, 0xf21, 0xf22, 0xf24, 0xf26, 0xf28, 0xf29, 0xf2b, 0xf2d, 0xf2f, 0xf30, 0xf32, 0xf34, 0xf36, 
0xf37, 0xf39, 0xf3b, 0xf3d, 0xf3e, 0xf40, 0xf42, 0xf44, 0xf45, 0xf47, 0xf49, 0xf4b, 0xf4d, 0xf4e, 0xf50, 0xf52, 
0xf54, 0xf55, 0xf57, 0xf59, 0xf5b, 0xf5c, 0xf5e, 0xf60, 0xf62, 0xf64, 0xf65, 0xf67, 0xf69, 0xf6b, 0xf6c, 0xf6e, 
0xf70, 0xf72, 0xf74, 0xf75, 0xf77, 0xf79, 0xf7b, 0xf7d, 0xf7e, 0xf80, 0xf82, 0xf84, 0xf86, 0xf87, 0xf89, 0xf8b, 
0xf8d, 0xf8e, 0xf90, 0xf92, 0xf94, 0xf96, 0xf97, 0xf99, 0xf9b, 0xf9d, 0xf9f, 0xfa1, 0xfa2, 0xfa4, 0xfa6, 0xfa8, 
0xfaa, 0xfab, 0xfad, 0xfaf, 0xfb1, 0xfb3, 0xfb4, 0xfb6, 0xfb8, 0xfba, 0xfbc, 0xfbd, 0xfbf, 0xfc1, 0xfc3, 0xfc5, 
0xfc7, 0xfc8, 0xfca, 0xfcc, 0xfce, 0xfd0, 0xfd2, 0xfd3, 0xfd5, 0xfd7, 0xfd9, 0xfdb, 0xfdd, 0xfde, 0xfe0, 0xfe2, 
0xfe4, 0xfe6, 0xfe8, 0xfe9, 0xfeb, 0xfed, 0xfef, 0xff1, 0xff3, 0xff4, 0xff6, 0xff8, 0xffa, 0xffc, 0xffe, 0x1000, 
0x1001, 0x1003, 0x1005, 0x1007, 0x1009, 0x100b, 0x100c, 0x100e, 0x1010, 0x1012, 0x1014, 0x1016, 0x1018, 0x1019, 
0x101b, 0x101d, 0x101f, 0x1021, 0x1023, 0x1025, 0x1027, 0x1028, 0x102a, 0x102c, 0x102e, 0x1030, 0x1032, 0x1034, 
0x1035, 0x1037, 0x1039, 0x103b, 0x103d, 0x103f, 0x1041, 0x1043, 0x1044, 0x1046, 0x1048, 0x104a, 0x104c, 0x104e, 
0x1050, 0x1052, 0x1054, 0x1055, 0x1057, 0x1059, 0x105b, 0x105d, 0x105f, 0x1061, 0x1063, 0x1065, 0x1066, 0x1068, 
0x106a, 0x106c, 0x106e, 0x1070, 0x1072, 0x1074, 0x1076, 0x1078, 0x1079, 0x107b, 0x107d, 0x107f, 0x1081, 0x1083, 
0x1085, 0x1087, 0x1089, 0x108b, 0x108d, 0x108e, 0x1090, 0x1092, 0x1094, 0x1096, 0x1098, 0x109a, 0x109c, 0x109e, 
0x10a0, 0x10a2, 0x10a4, 0x10a5, 0x10a7, 0x10a9, 0x10ab, 0x10ad, 0x10af, 0x10b1, 0x10b3, 0x10b5, 0x10b7, 0x10b9, 
0x10bb, 0x10bd, 0x10bf, 0x10c0, 0x10c2, 0x10c4, 0x10c6, 0x10c8, 0x10ca, 0x10cc, 0x10ce, 0x10d0, 0x10d2, 0x10d4, 
0x10d6, 0x10d8, 0x10da, 0x10dc, 0x10de, 0x10e0, 0x10e1, 0x10e3, 0x10e5, 0x10e7, 0x10e9, 0x10eb, 0x10ed, 0x10ef, 0x10f1};*/
/*int bendTable[256]={-229, -228, -226, -224, -222, -221, -219, -217, -215, -214, -212, -210, -208, -207, -205, -203, 
-201, -200, -198, -196, -194, -193, -191, -189, -187, -186, -184, -182, -180, -178, -177, -175, 
-173, -171, -170, -168, -166, -164, -163, -161, -159, -157, -155, -154, -152, -150, -148, -147, 
-145, -143, -141, -139, -138, -136, -134, -132, -130, -129, -127, -125, -123, -121, -120, -118, 
-116, -114, -113, -111, -109, -107, -105, -104, -102, -100, -98, -96, -94, -93, -91, -89, -87, 
-85, -84, -82, -80, -78, -76, -75, -73, -71, -69, -67, -66, -64, -62, -60, -58, -56, -55, -53, 
-51, -49, -47, -45, -44, -42, -40, -38, -36, -34, -33, -31, -29, -27, -25, -23, -22, -20, -18, 
-16, -14, -12, -11, -9, -7, -5, -3, -1, 0, 1, 3, 5, 7, 9, 11, 
12, 14, 16, 18, 20, 22, 24, 25, 27, 29, 31, 33, 35, 37, 39, 40, 
42, 44, 46, 48, 50, 52, 53, 55, 57, 59, 61, 63, 65, 67, 68, 70, 
72, 74, 76, 78, 80, 82, 84, 85, 87, 89, 91, 93, 95, 97, 99, 101, 
102, 104, 106, 108, 110, 112, 114, 116, 118, 120, 121, 123, 125, 
127, 129, 131, 133, 135, 137, 139, 141, 142, 144, 146, 148, 150, 
152, 154, 156, 158, 160, 162, 164, 165, 167, 169, 171, 173, 175, 
177, 179, 181, 183, 185, 187, 189, 191, 192, 194, 196, 198, 200, 
202, 204, 206, 208, 210, 212, 214, 216, 218, 220, 222, 224, 225, 
227, 229, 231, 233, 235, 237, 239, 241};*/
int bendTable2semitone[256]={-446, -443, -440, -436, -433, -430, -427, -423, -420, -417, -413, -410, -407, -403, -400, -397, -393, -390, -387, -383, -380, -377, -373, -370, -366, -363, -360, -356, -353, -350, -346, -343, -339, -336, -333, -329, -326, -322, -319, -316, -312, -309, -305, -302, -299, -295, -292, -288, -285, -281, -278, -274, -271, -268, -264, -261, -257, -254, -250, -247, -243, -240, -236, -233, -229, -226, -222, -219, -215, -212, -208, -205, -201, -198, -194, -191, -187, -184, -180, -177, -173, -170, -166, -163, -159, -155, -152, -148, -145, -141, -138, -134, -130, -127, -123, -120, -116, -113, -109, -105, -102, -98, -94, -91, -87, -84, -80, -76, -73, -69, -66, -62, -58, -55, -51, -47, -44, -40, -36, -33, -29, -25, -22, -18, -14, -11, -7, -3, 0, 3, 7, 11, 14, 18, 22, 25, 29, 33, 37, 40, 44, 48, 52, 55, 59, 63, 67, 70, 74, 78, 82, 85, 89, 93, 97, 101, 104, 108, 112, 116, 120, 123, 127, 131, 135, 139, 142, 146, 150, 154, 158, 162, 165, 169, 173, 177, 181, 185, 189, 192, 196, 200, 204, 208, 212, 216, 220, 224, 227, 231, 235, 239, 243, 247, 251, 255, 259, 263, 267, 271, 275, 278, 282, 286, 290, 294, 298, 302, 306, 310, 314, 318, 322, 326, 330, 334, 338, 342, 346, 350, 354, 358, 362, 366, 370, 374, 378, 382, 386, 390, 394, 399, 403, 407, 411, 415, 419, 423, 427, 431, 435, 439, 443, 447, 452, 456, 460, 464, 468, 472, 476, 480, 485, 489, 493, 497};
typedef struct synthchannel{
	unsigned char velocity;
	unsigned char midiNote;
	unsigned char realNote;
	unsigned char midiChannel;
	unsigned short frequency;
	unsigned int phaseinc;
	unsigned int samppos;
	unsigned int loop;
	unsigned int loopStart;
	unsigned int loopEnd;
	unsigned char* sample;
	unsigned int samplen;
	unsigned int active;
	unsigned int busy;/*Note still playing but allocation freed for Note-Stealing*/
	unsigned int noteage;
	unsigned int instrument;
}SynthChannel;
typedef struct midichannel{
	unsigned char program;
	unsigned char bankMSB;
	unsigned char bankLSB;
	unsigned char volume;
	unsigned short pitchbend;
	
}MidiChannel;
#define NUMCHAN 24
SynthChannel channels[NUMCHAN];
MidiChannel midichannels[16];
int currentNoteAge=0;
unsigned int outsamplerate;
//unsigned int samppos=0;
//unsigned int phaseinc=1.0*(1<<SHIFT);
void lwsynth_init(unsigned int samplerate){
	int i=0;
	outsamplerate=samplerate;
	memset(channels,0,sizeof(channels));
	for(i=0;i<16;i++){
		midichannels[i].volume=100;
		midichannels[i].pitchbend=8192;
	}
}
/*unsigned int midiNoteToFrequency(unsigned char midinote){
	return midiFrequencies[midinote];
	
}*/
unsigned int calcPhaseInc(int outrate,int samplerate, int samplefreq, int notefreq){
		return (((samplerate<<SHIFT)/samplefreq)*notefreq)/outrate;
	
}
/*unsigned int calcPhaseIncShifted(int outrate,int samplerate, int samplefreq, int notefreqShifted){
		return ((((samplerate<<SHIFT)/samplefreq)*notefreqShifted)/outrate)>>3;
	
}*/
/*unsigned int calcPhaseIncAccurately(int outrate,int samplerate, int samplefreq, int notefreqShifted, int midinote){
		if(midinote>=60){
			return ((((samplerate<<SHIFT)/samplefreq)*(notefreqShifted>>12))/outrate);
		}else{
			return ((((samplerate<<SHIFT)/samplefreq)*(notefreqShifted>>9))/outrate)>>3;
		}
		
	
}*/
unsigned int calcPhaseIncrease(int outrate,int samplerate, int samplenote, int midinote, int pitchBend){
		int notefreq=midiOctave[midinote%12];
		int samplenotefreq=midiOctave[samplenote%12];
		int sampleoct=(samplenote/12);
		int noteoct=(midinote/12);
		int phaseInc=0;
		int bendamount=bendTable2semitone[(pitchBend)>>6];
		if(sampleoct>=5){
			samplenotefreq=samplenotefreq<<(sampleoct-5);
		}else{
			samplenotefreq=samplenotefreq>>(5-sampleoct);
		}
		phaseInc=((((samplerate<<SHIFT)/(samplenotefreq>>12))*(notefreq>>9))/outrate)>>3;
		
		phaseInc+=(phaseInc*(bendamount/**2*/))>>12;
		if(noteoct>=5){
			phaseInc=phaseInc<<(noteoct-5);
		}else{
			phaseInc=phaseInc>>(5-noteoct);
		}
		
		return phaseInc;
}
signed short rendersample(SynthChannel* c){
	//signed short* piano=(signed short*)rawData;
	signed short samp;
	int samp1pos;
	signed short sample1,sample2;
	//int size=sizeof(rawData)/2;
	if(c->samppos>=c->samplen<<SHIFT&&c->loop==0){/*End of sample*/
		/*c->samppos-=c->samplen<<SHIFT;*/
		/*End One-Shot*/
			c->active=0;
			c->busy=0;
			return 0;
		
	}else if(c->samppos>=c->loopEnd<<SHIFT&&c->loop==1){/*Loop overshoot*/
			int newpos=c->samppos-(c->loopEnd<<SHIFT);
			c->samppos=(c->loopStart<<SHIFT)+newpos;
		/*}*/
			if(c->samppos>=c->loopEnd<<SHIFT){/*Too high frequency, avoid overrun*/
				c->active=0;
				c->busy=0;
				return 0;
			}
	}
	samp1pos=(int)c->samppos>>SHIFT;
	
	sample1=(signed int)((int)(c->sample[samp1pos]))<<8;
#ifdef INTERPOLATION
	{
		int samp2pos=((int)c->samppos>>SHIFT)+1;
		/*sample2=c->sample[((int)c->samppos>>SHIFT)+1];*/
		sample2=(signed int)((int)(c->sample[samp2pos-(c->loopEnd-c->loopStart)*(samp2pos>=c->loopEnd)]))<<8;
		/*unsigned int proport=samppos-((samppos>>SHIFT)<<SHIFT);
		samp=(((1<<SHIFT)-proport*piano[((int)samppos>>SHIFT)])>>SHIFT)+((proport*piano[((int)samppos>>SHIFT)+1])>>SHIFT);*/
		unsigned int proport=c->samppos-((c->samppos>>SHIFT)<<SHIFT);
		int var1=(int)(((1<<SHIFT)-proport)*(int)sample1)/*/(1<<SHIFT)*/;
		int var2=(int)(proport*(int)sample2)/*/(1<<SHIFT)*/;
		samp=((var1+var2)>>SHIFT);
		/*float proport=((float)(samppos)/(1<<SHIFT))-(samppos>>SHIFT);
		samp=(1.0-proport)*piano[((int)samppos>>SHIFT)]+proport*piano[((int)samppos>>SHIFT)+1];*/
	}
	
#else
	samp=sample1;
#endif
	c->samppos+=c->phaseinc;
	
	samp=((int)(samp*c->velocity*midichannels[c->midiChannel].volume))>>14;
	return samp;
}

void getsamples(signed short* buf,int num){
	int i,j;
	signed int mixvar=0;
	for(i=0;i<num;i++){
		mixvar=0;
		for(j=0;j<NUMCHAN;j++){
			if(channels[j].active==1){
				mixvar+=rendersample(&channels[j]);
				/*printf("mixvar=%i\n",mixvar);*/
			}
		}
		if(mixvar>32767){
			mixvar=32767;
		}else if(mixvar<-32768){
			mixvar=-32768;
		}
		buf[i]=mixvar;
	}
	
}

void noteOn(unsigned char midiChannel, unsigned char note, unsigned char velocity){
	int i;
	char voice=-1;
	for(i=0;i<NUMCHAN;i++){
		if(channels[i].active==0){
			voice=i;
			break;
		}
		
	}
	if(voice==-1){/*Note Steal*/
		for(i=0;i<NUMCHAN;i++){
			if(channels[i].busy==0){/*Steal Note Already Off but still playing*/
				voice=i;
				break;
			}
		
		}
		if(voice==-1){
			unsigned int minagechan=0;
			for(i=0;i<NUMCHAN;i++){
				if(channels[i].noteage<channels[minagechan].noteage){
					minagechan=i;
				}	
		
			}
			voice=minagechan;
		}
		
	}
	if(midiChannel==9){/*Drum*/
		DrumInstrument* drum;
		int drumnum=drumMap[note];
		if(drumnum==-1){
			return;
		}else{
			drum=&drums[drumnum];
		}
		channels[voice].midiNote=note;
		channels[voice].realNote=drum->playNote;
		channels[voice].midiChannel=midiChannel;
		/*channels[voice].phaseinc=calcPhaseIncAccurately(outsamplerate,drum->sampleRate, midiNoteToFrequency(drum->recordedNote)>>12, midiFrequencies[drum->playNote],drum->playNote);*/
		channels[voice].phaseinc=calcPhaseIncrease(outsamplerate,drum->sampleRate, drum->recordedNote,drum->playNote,midichannels[midiChannel].pitchbend);
		/*channels[voice].phaseinc=calcPhaseInc(outsamplerate,drum->sampleRate, midiNoteToFrequency(drum->recordedNote)>>12, midiFrequencies[drum->playNote]>>12);*/
		channels[voice].samppos=0;
		channels[voice].sample=drum->wavetable;
		channels[voice].samplen=drum->length;
		channels[voice].velocity=velocity;
		channels[voice].loop=instruments[programs[midichannels[midiChannel].program]].looped;
		channels[voice].loopStart=instruments[programs[midichannels[midiChannel].program]].loopStart;
		channels[voice].loopEnd=instruments[programs[midichannels[midiChannel].program]].loopEnd;
		channels[voice].active=1;
		channels[voice].busy=1;
		channels[voice].noteage=currentNoteAge;
		channels[voice].instrument=drumnum;
		
	}else{
		channels[voice].midiNote=note;
		channels[voice].realNote=note;
		channels[voice].midiChannel=midiChannel;
		/*channels[voice].phaseinc=calcPhaseIncAccurately(outsamplerate,instruments[programs[midichannels[midiChannel].program]].sampleRate, midiNoteToFrequency(instruments[programs[midichannels[midiChannel].program]].recordedNote)>>12, midiFrequencies[note],note);*/
		channels[voice].phaseinc=calcPhaseIncrease(outsamplerate,instruments[programs[midichannels[midiChannel].program]].sampleRate, instruments[programs[midichannels[midiChannel].program]].recordedNote, note,midichannels[midiChannel].pitchbend);
		/*channels[voice].phaseinc=calcPhaseInc(outsamplerate,instruments[programs[midichannels[midiChannel].program]].sampleRate, midiNoteToFrequency(instruments[programs[midichannels[midiChannel].program]].recordedNote)>>12, midiFrequencies[note]>>12);*/
		channels[voice].samppos=0;
		channels[voice].sample=instruments[programs[midichannels[midiChannel].program]].wavetable;
		channels[voice].samplen=instruments[programs[midichannels[midiChannel].program]].length;
		channels[voice].velocity=velocity;
		channels[voice].loop=instruments[programs[midichannels[midiChannel].program]].looped;
		channels[voice].loopStart=instruments[programs[midichannels[midiChannel].program]].loopStart;
		channels[voice].loopEnd=instruments[programs[midichannels[midiChannel].program]].loopEnd;
		channels[voice].active=1;
		channels[voice].busy=1;
		channels[voice].noteage=currentNoteAge;
		channels[voice].instrument=programs[midichannels[midiChannel].program];
		
	}
	currentNoteAge++;
	return;
}
void noteOff(unsigned char midiChannel, unsigned char note){
	int i;
	for(i=0;i<NUMCHAN;i++){
		if(channels[i].active==1&&channels[i].midiChannel==midiChannel&&channels[i].midiNote==note){
			channels[i].busy=0;
			if(midiChannel!=9){
				channels[i].active=0;
			}
			
		}
		
	}
}
void programChange(unsigned char midiChannel, unsigned char program){
	midichannels[midiChannel].program=program;
	
}
void controlChange(unsigned char midiChannel, unsigned char control, unsigned char controlvalue){
	switch(control){
		case 7:
			midichannels[midiChannel].volume=controlvalue;
			break;
		
	}
}
void pitchBend(unsigned char midiChannel, signed short bendamount){
	int i=0;
	midichannels[midiChannel].pitchbend=bendamount;
	for(i=0;i<NUMCHAN;i++){
		if(channels[i].active==1&&channels[i].midiChannel==midiChannel){
			/*channels[i].busy=0;
			if(midiChannel!=9){
				channels[i].active=0;
			}*/
			if(midiChannel!=9){
				channels[i].phaseinc=calcPhaseIncrease(outsamplerate,instruments[channels[i].instrument].sampleRate, instruments[channels[i].instrument].recordedNote, channels[i].realNote,midichannels[midiChannel].pitchbend);
			}else{
				channels[i].phaseinc=calcPhaseIncrease(outsamplerate,instruments[channels[i].instrument].sampleRate, drums[channels[i].instrument].recordedNote, drums[channels[i].instrument].playNote,midichannels[midiChannel].pitchbend);
			}
		}
		
	}
	
}
#endif