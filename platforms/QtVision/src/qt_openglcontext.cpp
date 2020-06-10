#include "qt_openglcontext.h"

#include <QtGui/QOpenGLContext>
#include <QtGui/QOpenGLFunctions>
#include <QtGui/QOpenGLExtraFunctions>
#include <last.h>

VSN_BEGIN_NAMESPACE
namespace QtVision {

//----------------------------------------------------------------------------
//
// ---
QtOpenGLFunctionList::QtOpenGLFunctionList()
    : m_pQtFunctions(nullptr)
{
}

//----------------------------------------------------------------------------
//
// ---
QtOpenGLFunctionList::~QtOpenGLFunctionList()
{
}

//----------------------------------------------------------------------------
//
// ---
void QtOpenGLFunctionList::Update(QOpenGLFunctions* pQtFunctions)
{
    m_pQtFunctions = pQtFunctions;
}

void QtOpenGLFunctionList::InitGLFunctionList()
{
    Q_ASSERT(m_pQtFunctions != nullptr);
    m_pQtFunctions->initializeOpenGLFunctions();
}

void QtOpenGLFunctionList::glBindTexture(GLenum target, GLuint texture) { m_pQtFunctions->glBindTexture(target, texture); }
void QtOpenGLFunctionList::glBlendFunc(GLenum sfactor, GLenum dfactor) { m_pQtFunctions->glBlendFunc(sfactor, dfactor); }
void QtOpenGLFunctionList::glClear(GLbitfield mask) { m_pQtFunctions->glClear(mask); }
void QtOpenGLFunctionList::glClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha) { m_pQtFunctions->glClearColor(red, green, blue, alpha); }
void QtOpenGLFunctionList::glClearStencil(GLint s) { m_pQtFunctions->glClearStencil(s); }
void QtOpenGLFunctionList::glColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha) { m_pQtFunctions->glColorMask(red, green, blue, alpha); }
void QtOpenGLFunctionList::glCopyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border) { m_pQtFunctions->glCopyTexImage2D(target, level, internalformat, x, y, width, height, border); }
void QtOpenGLFunctionList::glCopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height) { m_pQtFunctions->glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height); }
void QtOpenGLFunctionList::glCullFace(GLenum mode) { m_pQtFunctions->glCullFace(mode); }
void QtOpenGLFunctionList::glDeleteTextures(GLsizei n, const GLuint* textures) { m_pQtFunctions->glDeleteTextures(n, textures); }
void QtOpenGLFunctionList::glDepthFunc(GLenum func) { m_pQtFunctions->glDepthFunc(func); }
void QtOpenGLFunctionList::glDepthMask(GLboolean flag) { m_pQtFunctions->glDepthMask(flag); }
void QtOpenGLFunctionList::glDisable(GLenum cap) { m_pQtFunctions->glDisable(cap); }
void QtOpenGLFunctionList::glDrawArrays(GLenum mode, GLint first, GLsizei count) { m_pQtFunctions->glDrawArrays(mode, first, count); }
void QtOpenGLFunctionList::glDrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices) { m_pQtFunctions->glDrawElements(mode, count, type, indices); }
void QtOpenGLFunctionList::glEnable(GLenum cap) { m_pQtFunctions->glEnable(cap); }
void QtOpenGLFunctionList::glFinish() { m_pQtFunctions->glFinish(); }
void QtOpenGLFunctionList::glFlush() { m_pQtFunctions->glFlush(); }
void QtOpenGLFunctionList::glFrontFace(GLenum mode) { m_pQtFunctions->glFrontFace(mode); }
void QtOpenGLFunctionList::glGenTextures(GLsizei n, GLuint* textures) { m_pQtFunctions->glGenTextures(n, textures); }
void QtOpenGLFunctionList::glGetBooleanv(GLenum pname, GLboolean* params) { m_pQtFunctions->glGetBooleanv(pname, params); }
GLenum QtOpenGLFunctionList::glGetError() { return m_pQtFunctions->glGetError(); }
void QtOpenGLFunctionList::glGetFloatv(GLenum pname, GLfloat* params) { m_pQtFunctions->glGetFloatv(pname, params); }
void QtOpenGLFunctionList::glGetIntegerv(GLenum pname, GLint* params) { m_pQtFunctions->glGetIntegerv(pname, params); }
const GLubyte* QtOpenGLFunctionList::glGetString(GLenum name) { return m_pQtFunctions->glGetString(name); }
void QtOpenGLFunctionList::glGetTexParameterfv(GLenum target, GLenum pname, GLfloat* params) { m_pQtFunctions->glGetTexParameterfv(target, pname, params); }
void QtOpenGLFunctionList::glGetTexParameteriv(GLenum target, GLenum pname, GLint* params) { m_pQtFunctions->glGetTexParameteriv(target, pname, params); }
void QtOpenGLFunctionList::glHint(GLenum target, GLenum mode) { m_pQtFunctions->glHint(target, mode); }
GLboolean QtOpenGLFunctionList::glIsEnabled(GLenum cap) { return m_pQtFunctions->glIsEnabled(cap); }
GLboolean QtOpenGLFunctionList::glIsTexture(GLuint texture) { return m_pQtFunctions->glIsTexture(texture); }
void QtOpenGLFunctionList::glLineWidth(GLfloat width) { m_pQtFunctions->glLineWidth(width); }
void QtOpenGLFunctionList::glPixelStorei(GLenum pname, GLint param) { m_pQtFunctions->glPixelStorei(pname, param); }
void QtOpenGLFunctionList::glPolygonOffset(GLfloat factor, GLfloat units) { m_pQtFunctions->glPolygonOffset(factor, units); }
void QtOpenGLFunctionList::glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid* pixels) { m_pQtFunctions->glReadPixels(x, y, width, height, format, type, pixels); }
void QtOpenGLFunctionList::glScissor(GLint x, GLint y, GLsizei width, GLsizei height) { m_pQtFunctions->glScissor(x, y, width, height); }
void QtOpenGLFunctionList::glStencilFunc(GLenum func, GLint ref, GLuint mask) { m_pQtFunctions->glStencilFunc(func, ref, mask); }
void QtOpenGLFunctionList::glStencilMask(GLuint mask) { m_pQtFunctions->glStencilMask(mask); }
void QtOpenGLFunctionList::glStencilOp(GLenum fail, GLenum zfail, GLenum zpass) { m_pQtFunctions->glStencilOp(fail, zfail, zpass); }
void QtOpenGLFunctionList::glTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* pixels) { m_pQtFunctions->glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels); }
void QtOpenGLFunctionList::glTexParameterf(GLenum target, GLenum pname, GLfloat param) { m_pQtFunctions->glTexParameterf(target, pname, param); }
void QtOpenGLFunctionList::glTexParameterfv(GLenum target, GLenum pname, const GLfloat* params) { m_pQtFunctions->glTexParameterfv(target, pname, params); }
void QtOpenGLFunctionList::glTexParameteri(GLenum target, GLenum pname, GLint param) { m_pQtFunctions->glTexParameteri(target, pname, param); }
void QtOpenGLFunctionList::glTexParameteriv(GLenum target, GLenum pname, const GLint* params) { m_pQtFunctions->glTexParameteriv(target, pname, params); }
void QtOpenGLFunctionList::glTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* pixels) { m_pQtFunctions->glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels); }
void QtOpenGLFunctionList::glViewport(GLint x, GLint y, GLsizei width, GLsizei height) { m_pQtFunctions->glViewport(x, y, width, height); }

// GL(ES)2
void QtOpenGLFunctionList::glActiveTexture(GLenum texture) { m_pQtFunctions->glActiveTexture(texture); }
void QtOpenGLFunctionList::glAttachShader(GLuint program, GLuint shader) { m_pQtFunctions->glAttachShader(program, shader); }
void QtOpenGLFunctionList::glBindAttribLocation(GLuint program, GLuint index, const char* name) { m_pQtFunctions->glBindAttribLocation(program, index, name); }
void QtOpenGLFunctionList::glBindBuffer(GLenum target, GLuint buffer) { m_pQtFunctions->glBindBuffer(target, buffer); }
void QtOpenGLFunctionList::glBindFramebuffer(GLenum target, GLuint framebuffer) { m_pQtFunctions->glBindFramebuffer(target, framebuffer); }
void QtOpenGLFunctionList::glBindRenderbuffer(GLenum target, GLuint renderbuffer) { m_pQtFunctions->glBindRenderbuffer(target, renderbuffer); }
void QtOpenGLFunctionList::glBlendColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha) { m_pQtFunctions->glBlendColor(red, green, blue, alpha); }
void QtOpenGLFunctionList::glBlendEquation(GLenum mode) { m_pQtFunctions->glBlendEquation(mode); }
void QtOpenGLFunctionList::glBlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha) { m_pQtFunctions->glBlendEquationSeparate(modeRGB, modeAlpha); }
void QtOpenGLFunctionList::glBlendFuncSeparate(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha) { m_pQtFunctions->glBlendFuncSeparate(srcRGB, dstRGB, srcAlpha, dstAlpha); }
void QtOpenGLFunctionList::glBufferData(GLenum target, vsngl_GLsizeiptr size, const void* data, GLenum usage) { m_pQtFunctions->glBufferData(target, size, data, usage); }
void QtOpenGLFunctionList::glBufferSubData(GLenum target, vsngl_GLintptr offset, vsngl_GLsizeiptr size, const void* data) { m_pQtFunctions->glBufferSubData(target, offset, size, data); }
GLenum QtOpenGLFunctionList::glCheckFramebufferStatus(GLenum target) { return m_pQtFunctions->glCheckFramebufferStatus(target); }
void QtOpenGLFunctionList::glClearDepthf(GLclampf depth) { m_pQtFunctions->glClearDepthf(depth); }
void QtOpenGLFunctionList::glCompileShader(GLuint shader) { m_pQtFunctions->glCompileShader(shader); }
void QtOpenGLFunctionList::glCompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void* data) { m_pQtFunctions->glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data); }
void QtOpenGLFunctionList::glCompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void* data) { m_pQtFunctions->glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data); }
GLuint QtOpenGLFunctionList::glCreateProgram() { return m_pQtFunctions->glCreateProgram(); }
GLuint QtOpenGLFunctionList::glCreateShader(GLenum type) { return m_pQtFunctions->glCreateShader(type); }
void QtOpenGLFunctionList::glDeleteBuffers(GLsizei n, const GLuint* buffers) { m_pQtFunctions->glDeleteBuffers(n, buffers); }
void QtOpenGLFunctionList::glDeleteFramebuffers(GLsizei n, const GLuint* framebuffers) { m_pQtFunctions->glDeleteFramebuffers(n, framebuffers); }
void QtOpenGLFunctionList::glDeleteProgram(GLuint program) { m_pQtFunctions->glDeleteProgram(program); }
void QtOpenGLFunctionList::glDeleteRenderbuffers(GLsizei n, const GLuint* renderbuffers) { m_pQtFunctions->glDeleteRenderbuffers(n, renderbuffers); }
void QtOpenGLFunctionList::glDeleteShader(GLuint shader) { m_pQtFunctions->glDeleteShader(shader); }
void QtOpenGLFunctionList::glDepthRangef(GLclampf zNear, GLclampf zFar) { m_pQtFunctions->glDepthRangef(zNear, zFar); }
void QtOpenGLFunctionList::glDetachShader(GLuint program, GLuint shader) { m_pQtFunctions->glDetachShader(program, shader); }
void QtOpenGLFunctionList::glDisableVertexAttribArray(GLuint index) { m_pQtFunctions->glDisableVertexAttribArray(index); }
void QtOpenGLFunctionList::glEnableVertexAttribArray(GLuint index) { m_pQtFunctions->glEnableVertexAttribArray(index); }
void QtOpenGLFunctionList::glFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer) { m_pQtFunctions->glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer); }
void QtOpenGLFunctionList::glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) { m_pQtFunctions->glFramebufferTexture2D(target, attachment, textarget, texture, level); }
void QtOpenGLFunctionList::glGenBuffers(GLsizei n, GLuint* buffers) { m_pQtFunctions->glGenBuffers(n, buffers); }
void QtOpenGLFunctionList::glGenerateMipmap(GLenum target) { m_pQtFunctions->glGenerateMipmap(target); }
void QtOpenGLFunctionList::glGenFramebuffers(GLsizei n, GLuint* framebuffers) { m_pQtFunctions->glGenFramebuffers(n, framebuffers); }
void QtOpenGLFunctionList::glGenRenderbuffers(GLsizei n, GLuint* renderbuffers) { m_pQtFunctions->glGenRenderbuffers(n, renderbuffers); }
void QtOpenGLFunctionList::glGetActiveAttrib(GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, char* name) { m_pQtFunctions->glGetActiveAttrib(program, index, bufsize, length, size, type, name); }
void QtOpenGLFunctionList::glGetActiveUniform(GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, char* name) { m_pQtFunctions->glGetActiveUniform(program, index, bufsize, length, size, type, name); }
void QtOpenGLFunctionList::glGetAttachedShaders(GLuint program, GLsizei maxcount, GLsizei* count, GLuint* shaders) { m_pQtFunctions->glGetAttachedShaders(program, maxcount, count, shaders); }
GLint QtOpenGLFunctionList::glGetAttribLocation(GLuint program, const char* name) { return m_pQtFunctions->glGetAttribLocation(program, name); }
void QtOpenGLFunctionList::glGetBufferParameteriv(GLenum target, GLenum pname, GLint* params) { m_pQtFunctions->glGetBufferParameteriv(target, pname, params); }
void QtOpenGLFunctionList::glGetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint* params) { m_pQtFunctions->glGetFramebufferAttachmentParameteriv(target, attachment, pname, params); }
void QtOpenGLFunctionList::glGetProgramiv(GLuint program, GLenum pname, GLint* params) { m_pQtFunctions->glGetProgramiv(program, pname, params); }
void QtOpenGLFunctionList::glGetProgramInfoLog(GLuint program, GLsizei bufsize, GLsizei* length, char* infolog) { m_pQtFunctions->glGetProgramInfoLog(program, bufsize, length, infolog); }
void QtOpenGLFunctionList::glGetRenderbufferParameteriv(GLenum target, GLenum pname, GLint* params) { m_pQtFunctions->glGetRenderbufferParameteriv(target, pname, params); }
void QtOpenGLFunctionList::glGetShaderiv(GLuint shader, GLenum pname, GLint* params) { m_pQtFunctions->glGetShaderiv(shader, pname, params); }
void QtOpenGLFunctionList::glGetShaderInfoLog(GLuint shader, GLsizei bufsize, GLsizei* length, char* infolog) { m_pQtFunctions->glGetShaderInfoLog(shader, bufsize, length, infolog); }
void QtOpenGLFunctionList::glGetShaderPrecisionFormat(GLenum shadertype, GLenum precisiontype, GLint* range, GLint* precision) { m_pQtFunctions->glGetShaderPrecisionFormat(shadertype, precisiontype, range, precision); }
void QtOpenGLFunctionList::glGetShaderSource(GLuint shader, GLsizei bufsize, GLsizei* length, char* source) { m_pQtFunctions->glGetShaderSource(shader, bufsize, length, source); }
void QtOpenGLFunctionList::glGetUniformfv(GLuint program, GLint location, GLfloat* params) { m_pQtFunctions->glGetUniformfv(program, location, params); }
void QtOpenGLFunctionList::glGetUniformiv(GLuint program, GLint location, GLint* params) { m_pQtFunctions->glGetUniformiv(program, location, params); }
GLint QtOpenGLFunctionList::glGetUniformLocation(GLuint program, const char* name) { return m_pQtFunctions->glGetUniformLocation(program, name); }
void QtOpenGLFunctionList::glGetVertexAttribfv(GLuint index, GLenum pname, GLfloat* params) { m_pQtFunctions->glGetVertexAttribfv(index, pname, params); }
void QtOpenGLFunctionList::glGetVertexAttribiv(GLuint index, GLenum pname, GLint* params) { m_pQtFunctions->glGetVertexAttribiv(index, pname, params); }
void QtOpenGLFunctionList::glGetVertexAttribPointerv(GLuint index, GLenum pname, void** pointer) { m_pQtFunctions->glGetVertexAttribPointerv(index, pname, pointer); }
GLboolean QtOpenGLFunctionList::glIsBuffer(GLuint buffer) { return m_pQtFunctions->glIsBuffer(buffer); }
GLboolean QtOpenGLFunctionList::glIsFramebuffer(GLuint framebuffer) { return m_pQtFunctions->glIsFramebuffer(framebuffer); }
GLboolean QtOpenGLFunctionList::glIsProgram(GLuint program) { return m_pQtFunctions->glIsProgram(program); }
GLboolean QtOpenGLFunctionList::glIsRenderbuffer(GLuint renderbuffer) { return m_pQtFunctions->glIsRenderbuffer(renderbuffer); }
GLboolean QtOpenGLFunctionList::glIsShader(GLuint shader) { return m_pQtFunctions->glIsShader(shader); }
void QtOpenGLFunctionList::glLinkProgram(GLuint program) { m_pQtFunctions->glLinkProgram(program); }
void QtOpenGLFunctionList::glReleaseShaderCompiler() { m_pQtFunctions->glReleaseShaderCompiler(); }
void QtOpenGLFunctionList::glRenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height) { m_pQtFunctions->glRenderbufferStorage(target, internalformat, width, height); }
void QtOpenGLFunctionList::glSampleCoverage(GLclampf value, GLboolean invert) { m_pQtFunctions->glSampleCoverage(value, invert); }
void QtOpenGLFunctionList::glShaderBinary(GLint n, const GLuint* shaders, GLenum binaryformat, const void* binary, GLint length) { m_pQtFunctions->glShaderBinary(n, shaders, binaryformat, binary, length); }
void QtOpenGLFunctionList::glShaderSource(GLuint shader, GLsizei count, const char** string, const GLint* length) { m_pQtFunctions->glShaderSource(shader, count, string, length); }
void QtOpenGLFunctionList::glStencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask) { m_pQtFunctions->glStencilFuncSeparate(face, func, ref, mask); }
void QtOpenGLFunctionList::glStencilMaskSeparate(GLenum face, GLuint mask) { m_pQtFunctions->glStencilMaskSeparate(face, mask); }
void QtOpenGLFunctionList::glStencilOpSeparate(GLenum face, GLenum fail, GLenum zfail, GLenum zpass) { m_pQtFunctions->glStencilOpSeparate(face, fail, zfail, zpass); }
void QtOpenGLFunctionList::glUniform1f(GLint location, GLfloat x) { m_pQtFunctions->glUniform1f(location, x); }
void QtOpenGLFunctionList::glUniform1fv(GLint location, GLsizei count, const GLfloat* v) { m_pQtFunctions->glUniform1fv(location, count, v); }
void QtOpenGLFunctionList::glUniform1i(GLint location, GLint x) { m_pQtFunctions->glUniform1i(location, x); }
void QtOpenGLFunctionList::glUniform1iv(GLint location, GLsizei count, const GLint* v) { m_pQtFunctions->glUniform1iv(location, count, v); }
void QtOpenGLFunctionList::glUniform2f(GLint location, GLfloat x, GLfloat y) { m_pQtFunctions->glUniform2f(location, x, y); }
void QtOpenGLFunctionList::glUniform2fv(GLint location, GLsizei count, const GLfloat* v) { m_pQtFunctions->glUniform2fv(location, count, v); }
void QtOpenGLFunctionList::glUniform2i(GLint location, GLint x, GLint y) { m_pQtFunctions->glUniform2i(location, x, y); }
void QtOpenGLFunctionList::glUniform2iv(GLint location, GLsizei count, const GLint* v) { m_pQtFunctions->glUniform2iv(location, count, v); }
void QtOpenGLFunctionList::glUniform3f(GLint location, GLfloat x, GLfloat y, GLfloat z) { m_pQtFunctions->glUniform3f(location, x, y, z); }
void QtOpenGLFunctionList::glUniform3fv(GLint location, GLsizei count, const GLfloat* v) { m_pQtFunctions->glUniform3fv(location, count, v); }
void QtOpenGLFunctionList::glUniform3i(GLint location, GLint x, GLint y, GLint z) { m_pQtFunctions->glUniform3i(location, x, y, z); }
void QtOpenGLFunctionList::glUniform3iv(GLint location, GLsizei count, const GLint* v) { m_pQtFunctions->glUniform3iv(location, count, v); }
void QtOpenGLFunctionList::glUniform4f(GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w) { m_pQtFunctions->glUniform4f(location, x, y, z, w); }
void QtOpenGLFunctionList::glUniform4fv(GLint location, GLsizei count, const GLfloat* v) { m_pQtFunctions->glUniform4fv(location, count, v); }
void QtOpenGLFunctionList::glUniform4i(GLint location, GLint x, GLint y, GLint z, GLint w) { m_pQtFunctions->glUniform4i(location, x, y, z, w); }
void QtOpenGLFunctionList::glUniform4iv(GLint location, GLsizei count, const GLint* v) { m_pQtFunctions->glUniform4iv(location, count, v); }
void QtOpenGLFunctionList::glUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) { m_pQtFunctions->glUniformMatrix3fv(location, count, transpose, value); }
void QtOpenGLFunctionList::glUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) { m_pQtFunctions->glUniformMatrix3fv(location, count, transpose, value); }
void QtOpenGLFunctionList::glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) { m_pQtFunctions->glUniformMatrix4fv(location, count, transpose, value); }
void QtOpenGLFunctionList::glUseProgram(GLuint program) { m_pQtFunctions->glUseProgram(program); }
void QtOpenGLFunctionList::glValidateProgram(GLuint program) { m_pQtFunctions->glValidateProgram(program); }
void QtOpenGLFunctionList::glVertexAttrib1f(GLuint indx, GLfloat x) { m_pQtFunctions->glVertexAttrib1f(indx, x); }
void QtOpenGLFunctionList::glVertexAttrib1fv(GLuint indx, const GLfloat* values) { m_pQtFunctions->glVertexAttrib1fv(indx, values); }
void QtOpenGLFunctionList::glVertexAttrib2f(GLuint indx, GLfloat x, GLfloat y) { m_pQtFunctions->glVertexAttrib2f(indx, x, y); }
void QtOpenGLFunctionList::glVertexAttrib2fv(GLuint indx, const GLfloat* values) { m_pQtFunctions->glVertexAttrib2fv(indx, values); }
void QtOpenGLFunctionList::glVertexAttrib3f(GLuint indx, GLfloat x, GLfloat y, GLfloat z) { m_pQtFunctions->glVertexAttrib3f(indx, x, y, z); }
void QtOpenGLFunctionList::glVertexAttrib3fv(GLuint indx, const GLfloat* values) { m_pQtFunctions->glVertexAttrib3fv(indx, values); }
void QtOpenGLFunctionList::glVertexAttrib4f(GLuint indx, GLfloat x, GLfloat y, GLfloat z, GLfloat w) { m_pQtFunctions->glVertexAttrib4f(indx, x, y, z, w); }
void QtOpenGLFunctionList::glVertexAttrib4fv(GLuint indx, const GLfloat* values) { m_pQtFunctions->glVertexAttrib4fv(indx, values); }
void QtOpenGLFunctionList::glVertexAttribPointer(GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* ptr) { m_pQtFunctions->glVertexAttribPointer(indx, size, type, normalized, stride, ptr); }


//----------------------------------------------------------------------------
//
// ---
QtOpenGLExtraFunctionList::QtOpenGLExtraFunctionList()
    : m_pQtFunctions(nullptr)
{
}

//----------------------------------------------------------------------------
//
// ---
QtOpenGLExtraFunctionList::~QtOpenGLExtraFunctionList()
{
}

//----------------------------------------------------------------------------
//
// ---
void QtOpenGLExtraFunctionList::Update(QOpenGLExtraFunctions* pQtFunctions)
{
    m_pQtFunctions = pQtFunctions;
}

// GLES3
void QtOpenGLExtraFunctionList::glReadBuffer(GLenum mode) { m_pQtFunctions->glReadBuffer(mode); }
void QtOpenGLExtraFunctionList::glDrawRangeElements(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void *indices) { m_pQtFunctions->glDrawRangeElements(mode, start, end, count, type, indices); }
void QtOpenGLExtraFunctionList::glTexImage3D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void *pixels)  { m_pQtFunctions->glTexImage3D(target, level, internalformat, width, height, depth, border, format, type, pixels); }
void QtOpenGLExtraFunctionList::glTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *pixels) { m_pQtFunctions->glTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels); }
void QtOpenGLExtraFunctionList::glCopyTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height) { m_pQtFunctions->glCopyTexSubImage3D(target, level, xoffset, yoffset, zoffset, x, y, width, height); }
void QtOpenGLExtraFunctionList::glCompressedTexImage3D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void *data) { m_pQtFunctions->glCompressedTexImage3D(target, level, internalformat, width, height, depth, border, imageSize, data); }
void QtOpenGLExtraFunctionList::glCompressedTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void *data) { m_pQtFunctions->glCompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data); }
void QtOpenGLExtraFunctionList::glGenQueries(GLsizei n, GLuint *ids) { m_pQtFunctions->glGenQueries(n, ids); }
void QtOpenGLExtraFunctionList::glDeleteQueries(GLsizei n, const GLuint *ids) { m_pQtFunctions->glDeleteQueries(n, ids); }
GLboolean QtOpenGLExtraFunctionList::glIsQuery(GLuint id) { return m_pQtFunctions->glIsQuery(id); }
void QtOpenGLExtraFunctionList::glBeginQuery(GLenum target, GLuint id) { m_pQtFunctions->glBeginQuery(target, id); }
void QtOpenGLExtraFunctionList::glEndQuery(GLenum target) { m_pQtFunctions->glEndQuery(target); }
void QtOpenGLExtraFunctionList::glGetQueryiv(GLenum target, GLenum pname, GLint *params) { m_pQtFunctions->glGetQueryiv(target, pname, params); }
void QtOpenGLExtraFunctionList::glGetQueryObjectuiv(GLuint id, GLenum pname, GLuint *params) { m_pQtFunctions->glGetQueryObjectuiv(id, pname, params); }
GLboolean QtOpenGLExtraFunctionList::glUnmapBuffer(GLenum target) { return m_pQtFunctions->glUnmapBuffer(target); }
void QtOpenGLExtraFunctionList::glGetBufferPointerv(GLenum target, GLenum pname, void **params) { m_pQtFunctions->glGetBufferPointerv(target, pname, params); }
void QtOpenGLExtraFunctionList::glDrawBuffers(GLsizei n, const GLenum *bufs) { m_pQtFunctions->glDrawBuffers(n, bufs); }
void QtOpenGLExtraFunctionList::glUniformMatrix2x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) { m_pQtFunctions->glUniformMatrix2x3fv(location, count, transpose, value); }
void QtOpenGLExtraFunctionList::glUniformMatrix3x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) { m_pQtFunctions->glUniformMatrix3x2fv(location, count, transpose, value); }
void QtOpenGLExtraFunctionList::glUniformMatrix2x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) { m_pQtFunctions->glUniformMatrix2x4fv(location, count, transpose, value); }
void QtOpenGLExtraFunctionList::glUniformMatrix4x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) { m_pQtFunctions->glUniformMatrix4x2fv(location, count, transpose, value); }
void QtOpenGLExtraFunctionList::glUniformMatrix3x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) { m_pQtFunctions->glUniformMatrix3x4fv(location, count, transpose, value); }
void QtOpenGLExtraFunctionList::glUniformMatrix4x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) { m_pQtFunctions->glUniformMatrix4x3fv(location, count, transpose, value); }
void QtOpenGLExtraFunctionList::glBlitFramebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter) { m_pQtFunctions->glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter); }
void QtOpenGLExtraFunctionList::glRenderbufferStorageMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height) { m_pQtFunctions->glRenderbufferStorageMultisample(target, samples, internalformat, width, height); }
void QtOpenGLExtraFunctionList::glFramebufferTextureLayer(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer) { m_pQtFunctions->glFramebufferTextureLayer(target, attachment, texture, level, layer); }
void* QtOpenGLExtraFunctionList::glMapBufferRange(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access) { return m_pQtFunctions->glMapBufferRange(target, offset, length, access); }
void QtOpenGLExtraFunctionList::glFlushMappedBufferRange(GLenum target, GLintptr offset, GLsizeiptr length) { m_pQtFunctions->glFlushMappedBufferRange(target, offset, length); }
void QtOpenGLExtraFunctionList::glBindVertexArray(GLuint array) { m_pQtFunctions->glBindVertexArray(array); }
void QtOpenGLExtraFunctionList::glDeleteVertexArrays(GLsizei n, const GLuint *arrays) { m_pQtFunctions->glDeleteVertexArrays(n, arrays); }
void QtOpenGLExtraFunctionList::glGenVertexArrays(GLsizei n, GLuint* arrays) { m_pQtFunctions->glGenVertexArrays(n, arrays); }
GLboolean QtOpenGLExtraFunctionList::glIsVertexArray(GLuint array) { return m_pQtFunctions->glIsVertexArray(array); }
void QtOpenGLExtraFunctionList::glGetIntegeri_v(GLenum target, GLuint index, GLint *data) { m_pQtFunctions->glGetIntegeri_v(target, index, data); }
void QtOpenGLExtraFunctionList::glBeginTransformFeedback(GLenum primitiveMode) { m_pQtFunctions->glBeginTransformFeedback(primitiveMode); }
void QtOpenGLExtraFunctionList::glEndTransformFeedback(void) { m_pQtFunctions->glEndTransformFeedback(); }
void QtOpenGLExtraFunctionList::glBindBufferRange(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size) { m_pQtFunctions->glBindBufferRange(target, index, buffer, offset, size); }
void QtOpenGLExtraFunctionList::glBindBufferBase(GLenum target, GLuint index, GLuint buffer) { m_pQtFunctions->glBindBufferBase(target, index, buffer); }
void QtOpenGLExtraFunctionList::glTransformFeedbackVaryings(GLuint program, GLsizei count, const GLchar *const*varyings, GLenum bufferMode) { m_pQtFunctions->glTransformFeedbackVaryings(program, count, varyings, bufferMode); }
void QtOpenGLExtraFunctionList::glGetTransformFeedbackVarying(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLsizei *size, GLenum *type, GLchar *name) { m_pQtFunctions->glGetTransformFeedbackVarying(program, index, bufSize, length, size, type, name); }
void QtOpenGLExtraFunctionList::glVertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer) { m_pQtFunctions->glVertexAttribIPointer(index, size, type, stride, pointer); }
void QtOpenGLExtraFunctionList::glGetVertexAttribIiv(GLuint index, GLenum pname, GLint *params) { m_pQtFunctions->glGetVertexAttribIiv(index, pname, params); }
void QtOpenGLExtraFunctionList::glGetVertexAttribIuiv(GLuint index, GLenum pname, GLuint *params) { m_pQtFunctions->glGetVertexAttribIuiv(index, pname, params); }
void QtOpenGLExtraFunctionList::glVertexAttribI4i(GLuint index, GLint x, GLint y, GLint z, GLint w) { m_pQtFunctions->glVertexAttribI4i(index, x, y, z, w); }
void QtOpenGLExtraFunctionList::glVertexAttribI4ui(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w) { m_pQtFunctions->glVertexAttribI4ui(index, x, y, z, w); }
void QtOpenGLExtraFunctionList::glVertexAttribI4iv(GLuint index, const GLint *v) { m_pQtFunctions->glVertexAttribI4iv(index, v); }
void QtOpenGLExtraFunctionList::glVertexAttribI4uiv(GLuint index, const GLuint *v) { m_pQtFunctions->glVertexAttribI4uiv(index, v); }
void QtOpenGLExtraFunctionList::glGetUniformuiv(GLuint program, GLint location, GLuint *params) { m_pQtFunctions->glGetUniformuiv(program, location, params); }
GLint QtOpenGLExtraFunctionList::glGetFragDataLocation(GLuint program, const GLchar *name) { return m_pQtFunctions->glGetFragDataLocation(program, name); }
void QtOpenGLExtraFunctionList::glUniform1ui(GLint location, GLuint v0) { m_pQtFunctions->glUniform1ui(location, v0); }
void QtOpenGLExtraFunctionList::glUniform2ui(GLint location, GLuint v0, GLuint v1) { m_pQtFunctions->glUniform2ui(location, v0, v1); }
void QtOpenGLExtraFunctionList::glUniform3ui(GLint location, GLuint v0, GLuint v1, GLuint v2) { m_pQtFunctions->glUniform3ui(location, v0, v1, v2); }
void QtOpenGLExtraFunctionList::glUniform4ui(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3) { m_pQtFunctions->glUniform4ui(location, v0, v1, v2, v3); }
void QtOpenGLExtraFunctionList::glUniform1uiv(GLint location, GLsizei count, const GLuint *value) { m_pQtFunctions->glUniform1uiv(location, count, value); }
void QtOpenGLExtraFunctionList::glUniform2uiv(GLint location, GLsizei count, const GLuint *value) { m_pQtFunctions->glUniform2uiv(location, count, value); }
void QtOpenGLExtraFunctionList::glUniform3uiv(GLint location, GLsizei count, const GLuint *value) { m_pQtFunctions->glUniform3uiv(location, count, value); }
void QtOpenGLExtraFunctionList::glUniform4uiv(GLint location, GLsizei count, const GLuint *value) { m_pQtFunctions->glUniform4uiv(location, count, value); }
void QtOpenGLExtraFunctionList::glClearBufferiv(GLenum buffer, GLint drawbuffer, const GLint *value) { m_pQtFunctions->glClearBufferiv(buffer, drawbuffer, value); }
void QtOpenGLExtraFunctionList::glClearBufferuiv(GLenum buffer, GLint drawbuffer, const GLuint *value) { m_pQtFunctions->glClearBufferuiv(buffer, drawbuffer, value); }
void QtOpenGLExtraFunctionList::glClearBufferfv(GLenum buffer, GLint drawbuffer, const GLfloat *value) { m_pQtFunctions->glClearBufferfv(buffer, drawbuffer, value); }
void QtOpenGLExtraFunctionList::glClearBufferfi(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil) { m_pQtFunctions->glClearBufferfi(buffer, drawbuffer, depth, stencil); }
const GLubyte* QtOpenGLExtraFunctionList::glGetStringi(GLenum name, GLuint index) { return m_pQtFunctions->glGetStringi(name, index); }
void QtOpenGLExtraFunctionList::glCopyBufferSubData(GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size) { m_pQtFunctions->glCopyBufferSubData(readTarget, writeTarget, readOffset, writeOffset, size); }
void QtOpenGLExtraFunctionList::glGetUniformIndices(GLuint program, GLsizei uniformCount, const GLchar *const*uniformNames, GLuint *uniformIndices) { m_pQtFunctions->glGetUniformIndices(program, uniformCount, uniformNames, uniformIndices); }
void QtOpenGLExtraFunctionList::glGetActiveUniformsiv(GLuint program, GLsizei uniformCount, const GLuint *uniformIndices, GLenum pname, GLint *params) { m_pQtFunctions->glGetActiveUniformsiv(program, uniformCount, uniformIndices, pname, params); }
GLuint QtOpenGLExtraFunctionList::glGetUniformBlockIndex(GLuint program, const GLchar *uniformBlockName) { return m_pQtFunctions->glGetUniformBlockIndex(program, uniformBlockName); }
void QtOpenGLExtraFunctionList::glGetActiveUniformBlockiv(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint *params) { m_pQtFunctions->glGetActiveUniformBlockiv(program, uniformBlockIndex, pname, params); }
void QtOpenGLExtraFunctionList::glGetActiveUniformBlockName(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei *length, GLchar *uniformBlockName) { m_pQtFunctions->glGetActiveUniformBlockName(program, uniformBlockIndex, bufSize, length, uniformBlockName); }
void QtOpenGLExtraFunctionList::glUniformBlockBinding(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding) { m_pQtFunctions->glUniformBlockBinding(program, uniformBlockIndex, uniformBlockBinding); }
void QtOpenGLExtraFunctionList::glDrawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei instancecount) { m_pQtFunctions->glDrawArraysInstanced(mode, first, count, instancecount); }
void QtOpenGLExtraFunctionList::glDrawElementsInstanced(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount) { m_pQtFunctions->glDrawElementsInstanced(mode, count, type, indices, instancecount); }
GLsync QtOpenGLExtraFunctionList::glFenceSync(GLenum condition, GLbitfield flags) { return m_pQtFunctions->glFenceSync(condition, flags); }
GLboolean QtOpenGLExtraFunctionList::glIsSync(GLsync sync) { return m_pQtFunctions->glIsSync(sync); }
void QtOpenGLExtraFunctionList::glDeleteSync(GLsync sync) { m_pQtFunctions->glDeleteSync(sync); }
GLenum QtOpenGLExtraFunctionList::glClientWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout) { return m_pQtFunctions->glClientWaitSync(sync, flags, timeout); }
void QtOpenGLExtraFunctionList::glWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout) { m_pQtFunctions->glWaitSync(sync, flags, timeout); }
void QtOpenGLExtraFunctionList::glGetInteger64v(GLenum pname, GLint64 *data) { m_pQtFunctions->glGetInteger64v(pname, data); }
void QtOpenGLExtraFunctionList::glGetSynciv(GLsync sync, GLenum pname, GLsizei bufSize, GLsizei *length, GLint *values) { m_pQtFunctions->glGetSynciv(sync, pname, bufSize, length, values); }
void QtOpenGLExtraFunctionList::glGetInteger64i_v(GLenum target, GLuint index, GLint64 *data) { m_pQtFunctions->glGetInteger64i_v(target, index, data); }
void QtOpenGLExtraFunctionList::glGetBufferParameteri64v(GLenum target, GLenum pname, GLint64 *params) { m_pQtFunctions->glGetBufferParameteri64v(target, pname, params); }
void QtOpenGLExtraFunctionList::glGenSamplers(GLsizei count, GLuint *samplers) { m_pQtFunctions->glGenSamplers(count, samplers); }
void QtOpenGLExtraFunctionList::glDeleteSamplers(GLsizei count, const GLuint *samplers) { m_pQtFunctions->glDeleteSamplers(count, samplers); }
GLboolean QtOpenGLExtraFunctionList::glIsSampler(GLuint sampler) { return m_pQtFunctions->glIsSampler(sampler); }
void QtOpenGLExtraFunctionList::glBindSampler(GLuint unit, GLuint sampler) { m_pQtFunctions->glBindSampler(unit, sampler); }
void QtOpenGLExtraFunctionList::glSamplerParameteri(GLuint sampler, GLenum pname, GLint param) { m_pQtFunctions->glSamplerParameteri(sampler, pname, param); }
void QtOpenGLExtraFunctionList::glSamplerParameteriv(GLuint sampler, GLenum pname, const GLint *param) { m_pQtFunctions->glSamplerParameteriv(sampler, pname, param); }
void QtOpenGLExtraFunctionList::glSamplerParameterf(GLuint sampler, GLenum pname, GLfloat param) { m_pQtFunctions->glSamplerParameterf(sampler, pname, param); }
void QtOpenGLExtraFunctionList::glSamplerParameterfv(GLuint sampler, GLenum pname, const GLfloat *param) { m_pQtFunctions->glSamplerParameterfv(sampler, pname, param); }
void QtOpenGLExtraFunctionList::glGetSamplerParameteriv(GLuint sampler, GLenum pname, GLint *params) { m_pQtFunctions->glGetSamplerParameteriv(sampler, pname, params); }
void QtOpenGLExtraFunctionList::glGetSamplerParameterfv(GLuint sampler, GLenum pname, GLfloat *params) { m_pQtFunctions->glGetSamplerParameterfv(sampler, pname, params); }
void QtOpenGLExtraFunctionList::glVertexAttribDivisor(GLuint index, GLuint divisor) { m_pQtFunctions->glVertexAttribDivisor(index, divisor); }
void QtOpenGLExtraFunctionList::glBindTransformFeedback(GLenum target, GLuint id) { m_pQtFunctions->glBindTransformFeedback(target, id); }
void QtOpenGLExtraFunctionList::glDeleteTransformFeedbacks(GLsizei n, const GLuint *ids) { m_pQtFunctions->glDeleteTransformFeedbacks(n, ids); }
void QtOpenGLExtraFunctionList::glGenTransformFeedbacks(GLsizei n, GLuint *ids) { m_pQtFunctions->glGenTransformFeedbacks(n, ids); }
GLboolean QtOpenGLExtraFunctionList::glIsTransformFeedback(GLuint id) { return m_pQtFunctions->glIsTransformFeedback(id); }
void QtOpenGLExtraFunctionList::glPauseTransformFeedback(void) { m_pQtFunctions->glPauseTransformFeedback(); }
void QtOpenGLExtraFunctionList::glResumeTransformFeedback(void) { m_pQtFunctions->glResumeTransformFeedback(); }
void QtOpenGLExtraFunctionList::glGetProgramBinary(GLuint program, GLsizei bufSize, GLsizei *length, GLenum *binaryFormat, void *binary) { m_pQtFunctions->glGetProgramBinary(program, bufSize, length, binaryFormat, binary); }
void QtOpenGLExtraFunctionList::glProgramBinary(GLuint program, GLenum binaryFormat, const void *binary, GLsizei length) { m_pQtFunctions->glProgramBinary(program, binaryFormat, binary, length); }
void QtOpenGLExtraFunctionList::glProgramParameteri(GLuint program, GLenum pname, GLint value) { m_pQtFunctions->glProgramParameteri(program, pname, value); }
void QtOpenGLExtraFunctionList::glInvalidateFramebuffer(GLenum target, GLsizei numAttachments, const GLenum *attachments) { m_pQtFunctions->glInvalidateFramebuffer(target, numAttachments, attachments); }
void QtOpenGLExtraFunctionList::glInvalidateSubFramebuffer(GLenum target, GLsizei numAttachments, const GLenum *attachments, GLint x, GLint y, GLsizei width, GLsizei height) { m_pQtFunctions->glInvalidateSubFramebuffer(target, numAttachments, attachments, x, y, width, height); }
void QtOpenGLExtraFunctionList::glTexStorage2D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height) { m_pQtFunctions->glTexStorage2D(target, levels, internalformat, width, height); }
void QtOpenGLExtraFunctionList::glTexStorage3D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth) { m_pQtFunctions->glTexStorage3D(target, levels, internalformat, width, height, depth); }
void QtOpenGLExtraFunctionList::glGetInternalformativ(GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint *params) { m_pQtFunctions->glGetInternalformativ(target, internalformat, pname, bufSize, params); }

// GLES 3.1
void QtOpenGLExtraFunctionList::glDispatchCompute(GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z) { m_pQtFunctions->glDispatchCompute(num_groups_x, num_groups_y, num_groups_z); }
void QtOpenGLExtraFunctionList::glDispatchComputeIndirect(GLintptr indirect) { m_pQtFunctions->glDispatchComputeIndirect(indirect); }
void QtOpenGLExtraFunctionList::glDrawArraysIndirect(GLenum mode, const void *indirect) { m_pQtFunctions->glDrawArraysIndirect(mode, indirect); }
void QtOpenGLExtraFunctionList::glDrawElementsIndirect(GLenum mode, GLenum type, const void *indirect) { m_pQtFunctions->glDrawElementsIndirect(mode, type, indirect); }
void QtOpenGLExtraFunctionList::glFramebufferParameteri(GLenum target, GLenum pname, GLint param) { m_pQtFunctions->glFramebufferParameteri(target, pname, param); }
void QtOpenGLExtraFunctionList::glGetFramebufferParameteriv(GLenum target, GLenum pname, GLint *params) { m_pQtFunctions->glGetFramebufferParameteriv(target, pname, params); }
void QtOpenGLExtraFunctionList::glGetProgramInterfaceiv(GLuint program, GLenum programInterface, GLenum pname, GLint *params) { m_pQtFunctions->glGetProgramInterfaceiv(program, programInterface, pname, params); }
GLuint QtOpenGLExtraFunctionList::glGetProgramResourceIndex(GLuint program, GLenum programInterface, const GLchar *name) { return m_pQtFunctions->glGetProgramResourceIndex(program, programInterface, name); }
void QtOpenGLExtraFunctionList::glGetProgramResourceName(GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei *length, GLchar *name) { m_pQtFunctions->glGetProgramResourceName(program, programInterface, index, bufSize, length, name); }
void QtOpenGLExtraFunctionList::glGetProgramResourceiv(GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum *props, GLsizei bufSize, GLsizei *length, GLint *params) { m_pQtFunctions->glGetProgramResourceiv(program, programInterface, index, propCount, props, bufSize, length, params); }
GLint QtOpenGLExtraFunctionList::glGetProgramResourceLocation(GLuint program, GLenum programInterface, const GLchar *name) { return m_pQtFunctions->glGetProgramResourceLocation(program, programInterface, name); }
void QtOpenGLExtraFunctionList::glUseProgramStages(GLuint pipeline, GLbitfield stages, GLuint program) { m_pQtFunctions->glUseProgramStages(pipeline, stages, program); }
void QtOpenGLExtraFunctionList::glActiveShaderProgram(GLuint pipeline, GLuint program) { m_pQtFunctions->glActiveShaderProgram(pipeline, program); }
GLuint QtOpenGLExtraFunctionList::glCreateShaderProgramv(GLenum type, GLsizei count, const GLchar *const*strings) { return m_pQtFunctions->glCreateShaderProgramv(type, count, strings); }
void QtOpenGLExtraFunctionList::glBindProgramPipeline(GLuint pipeline) { m_pQtFunctions->glBindProgramPipeline(pipeline); }
void QtOpenGLExtraFunctionList::glDeleteProgramPipelines(GLsizei n, const GLuint *pipelines) { m_pQtFunctions->glDeleteProgramPipelines(n, pipelines); }
void QtOpenGLExtraFunctionList::glGenProgramPipelines(GLsizei n, GLuint *pipelines) { m_pQtFunctions->glGenProgramPipelines(n, pipelines); }
GLboolean QtOpenGLExtraFunctionList::glIsProgramPipeline(GLuint pipeline) { return m_pQtFunctions->glIsProgramPipeline(pipeline); }
void QtOpenGLExtraFunctionList::glGetProgramPipelineiv(GLuint pipeline, GLenum pname, GLint *params) { m_pQtFunctions->glGetProgramPipelineiv(pipeline, pname, params); }
void QtOpenGLExtraFunctionList::glProgramUniform1i(GLuint program, GLint location, GLint v0) { m_pQtFunctions->glProgramUniform1i(program, location, v0); }
void QtOpenGLExtraFunctionList::glProgramUniform2i(GLuint program, GLint location, GLint v0, GLint v1) { m_pQtFunctions->glProgramUniform2i(program, location, v0, v1); }
void QtOpenGLExtraFunctionList::glProgramUniform3i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2) { m_pQtFunctions->glProgramUniform3i(program, location, v0, v1, v2); }
void QtOpenGLExtraFunctionList::glProgramUniform4i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3) { m_pQtFunctions->glProgramUniform4i(program, location, v0, v1, v2, v3); }
void QtOpenGLExtraFunctionList::glProgramUniform1ui(GLuint program, GLint location, GLuint v0) { m_pQtFunctions->glProgramUniform1ui(program, location, v0); }
void QtOpenGLExtraFunctionList::glProgramUniform2ui(GLuint program, GLint location, GLuint v0, GLuint v1) { m_pQtFunctions->glProgramUniform2ui(program, location, v0, v1); }
void QtOpenGLExtraFunctionList::glProgramUniform3ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2) { m_pQtFunctions->glProgramUniform3ui(program, location, v0, v1, v2); }
void QtOpenGLExtraFunctionList::glProgramUniform4ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3) { m_pQtFunctions->glProgramUniform4ui(program, location, v0, v1, v2, v3); }
void QtOpenGLExtraFunctionList::glProgramUniform1f(GLuint program, GLint location, GLfloat v0) { m_pQtFunctions->glProgramUniform1f(program, location, v0); }
void QtOpenGLExtraFunctionList::glProgramUniform2f(GLuint program, GLint location, GLfloat v0, GLfloat v1) { m_pQtFunctions->glProgramUniform2f(program, location, v0, v1); }
void QtOpenGLExtraFunctionList::glProgramUniform3f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2) { m_pQtFunctions->glProgramUniform3f(program, location, v0, v1, v2); }
void QtOpenGLExtraFunctionList::glProgramUniform4f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) { m_pQtFunctions->glProgramUniform4f(program, location, v0, v1, v2, v3); }
void QtOpenGLExtraFunctionList::glProgramUniform1iv(GLuint program, GLint location, GLsizei count, const GLint *value) { m_pQtFunctions->glProgramUniform1iv(program, location, count, value); }
void QtOpenGLExtraFunctionList::glProgramUniform2iv(GLuint program, GLint location, GLsizei count, const GLint *value) { m_pQtFunctions->glProgramUniform2iv(program, location, count, value); }
void QtOpenGLExtraFunctionList::glProgramUniform3iv(GLuint program, GLint location, GLsizei count, const GLint *value)  { m_pQtFunctions->glProgramUniform3iv(program, location, count, value); }
void QtOpenGLExtraFunctionList::glProgramUniform4iv(GLuint program, GLint location, GLsizei count, const GLint *value) { m_pQtFunctions->glProgramUniform4iv(program, location, count, value); }
void QtOpenGLExtraFunctionList::glProgramUniform1uiv(GLuint program, GLint location, GLsizei count, const GLuint *value) { m_pQtFunctions->glProgramUniform1uiv(program, location, count, value); }
void QtOpenGLExtraFunctionList::glProgramUniform2uiv(GLuint program, GLint location, GLsizei count, const GLuint *value) { m_pQtFunctions->glProgramUniform2uiv(program, location, count, value); }
void QtOpenGLExtraFunctionList::glProgramUniform3uiv(GLuint program, GLint location, GLsizei count, const GLuint *value) { m_pQtFunctions->glProgramUniform3uiv(program, location, count, value); }
void QtOpenGLExtraFunctionList::glProgramUniform4uiv(GLuint program, GLint location, GLsizei count, const GLuint *value) { m_pQtFunctions->glProgramUniform4uiv(program, location, count, value); }
void QtOpenGLExtraFunctionList::glProgramUniform1fv(GLuint program, GLint location, GLsizei count, const GLfloat *value) { m_pQtFunctions->glProgramUniform1fv(program, location, count, value); }
void QtOpenGLExtraFunctionList::glProgramUniform2fv(GLuint program, GLint location, GLsizei count, const GLfloat *value) { m_pQtFunctions->glProgramUniform2fv(program, location, count, value); }
void QtOpenGLExtraFunctionList::glProgramUniform3fv(GLuint program, GLint location, GLsizei count, const GLfloat *value) { m_pQtFunctions->glProgramUniform3fv(program, location, count, value); }
void QtOpenGLExtraFunctionList::glProgramUniform4fv(GLuint program, GLint location, GLsizei count, const GLfloat *value) { m_pQtFunctions->glProgramUniform4fv(program, location, count, value); }
void QtOpenGLExtraFunctionList::glProgramUniformMatrix2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) { m_pQtFunctions->glProgramUniformMatrix2fv(program, location, count, transpose, value); }
void QtOpenGLExtraFunctionList::glProgramUniformMatrix3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) { m_pQtFunctions->glProgramUniformMatrix3fv(program, location, count, transpose, value); }
void QtOpenGLExtraFunctionList::glProgramUniformMatrix4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) { m_pQtFunctions->glProgramUniformMatrix4fv(program, location, count, transpose, value); }
void QtOpenGLExtraFunctionList::glProgramUniformMatrix2x3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) { m_pQtFunctions->glProgramUniformMatrix2x3fv(program, location, count, transpose, value); }
void QtOpenGLExtraFunctionList::glProgramUniformMatrix3x2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) { m_pQtFunctions->glProgramUniformMatrix3x2fv(program, location, count, transpose, value); }
void QtOpenGLExtraFunctionList::glProgramUniformMatrix2x4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) { m_pQtFunctions->glProgramUniformMatrix2x4fv(program, location, count, transpose, value); }
void QtOpenGLExtraFunctionList::glProgramUniformMatrix4x2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) { m_pQtFunctions->glProgramUniformMatrix4x2fv(program, location, count, transpose, value); }
void QtOpenGLExtraFunctionList::glProgramUniformMatrix3x4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) { m_pQtFunctions->glProgramUniformMatrix3x4fv(program, location, count, transpose, value); }
void QtOpenGLExtraFunctionList::glProgramUniformMatrix4x3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) { m_pQtFunctions->glProgramUniformMatrix4x3fv(program, location, count, transpose, value); }
void QtOpenGLExtraFunctionList::glValidateProgramPipeline(GLuint pipeline) { m_pQtFunctions->glValidateProgramPipeline(pipeline); }
void QtOpenGLExtraFunctionList::glGetProgramPipelineInfoLog(GLuint pipeline, GLsizei bufSize, GLsizei *length, GLchar *infoLog) { m_pQtFunctions->glGetProgramPipelineInfoLog(pipeline, bufSize, length, infoLog); }
void QtOpenGLExtraFunctionList::glBindImageTexture(GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format) { m_pQtFunctions->glBindImageTexture(unit, texture, level, layered, layer, access, format); }
void QtOpenGLExtraFunctionList::glGetBooleani_v(GLenum target, GLuint index, GLboolean *data) { m_pQtFunctions->glGetBooleani_v(target, index, data); }
void QtOpenGLExtraFunctionList::glMemoryBarrier(GLbitfield barriers) { m_pQtFunctions->glMemoryBarrier(barriers); }
void QtOpenGLExtraFunctionList::glMemoryBarrierByRegion(GLbitfield barriers) { m_pQtFunctions->glMemoryBarrierByRegion(barriers); }
void QtOpenGLExtraFunctionList::glTexStorage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations) { m_pQtFunctions->glTexStorage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations); }
void QtOpenGLExtraFunctionList::glGetMultisamplefv(GLenum pname, GLuint index, GLfloat *val) { m_pQtFunctions->glGetMultisamplefv(pname, index, val); }
void QtOpenGLExtraFunctionList::glSampleMaski(GLuint maskNumber, GLbitfield mask) { m_pQtFunctions->glSampleMaski(maskNumber, mask); }
void QtOpenGLExtraFunctionList::glGetTexLevelParameteriv(GLenum target, GLint level, GLenum pname, GLint *params) { m_pQtFunctions->glGetTexLevelParameteriv(target, level, pname, params); }
void QtOpenGLExtraFunctionList::glGetTexLevelParameterfv(GLenum target, GLint level, GLenum pname, GLfloat *params) { m_pQtFunctions->glGetTexLevelParameterfv(target, level, pname, params); }
void QtOpenGLExtraFunctionList::glBindVertexBuffer(GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride) { m_pQtFunctions->glBindVertexBuffer(bindingindex, buffer, offset, stride); }
void QtOpenGLExtraFunctionList::glVertexAttribFormat(GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset) { m_pQtFunctions->glVertexAttribFormat(attribindex, size, type, normalized, relativeoffset); }
void QtOpenGLExtraFunctionList::glVertexAttribIFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset) { m_pQtFunctions->glVertexAttribIFormat(attribindex, size, type, relativeoffset); }
void QtOpenGLExtraFunctionList::glVertexAttribBinding(GLuint attribindex, GLuint bindingindex) { m_pQtFunctions->glVertexAttribBinding(attribindex, bindingindex); }
void QtOpenGLExtraFunctionList::glVertexBindingDivisor(GLuint bindingindex, GLuint divisor) { m_pQtFunctions->glVertexBindingDivisor(bindingindex, divisor); }



//----------------------------------------------------------------------------
//
// ---
QtOpenGLContext::QtOpenGLContext(QWindow* pWindow, RenderingAreaFormat frm)
    : m_pWindow(pWindow)
    , m_areaFormat(frm)
    , m_pContextContainer(new OpenGLContextContainer)
    , m_pFuncs(nullptr)
    , m_pExFuncs(nullptr)
{
    m_pContextContainer->AddContext(this);
}

//----------------------------------------------------------------------------
//
// ---
QtOpenGLContext::~QtOpenGLContext()
{
    m_pContextContainer->RemoveContext(this);
    VSN_DELETE_AND_NULL(m_pFuncs);
    VSN_DELETE_AND_NULL(m_pExFuncs);
}

//----------------------------------------------------------------------------
//
// ---
bool QtOpenGLContext::MakeCurrent()
{
    if (QOpenGLContext::makeCurrent(m_pWindow))
    {
        m_pContextInterface = static_cast<OpenGLContextInterface*>((QtOpenGLContext*)QOpenGLContext::currentContext());
        if (m_pFuncs == nullptr)
            m_pFuncs = new QtOpenGLFunctionList();

        if (m_pExFuncs == nullptr)
            m_pExFuncs = new QtOpenGLExtraFunctionList();

        m_pFuncs->Update(functions());
        m_pExFuncs->Update(extraFunctions());

        return true;
    }
    return false;
}

//----------------------------------------------------------------------------
//
// ---
void QtOpenGLContext::DoneCurrent()
{
    QOpenGLContext::doneCurrent();
    m_pContextInterface = static_cast<OpenGLContextInterface*>((QtOpenGLContext*)QOpenGLContext::currentContext());
}

//----------------------------------------------------------------------------
//
// ---
void QtOpenGLContext::SwapBuffers()
{
    QOpenGLContext::swapBuffers(m_pWindow);
}

//----------------------------------------------------------------------------
//
// ---
RenderingAreaFormat QtOpenGLContext::GetFormat() const 
{ 
    return m_areaFormat; 
}

//----------------------------------------------------------------------------
//
// ---
OpenGLFunctionListInterface* QtOpenGLContext::GetFunctionList() const
{ 
    return m_pFuncs; 
}

//----------------------------------------------------------------------------
//
// ---
OpenGLExtraFunctionListInterface* QtOpenGLContext::GetExtraFunctionList() const
{ 
    return m_pExFuncs;
}

//----------------------------------------------------------------------------
//
// ---
FunctionPtr QtOpenGLContext::GetProcAddress(const std::string& procName) const 
{ 
    return (FunctionPtr)getProcAddress(procName.c_str()); 
}

//----------------------------------------------------------------------------
//
// ---
bool QtOpenGLContext::IsValid() const 
{ 
    return QOpenGLContext::isValid(); 
}

//----------------------------------------------------------------------------
//
// ---
GLuint QtOpenGLContext::GetDefaultFrameBufferObject() const 
{ 
    return QOpenGLContext::defaultFramebufferObject(); 
}

//----------------------------------------------------------------------------
//
// ---
OpenGLContextContainer* QtOpenGLContext::GetContextContainer() const 
{ 
    return m_pContextContainer; 
}

//----------------------------------------------------------------------------
//
// ---
bool QtOpenGLContext::IsOpenGLES() const 
{ 
    return QOpenGLContext::isOpenGLES(); 
}

//----------------------------------------------------------------------------
//
// ---
QtOpenGLContextShell::QtOpenGLContextShell(QOpenGLWidget* pWidget, OpenGLContextContainer* sharedContainer)
    : m_pWidget(pWidget)
    , m_pContextContainer(sharedContainer ? sharedContainer : new OpenGLContextContainer)
    , m_pFuncs(nullptr)
    , m_pExFuncs(nullptr)
{
    m_pContextContainer->AddContext(this);
}

//----------------------------------------------------------------------------
//
// ---
QtOpenGLContextShell::~QtOpenGLContextShell()
{
    m_pContextContainer->RemoveContext(this);
    VSN_DELETE_AND_NULL(m_pFuncs);
    VSN_DELETE_AND_NULL(m_pExFuncs);
}

//----------------------------------------------------------------------------
//
// ---
bool QtOpenGLContextShell::MakeCurrent()
{
    if (m_pWidget == nullptr || m_pWidget->context() == nullptr)
        return false;
    if (m_pWidget)
        m_pWidget->makeCurrent();

    if (QOpenGLContext::currentContext() != m_pWidget->context())
    {
        Q_ASSERT(false);
        return false;
    }
    m_pContextInterface = this;
    if (m_pFuncs == nullptr)
        m_pFuncs = new QtOpenGLFunctionList();
    if (m_pExFuncs == nullptr)
        m_pExFuncs = new QtOpenGLExtraFunctionList();

    m_pFuncs->Update(m_pWidget->context()->functions());
    m_pExFuncs->Update(m_pWidget->context()->extraFunctions());
    return true;
}

//----------------------------------------------------------------------------
//
// ---
void QtOpenGLContextShell::DoneCurrent()
{
    if (QOpenGLContext::currentContext() != nullptr)
        return;
    if (m_pWidget)
        m_pWidget->doneCurrent();
    m_pContextInterface = nullptr;
}

OpenGLFunctionListInterface* QtOpenGLContextShell::GetFunctionList() const 
{ return m_pFuncs; }
OpenGLExtraFunctionListInterface* QtOpenGLContextShell::GetExtraFunctionList() const 
{ return m_pExFuncs; }
FunctionPtr QtOpenGLContextShell::GetProcAddress(const std::string& procName) const 
{ return (FunctionPtr)m_pWidget->context()->getProcAddress(procName.c_str()); }
bool QtOpenGLContextShell::IsValid() const 
{ return m_pWidget->context()->isValid(); }
GLuint QtOpenGLContextShell::GetDefaultFrameBufferObject() const 
{ return m_pWidget->context()->defaultFramebufferObject(); }
OpenGLContextContainer* QtOpenGLContextShell::GetContextContainer() const 
{ return m_pContextContainer; }
bool QtOpenGLContextShell::IsOpenGLES() const 
{ return m_pWidget->context()->isOpenGLES(); }
QOpenGLContext* QtOpenGLContextShell::context() const
{ return m_pWidget->context(); }

} // namespace QtVision
VSN_END_NAMESPACE