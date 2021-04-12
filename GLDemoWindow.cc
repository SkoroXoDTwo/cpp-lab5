#include <cmath>
#include "GLDemoWindow.h"

#include "Primitives.h"

static constexpr double Pi = acos(-1.);

static VertexVector s_cube_vertices{
        {1.0,  1.0,  2.0},
        {1.0,  -1.0, 2.0},
        {-1.0, -1.0, 2.0},
        {-1.0, 1.0,  2.0},
        {1.0,  1.0,  0.0},
        {1.0,  -1.0, 0.0},
        {-1.0, -1.0, 0.0},
        {-1.0, 1.0,  0.0},
};

static FaceVector s_cube_faces{
        {4, 0, 1, 2, 3},
        {4, 7, 6, 5, 4},
        {4, 1, 0, 4, 5},
        {4, 3, 2, 6, 7},
        {4, 0, 3, 7, 4},
        {4, 2, 1, 5, 6},
};

static NormalVector s_cube_normals{
        {0.0,  0.0,  1.0},
        {0.0,  0.0,  -1.0},
        {1.0,  0.0,  0.0},
        {-1.0, 0.0,  0.0},
        {0.0,  1.0,  0.0},
        {0.0,  -1.0, 0.0},
};

static ColorVector s_cube_colors{
        {1.0f, 1.0f, 1.0f},
        {1.0f, 1.0f, 1.0f},
        {1.0f, 1.0f, 1.0f},
        {1.0f, 1.0f, 1.0f},
        {1.0f, 1.0f, 1.0f},
        {1.0f, 1.0f, 1.0f},
};

static TexCoordVector s_cube_tex_coords{
        {{0.00, 0.00}, {0.00, 0.00}, {0.00, 0.00}, {0.00, 0.00}},
        {{0.00, 0.00}, {0.00, 0.00}, {0.00, 0.00}, {0.00, 0.00}},
        {{0.00, 0.00}, {0.50, 0.00}, {0.50, 0.50}, {0.00, 0.50}},
        {{0.50, 0.50}, {1.00, 0.50}, {1.00, 1.00}, {0.50, 1.00}},
        {{0.50, 0.00}, {1.00, 0.00}, {1.00, 0.50}, {0.50, 0.50}},
        {{0.50, 0.00}, {1.00, 0.00}, {1.00, 0.50}, {0.50, 0.50}},
};


static VertexVector s_crisha_vertices{
        {1.0,  -1.2, 2.0},
        {1.0,  1.2,  2.0},
        {-1.0, 1.2,  2.0},
        {-1.0, -1.2, 2.0},
        {1.0,  0.0,  3.2},
        {-1.0, 0.0,  3.2},
};

static FaceVector s_crisha_faces{
        {4, 0, 1, 2, 3},
        {4, 1, 4, 5, 2},
        {4, 0, 3, 5, 4},
        {3, 0, 4, 1},
        {3, 2, 5, 3},
};

static NormalVector s_crisha_normals{
        {0.0,  0.0,  -1.0},
        {0.0,  1.0,  1.0},
        {0.0,  -1.0, 1.0},
        {1.0,  0.0,  0.0},
        {-1.0, 0.0,  0.0},
};

static ColorVector s_crisha_colors{
        {1.0f, 1.0f, 1.0f},
        {1.0f, 1.0f, 1.0f},
        {1.0f, 1.0f, 1.0f},
        {1.0f, 1.0f, 1.0f},
        {1.0f, 1.0f, 1.0f},
};

static TexCoordVector s_crisha_tex_coords{
        {{0.00, 0.00}, {0.00, 0.00}, {0.00, 0.00}, {0.00, 0.00}},
        {{0.00, 0.50}, {0.00, 0.00}, {0.50, 0.00}, {0.50, 0.50}},
        {{0.50, 0.50}, {0.00, 0.50}, {0.00, 0.00}, {0.50, 0.00}},
        {{0.50, 0.50}, {0.75, 0.25}, {1.00, 0.50}},
        {{0.50, 0.50}, {0.75, 0.25}, {1.00, 0.50}},
};


static VertexVector s_tube_vertices{
        {-0.25, -0.25, 3.4},
        {-0.25, -0.5,  3.4},
        {-0.5,  -0.5,  3.4},
        {-0.5,  -0.25, 3.4},
        {-0.25, -0.25, 2.0},
        {-0.25, -0.5,  2.0},
        {-0.5,  -0.5,  2.0},
        {-0.5,  -0.25, 2.0},
};

static FaceVector s_tube_faces{
        {4, 0, 1, 2, 3},
        {4, 7, 6, 5, 4},
        {4, 1, 0, 4, 5},
        {4, 3, 2, 6, 7},
        {4, 0, 3, 7, 4},
        {4, 2, 1, 5, 6},
};

static NormalVector s_tube_normals{
        {0.0,  0.0,  1.0},
        {0.0,  0.0,  -1.0},
        {1.0,  0.0,  0.0},
        {-1.0, 0.0,  0.0},
        {0.0,  1.0,  0.0},
        {0.0,  -1.0, 0.0},
};

static ColorVector s_tube_colors{
        {0.0f, 0.0f, 0.0f},
        {1.0f, 1.0f, 1.0f},
        {1.0f, 1.0f, 1.0f},
        {1.0f, 1.0f, 1.0f},
        {1.0f, 1.0f, 1.0f},
        {1.0f, 1.0f, 1.0f},
};

static TexCoordVector s_tube_tex_coords{
        {{0.00, 0.00}, {0.00, 0.00}, {0.00, 0.00}, {0.00, 0.00}},
        {{0.00, 0.00}, {0.00, 0.00}, {0.00, 0.00}, {0.00, 0.00}},
        {{0.00, 0.00}, {1.00, 0.00}, {1.00, 1.00}, {0.00, 1.00}},
        {{0.00, 0.00}, {1.00, 0.00}, {1.00, 1.00}, {0.00, 1.00}},
        {{0.00, 0.00}, {1.00, 0.00}, {1.00, 1.00}, {0.00, 1.00}},
        {{0.00, 0.00}, {1.00, 0.00}, {1.00, 1.00}, {0.00, 1.00}},
};


Model cube{s_cube_vertices, s_cube_faces, s_cube_normals, s_cube_colors, s_cube_tex_coords};
Model crisha{s_crisha_vertices, s_crisha_faces, s_crisha_normals, s_crisha_colors, s_crisha_tex_coords};
Model tube{s_tube_vertices, s_tube_faces, s_tube_normals, s_tube_colors, s_tube_tex_coords};

GLDemoWindow::GLDemoWindow(int width, int height) // @suppress("Class members should be properly initialized")
        : Window(width, height),
          _crate_texture("texture_home.png"), _crate_texture2("texture_roof.png"), _tube("tube.jpg"),
          _green("green.png"), _brown("brown.png"), _orange("orange.png") {
    SDL_GL_SetSwapInterval(1);

}

void GLDemoWindow::setup() {
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_TEXTURE);

    glClearColor(0.2f, 0.35f, 0.45f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    gluPerspective(45.0, double(width()) / double(height()), 0.1, 30.0);
    glMatrixMode(GL_MODELVIEW);
}

void GLDemoWindow::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    gluLookAt(10.0, 10.0, 8.0,
              0.0, 0.0, 0.0,
              0.0, 0.0, 1.0);


    glRotated(_angle, 0.0, 0.0, 1.0);

    glBegin(GL_QUADS);
    glColor3d(1.000, 1.000, 1.000);
    glNormal3d(0.0, 0.0, 1.0);
    glVertex3d(-9.0, -9.0, 0.0);
    glVertex3d(-9.0, 9.0, 0.0);
    glVertex3d(9.0, 9.0, 0.0);
    glVertex3d(9.0, -9.0, 0.0);
    glEnd();

    _crate_texture.bind();
    glEnable(GL_TEXTURE_2D);
    draw_model(cube);
    glDisable(GL_TEXTURE_2D);

    _crate_texture2.bind();
    glEnable(GL_TEXTURE_2D);
    draw_model(crisha);
    glDisable(GL_TEXTURE_2D);

    _brown.bind();
    glEnable(GL_TEXTURE_2D);
    make_cylinder_smooth(32, 0., 4.); //1
    make_cylinder_smooth(32, 3., 6.); //2
    make_cylinder_smooth(32, -5., 6.); //3
    make_cylinder_smooth(32, 5., 3.); //4
    make_cylinder_smooth(32, 0., -7.); //5
    make_cylinder_smooth(32, 4., -8.); //6
    make_cylinder_smooth(32, -4., -5.); //7
    make_cylinder_smooth(32, -5., 1.); //8
    make_cylinder_smooth(32, 5., -1.); //9
    make_cylinder_smooth(32, 8., -3.); //10
    make_cylinder_smooth(32, 6., -5.); //11
    glDisable(GL_TEXTURE_2D);


    _green.bind();
    glEnable(GL_TEXTURE_2D);
    make_cone_smooth(32, 0., 4., 2, 1, 1); //1
    make_cone_smooth(32, 0., 4., 2.5, 1.5, 0.9);
    make_cone_smooth(32, 0., 4., 3.0, 2.0, 0.8);
    make_cone_smooth(32, 0., 4., 3.5, 2.5, 0.7);
    make_cone_smooth(32, 0., 4., 4.0, 3.0, 0.6);
    make_cone_smooth(32, 0., 4., 4.2, 3.5, 0.4);

    make_cone_smooth(32, 3., 6., 2, 1, 0.9); //2
    make_cone_smooth(32, 3., 6., 2.8, 1.8, 0.75);
    make_cone_smooth(32, 3., 6., 3.6, 2.6, 0.6);

    make_cone_smooth(32, -5., 6., 4, 1, 0.7); //3

    make_cone_smooth(32, 5., 3., 3, 1, 0.5); //4
    make_cone_smooth(32, 5., 3., 3.5, 2, 0.4);
    make_cone_smooth(32, 5., 3., 4, 3, 0.3);

    make_cone_smooth(32, 0., -7., 2, 1, 0.9); //5
    make_cone_smooth(32, 0., -7., 2.8, 1.8, 0.75);
    make_cone_smooth(32, 0., -7., 3.6, 2.6, 0.6);

    make_cone_smooth(32, 4., -8., 4, 1, 0.7); //6

    make_cone_smooth(32, -4., -5., 3, 1, 0.5); //7
    make_cone_smooth(32, -4., -5., 3.5, 2, 0.4);
    make_cone_smooth(32, -4., -5., 4, 3, 0.3);

    make_cone_smooth(32, -5., 1., 2, 1, 0.9); //8
    make_cone_smooth(32, -5., 1., 2.8, 1.8, 0.75);
    make_cone_smooth(32, -5., 1., 3.6, 2.6, 0.6);

    make_cone_smooth(32, 5., -1., 2, 1, 0.9); //9
    make_cone_smooth(32, 5., -1., 2.8, 1.8, 0.75);
    make_cone_smooth(32, 5., -1., 3.6, 2.6, 0.6);

    make_cone_smooth(32, 8., -3., 5, 1, 0.9); //10

    make_cone_smooth(32, 6., -5., 3, 1, 0.5); //11
    make_cone_smooth(32, 6., -5., 3.5, 2, 0.4);
    make_cone_smooth(32, 6., -5., 4, 3, 0.3);

    glDisable(GL_TEXTURE_2D);

    make_sphere_smooth(64, 32, 2 + xx, 2 + yy, 0.5 + zz, 0.5);
    make_sphere_smooth(64, 32, 2 + xx, 2 + yy, 1.2 + zz, 0.35);
    make_sphere_smooth(64, 32, 2 + xx, 2 + yy, 1.7 + zz, 0.2);

    _orange.bind();
    glEnable(GL_TEXTURE_2D);
    if (k == 1)
        make_cone_flat(32, 2 + xx, 1.7 + zz, 1.5 + yy, 1.9 + yy, 0.03);
    if (k == 2)
        make_cone_carr(32, 1.7 + zz, 2 + yy, 1.5 + xx, 1.9 + xx, 0.03);
    if (k == 3)
        make_cone_flat(32, 2 + xx, 1.7 + zz, 2.5 + yy, 2.1 + yy, 0.03);
    if (k == 4)
        make_cone_carr(32, 1.7 + zz, 2 + yy, 2.5 + xx, 2.1 + xx, 0.03);
    glDisable(GL_TEXTURE_2D);

    _crate_texture.bind();
    glEnable(GL_TEXTURE_2D);
    draw_model(tube);
    glDisable(GL_TEXTURE_2D);
}

void GLDemoWindow::draw_model(Model &model) {
    for (unsigned i = 0; i < model.faces.size(); ++i) {
        int count = model.faces[i][0];
        if (count == 3)
            glBegin(GL_TRIANGLES);
        else if (count == 4)
            glBegin(GL_QUADS);
        else
            glBegin(GL_POLYGON);

        glNormal3dv(&model.normals[i][0]);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, &model.colors[i][0]);
        for (int j = 1; j <= count; ++j) {
            glTexCoord2dv(&model.tex_coords[i][j - 1][0]);
            glVertex3dv(&model.vertices[model.faces[i][j]][0]);
        }

        glEnd();
    }
}

void GLDemoWindow::do_logic() {
    _angle += 0.3;
    if (_angle >= 360.)
        _angle -= 360.;

    zz += 0.05 * i;
    if (zz >= 1) i = -1;
    else if (zz <= 0) i = 1;

    if (k == 1) {
        yy -= 0.05;
        if (yy <= -4) k = 2;
    } else if (k == 2) {
        xx -= 0.05;
        if (xx <= -4) k = 3;
    } else if (k == 3) {
        yy += 0.05;
        if (yy >= 0) k = 4;
    } else if (k == 4) {
        xx += 0.05;
        if (xx >= 0) k = 1;
    }
}



