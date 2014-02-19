/**
 *
 * SDL 2.0 OpenGL ES Test Application
 *
 * Copyright (C) 2013 Jolla Ltd.
 * Contact: Thomas Perl <thomas.perl@jollamobile.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 **/


#include <GLES2/gl2.h>

#include "common.h"

class SDL2TestApplicationGLESv2 : public SDL2TestApplication {
    public:
        SDL2TestApplicationGLESv2();
        ~SDL2TestApplicationGLESv2();

        virtual void initGL();
        virtual void resizeGL(int width, int height);
        virtual void renderGL();

    private:
        GLuint m_program;
};

static const char *vertex_shader_src =
"precision mediump float;\n"
"\n"
"attribute vec2 vtxcoord;\n"
"uniform mat4 projection;\n"
"\n"
"void main(void)\n"
"{\n"
"    gl_Position = projection * vec4(vtxcoord, 0.0, 1.0);\n"
"}\n"
;

static const char *fragment_shader_src =
"precision mediump float;\n"
"\n"
"uniform vec4 color;\n"
"\n"
"void main(void)\n"
"{\n"
"    gl_FragColor = color;\n"
"}\n"
;

static GLuint
build_shader(GLenum type, const char *source)
{
    GLuint id = glCreateShader(type);

    glShaderSource(id, 1, &source, NULL);
    glCompileShader(id);

    GLint result = GL_FALSE;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result != GL_TRUE) {
        char tmp[2048];
        glGetShaderInfoLog(id, sizeof(tmp), NULL, tmp);
        printf("%s shader compile error:\n====\n%s\n====\n",
                (type == GL_VERTEX_SHADER) ? "Vertex" : "Fragment", tmp);
    }

    return id;
}

static GLuint
build_program()
{
    GLuint id = glCreateProgram();

    GLuint vertex_shader_id = build_shader(GL_VERTEX_SHADER, vertex_shader_src);
    GLuint fragment_shader_id = build_shader(GL_FRAGMENT_SHADER, fragment_shader_src);

    glAttachShader(id, vertex_shader_id);
    glAttachShader(id, fragment_shader_id);

    glLinkProgram(id);
    GLint result = GL_FALSE;
    glGetProgramiv(id, GL_LINK_STATUS, &result);
    if (result != GL_TRUE) {
        char tmp[2048];
        glGetProgramInfoLog(id, sizeof(tmp), NULL, tmp);
        printf("Program link error:\n====\n%s\n====\n", tmp);
    }

    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);

    return id;
}

SDL2TestApplicationGLESv2::SDL2TestApplicationGLESv2()
    : SDL2TestApplication(2, 0)
{
}

SDL2TestApplicationGLESv2::~SDL2TestApplicationGLESv2()
{
    glDeleteProgram(m_program);
}

void
SDL2TestApplicationGLESv2::initGL()
{
    glClearColor(0.3, 0.2, 0.1, 1.0);

    m_program = build_program();
}

void
SDL2TestApplicationGLESv2::resizeGL(int width, int height)
{
    glUseProgram(m_program);

    // Orthographic projection
    // https://www.opengl.org/sdk/docs/man2/xhtml/glOrtho.xml
    float left = 0, right = width, bottom = height, top = 0;
    float nearVal = -1, farVal = +1;

    float tx = - (right + left) / (right - left);
    float ty = - (top + bottom) / (top - bottom);
    float tz = - (farVal + nearVal) / (farVal - nearVal);

    // Transposed
    float projection[] = {
        2.0 / (right - left), 0.0, 0.0, 0.0,
        0.0, 2.0 / (top - bottom), 0.0, 0.0,
        0.0, 0.0, -2.0 / (farVal - nearVal), 0.0,
        tx, ty, tz, 1.0,
    };

    int projection_loc = glGetUniformLocation(m_program, "projection");
    glUniformMatrix4fv(projection_loc, 1, GL_FALSE, projection);

    glUseProgram(0);
}

static void
draw_touch_point(TouchPoint *touch, void *user_data)
{
    float d = 30;

    float vertices[] = {
        touch->x - d, touch->y - d,
        touch->x + d, touch->y - d,
        touch->x - d, touch->y + d,
        touch->x + d, touch->y + d,
    };

    int vtxcoord_loc = *((int*)user_data);
    glVertexAttribPointer(vtxcoord_loc, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void
SDL2TestApplicationGLESv2::renderGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(m_program);

    int color_loc = glGetUniformLocation(m_program, "color");
    glUniform4f(color_loc, 0.1, 0.3, 0.7, 1.0);

    int vtxcoord_loc = glGetAttribLocation(m_program, "vtxcoord");
    glEnableVertexAttribArray(vtxcoord_loc);

    for_each_touch(draw_touch_point, &vtxcoord_loc);

    glDisableVertexAttribArray(vtxcoord_loc);

    glUseProgram(0);
}

int
main(int argc, char *argv[])
{
    SDL2TestApplicationGLESv2 testapp_glesv2;
    return testapp_glesv2.run();
}

