////////////////////////////////////////////////////////////////////////////////
/**
    \file
    \brief \ru Эти классы необходимы для интеграции Vision с Qt, чтобы обеспечить работу Vision
               c контекстом Qt и разным набором функций любой версии OpenGL.
           \en These classes are needed to integrate Vision with Qt and provides Vision
               with services to work with Qt context and different function set of any OpenGL version. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __QT_OPENGLCONTEXT_H
#define __QT_OPENGLCONTEXT_H

#include <QWindow>
#include <QOpenGLWidget>
#include <QOpenGLContext>
#include <vsn_vision.h>

VSN_BEGIN_NAMESPACE

/** \brief \ru ВНИМАНИЕ! Этот файл не является частью API Vision. Он необходим для иллюстрации использования
               ядра Vision с библиотекой Qt и ее классами. Этот заголовочный файл может изменяться от версии
               к версии без предупреждения или полностью удаляться.
           \en WARNING! The file is not a part of API Vision. It is needed to illustrate using of the Vision kernel
               with Qt library and its classes. This header file can be changed from version to version with
               no warning or completely deleted. \~
*/

namespace QtVision {
//------------------------------------------------------------------------------
/** \brief \ru Класс QtOpenGLFunctionList представляет кроссплатформенный доступ к функциям OpenGL ES 2.0.
           \en The QtOpenGLFunctionList class provides cross-platform access to the OpenGL ES 2.0 functions. \~
    \ingroup QtVision
*/
// ---
class QtOpenGLFunctionList : public OpenGLFunctionListInterface
{
public:
     QtOpenGLFunctionList();
    ~QtOpenGLFunctionList();
public:
    void InitGLFunctionList() override;
    void Update(QOpenGLFunctions* pQtFunctions);
public:
    void glBindTexture(GLenum target, GLuint texture) override;
    void glBlendFunc(GLenum sfactor, GLenum dfactor) override;
    void glClear(GLbitfield mask) override;
    void glClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha) override;
    void glClearStencil(GLint s);
    void glColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha) override;
    void glCopyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border) override;
    void glCopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height) override;
    void glCullFace(GLenum mode) override;
    void glDeleteTextures(GLsizei n, const GLuint* textures) override;
    void glDepthFunc(GLenum func) override;
    void glDepthMask(GLboolean flag) override;
    void glDisable(GLenum cap) override;
    void glDrawArrays(GLenum mode, GLint first, GLsizei count) override;
    void glDrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices) override;
    void glEnable(GLenum cap) override;
    void glFinish() override;
    void glFlush() override;
    void glFrontFace(GLenum mode) override;
    void glGenTextures(GLsizei n, GLuint* textures) override;
    void glGetBooleanv(GLenum pname, GLboolean* params) override;
    GLenum glGetError() override;
    void glGetFloatv(GLenum pname, GLfloat* params) override;
    void glGetIntegerv(GLenum pname, GLint* params) override;
    const GLubyte *glGetString(GLenum name) override;
    void glGetTexParameterfv(GLenum target, GLenum pname, GLfloat* params) override;
    void glGetTexParameteriv(GLenum target, GLenum pname, GLint* params) override;
    void glHint(GLenum target, GLenum mode) override;
    GLboolean glIsEnabled(GLenum cap) override;
    GLboolean glIsTexture(GLuint texture) override;
    void glLineWidth(GLfloat width) override;
    void glPixelStorei(GLenum pname, GLint param) override;
    void glPolygonOffset(GLfloat factor, GLfloat units) override;
    void glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid* pixels) override;
    void glScissor(GLint x, GLint y, GLsizei width, GLsizei height) override;
    void glStencilFunc(GLenum func, GLint ref, GLuint mask) override;
    void glStencilMask(GLuint mask) override;
    void glStencilOp(GLenum fail, GLenum zfail, GLenum zpass) override;
    void glTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* pixels) override;
    void glTexParameterf(GLenum target, GLenum pname, GLfloat param) override;
    void glTexParameterfv(GLenum target, GLenum pname, const GLfloat* params) override;
    void glTexParameteri(GLenum target, GLenum pname, GLint param) override;
    void glTexParameteriv(GLenum target, GLenum pname, const GLint* params) override;
    void glTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* pixels) override;
    void glViewport(GLint x, GLint y, GLsizei width, GLsizei height) override;

    // GL(ES)2
    void glActiveTexture(GLenum texture) override;
    void glAttachShader(GLuint program, GLuint shader) override;
    void glBindAttribLocation(GLuint program, GLuint index, const char* name) override;
    void glBindBuffer(GLenum target, GLuint buffer) override;
    void glBindFramebuffer(GLenum target, GLuint framebuffer) override;
    void glBindRenderbuffer(GLenum target, GLuint renderbuffer) override;
    void glBlendColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha) override;
    void glBlendEquation(GLenum mode) override;
    void glBlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha) override;
    void glBlendFuncSeparate(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha) override;
    void glBufferData(GLenum target, vsngl_GLsizeiptr size, const void* data, GLenum usage) override;
    void glBufferSubData(GLenum target, vsngl_GLintptr offset, vsngl_GLsizeiptr size, const void* data) override;
    GLenum glCheckFramebufferStatus(GLenum target) override;
    void glClearDepthf(GLclampf depth) override;
    void glCompileShader(GLuint shader) override;
    void glCompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void* data) override;
    void glCompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void* data) override;
    GLuint glCreateProgram() override;
    GLuint glCreateShader(GLenum type) override;
    void glDeleteBuffers(GLsizei n, const GLuint* buffers) override;
    void glDeleteFramebuffers(GLsizei n, const GLuint* framebuffers) override;
    void glDeleteProgram(GLuint program) override;
    void glDeleteRenderbuffers(GLsizei n, const GLuint* renderbuffers) override;
    void glDeleteShader(GLuint shader) override;
    void glDepthRangef(GLclampf zNear, GLclampf zFar) override;
    void glDetachShader(GLuint program, GLuint shader) override;
    void glDisableVertexAttribArray(GLuint index) override;
    void glEnableVertexAttribArray(GLuint index) override;
    void glFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer) override;
    void glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) override;
    void glGenBuffers(GLsizei n, GLuint* buffers) override;
    void glGenerateMipmap(GLenum target) override;
    void glGenFramebuffers(GLsizei n, GLuint* framebuffers) override;
    void glGenRenderbuffers(GLsizei n, GLuint* renderbuffers) override;
    void glGetActiveAttrib(GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, char* name) override;
    void glGetActiveUniform(GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, char* name) override;
    void glGetAttachedShaders(GLuint program, GLsizei maxcount, GLsizei* count, GLuint* shaders) override;
    GLint glGetAttribLocation(GLuint program, const char* name) override;
    void glGetBufferParameteriv(GLenum target, GLenum pname, GLint* params) override;
    void glGetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint* params) override;
    void glGetProgramiv(GLuint program, GLenum pname, GLint* params) override;
    void glGetProgramInfoLog(GLuint program, GLsizei bufsize, GLsizei* length, char* infolog) override;
    void glGetRenderbufferParameteriv(GLenum target, GLenum pname, GLint* params) override;
    void glGetShaderiv(GLuint shader, GLenum pname, GLint* params) override;
    void glGetShaderInfoLog(GLuint shader, GLsizei bufsize, GLsizei* length, char* infolog) override;
    void glGetShaderPrecisionFormat(GLenum shadertype, GLenum precisiontype, GLint* range, GLint* precision) override;
    void glGetShaderSource(GLuint shader, GLsizei bufsize, GLsizei* length, char* source) override;
    void glGetUniformfv(GLuint program, GLint location, GLfloat* params) override;
    void glGetUniformiv(GLuint program, GLint location, GLint* params) override;
    GLint glGetUniformLocation(GLuint program, const char* name) override;
    void glGetVertexAttribfv(GLuint index, GLenum pname, GLfloat* params) override;
    void glGetVertexAttribiv(GLuint index, GLenum pname, GLint* params) override;
    void glGetVertexAttribPointerv(GLuint index, GLenum pname, void** pointer) override;
    GLboolean glIsBuffer(GLuint buffer) override;
    GLboolean glIsFramebuffer(GLuint framebuffer) override;
    GLboolean glIsProgram(GLuint program) override;
    GLboolean glIsRenderbuffer(GLuint renderbuffer) override;
    GLboolean glIsShader(GLuint shader) override;
    void glLinkProgram(GLuint program) override;
    void glReleaseShaderCompiler() override;
    void glRenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height) override;
    void glSampleCoverage(GLclampf value, GLboolean invert) override;
    void glShaderBinary(GLint n, const GLuint* shaders, GLenum binaryformat, const void* binary, GLint length) override;
    void glShaderSource(GLuint shader, GLsizei count, const char** string, const GLint* length) override;
    void glStencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask) override;
    void glStencilMaskSeparate(GLenum face, GLuint mask) override;
    void glStencilOpSeparate(GLenum face, GLenum fail, GLenum zfail, GLenum zpass) override;
    void glUniform1f(GLint location, GLfloat x) override;
    void glUniform1fv(GLint location, GLsizei count, const GLfloat* v) override;
    void glUniform1i(GLint location, GLint x) override;
    void glUniform1iv(GLint location, GLsizei count, const GLint* v) override;
    void glUniform2f(GLint location, GLfloat x, GLfloat y) override;
    void glUniform2fv(GLint location, GLsizei count, const GLfloat* v) override;
    void glUniform2i(GLint location, GLint x, GLint y) override;
    void glUniform2iv(GLint location, GLsizei count, const GLint* v) override;
    void glUniform3f(GLint location, GLfloat x, GLfloat y, GLfloat z) override;
    void glUniform3fv(GLint location, GLsizei count, const GLfloat* v) override;
    void glUniform3i(GLint location, GLint x, GLint y, GLint z) override;
    void glUniform3iv(GLint location, GLsizei count, const GLint* v) override;
    void glUniform4f(GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w) override;
    void glUniform4fv(GLint location, GLsizei count, const GLfloat* v) override;
    void glUniform4i(GLint location, GLint x, GLint y, GLint z, GLint w) override;
    void glUniform4iv(GLint location, GLsizei count, const GLint* v) override;
    void glUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) override;
    void glUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) override;
    void glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) override;
    void glUseProgram(GLuint program) override;
    void glValidateProgram(GLuint program) override;
    void glVertexAttrib1f(GLuint indx, GLfloat x) override;
    void glVertexAttrib1fv(GLuint indx, const GLfloat* values) override;
    void glVertexAttrib2f(GLuint indx, GLfloat x, GLfloat y) override;
    void glVertexAttrib2fv(GLuint indx, const GLfloat* values) override;
    void glVertexAttrib3f(GLuint indx, GLfloat x, GLfloat y, GLfloat z) override;
    void glVertexAttrib3fv(GLuint indx, const GLfloat* values) override;
    void glVertexAttrib4f(GLuint indx, GLfloat x, GLfloat y, GLfloat z, GLfloat w) override;
    void glVertexAttrib4fv(GLuint indx, const GLfloat* values) override;
    void glVertexAttribPointer(GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* ptr) override;
private:
    QOpenGLFunctions* m_pQtFunctions;
};


//------------------------------------------------------------------------------
/** \brief \ru Класс QtOpenGLExtraFunctionList представляет кроссплатформенный доступ к функциям OpenGL ES 2.0.
           \en The QtOpenGLExtraFunctionList class provides cross-platform access to the OpenGL ES 2.0 functions. \~
    \ingroup QtVision
*/
// ---
class QtOpenGLExtraFunctionList : public OpenGLExtraFunctionListInterface
{
public:
    explicit QtOpenGLExtraFunctionList();
    ~QtOpenGLExtraFunctionList();

    void Update(QOpenGLExtraFunctions* pQtFunctions);
public:
    // GLES3
    void glReadBuffer(GLenum mode) override;
    void glDrawRangeElements(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void *indices) override;
    void glTexImage3D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void *pixels) override;
    void glTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *pixels) override;
    void glCopyTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height) override;
    void glCompressedTexImage3D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void *data) override;
    void glCompressedTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void *data) override;
    void glGenQueries(GLsizei n, GLuint *ids) override;
    void glDeleteQueries(GLsizei n, const GLuint *ids) override;
    GLboolean glIsQuery(GLuint id) override;
    void glBeginQuery(GLenum target, GLuint id) override;
    void glEndQuery(GLenum target) override;
    void glGetQueryiv(GLenum target, GLenum pname, GLint *params) override;
    void glGetQueryObjectuiv(GLuint id, GLenum pname, GLuint *params) override;
    GLboolean glUnmapBuffer(GLenum target) override;
    void glGetBufferPointerv(GLenum target, GLenum pname, void **params) override;
    void glDrawBuffers(GLsizei n, const GLenum *bufs) override;
    void glUniformMatrix2x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) override;
    void glUniformMatrix3x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) override;
    void glUniformMatrix2x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) override;
    void glUniformMatrix4x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) override;
    void glUniformMatrix3x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) override;
    void glUniformMatrix4x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) override;
    void glBlitFramebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter) override;
    void glRenderbufferStorageMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height) override;
    void glFramebufferTextureLayer(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer) override;
    void *glMapBufferRange(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access) override;
    void glFlushMappedBufferRange(GLenum target, GLintptr offset, GLsizeiptr length) override;
    void glBindVertexArray(GLuint array) override;
    void glDeleteVertexArrays(GLsizei n, const GLuint *arrays) override;
    void glGenVertexArrays(GLsizei n, GLuint* arrays) override;
    GLboolean glIsVertexArray(GLuint array) override;
    void glGetIntegeri_v(GLenum target, GLuint index, GLint *data) override;
    void glBeginTransformFeedback(GLenum primitiveMode) override;
    void glEndTransformFeedback(void) override;
    void glBindBufferRange(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size) override;
    void glBindBufferBase(GLenum target, GLuint index, GLuint buffer) override;
    void glTransformFeedbackVaryings(GLuint program, GLsizei count, const GLchar *const*varyings, GLenum bufferMode) override;
    void glGetTransformFeedbackVarying(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLsizei *size, GLenum *type, GLchar *name) override;
    void glVertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer) override;
    void glGetVertexAttribIiv(GLuint index, GLenum pname, GLint *params) override;
    void glGetVertexAttribIuiv(GLuint index, GLenum pname, GLuint *params) override;
    void glVertexAttribI4i(GLuint index, GLint x, GLint y, GLint z, GLint w) override;
    void glVertexAttribI4ui(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w) override;
    void glVertexAttribI4iv(GLuint index, const GLint *v) override;
    void glVertexAttribI4uiv(GLuint index, const GLuint *v) override;
    void glGetUniformuiv(GLuint program, GLint location, GLuint *params) override;
    GLint glGetFragDataLocation(GLuint program, const GLchar *name) override;
    void glUniform1ui(GLint location, GLuint v0) override;
    void glUniform2ui(GLint location, GLuint v0, GLuint v1) override;
    void glUniform3ui(GLint location, GLuint v0, GLuint v1, GLuint v2) override;
    void glUniform4ui(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3) override;
    void glUniform1uiv(GLint location, GLsizei count, const GLuint *value) override;
    void glUniform2uiv(GLint location, GLsizei count, const GLuint *value) override;
    void glUniform3uiv(GLint location, GLsizei count, const GLuint *value) override;
    void glUniform4uiv(GLint location, GLsizei count, const GLuint *value) override;
    void glClearBufferiv(GLenum buffer, GLint drawbuffer, const GLint *value) override;
    void glClearBufferuiv(GLenum buffer, GLint drawbuffer, const GLuint *value) override;
    void glClearBufferfv(GLenum buffer, GLint drawbuffer, const GLfloat *value) override;
    void glClearBufferfi(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil) override;
    const GLubyte *glGetStringi(GLenum name, GLuint index) override;
    void glCopyBufferSubData(GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size) override;
    void glGetUniformIndices(GLuint program, GLsizei uniformCount, const GLchar *const*uniformNames, GLuint *uniformIndices) override;
    void glGetActiveUniformsiv(GLuint program, GLsizei uniformCount, const GLuint *uniformIndices, GLenum pname, GLint *params) override;
    GLuint glGetUniformBlockIndex(GLuint program, const GLchar *uniformBlockName) override;
    void glGetActiveUniformBlockiv(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint *params) override;
    void glGetActiveUniformBlockName(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei *length, GLchar *uniformBlockName) override;
    void glUniformBlockBinding(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding) override;
    void glDrawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei instancecount) override;
    void glDrawElementsInstanced(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount) override;
    GLsync glFenceSync(GLenum condition, GLbitfield flags) override;
    GLboolean glIsSync(GLsync sync) override;
    void glDeleteSync(GLsync sync) override;
    GLenum glClientWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout) override;
    void glWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout) override;
    void glGetInteger64v(GLenum pname, GLint64 *data) override;
    void glGetSynciv(GLsync sync, GLenum pname, GLsizei bufSize, GLsizei *length, GLint *values) override;
    void glGetInteger64i_v(GLenum target, GLuint index, GLint64 *data) override;
    void glGetBufferParameteri64v(GLenum target, GLenum pname, GLint64 *params) override;
    void glGenSamplers(GLsizei count, GLuint *samplers) override;
    void glDeleteSamplers(GLsizei count, const GLuint *samplers) override;
    GLboolean glIsSampler(GLuint sampler) override;
    void glBindSampler(GLuint unit, GLuint sampler) override;
    void glSamplerParameteri(GLuint sampler, GLenum pname, GLint param) override;
    void glSamplerParameteriv(GLuint sampler, GLenum pname, const GLint *param) override;
    void glSamplerParameterf(GLuint sampler, GLenum pname, GLfloat param) override;
    void glSamplerParameterfv(GLuint sampler, GLenum pname, const GLfloat *param) override;
    void glGetSamplerParameteriv(GLuint sampler, GLenum pname, GLint *params) override;
    void glGetSamplerParameterfv(GLuint sampler, GLenum pname, GLfloat *params) override;
    void glVertexAttribDivisor(GLuint index, GLuint divisor) override;
    void glBindTransformFeedback(GLenum target, GLuint id) override;
    void glDeleteTransformFeedbacks(GLsizei n, const GLuint *ids) override;
    void glGenTransformFeedbacks(GLsizei n, GLuint *ids) override;
    GLboolean glIsTransformFeedback(GLuint id) override;
    void glPauseTransformFeedback(void) override;
    void glResumeTransformFeedback(void) override;
    void glGetProgramBinary(GLuint program, GLsizei bufSize, GLsizei *length, GLenum *binaryFormat, void *binary) override;
    void glProgramBinary(GLuint program, GLenum binaryFormat, const void *binary, GLsizei length) override;
    void glProgramParameteri(GLuint program, GLenum pname, GLint value) override;
    void glInvalidateFramebuffer(GLenum target, GLsizei numAttachments, const GLenum *attachments) override;
    void glInvalidateSubFramebuffer(GLenum target, GLsizei numAttachments, const GLenum *attachments, GLint x, GLint y, GLsizei width, GLsizei height) override;
    void glTexStorage2D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height) override;
    void glTexStorage3D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth) override;
    void glGetInternalformativ(GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint *params) override;

    // GLES 3.1
    void glDispatchCompute(GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z) override;
    void glDispatchComputeIndirect(GLintptr indirect) override;
    void glDrawArraysIndirect(GLenum mode, const void *indirect) override;
    void glDrawElementsIndirect(GLenum mode, GLenum type, const void *indirect) override;
    void glFramebufferParameteri(GLenum target, GLenum pname, GLint param) override;
    void glGetFramebufferParameteriv(GLenum target, GLenum pname, GLint *params) override;
    void glGetProgramInterfaceiv(GLuint program, GLenum programInterface, GLenum pname, GLint *params) override;
    GLuint glGetProgramResourceIndex(GLuint program, GLenum programInterface, const GLchar *name) override;
    void glGetProgramResourceName(GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei *length, GLchar *name) override;
    void glGetProgramResourceiv(GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum *props, GLsizei bufSize, GLsizei *length, GLint *params) override;
    GLint glGetProgramResourceLocation(GLuint program, GLenum programInterface, const GLchar *name) override;
    void glUseProgramStages(GLuint pipeline, GLbitfield stages, GLuint program) override;
    void glActiveShaderProgram(GLuint pipeline, GLuint program) override;
    GLuint glCreateShaderProgramv(GLenum type, GLsizei count, const GLchar *const*strings) override;
    void glBindProgramPipeline(GLuint pipeline) override;
    void glDeleteProgramPipelines(GLsizei n, const GLuint *pipelines) override;
    void glGenProgramPipelines(GLsizei n, GLuint *pipelines) override;
    GLboolean glIsProgramPipeline(GLuint pipeline) override;
    void glGetProgramPipelineiv(GLuint pipeline, GLenum pname, GLint *params) override;
    void glProgramUniform1i(GLuint program, GLint location, GLint v0) override;
    void glProgramUniform2i(GLuint program, GLint location, GLint v0, GLint v1) override;
    void glProgramUniform3i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2) override;
    void glProgramUniform4i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3) override;
    void glProgramUniform1ui(GLuint program, GLint location, GLuint v0) override;
    void glProgramUniform2ui(GLuint program, GLint location, GLuint v0, GLuint v1) override;
    void glProgramUniform3ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2) override;
    void glProgramUniform4ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3) override;
    void glProgramUniform1f(GLuint program, GLint location, GLfloat v0) override;
    void glProgramUniform2f(GLuint program, GLint location, GLfloat v0, GLfloat v1) override;
    void glProgramUniform3f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2) override;
    void glProgramUniform4f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) override;
    void glProgramUniform1iv(GLuint program, GLint location, GLsizei count, const GLint *value) override;
    void glProgramUniform2iv(GLuint program, GLint location, GLsizei count, const GLint *value) override;
    void glProgramUniform3iv(GLuint program, GLint location, GLsizei count, const GLint *value) override;
    void glProgramUniform4iv(GLuint program, GLint location, GLsizei count, const GLint *value) override;
    void glProgramUniform1uiv(GLuint program, GLint location, GLsizei count, const GLuint *value) override;
    void glProgramUniform2uiv(GLuint program, GLint location, GLsizei count, const GLuint *value) override;
    void glProgramUniform3uiv(GLuint program, GLint location, GLsizei count, const GLuint *value) override;
    void glProgramUniform4uiv(GLuint program, GLint location, GLsizei count, const GLuint *value) override;
    void glProgramUniform1fv(GLuint program, GLint location, GLsizei count, const GLfloat *value) override;
    void glProgramUniform2fv(GLuint program, GLint location, GLsizei count, const GLfloat *value) override;
    void glProgramUniform3fv(GLuint program, GLint location, GLsizei count, const GLfloat *value) override;
    void glProgramUniform4fv(GLuint program, GLint location, GLsizei count, const GLfloat *value) override;
    void glProgramUniformMatrix2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) override;
    void glProgramUniformMatrix3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) override;
    void glProgramUniformMatrix4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) override;
    void glProgramUniformMatrix2x3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) override;
    void glProgramUniformMatrix3x2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) override;
    void glProgramUniformMatrix2x4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) override;
    void glProgramUniformMatrix4x2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) override;
    void glProgramUniformMatrix3x4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) override;
    void glProgramUniformMatrix4x3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) override;
    void glValidateProgramPipeline(GLuint pipeline) override;
    void glGetProgramPipelineInfoLog(GLuint pipeline, GLsizei bufSize, GLsizei *length, GLchar *infoLog) override;
    void glBindImageTexture(GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format) override;
    void glGetBooleani_v(GLenum target, GLuint index, GLboolean *data) override;
    void glMemoryBarrier(GLbitfield barriers) override;
    void glMemoryBarrierByRegion(GLbitfield barriers) override;
    void glTexStorage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations) override;
    void glGetMultisamplefv(GLenum pname, GLuint index, GLfloat *val) override;
    void glSampleMaski(GLuint maskNumber, GLbitfield mask) override;
    void glGetTexLevelParameteriv(GLenum target, GLint level, GLenum pname, GLint *params) override;
    void glGetTexLevelParameterfv(GLenum target, GLint level, GLenum pname, GLfloat *params) override;
    void glBindVertexBuffer(GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride) override;
    void glVertexAttribFormat(GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset) override;
    void glVertexAttribIFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset) override;
    void glVertexAttribBinding(GLuint attribindex, GLuint bindingindex) override;
    void glVertexBindingDivisor(GLuint bindingindex, GLuint divisor) override;
private:
    QOpenGLExtraFunctions* m_pQtFunctions;
};


//------------------------------------------------------------------------------
/** \brief \ru Класс QtOpenGLContext интегрирует QOpenGLContext для работы его в Vision.
           \en QtOpenGLContext class integrates QOpenGLContext for it to work in Vision. \~
    \details \ru QtOpenGLContext представляет набор функций для работы внутри Vision, а также
                 для установки текущего OpenGL контекста и его "свепирования" при отрисовке.
             \en QtOpenGLContext class represents a set of functions to work inside Vision
                 and also to set the current OpenGL context and its swapping while rendering. \n \~
    \ingroup QtVision
*/
// ---
class QtOpenGLContext : public QOpenGLContext, public OpenGLContextInterface
{
public:
    explicit QtOpenGLContext(QWindow* pWindow, RenderingAreaFormat frm);
    virtual ~QtOpenGLContext();
public:
    virtual bool MakeCurrent();
    virtual void DoneCurrent() override;
    virtual void SwapBuffers();
    virtual RenderingAreaFormat GetFormat() const override;
    virtual OpenGLFunctionListInterface* GetFunctionList() const override;
    virtual OpenGLExtraFunctionListInterface* GetExtraFunctionList() const override;
    virtual FunctionPtr GetProcAddress(const std::string& procName) const override;
    virtual bool IsValid() const override;
    virtual GLuint GetDefaultFrameBufferObject() const override;
    virtual OpenGLContextContainer* GetContextContainer() const override;
    virtual bool IsOpenGLES() const override;
protected:
    QWindow* m_pWindow;
    RenderingAreaFormat m_areaFormat;
    OpenGLContextContainer* m_pContextContainer;
    QtOpenGLFunctionList* m_pFuncs;
    QtOpenGLExtraFunctionList* m_pExFuncs;
};


//------------------------------------------------------------------------------
/** \brief \ru Класс QtOpenGLContextShell является оболочкой для QOpenGLContext.
           \en QtOpenGLContextShell class is a shell for QOpenGLContext. \~
    \details \ru Класс QtOpenGLContextShell инкапсулирует QOpenGLContext и перевызывает основной функционал, 
                 который необходим для совместной работы Vision и QOpenGLWidget.
             \en QtOpenGLContextShell class uncollapses QOpenGLContext and recalls the main functional
                 necessary for Vision and QOpenGLWidget to work jointly. \n \~
    \ingroup QtVision
*/
// ---
class QtOpenGLContextShell : public OpenGLContextInterface
{
public:
    explicit QtOpenGLContextShell(QOpenGLWidget* pWidget, OpenGLContextContainer* sharedContainer = nullptr);
    virtual ~QtOpenGLContextShell();
public:
    virtual bool MakeCurrent() override;
    virtual void DoneCurrent() override;
    virtual OpenGLFunctionListInterface* GetFunctionList() const override;
    virtual OpenGLExtraFunctionListInterface* GetExtraFunctionList() const override;
    virtual FunctionPtr GetProcAddress(const std::string& procName) const override;
    virtual bool IsValid() const override;
    virtual GLuint GetDefaultFrameBufferObject() const override;
    virtual OpenGLContextContainer* GetContextContainer() const override;
    virtual bool IsOpenGLES() const override;
public:
    QOpenGLContext* context() const;
protected:
    QOpenGLWidget* m_pWidget;
    RenderingAreaFormat m_areaFormat;
    OpenGLContextContainer* m_pContextContainer;
    QtOpenGLFunctionList* m_pFuncs;
    QtOpenGLExtraFunctionList* m_pExFuncs;
};

} // namespace QtVision

VSN_END_NAMESPACE

#endif // __QT_OPENGLCONTEXT_H
