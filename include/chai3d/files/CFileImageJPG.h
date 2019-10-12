//==============================================================================
/*
    Software License Agreement (BSD License)
    Copyright (c) 2003-2016, CHAI3D.
    (www.chai3d.org)

    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions
    are met:

    * Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.

    * Redistributions in binary form must reproduce the above
    copyright notice, this list of conditions and the following
    disclaimer in the documentation and/or other materials provided
    with the distribution.

    * Neither the name of CHAI3D nor the names of its contributors may
    be used to endorse or promote products derived from this software
    without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
    "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
    LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
    FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
    COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
    INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
    BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
    CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
    LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
    ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
    POSSIBILITY OF SUCH DAMAGE. 

    \author    <http://www.chai3d.org>
    \author    Sebastien Grange
    \version   3.1.1 $Rev: 1869 $
*/
//==============================================================================

//------------------------------------------------------------------------------
#ifndef CFileImageJPGH
#define CFileImageJPGH
//------------------------------------------------------------------------------
#include "graphics/CImage.h"
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
namespace chai3d {
//------------------------------------------------------------------------------

//==============================================================================
/*!
    \file       CFileImageJPG.h
    \ingroup    files

    \brief
    Implements JPG image file support.
*/
//==============================================================================

//------------------------------------------------------------------------------
/*!
    \addtogroup files
*/
//------------------------------------------------------------------------------

#ifdef C_USE_FILE_JPG

//@{

    //! This function loads a JPG image file.
    bool cLoadFileJPG(cImage* a_image, const std::string& a_filename);

    //! This function loads a PNG image buffer.
    bool cLoadJPG (cImage *a_image, const unsigned char *a_buffer, unsigned int a_len);

    //! This function saves a JPG image file.
    bool cSaveFileJPG(cImage* a_image, const std::string& a_filename);

    //! This function saves a JPG image buffer.
    bool cSaveJPG (cImage *a_image, unsigned char **a_buffer, unsigned int *a_len);

//@}

#else

    inline bool cLoadFileJPG(cImage* a_image, std::string a_filename) { return (false); }
    inline bool cLoadJPG (cImage *a_image, const unsigned char *a_buffer, unsigned int a_len) { return (false); }
    inline bool cSaveFileJPG(cImage* a_image, std::string a_filename) { return (false); }
    inline bool cSaveJPG (cImage *a_image, unsigned char **a_buffer, unsigned int *a_len) { return (false); }

#endif

//------------------------------------------------------------------------------
} // namespace chai3d
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------------
