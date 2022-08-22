#include <stdio.h>
#include <stdlib.h>
#include <aubio/aubio.h>
#include <string.h>

#include "source_raw.h"

// FOR MACRO AUBIO_NEW AUBIO_ARRAY
#include "../aubio_priv.h"
//#include "../aubio/aubio-0.4.9/src/aubio.h"

typedef void (*aubio_source_do_t)(aubio_source_t * s, fvec_t *data, uint_t *read);
typedef void (*aubio_source_do_multi_t)(aubio_source_t * s, fmat_t *data, uint_t *read);
typedef uint_t (*aubio_source_get_samplerate_t)(aubio_source_t * s);
typedef uint_t (*aubio_source_get_channels_t)(aubio_source_t * s);
typedef uint_t (*aubio_source_get_duration_t)(aubio_source_t * s);
typedef uint_t (*aubio_source_seek_t)(aubio_source_t * s, uint_t seek);
typedef uint_t (*aubio_source_close_t)(aubio_source_t * s);
typedef void (*del_aubio_source_t)(aubio_source_t * s);

struct _aubio_source_t {
	void *source;
	aubio_source_do_t s_do;
	aubio_source_do_multi_t s_do_multi;
	aubio_source_get_samplerate_t s_get_samplerate;
	aubio_source_get_channels_t s_get_channels;
	aubio_source_get_duration_t s_get_duration;
	aubio_source_seek_t s_seek;
	aubio_source_close_t s_close;
	del_aubio_source_t s_del;
};



// CALLBACKS DEFINITION
void aubio_source_raw_do(aubio_source_t * s, fvec_t *data_vec, uint_t *read)
{
	uint64_t size_buffer = ((aubio_source_raw_data_t*)s)->size_buffer;
	uint64_t size_to_do = ((size_buffer - *read) >= 256) ? (256) : (size_buffer - *read);
	data_vec->length = size_buffer;

	if (!size_to_do) {
		// Averting the condition to break the loop to break
		*read=0;
		return;
	}

	memcpy(data_vec->data, 
		    ((aubio_source_raw_data_t*)s)->buffer + *read, 
		    size_to_do * sizeof(smpl_t));

	*read = (*read) + size_to_do;

	return;
}

void aubio_source_raw_do_multi(aubio_source_t * s, fmat_t *data, uint_t *read)
{
	printf("callback: aubio_source_raw_do_multi\n");

	return;
}

unsigned int aubio_source_raw_get_samplerate(aubio_source_t * s)
{

	if (s->source != NULL)
		return ((aubio_source_raw_data_t*)s)->samplerate;

	return 0;
}

unsigned int aubio_source_raw_get_channels(aubio_source_t * s)
{
	printf("callback: aubio_source_raw_get_channels\n");

	return 0;
}

unsigned int aubio_source_raw_get_duration(aubio_source_t * s)
{
	printf("callback: aubio_source_raw_get_duration\n");

	return 0;
}

unsigned int aubio_source_raw_seek(aubio_source_t * s, uint_t seek)
{
	printf("callback: aubio_source_raw_seek\n");

	return 0;
}

unsigned int aubio_source_raw_close(aubio_source_t * s)
{
	printf("callback: aubio_source_raw_close\n");

	return 0;
}

void del_aubio_source_raw(aubio_source_t * s)
{
	free(((aubio_source_raw_data_t*)s)->buffer);
	free((aubio_source_raw_data_t*)s);
	return;
}


// Test de notre source_raw
aubio_source_t * new_aubio_source_raw(aubio_source_raw_data_t* aubio_source_raw_data, uint_t samplerate, uint_t hop_size)
{
	aubio_source_t * s = AUBIO_NEW(aubio_source_t);


	if (s != NULL)
	{
		// CALLBACKS 
		s->s_do = (aubio_source_do_t)(aubio_source_raw_do);
		s->s_do_multi = (aubio_source_do_multi_t)(aubio_source_raw_do_multi);
		s->s_get_channels = (aubio_source_get_channels_t)(aubio_source_raw_get_channels);
		s->s_get_samplerate = (aubio_source_get_samplerate_t)(aubio_source_raw_get_samplerate);
		s->s_get_duration = (aubio_source_get_duration_t)(aubio_source_raw_get_duration);
		s->s_seek = (aubio_source_seek_t)(aubio_source_raw_seek);
		s->s_close = (aubio_source_close_t)(aubio_source_raw_close);
		s->s_del = (del_aubio_source_t)(del_aubio_source_raw);

		// source = structure custom raw_data
		s->source = aubio_source_raw_data;
	}

	return s;
}

