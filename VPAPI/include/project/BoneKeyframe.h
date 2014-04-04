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

#include <vpvl2/IBoneKeyframe.h>

namespace project
{
class Motion;

class BoneKeyframe : public vpvl2::IBoneKeyframe {
public:
    BoneKeyframe(Motion *parent, int rowID);
    ~BoneKeyframe();

    void read(const vpvl2::uint8 *data);
    void write(vpvl2::uint8 *data) const;
    vpvl2::vsize estimateSize() const;
    const vpvl2::IString *name() const;
    TimeIndex timeIndex() const;
    LayerIndex layerIndex() const;
    void setName(const vpvl2::IString *value);
    void setTimeIndex(const TimeIndex &value);
    void setLayerIndex(const LayerIndex &value);
    Type type() const;

    IBoneKeyframe *clone() const;
    void setDefaultInterpolationParameter();
    void setInterpolationParameter(InterpolationType type, const vpvl2::QuadWord &value);
    void getInterpolationParameter(InterpolationType type, vpvl2::QuadWord &value) const;
    vpvl2::Vector3 localTranslation() const;
    vpvl2::Quaternion localOrientation() const;
    void setLocalTranslation(const vpvl2::Vector3 &value);
    void setLocalOrientation(const vpvl2::Quaternion &value);

    int rowID() const;
    void setRowID(int value);

private:
    struct PrivateContext;
    PrivateContext *m_context;
};

} /* namespace project */
