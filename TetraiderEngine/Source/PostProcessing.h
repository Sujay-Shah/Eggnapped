/* Start Header -------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Author: <Holden Profit>
- End Header --------------------------------------------------------*/

#pragma once

#ifndef POST_PROCESSING_H
#define POST_PROCESSING_H

struct ImageRenderersData {
	ShaderProgram * pBaseShader;
	ShaderProgram * pGausHShader;
	ShaderProgram * pGausVShader;
	ShaderProgram * pMiniMapShader;
	ShaderProgram * pMiniMapFinalShader;
	ShaderProgram * pMaskShader;
};

class PostProcessing : public Subscriber
{
private:
	ShaderProgram * m_pBaseShader;
	Mesh& m_mesh;

	ImageRenderer * m_pBaseIR;
	ImageRenderer * m_pSecondBaseIR;
	ImageRenderer * m_pGaussianHIR;
	ImageRenderer * m_pGaussianVIR;

	ImageRenderer * m_pMiniMapMaskIR;
	ImageRenderer * m_pMiniMapOriginalIR;
	ImageRenderer * m_pMiniMapFinalIR;

	bool m_enabled;
	float m_levelWidthPixels;
	float m_levelHeightPixels;
	bool m_shouldGenerateMiniMap;

	void _Start();
	void _End();

	void _PaintMiniMap(Vector3D playerPos);
	void _PaintMiniMapMask(Vector3D playerPos);
public:
	friend class RenderManager;

	PostProcessing();
	~PostProcessing();
	PostProcessing(const PostProcessing &) = delete;
	void operator=(const PostProcessing &) = delete;

	virtual void HandleEvent(Event * p_event);

	inline Mesh& GetMesh() const { return m_mesh; }
	void DebugInitialize();
	void InitImageRenderers(const ImageRenderersData& metadata, const Resolution& resolution);

	inline void SetBaseShader(ShaderProgram* fboShader) { m_pBaseShader = fboShader; }
	inline void EnableBaseShader() const { glUseProgram(m_pBaseShader->GetProgramID()); }

	bool IsEnabled() const { return m_enabled; }
	inline void Enable() { m_enabled = true; }
	inline void Disable() { m_enabled = false; }
	inline void Toggle() { m_enabled = !m_enabled; };
	
	void RenderBaseFBO();
	void ClearBaseFBO(const Vector3D& color = Vector3D(0,0,0,0));
	void BindBaseFBO();
	void UnbindBaseFBO();

	FrameBufferObject* GetImageRendererFBO(const std::string& imageRendererType) const;

	/*
		Does Post Processing work to Second Base FBO
	*/
	void DoPostProcessing();

	/*
		Paints the MiniMap Mask and updates the MiniMapFinal texture
	*/
	void GenerateMiniMapTextureForFrame();

	void CreateMiniMapTexture(const std::vector<RoomNodeData>& roomNodeData, unsigned short rows, unsigned short cols, unsigned int levelWidthPixels, unsigned int levelHeightPixels);
};

#endif