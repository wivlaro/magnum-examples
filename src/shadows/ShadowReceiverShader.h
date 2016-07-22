#pragma once

#include <Magnum/AbstractShaderProgram.h>
#include <Magnum/Shaders/Generic.h>

class ShadowReceiverShader : public Magnum::AbstractShaderProgram {
public:
	ShadowReceiverShader(int numShaderLevels);
	virtual ~ShadowReceiverShader();

	typedef Magnum::Shaders::Generic3D::Position Position;
	typedef Magnum::Shaders::Generic3D::Normal Normal;

	ShadowReceiverShader& setTransformationProjectionMatrix(const Magnum::Matrix4& matrix);
	ShadowReceiverShader& setModelMatrix(const Magnum::Matrix4& matrix);
	ShadowReceiverShader& setShadowmapMatrices(const Corrade::Containers::ArrayView<Magnum::Matrix4>& matrix);
	ShadowReceiverShader& setLightDirection(const Magnum::Vector3& vector3);
	ShadowReceiverShader& setShadowmapTexture(Magnum::Texture2DArray& texture);

private:
	Magnum::Int modelMatrixUniform;
	Magnum::Int transformationProjectionMatrixUniform;
	Magnum::Int shadowmapMatrixUniform;
	Magnum::Int lightDirectionUniform;

	enum: Magnum::Int { ShadowmapTextureLayer = 0 };
};


