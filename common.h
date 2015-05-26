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


#ifndef SAILFISH_SDL_WAYLAND_OPENGL_TEST_H
#define SAILFISH_SDL_WAYLAND_OPENGL_TEST_H

#include <SDL.h>
#include <stdio.h>

#include <vector>

class TouchPoint {
    public:
        TouchPoint(int id, float x, float y) : id(id), x(x), y(y) {}

        int id;
        float x;
        float y;
};

typedef void (*touch_point_func)(const TouchPoint &touch, void *user_data);

class SDL2TestApplication {
    public:
        SDL2TestApplication(int major, int minor);
        ~SDL2TestApplication();

        int run();

        virtual void initGL() = 0;
        virtual void resizeGL(int width, int height) = 0;
        virtual void renderGL() = 0;

        virtual void onPressed(const TouchPoint &touch) {}

        void for_each_touch(touch_point_func f, void *user_data);

    private:
        int m_major;
        int m_minor;
        SDL_Window *m_window;
        SDL_GLContext m_gl_context;
        std::vector<TouchPoint> m_touches;
};

#endif /* SAILFISH_SDL_WAYLAND_OPENGL_TEST_H */
