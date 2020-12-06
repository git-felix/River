#pragma once

#include <iostream>
#include <GL/glew.h>
#include <vector> 

class FrameBuffer
{
public:
    FrameBuffer(int width, int height)
    {
        glGenFramebuffers(1, &m_frameBufferID);
        glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferID);
        InitTextureAttachment(width, height);
        InitRenderBufferAttachment(width, height);									// Texture buffer creation
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
    ~FrameBuffer()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glDeleteFramebuffers(1, &m_frameBufferID);
    }
    void Bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferID);
    }
    void Unbind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
    void BindTexture(int slot)
    {
        glActiveTexture(slot);
        glBindTexture(GL_TEXTURE_2D, m_textureID);
    }

private:
    int InitRenderBufferAttachment(int width, int height)
    {
        unsigned int rbo;
        glGenRenderbuffers(1, &rbo);
        glBindRenderbuffer(GL_RENDERBUFFER, rbo);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
        return rbo;
    }
    int InitTextureAttachment(int width, int height)
    {
        glGenTextures(1, &m_textureID);
        glBindTexture(GL_TEXTURE_2D, m_textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textureID, 0);
        return m_textureID;
    }
    unsigned int m_frameBufferID;
    unsigned int m_textureID;
};