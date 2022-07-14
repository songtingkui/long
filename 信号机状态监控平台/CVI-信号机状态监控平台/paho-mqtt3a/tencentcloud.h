//==============================================================================
//
// Title:		tencentcloud
// Purpose:		A short description of the interface.
//
// Created on:	2022/6/2 ÐÇÆÚËÄ at 22:02:19 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __tencentcloud_H__
#define __tencentcloud_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// External variables

//==============================================================================
// Global functions

int tencentcloud(const char* product_id, const char* device_name, const char* device_secret, char* serverURI, char* clientId, char* username, char* password);

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __tencentcloud_H__ */
