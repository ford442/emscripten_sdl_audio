
#ifndef MODPLUG_H__INCLUDED
#define MODPLUG_H__INCLUDED
#ifdef __cplusplus
extern "C" {
#endif
struct _ModPlugFile;
typedef struct _ModPlugFile ModPlugFile;
struct _ModPlugNote{
unsigned char Note;
unsigned char Instrument;
unsigned char VolumeEffect;
unsigned char Effect;
unsigned char Volume;
unsigned char Parameter;
};
typedef struct _ModPlugNote ModPlugNote;
typedef void (*ModPlugMixerProc)(int *,unsigned long,unsigned long);
ModPlugFile *ModPlug_Load(const void *data,int size);
void ModPlug_Unload(ModPlugFile *file);
int ModPlug_Read(ModPlugFile *file,void *buffer,int size);
const char *ModPlug_GetName(ModPlugFile *file);
int ModPlug_GetLength(ModPlugFile *file);
void ModPlug_Seek(ModPlugFile *file,int millisecond);
enum _ModPlug_Flags{
MODPLUG_ENABLE_OVERSAMPLING=1 << 0,  /* Enable oversampling (*highly* recommended) */
MODPLUG_ENABLE_NOISE_REDUCTION=1 << 1,  /* Enable noise reduction */
MODPLUG_ENABLE_REVERB=1 << 2,  /* Enable reverb */
MODPLUG_ENABLE_MEGABASS=1 << 3,  /* Enable megabass */
MODPLUG_ENABLE_SURROUND=1 << 4   /* Enable surround sound. */
};
enum _ModPlug_ResamplingMode{
MODPLUG_RESAMPLE_NEAREST=0,  /* No interpolation (very fast, extremely bad sound quality) */
MODPLUG_RESAMPLE_LINEAR=1,  /* Linear interpolation (fast, good quality) */
MODPLUG_RESAMPLE_SPLINE=2,  /* Cubic spline interpolation (high quality) */
MODPLUG_RESAMPLE_FIR=3   /* 8-tap fir filter (extremely high quality) */
};
typedef struct _ModPlug_Settings{
int mFlags;  /* One or more of the MODPLUG_ENABLE_* flags above, bitwise-OR'ed */
int mChannels;       /* Number of channels - 1 for mono or 2 for stereo */
int mBits;           /* Bits per sample - 8, 16, or 32 */
int mFrequency;      /* Sampling rate - 11025, 22050, or 44100 */
int mResamplingMode; /* One of MODPLUG_RESAMPLE_*, above */

int mStereoSeparation; /* Stereo separation, 1 - 256 */
int mMaxMixChannels; /* Maximum number of mixing channels (polyphony), 32 - 256 */

int mReverbDepth;    /* Reverb level 0(quiet)-100(loud)      */
int mReverbDelay;    /* Reverb delay in ms, usually 40-200ms */
int mBassAmount;     /* XBass level 0(quiet)-100(loud)       */
int mBassRange;      /* XBass cutoff in Hz 10-100            */
int mSurroundDepth;  /* Surround level 0(quiet)-100(heavy)   */
int mSurroundDelay;  /* Surround delay in ms, usually 5-40ms */
int mLoopCount;      /* Number of times to loop.  Zero prevents looping.
	                        -1 loops forever. */
}ModPlug_Settings;
void ModPlug_GetSettings(ModPlug_Settings *settings);
void ModPlug_SetSettings(const ModPlug_Settings *settings);
unsigned int ModPlug_GetMasterVolume(ModPlugFile *file);
void ModPlug_SetMasterVolume(ModPlugFile *file,unsigned int cvol);
int ModPlug_GetCurrentSpeed(ModPlugFile *file);
void ModPlug_SetCurrentSpeed(ModPlugFile *file,int s);
int ModPlug_GetCurrentTempo(ModPlugFile *file);
int ModPlug_GetCurrentOrder(ModPlugFile *file);
int ModPlug_GetCurrentPattern(ModPlugFile *file);
int ModPlug_GetCurrentRow(ModPlugFile *file);
int ModPlug_GetPlayingChannels(ModPlugFile *file);
void ModPlug_SeekOrder(ModPlugFile *file,int order);
int ModPlug_GetModuleType(ModPlugFile *file);
char *ModPlug_GetMessage(ModPlugFile *file);
#ifndef MODPLUG_NO_FILESAVE
char ModPlug_ExportS3M(ModPlugFile *file,const char *filepath);
char ModPlug_ExportXM(ModPlugFile *file,const char *filepath);
char ModPlug_ExportMOD(ModPlugFile *file,const char *filepath);
char ModPlug_ExportIT(ModPlugFile *file,const char *filepath);
#endif // MODPLUG_NO_FILESAVE
unsigned int ModPlug_NumInstruments(ModPlugFile *file);
unsigned int ModPlug_NumSamples(ModPlugFile *file);
unsigned int ModPlug_NumPatterns(ModPlugFile *file);
unsigned int ModPlug_NumChannels(ModPlugFile *file);
unsigned int ModPlug_SampleName(ModPlugFile *file,unsigned int qual,char *buff);
unsigned int ModPlug_InstrumentName(ModPlugFile *file,unsigned int qual,char *buff);
ModPlugNote *ModPlug_GetPattern(ModPlugFile *file,int pattern,unsigned int *numrows);
void ModPlug_InitMixerCallback(ModPlugFile *file,ModPlugMixerProc proc);
void ModPlug_UnloadMixerCallback(ModPlugFile *file);
#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
