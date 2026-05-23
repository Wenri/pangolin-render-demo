#include <pangolin/pangolin.h>
#include <pangolin/gl/gldraw.h>
#include <pangolin/gl/gl.h>
#include <pangolin/display/display.h>
#include <pangolin/image/image_io.h>
#include <cstdio>
#include <cstdlib>
#include <string>

int main(int argc, char** argv) {
    const int W = 1024, H = 768;
    const std::string out = (argc > 1) ? argv[1] : "output.ppm";

    setenv("PANGOLIN_WINDOW_URI", "headless:", 1);

    pangolin::CreateWindowAndBind("offscreen", W, H);
    // HeadlessWindow never emits a resize event, so do it ourselves
    // (otherwise child View::v stays 0x0 and rendering / framebuffer reads are empty).
    pangolin::DisplayBase().Resize(pangolin::Viewport(0, 0, W, H));
    glEnable(GL_DEPTH_TEST);

    pangolin::OpenGlRenderState cam(
        pangolin::ProjectionMatrix(W, H, 500, 500, W / 2.0, H / 2.0, 0.1, 100),
        pangolin::ModelViewLookAt(2.5, 2.0, 3.0, 0, 0, 0, pangolin::AxisY));

    pangolin::View& view = pangolin::CreateDisplay()
        .SetBounds(0.0, 1.0, 0.0, 1.0, -double(W) / H);

    glClearColor(0.08f, 0.10f, 0.14f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    view.Activate(cam);
    pangolin::glDrawColouredCube();
    glFinish();

    // PPM is RGB (no alpha). top_line_first=false because glReadPixels
    // returns rows bottom-to-top.
    pangolin::TypedImage img = pangolin::ReadFramebuffer(view.v, "RGB24");
    pangolin::SaveImage(img, out, false);
    std::printf("wrote %s (%zux%zu)\n", out.c_str(), img.w, img.h);
    return 0;
}
