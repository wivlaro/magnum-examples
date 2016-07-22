#include "ShadowReceiverShader.h"

#include <Corrade/Utility/Resource.h>
#include <Magnum/Context.h>
#include <Magnum/Shader.h>
#include <Magnum/Version.h>
#include <Magnum/Math/Matrix4.h>
#include <Magnum/TextureArray.h>

using namespace Magnum;

ShadowReceiverShader::ShadowReceiverShader(int numShaderLevels) {
	MAGNUM_ASSERT_VERSION_SUPPORTED(Version::GL330);

	const Utility::Resource rs{"shadow-data"};

	Shader vert{Version::GL330, Shader::Type::Vertex};
	Shader frag{Version::GL330, Shader::Type::Fragment};

	std::string preamble = "#define NUM_SHADOW_MAP_LEVELS " + std::to_string(numShaderLevels) + "\n";
	vert.addSource(preamble);
	vert.addSource(rs.get("ShadowReceiver.vert"));
	frag.addSource(preamble);
	frag.addSource(rs.get("ShadowReceiver.frag"));

	CORRADE_INTERNAL_ASSERT_OUTPUT(Shader::compile({vert, frag}));

	bindAttributeLocation(Position::Location, "position");
	bindAttributeLocation(Normal::Location, "normal");

	attachShaders({vert, frag});

	CORRADE_INTERNAL_ASSERT_OUTPUT(link());

	modelMatrixUniform = uniformLocation("modelMatrix");
	transformationProjectionMatrixUniform = uniformLocation("transformationProjectionMatrix");
	shadowmapMatrixUniform = uniformLocation("shadowmapMatrix");
	lightDirectionUniform = uniformLocation("lightDirection");

	setUniform(uniformLocation("shadowmapTexture"), ShadowmapTextureLayer);
}

ShadowReceiverShader::~ShadowReceiverShader() {

}

ShadowReceiverShader &ShadowReceiverShader::setTransformationProjectionMatrix(const Magnum::Matrix4 &matrix) {
	setUniform(transformationProjectionMatrixUniform, matrix);
	return *this;
}

ShadowReceiverShader &ShadowReceiverShader::setModelMatrix(const Magnum::Matrix4 &matrix) {
	setUniform(modelMatrixUniform, matrix);
	return *this;
}

ShadowReceiverShader &ShadowReceiverShader::setShadowmapMatrices(const Corrade::Containers::ArrayView<Magnum::Matrix4> &matrix) {
	setUniform(shadowmapMatrixUniform, matrix);
	return *this;
}

ShadowReceiverShader &ShadowReceiverShader::setLightDirection(const Magnum::Vector3 &vector3) {
	setUniform(lightDirectionUniform, vector3);
	return *this;
}

ShadowReceiverShader &ShadowReceiverShader::setShadowmapTexture(Magnum::Texture2DArray &texture) {
	texture.bind(ShadowmapTextureLayer);
	return *this;
}