/***********************************************************************
Copyright (c) 2006-2011, Skype Limited. All rights reserved. 
Redistribution and use in source and binary forms, with or without 
modification, (subject to the limitations in the disclaimer below) 
are permitted provided that the following conditions are met:
- Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright 
notice, this list of conditions and the following disclaimer in the 
documentation and/or other materials provided with the distribution.
- Neither the name of Skype Limited, nor the names of specific 
contributors, may be used to endorse or promote products derived from 
this software without specific prior written permission.
NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED 
BY THIS LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND 
CONTRIBUTORS ''AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND 
FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE 
COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, 
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF 
USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON 
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
***********************************************************************/

#include "SKP_Silk_main.h"
#include "SKP_Silk_control.h"
#include "SKP_Silk_errors.h"

/* Check encoder control struct */
SKP_int check_control_input( 
    SKP_SILK_SDK_EncControlStruct        *encControl     /* I:   Control structure                               */
)
{
    SKP_assert( encControl != NULL );

    if( ( ( encControl->API_sampleRate        !=  8000 ) &&
          ( encControl->API_sampleRate        != 12000 ) &&
          ( encControl->API_sampleRate        != 16000 ) &&
          ( encControl->API_sampleRate        != 24000 ) && 
          ( encControl->API_sampleRate        != 32000 ) &&
          ( encControl->API_sampleRate        != 44100 ) &&
          ( encControl->API_sampleRate        != 48000 ) ) ||
        ( ( encControl->maxInternalSampleRate !=  8000 ) &&
          ( encControl->maxInternalSampleRate != 12000 ) &&
          ( encControl->maxInternalSampleRate != 16000 ) ) ||
        ( ( encControl->minInternalSampleRate !=  8000 ) &&
          ( encControl->minInternalSampleRate != 12000 ) &&
          ( encControl->minInternalSampleRate != 16000 ) ) ||
          ( encControl->minInternalSampleRate > encControl->maxInternalSampleRate ) ) {
        SKP_assert( 0 );
        return SKP_SILK_ENC_FS_NOT_SUPPORTED;
    }
    if( encControl->payloadSize_ms != 10 && 
        encControl->payloadSize_ms != 20 && 
        encControl->payloadSize_ms != 40 && 
        encControl->payloadSize_ms != 60 ) {
        SKP_assert( 0 );
        return SKP_SILK_ENC_PACKET_SIZE_NOT_SUPPORTED;
    }
    if( encControl->packetLossPercentage < 0 || encControl->packetLossPercentage > 100 ) {
        SKP_assert( 0 );
        return SKP_SILK_ENC_INVALID_LOSS_RATE;
    }
    if( encControl->useDTX < 0 || encControl->useDTX > 1 ) {
        SKP_assert( 0 );
        return SKP_SILK_ENC_INVALID_DTX_SETTING;
    }
	if( encControl->useCBR < 0 || encControl->useCBR > 1 ) {
        SKP_assert( 0 );
        return SKP_SILK_ENC_INVALID_CBR_SETTING;
    }
	if( encControl->useInBandFEC < 0 || encControl->useInBandFEC > 1 ) {
        SKP_assert( 0 );
        return SKP_SILK_ENC_INVALID_INBAND_FEC_SETTING;
    }
    if( encControl->nChannels < 1 || encControl->nChannels > ENCODER_NUM_CHANNELS ) {
        SKP_assert( 0 );
        return SKP_SILK_ENC_INVALID_NUMBER_OF_CHANNELS_ERROR;
    }
    if( encControl->complexity < 0 || encControl->complexity > 10 ) {
        SKP_assert( 0 );
        return SKP_SILK_ENC_INVALID_COMPLEXITY_SETTING;
    }

    return SKP_SILK_NO_ERROR;
}
