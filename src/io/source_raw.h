#ifndef AUBIO_SOURCE_RAW
#define AUBIO_SOURCE_RAW

#include <stdint.h>
#include "../../../src/lib_ad.h"
#include "../aubio.h"

// Remplace les infos transmises normalement 
// par le header d'un fichier audio
struct aubio_source_raw_data
{
	smpl_t * buffer;
	size_t size_buffer;
	uint8_t size_point;
	uint32_t samplerate;
	uint8_t nb_channels;
};
typedef struct aubio_source_raw_data aubio_source_raw_data_t;

// Initalise un object aubio_source_t avec des callbacks personalisés
aubio_source_t * new_aubio_source_raw(aubio_source_raw_data_t* aubio_source_raw_data, uint_t samplerate, uint_t hop_size);

// CALLBACKS
void aubio_source_raw_do(aubio_source_t * s, fvec_t *data, uint_t *read);
void aubio_source_raw_do_multi(aubio_source_t * s, fmat_t *data, uint_t *read);
unsigned int aubio_source_raw_get_samplerate(aubio_source_t * s);
unsigned int aubio_source_raw_get_channels(aubio_source_t * s);
unsigned int aubio_source_raw_get_duration(aubio_source_t * s);
unsigned int aubio_source_raw_seek(aubio_source_t * s, uint_t seek);
unsigned int aubio_source_raw_close(aubio_source_t * s);
void del_aubio_source_raw(aubio_source_t * s);



#endif
