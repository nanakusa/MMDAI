/**

 Copyright (c) 2010-2014  hkrn

 All rights reserved.

 Redistribution and use in source and binary forms, with or
 without modification, are permitted provided that the following
 conditions are met:

 - Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
 - Redistributions in binary form must reproduce the above
   copyright notice, this list of conditions and the following
   disclaimer in the documentation and/or other materials provided
   with the distribution.
 - Neither the name of the MMDAI project team nor the names of
   its contributors may be used to endorse or promote products
   derived from this software without specific prior written
   permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
 BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 POSSIBILITY OF SUCH DAMAGE.

*/

#pragma once
#ifndef VPVL2_GL_TEXTUREPTRREF_H_
#define VPVL2_GL_TEXTUREPTRREF_H_

#include <vpvl2/ITexture.h>
#include <vpvl2/gl/BaseTexture.h>

namespace vpvl2
{
namespace VPVL2_VERSION_NS
{
namespace gl
{

class TexturePtrRef VPVL2_DECL_FINAL : public ITexture {
public:
    TexturePtrRef(const ITexture *texture)
        : VPVL2_BASESURFACE_INITIALIZE_FIELDS(*reinterpret_cast<const BaseSurface::Format *>(texture->format()), texture->size(), static_cast<GLuint>(texture->sampler()))
    {
        m_name = static_cast<GLuint>(texture->data());
    }
    ~TexturePtrRef() {
        VPVL2_BASESURFACE_DESTROY_FIELDS()
    }

    /* do nothing */
    void create() {}
    void bind() {}
    void fillPixels(const void * /* pixels */) {}
    void allocate(const void * /* data */) {}
    void write(const void * /* data */) {}
    void resize(const Vector3 & /* size */) {}
    void unbind() {}
    void release() {}
    void generateMipmaps() {}
    void getParameters(unsigned int /* key */, float * /* values */) const {}
    void getParameters(unsigned int /* key */, int * /* values */) const {}
    void setParameter(unsigned int /* key */, float /* value */) {}
    void setParameter(unsigned int /* key */, int /* value */) {}

    VPVL2_BASESURFACE_DEFINE_METHODS()

private:
    VPVL2_BASESURFACE_DEFINE_FIELDS()
};

} /* namespace gl */
} /* namespace VPVL2_VERSION_NS */
using namespace VPVL2_VERSION_NS;

} /* namespace vpvl2 */

#endif
