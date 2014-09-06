/**
 * \file MBRT_VideoAcq.cpp
 * \author Nicolas Beucher
 * \date 03-27-2009
 *
 */
 
/*
 * Copyright (c) <2009>, <Nicolas BEUCHER and ARMINES for the Centre de 
 * Morphologie Mathématique(CMM), common research center to ARMINES and MINES 
 * Paristech>
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation files
 * (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, 
 * distribute, sublicense, and/or sell copies of the Software, and to permit 
 * persons to whom the Software is furnished to do so, subject to the following 
 * conditions: The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 *
 * Except as contained in this notice, the names of the above copyright 
 * holders shall not be used in advertising or otherwise to promote the sale, 
 * use or other dealings in this Software without their prior written 
 * authorization.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include "mambaRTApi_loc.h"


/**
 * Fillss the video acquisition structure with the parameters of the given
 * device and initializes it.
 * \param device the video device (a string containing a number) or the video file.
 * \param type the type of device (e.g directshow, avc ...)
 * \return an error code (MBRT_NO_ERR if successful)
 */
MBRT_errcode MBRT_CreateVideoAcq(char *device, MBRT_vidType type)
{
    int dev_number;
    
    /* Verification over context */
    if (context==NULL) return MBRT_ERR_INVD_CTX;
    
    context->type = type;
    
    switch(type){
        case DSHOW_TYPE:
            dev_number = atoi(device);
            return MBRT_CreateVideoAcq_dshow(dev_number);
            break;
        case AVC_TYPE:
            return MBRT_CreateVideoAcq_avc(device);
            break;
        default:
            break;
    }
    
    /* should not attain here */
    return MBRT_ERR_VID_TYPE;
}

/**
 * Closes the acquisition device and resets the structure
 * \return MBRT_NO_ERR if successful
 */
MBRT_errcode MBRT_DestroyVideoAcq()
{
    /* Verification over context */
    if (context==NULL) return MBRT_ERR_INVD_CTX;
    
    switch(context->type){
        case DSHOW_TYPE:
            context->type = NONE_TYPE;
            return MBRT_DestroyVideoAcq_dshow();
            break;
        case AVC_TYPE:
            context->type = NONE_TYPE;
            return MBRT_DestroyVideoAcq_avc();
            break;
        default:
            break;
    }
         
    /* should not attain here */
    return MBRT_ERR_VID_TYPE;
}

/**
 * Returns the acquisition device resolution.
 * \param acq_w the width (output)
 * \param acq_h the height (output)
 * \return MBRT_NO_ERR if successful
 */
MBRT_errcode MBRT_GetAcqSize(int *acq_w, int *acq_h)
{
    /* Verification over context */
    if (context==NULL) return MBRT_ERR_INVD_CTX;
    
    switch(context->type){
        case DSHOW_TYPE:
            return MBRT_GetAcqSize_dshow(acq_w,acq_h);
            break;
        case AVC_TYPE:
            return MBRT_GetAcqSize_avc(acq_w,acq_h);
            break;
        default:
            break;
    }
         
    /* should not attain here */
    return MBRT_ERR_VID_TYPE;
}

/**
 * Returns the acquisition device default framerate.
 * \param ofps the framerate in frame per second (output)
 * \return MBRT_NO_ERR if successful
 */
MBRT_errcode MBRT_GetAcqFrameRate(double *ofps)
{
    /* Verification over context */
    if (context==NULL) return MBRT_ERR_INVD_CTX;
    
    switch(context->type){
        case DSHOW_TYPE:
            return MBRT_GetAcqFrameRate_dshow(ofps);
            break;
        case AVC_TYPE:
            return MBRT_GetAcqFrameRate_avc(ofps);
            break;
        default:
            break;
    }
         
    /* should not attain here */
    return MBRT_ERR_VID_TYPE;
}

/**
 * Obtains an image form the acquisition device
 * \param dest the mamba image filled by the device
 * \return MBRT_NO_ERR if successful
 */
MBRT_errcode MBRT_GetImageFromAcq(MB_Image *dest)
{
    /* Verification over context */
    if (context==NULL) return MBRT_ERR_INVD_CTX;
    
    switch(context->type){
        case DSHOW_TYPE:
            return MBRT_GetImageFromAcq_dshow(dest);
            break;
        case AVC_TYPE:
            return MBRT_GetImageFromAcq_avc(dest);
            break;
        default:
            break;
    }
         
    /* should not attain here */
    return MBRT_ERR_VID_TYPE;
}

/**
 * Obtains a color image from the acquisition device
 * \param destRed the mamba image filled by the device with the red channel
 * \param destGreen the mamba image filled by the device with the green channel
 * \param destBlue the mamba image filled by the device with the blue channel
 * \return MBRT_NO_ERR if successful
 */
MBRT_errcode MBRT_GetColorImageFromAcq(MB_Image *destRed, MB_Image *destGreen, MB_Image *destBlue)
{
    /* Verification over context */
    if (context==NULL) return MBRT_ERR_INVD_CTX;
    
    switch(context->type){
        case DSHOW_TYPE:
            return MBRT_GetColorImageFromAcq_dshow(destRed,destGreen,destBlue);
            break;
        case AVC_TYPE:
            return MBRT_GetColorImageFromAcq_avc(destRed,destGreen,destBlue);
            break;
        default:
            break;
    }
         
    /* should not attain here */
    return MBRT_ERR_VID_TYPE;
}


/**
 * Starts the acquisition device capture process
 * \return MBRT_NO_ERR if successful
 */
MBRT_errcode MBRT_StartAcq()
{
    /* Verification over context */
    if (context==NULL) return MBRT_ERR_INVD_CTX;
    
    switch(context->type){
        case DSHOW_TYPE:
            return MBRT_StartAcq_dshow();
            break;
        case AVC_TYPE:
            return MBRT_StartAcq_avc();
            break;
        default:
            break;
    }
         
    /* should not attain here */
    return MBRT_ERR_VID_TYPE;
}

/**
 * Stops the acquisition device capture process
 * \return MBRT_NO_ERR if successful
 */
MBRT_errcode MBRT_StopAcq()
{
    /* Verification over context */
    if (context==NULL) return MBRT_ERR_INVD_CTX;
    
    switch(context->type){
        case DSHOW_TYPE:
            return MBRT_StopAcq_dshow();
            break;
        case AVC_TYPE:
            return MBRT_StopAcq_avc();
            break;
        default:
            break;
    }
         
    /* should not attain here */
    return MBRT_ERR_VID_TYPE;
}


