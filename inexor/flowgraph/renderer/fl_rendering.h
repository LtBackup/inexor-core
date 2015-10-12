/// @file fl_timer.h (flowgraph's timer implementation)
/// @author Johannes Schneider
/// @brief Timers will be called every [n] miliseconds

/// include guard
#ifndef INEXOR_VSCRIPT_RENDERING_HEADER
#define INEXOR_VSCRIPT_RENDERING_HEADER

//#include "inexor/flowgraph/debugger/fl_dbgrays.h"
#include "inexor/engine/engine.h"
#include <vector>

/// project's namespace protection
namespace inexor {
namespace vscript {


/// the size of the quads which will be rendered as box
/// around the target node's position
const float boxsize = 4.0f;

/// box side selection indices (defined by Cube engine)
enum VSCRIPT_ENTITY_BOX_ORIENTATION
{
    VSCRIPT_BOX_NO_INTERSECTION = -1,
    VSCRIPT_BOX_LEFT,
    VSCRIPT_BOX_RIGHT,
    VSCRIPT_BOX_FRONT,
    VSCRIPT_BOX_BACK,
    VSCRIPT_BOX_BOTTOM,
    VSCRIPT_BOX_TOP
};

/// Visual Scripting Renderer
class CVisualScriptRenderer
{
    public:

    /// constructor
    CVisualScriptRenderer::CVisualScriptRenderer()
    {
    }

    /// destuctor
    CVisualScriptRenderer::~CVisualScriptRenderer()
    {
    }

    /// buffer for debug rays
    //std::vector<debug_ray> rays;

    void CVisualScriptRenderer::adjust_selection_color(int orient, int index)
    {
        /// if this side of the box is selected, use a spicy orange color
        /// otherwise use a light blue color
        if(orient==index) 
        {
            glColor3f(1.0f, 89/255.0f, 0.0f);
            //if(selected) glColor3f(1.0f, 89/255.0f, 0.0f);
            //else glColor3f(1.0f, 182/255.0f, 0.0f);
        }
        else glColor3f(0, 148/255.0f, 1.0f);
    }


    void CVisualScriptRenderer::renderbox(vec p, int orient)
    {
        /// lets avoid macros here
        const float b = boxsize;

        glBegin(GL_QUADS);

        /// top
        adjust_selection_color(orient, VSCRIPT_BOX_TOP);
        glVertex3f(p.x,p.y,p.z+b);
        glVertex3f(p.x+b,p.y,p.z+b);
        glVertex3f(p.x+b,p.y+b,p.z+b);
        glVertex3f(p.x,p.y+b,p.z+b);

        /// bottom
        adjust_selection_color(orient, VSCRIPT_BOX_BOTTOM);
        glVertex3f(p.x,p.y+b,p.z);
        glVertex3f(p.x+b,p.y+b,p.z);
        glVertex3f(p.x+b,p.y,p.z);
        glVertex3f(p.x,p.y,p.z);

        /// front
        adjust_selection_color(orient, VSCRIPT_BOX_FRONT);
        glVertex3f(p.x,p.y,p.z);
        glVertex3f(p.x+b,p.y,p.z);
        glVertex3f(p.x+b,p.y,p.z+b);
        glVertex3f(p.x,p.y,p.z+b);

        /// back
        adjust_selection_color(orient, VSCRIPT_BOX_BACK);
        glVertex3f(p.x,p.y+b,p.z+b);
        glVertex3f(p.x+b,p.y+b,p.z+b);
        glVertex3f(p.x+b,p.y+b,p.z);
        glVertex3f(p.x,p.y+b,p.z);

        /// left
        adjust_selection_color(orient, VSCRIPT_BOX_LEFT);
        glVertex3f(p.x,p.y,p.z+b);
        glVertex3f(p.x,p.y+b,p.z+b);
        glVertex3f(p.x,p.y+b,p.z);
        glVertex3f(p.x,p.y,p.z);

        /// right
        adjust_selection_color(orient, VSCRIPT_BOX_RIGHT);
        glVertex3f(p.x+b,p.y,p.z);
        glVertex3f(p.x+b,p.y+b,p.z);
        glVertex3f(p.x+b,p.y+b,p.z+b);
        glVertex3f(p.x+b,p.y,p.z+b);
        glEnd();
    }

    void CVisualScriptRenderer::renderboxoutline(vec p)
    {
        const float b = boxsize;

        /// render gray outline (TOP)
        glBegin(GL_LINE_LOOP);
    
        /// TODO: does this work?
        glDepthFunc(GL_LEQUAL);

        glColor3f(0.0f,0.0f,0.0f);
        glVertex3f(p.x,p.y,p.z+b);
        glVertex3f(p.x+b,p.y,p.z+b);
        glVertex3f(p.x+b,p.y+b,p.z+b);
        glVertex3f(p.x,p.y+b,p.z+b);
        glEnd();

        /// render gray outline (BOTTOM)
        glBegin(GL_LINE_LOOP);
        glColor3f(0.0f,0.0f,0.0f);
        glVertex3f(p.x,p.y,p.z);
        glVertex3f(p.x+b,p.y,p.z);
        glVertex3f(p.x+b,p.y+b,p.z);
        glVertex3f(p.x,p.y+b,p.z);
        glEnd();

        /// render connection lines
        glBegin(GL_LINES);
        glVertex3f(p.x,p.y,p.z);
        glVertex3f(p.x,p.y,p.z+b);
        glVertex3f(p.x+b,p.y,p.z);
        glVertex3f(p.x+b,p.y,p.z+b);
        glVertex3f(p.x+b,p.y+b,p.z);
        glVertex3f(p.x+b,p.y+b,p.z+b);
        glVertex3f(p.x,p.y+b,p.z);
        glVertex3f(p.x,p.y+b,p.z+b);
        glEnd();
    }

    void CVisualScriptRenderer::renderboxhelplines(vec p)
    {
        glBegin(GL_LINES);

        /// we can't render to infinity, so lets just use a very big value
        const float helpline_distance = 1000.0f;
        const float b = boxsize;

        /// render help line for X AXIS
        glVertex3f(p.x-helpline_distance,p.y,p.z);
        glVertex3f(p.x+helpline_distance,p.y,p.z);
        glVertex3f(p.x-helpline_distance,p.y,p.z+b);
        glVertex3f(p.x+helpline_distance,p.y,p.z+b);
        glVertex3f(p.x-helpline_distance,p.y+b,p.z);
        glVertex3f(p.x+helpline_distance,p.y+b,p.z);
        glVertex3f(p.x-helpline_distance,p.y+b,p.z+b);
        glVertex3f(p.x+helpline_distance,p.y+b,p.z+b);

        /// render help line for Y AXIS
        glVertex3f(p.x,p.y-helpline_distance,p.z);
        glVertex3f(p.x,p.y+helpline_distance,p.z);
        glVertex3f(p.x+b,p.y-helpline_distance,p.z);
        glVertex3f(p.x+b,p.y+helpline_distance,p.z);
        glVertex3f(p.x,p.y-helpline_distance,p.z+b);
        glVertex3f(p.x,p.y+helpline_distance,p.z+b);
        glVertex3f(p.x+b,p.y-helpline_distance,p.z+b);
        glVertex3f(p.x+b,p.y+helpline_distance,p.z+b);

        /// render help line for Z AXIS
        glVertex3f(p.x,p.y,p.z-helpline_distance);
        glVertex3f(p.x,p.y,p.z+helpline_distance);
        glVertex3f(p.x+b,p.y,p.z-helpline_distance);
        glVertex3f(p.x+b,p.y,p.z+helpline_distance);
        glVertex3f(p.x,p.y+b,p.z-helpline_distance);
        glVertex3f(p.x,p.y+b,p.z+helpline_distance);
        glVertex3f(p.x+b,p.y+b,p.z-helpline_distance);
        glVertex3f(p.x+b,p.y+b,p.z+helpline_distance);    
        glEnd();
    }


};


};
};

#endif