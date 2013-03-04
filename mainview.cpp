#include "mainview.h"
#include "simplescene.h"

#include <iostream>
using std::cout;
using std::endl;

MainView::MainView(const QGLFormat & format, QWidget *parent) : QGLWidget(format, parent)
{
    // This tells the widget to accept keyboard focus when the widget is clicked.
    this->setFocusPolicy(Qt::ClickFocus);

    timer = new QTimer(this);
    connect( timer, SIGNAL(timeout()), this, SLOT(timerUpdate()) );

    this->setMinimumSize(800,800);
}

void MainView::initializeGL()
{
    scene = new SimpleScene();

    if (gl3wInit())
    {
        std::cerr << "Failed to initialize OpenGL.\n";
        return;
     }

     if (!gl3wIsSupported(4, 3))
     {
        std::cerr << "OpenGL 4.3 is not supported.\n";
        return;
     }
     std::cout << "\nOpenGL " << glGetString(GL_VERSION) << "\nGLSL " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;

    glClearColor(0.2f,0.2f,0.2f,1.0f);

    scene->initScene();
}

void MainView::paintGL()
{
    scene->render();
}

void MainView::resizeGL(int w, int h )
{
    scene->resize(w,h);
}

void MainView::takeScreenShot()
{
    QImage img = this->grabFrameBuffer(true);
    img.save("screen.png", "PNG");
}

void MainView::toggleAnimation()
{
    if( timer->isActive() )
        timer->stop();
    else
        timer->start(16);
}

void MainView::switchModel()
{
    static int activeBuffer = 1;
    activeBuffer = activeBuffer == 1 ? 2 : 1;
    scene->changeScene(activeBuffer);
    updateGL();
}

void MainView::timerUpdate()
{
    scene->update(0.2f);
    updateGL();
}

