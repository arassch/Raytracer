#ifndef __RENDERALG_H
#define __RENDERALG_H


#include "Definitions.h"
#include <QObject>
#include <QImage>

class Scene;

class RenderAlg : public QObject
{
    Q_OBJECT

protected:

	Scene* m_scene;

    bool m_drawNormals;
    bool m_drawAmbient;
    bool m_drawDiffuse;
    bool m_drawSpecular;
    bool m_drawIndirect;

    // Global illumination attributes
    int m_maxDepth;
    int m_numBounceDirections;

    // Anti-aliasing
    int m_subpixels;

    bool m_restart;

public:
    unsigned char *pixels;

	RenderAlg(Scene* scene);
	virtual ~RenderAlg();

    std::vector<Ray> raysFromCamera();

    void writeToFile(string filename);

    void setDrawNormals(bool drawNormals) { m_drawNormals = drawNormals;   }
    void setDrawAmbient(bool drawAmbient) { m_drawAmbient = drawAmbient;   }
    void setDrawDiffuse(bool drawDiffuse) { m_drawDiffuse = drawDiffuse;   }
    void setDrawSpecular(bool drawSpecular) { m_drawSpecular = drawSpecular;  }
    void setDrawIndirect(bool drawIndirect) { m_drawIndirect = drawIndirect;  }

    void setMaxDepth(int depth) { m_maxDepth = depth; }
    void setNumBounceDirections(int numDirections) { m_numBounceDirections = numDirections; }

    void setNumSubpixels(int num) { m_subpixels = num; }
    int getNumSubpixels() { return m_subpixels; }

public Q_SLOTS:
    virtual void process() = 0;
    void restart()
    {
        m_restart = true;
    }

signals:
    void finished();
};


#endif

