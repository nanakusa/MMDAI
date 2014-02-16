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
#ifndef VPVL2_PMX_LABEL_H_
#define VPVL2_PMX_LABEL_H_

#include "vpvl2/ILabel.h"
#include "vpvl2/IString.h"
#include "vpvl2/pmx/Model.h"

namespace vpvl2
{
namespace VPVL2_VERSION_NS
{
namespace pmx
{

/**
 * @file
 * @author hkrn
 *
 * @section DESCRIPTION
 *
 * Label class represents a label of a Polygon Model Extended object.
 */

class VPVL2_API Label VPVL2_DECL_FINAL : public ILabel
{
public:
    /**
     * Constructor
     */
    Label(IModel *modelRef);
    ~Label();

    static bool preparse(uint8 *&ptr, vsize &rest, Model::DataInfo &info);
    static bool loadLabels(const Array<Label *> &labels,
                           const Array<Bone *> &bones,
                           const Array<Morph *> &morphs);
    static void writeLabels(const Array<Label *> &labels, const Model::DataInfo &info, uint8 *&data);
    static vsize estimateTotalSize(const Array<Label *> &labels, const Model::DataInfo &info);

    void addEventListenerRef(PropertyEventListener *value);
    void removeEventListenerRef(PropertyEventListener *value);
    void getEventListenerRefs(Array<PropertyEventListener *> &value);

    /**
     * Read and parse the buffer with id and sets it's result to the class.
     *
     * @param data The buffer to read and parse
     */
    void read(const uint8 *data, const Model::DataInfo &info, vsize &size);
    void write(uint8 *&data, const Model::DataInfo &info) const;
    vsize estimateSize(const Model::DataInfo &info) const;

    const IString *name(IEncoding::LanguageType type) const;
    IModel *parentModelRef() const;
    int index() const;
    bool isSpecial() const;
    IBone *boneRef(int index) const;
    IMorph *morphRef(int index) const;
    int count() const;

    void setName(const IString *value, IEncoding::LanguageType type);
    void setSpecial(bool value);
    void addBoneRef(IBone *value);
    void addMorphRef(IMorph *value);
    void removeBoneRef(IBone *value);
    void removeMorphRef(IMorph *value);
    void setIndex(int value);

private:
    struct PrivateContext;
    PrivateContext *m_context;

    VPVL2_DISABLE_COPY_AND_ASSIGN(Label)
};

} /* namespace pmx */
} /* namespace VPVL2_VERSION_NS */
} /* namespace vpvl2 */

#endif
