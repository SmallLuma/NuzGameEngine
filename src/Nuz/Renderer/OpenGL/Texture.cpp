#include "Texture.h"
#include "../CtxReader.h"
#include "../../../../include/Nuz.h"
using namespace Nuz_::Renderer;


Texture::Texture()
{
	glGenTextures(1, &m_texture);
	if (m_texture == 0) throw Nuz::IEngine::RendererError("Cannot create texture:" + glGetError());
}


Texture::~Texture()
{
	glDeleteTextures(1,&m_texture);
}

void Nuz_::Renderer::Texture::LoadImage(const std::string & path)
{
	Clear();
	auto& p = Nuz::IEngine::GetGameDevice().GetFileSystem().LoadFile(path);
	CTXReader reader;
	reader.OpenBuffer(&(*p)[0]);
	m_w = m_h = reader.GetLength();
	for (int i = 0; i < reader.GetRectNum(); ++i) {
		int x, y, w, h;
		reader.GetRect(i, x, y, w, h);
		y = m_h - y;	//UV����ת��
		m_rects.push_back({ float(x) / m_w, float(y) / m_h, float(w) / m_w, float(h) / m_h });
	}
	/*glBindTexture(GL_TEXTURE_2D,m_texture);
	glTexImage2D(GL_TEXTURE_2D,0,4, m_w, m_h, 0, GL_ABGR_EXT, GL_UNSIGNED_BYTE, reader.GetPixels());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D,0);*/
	glTextureImage2DEXT(m_texture, GL_TEXTURE_2D, 0, 4, m_w, m_h, 0, GL_ABGR_EXT, GL_UNSIGNED_BYTE, reader.GetPixels());
	glTextureParameterfEXT(m_texture, GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameterfEXT(m_texture, GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Nuz_::Renderer::Texture::Clear()
{
	m_w = m_h = 0;
	m_rects.clear();
}