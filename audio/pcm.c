#include "mpeg3private.h"
#include "mpeg3protos.h"

#include <stdlib.h>


mpeg3_pcm_t* mpeg3_new_pcm()
{
	mpeg3_pcm_t *result = calloc(1, sizeof(mpeg3_pcm_t));
	return result;
}



void mpeg3_delete_pcm(mpeg3_pcm_t *audio)
{
	free(audio);
}


int mpeg3_pcm_check(unsigned char *header)
{
	if(header[0] == ((MPEG3_PCM_START_CODE & 0xff000000) >> 24) &&
		header[1] == ((MPEG3_PCM_START_CODE & 0xff0000) >> 16) &&
		header[2] == ((MPEG3_PCM_START_CODE & 0xff00) >> 8) &&
		header[3] == (MPEG3_PCM_START_CODE & 0xff))
		return 0;
	else
		return 1;
}




int mpeg3_pcm_header(mpeg3_pcm_t *audio, unsigned char *data)
{
	if(mpeg3_pcm_check(data)) return 0;

/* Custom header generated by the demuxer */
	audio->samplerate = *(int32_t*)(data + 4);
	audio->bits = *(int32_t*)(data + 8);
	audio->channels = *(int32_t*)(data + 12);
	audio->framesize = *(int32_t*)(data + 16);

	return audio->framesize;
}

int mpeg3audio_dopcm(mpeg3_pcm_t *audio, 
	char *frame, 
	int frame_size, 
	float **output,
	int render)
{
	int bytes_per_sample = audio->bits / 8 * audio->channels;
	int output_size = (frame_size - PCM_HEADERSIZE) / bytes_per_sample;
	int i, j;
//printf("mpeg3audio_dopcm 2 %d\n", frame_size);

	if(render)
	{
		for(i = 0; i < audio->channels; i++)
		{
//printf("mpeg3audio_dopcm 3\n");
			float *output_channel = output[i];
//printf("mpeg3audio_dopcm 4\n");
			switch(audio->bits)
			{
				case 16:
				{
//printf("mpeg3audio_dopcm 5\n");
					unsigned char *input = frame + 
						PCM_HEADERSIZE + 
						audio->bits / 8 * i;
						int16_t sample;
//printf("mpeg3audio_dopcm 6\n");
					for(j = 0; j < output_size; j++)
					{
						sample = ((int16_t)(input[0])) << 8;
						sample |= input[1];
						*output_channel = (float)sample / 32767.0;
						input += bytes_per_sample;
						output_channel++;
					}
//printf("mpeg3audio_dopcm 7\n");
				}
					break;
			}
		}
	}

/*
 * printf("mpeg3audio_dopcm 2 %02x%02x%02x%02x\n", 
 * *(unsigned char*)(frame + PCM_HEADERSIZE + 0),
 * *(unsigned char*)(frame + PCM_HEADERSIZE + 1),
 * *(unsigned char*)(frame + PCM_HEADERSIZE + 2),
 * *(unsigned char*)(frame + PCM_HEADERSIZE + 3));
 */

	return output_size;
}