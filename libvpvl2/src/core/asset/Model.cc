/* ----------------------------------------------------------------- */
/*                                                                   */
/*  Copyright (c) 2010-2012  hkrn                                    */
/*                                                                   */
/* All rights reserved.                                              */
/*                                                                   */
/* Redistribution and use in source and binary forms, with or        */
/* without modification, are permitted provided that the following   */
/* conditions are met:                                               */
/*                                                                   */
/* - Redistributions of source code must retain the above copyright  */
/*   notice, this list of conditions and the following disclaimer.   */
/* - Redistributions in binary form must reproduce the above         */
/*   copyright notice, this list of conditions and the following     */
/*   disclaimer in the documentation and/or other materials provided */
/*   with the distribution.                                          */
/* - Neither the name of the MMDAI project team nor the names of     */
/*   its contributors may be used to endorse or promote products     */
/*   derived from this software without specific prior written       */
/*   permission.                                                     */
/*                                                                   */
/* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND            */
/* CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,       */
/* INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF          */
/* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE          */
/* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS */
/* BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,          */
/* EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED   */
/* TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,     */
/* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON */
/* ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,   */
/* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY    */
/* OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE           */
/* POSSIBILITY OF SUCH DAMAGE.                                       */
/* ----------------------------------------------------------------- */

#include "vpvl2/asset/Model.h"
#include "vpvl2/internal/util.h"

namespace vpvl2
{
namespace asset
{

Model::Model(IEncoding *encoding)
    : m_encodingRef(encoding),
      m_name(0),
      m_comment(0),
      m_parentModelRef(0),
      m_parentBoneRef(0),
      m_visible(false)
{
}

Model::~Model()
{
    delete m_comment;
    m_comment = 0;
    delete m_name;
    m_name = 0;
    m_parentBoneRef = 0;
    m_parentModelRef = 0;
    m_encodingRef = 0;
    m_visible = false;
}

bool Model::load(const uint8_t *data, size_t size)
{
#ifdef VPVL2_LINK_ASSIMP
    int flags = aiProcessPreset_TargetRealtime_Quality | aiProcess_FlipUVs;
    m_scene = m_importer.ReadFileFromMemory(data, size, flags);
    return m_scene != 0;
#else
    return false;
#endif
}

void Model::getBoundingBox(Vector3 &min, Vector3 &max) const
{
    min.setZero();
    max.setZero();
#ifdef VPVL2_LINK_ASSIMP
    getBoundingBoxRecurse(m_scene, m_scene->mRootNode, min, max);
#endif
}

void Model::setName(const IString *value)
{
    internal::setString(value, m_name);
}

void Model::setEnglishName(const IString *value)
{
    setName(value);
}

void Model::setComment(const IString *value)
{
    internal::setString(value, m_comment);
}

void Model::setEnglishComment(const IString *value)
{
    setComment(value);
}

void Model::setPosition(const Vector3 &value) {
    m_position = value;
}

void Model::setRotation(const Quaternion &value)
{
    m_rotation = value;
}

void Model::setOpacity(const Scalar &value)
{
    m_opacity = value;
}

void Model::setScaleFactor(const Scalar &value)
{
    m_scaleFactor = value;
}

void Model::setParentModel(IModel *value)
{
    m_parentModelRef = value;
}

void Model::setParentBone(IBone *value)
{
    m_parentBoneRef = value;
}

void Model::setVisible(bool value)
{
    m_visible = value;
}

#ifdef VPVL2_LINK_ASSIMP
void Model::getBoundingBoxRecurse(const aiScene *scene, const aiNode *node, Vector3 &min, Vector3 &max) const
{
    const unsigned int nmeshes = node->mNumMeshes;
    const Scalar &scale = scaleFactor();
    Vector3 position;
    for (unsigned int i = 0; i < nmeshes; i++) {
        const struct aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        const aiVector3D *vertices = mesh->mVertices;
        const unsigned int nvertices = mesh->mNumVertices;
        for (unsigned int j = 0; j < nvertices; j++) {
            const aiVector3D &vertex = vertices[i] * scale;
            position.setValue(vertex.x, vertex.y, vertex.z);
            min.setMin(position);
            max.setMax(position);
        }
    }
    const unsigned int nChildNodes = node->mNumChildren;
    for (unsigned int i = 0; i < nChildNodes; i++)
        getBoundingBoxRecurse(scene, node->mChildren[i], min, max);
}
#endif

} /* namespace asset */
} /* namespace vpvl2 */
