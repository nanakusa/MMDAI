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

#include <vpvl2/IEffectKeyframe.h>

namespace project
{
class Motion;

class EffectKeyframe : public vpvl2::IEffectKeyframe {
public:
    EffectKeyframe(Motion *parent, int rowID);
    ~EffectKeyframe();

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

    IEffectKeyframe *clone() const;
    bool isVisible() const;
    bool isAddBlendEnabled() const;
    bool isShadowEnabled() const;
    vpvl2::float32 scaleFactor() const;
    vpvl2::float32 opacity() const;
    vpvl2::IModel *parentModelRef() const;
    vpvl2::IBone *parentBoneRef() const;
    void setVisible(bool value);
    void setAddBlendEnable(bool value);
    void setShadowEnable(bool value);
    void setScaleFactor(vpvl2::float32 value);
    void setOpacity(vpvl2::float32 value);
    void setParentModelRef(vpvl2::IModel *value);
    void setParentBoneRef(vpvl2::IBone *value);

    int rowID() const;
    void setRowID(int value);

private:
    struct PrivateContext;
    PrivateContext *m_context;
};

} /* namespace project */

